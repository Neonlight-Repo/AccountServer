#include "pch.h"
#include "LoginProc.hpp"

#include "Session/AccountSession.hpp"
#include "Session/LogSession.hpp"

#include "generated/logs/Enum.gen.hpp"

void LoginProc::HandleLogin(Session* session, std::shared_ptr<gen::account::LoginReq> request)
{
	auto accountSession = static_cast<AccountSession*>(session);
	gen::account::LoginRes res;
	res.success = false;
	res.uuid = TEXT("");
	res.cause = gen::account::ELoginFail::INVALID;
	if (CheckUser(request->nickname) && !m_loginUserCheck[request->nickname])
	{
		auto uuid = Login(request->nickname, request->password);
		accountSession->uuid = uuid;
		if (uuid.has_value())
		{
			if (!m_loginUserCheck[uuid.value()])
			{
				res.uuid = uuid.value();
				res.success = true;
				res.cause = gen::account::ELoginFail::SUCCESS;

				Console::Log(Category::AccountServer, TEXT("User logined."));

				m_loginUserCheck[uuid.value()] = true;
				SendLog(uuid.value(), accountSession, gen::logs::LOGIN);
			}
			else
			{
				res.cause = gen::account::ELoginFail::EXIST;
			}
		}
	}
	session->Send(&res, true);
}

void LoginProc::HandleLogout(Session* session, std::shared_ptr<gen::account::LogoutReq> request)
{
	auto accountSession = static_cast<AccountSession*>(session);
	Logout(session, request->uuid);
}

void LoginProc::HandleRegister(Session* session, std::shared_ptr<gen::account::RegisterReq> request)
{
	gen::account::RegisterRes res;
	res.success = false;
	if (!CheckUser(request->nickname))
	{
		String uuid;
		res.success = Register(request->nickname, request->password, uuid);
		if (res.success)
			SendLog(uuid, session, gen::logs::REGISTER);
	}
	session->Send(&res, true);
}

void LoginProc::HandleCheck(Session* session, std::shared_ptr<gen::account::CheckNicknameReq> request)
{
	gen::account::CheckNicknameRes res;
	res.exists = CheckUser(request->nickname);
	session->Send(&res, true);
}

bool LoginProc::CheckUser(String nickname)
{
	auto pstmt = GDatabase->CallProcedure("SP_CheckUser", ToAnsiString(nickname));
	auto res = std::unique_ptr<sql::ResultSet>(pstmt->executeQuery());
	if (res && res->next())
		return res->getUInt(0);
	else
		return false;
}

std::optional<String> LoginProc::Login(String nickname, String pwdhash)
{
	auto pstmt = GDatabase->CallProcedure("SP_Login", ToAnsiString(nickname), ToAnsiString(pwdhash));
	auto res = std::unique_ptr<sql::ResultSet>(pstmt->executeQuery());
	if (res && res->next()) {
		return ToUnicodeString(res->getString(0).c_str());
	}
	else
		return std::nullopt;
}

bool LoginProc::Register(String nickname, String pwdhash, String& uuid)
{
	uuid = UUIDv4();
	auto pstmt = GDatabase->CallProcedure("SP_Register", ToAnsiString(uuid), ToAnsiString(nickname), ToAnsiString(pwdhash));
	return pstmt->execute();
}

bool LoginProc::Logout(Session* session, String uuid)
{
	auto accountSession = static_cast<AccountSession*>(session);
	if (m_loginUserCheck[uuid]) {
		Console::Log(Category::AccountServer, TEXT("user logout"));

		m_loginUserCheck[uuid] = false;

		SendLog(uuid, accountSession, gen::logs::LOGOUT);
		return true;
	}
	return false;
}

void LoginProc::SendLog(String uid, Session* session, gen::logs::ELoginType type)
{
	gen::logs::SecurityLog secuLog;
	secuLog.uid = uid;
	secuLog.ipAddress = ToUnicodeString(session->GetSocket()->getRemoteEndpoint()->toString());
	secuLog.loginType = type;
	LogSession::Get()->Send(&secuLog, true);
}