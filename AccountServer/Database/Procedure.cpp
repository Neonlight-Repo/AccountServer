#include "pch.h"
#include "Procedure.hpp"

#include "Database/DBConnectionPool.hpp"
#include "Database/Statement.hpp"

#include "Session/AccountSession.hpp"
#include "Session/LogSession.hpp"

#include "generated/logs/Enum.gen.hpp"

//std::shared_ptr<Procedure> GProcedure = std::make_shared<Procedure>();

void Procedure::HandleLogin(std::shared_ptr<Session> session, std::shared_ptr<gen::account::LoginReq> request)
{
	auto accountSession = std::static_pointer_cast<AccountSession>(session);
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

				Console::Debug(Category::AccountServer, TEXT("User logined."));

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

void Procedure::HandleLogout(std::shared_ptr<Session> session, std::shared_ptr<gen::account::LogoutReq> request)
{
	auto accountSession = std::static_pointer_cast<AccountSession>(session);
	Logout(session, request->uuid);
}

void Procedure::HandleRegister(std::shared_ptr<Session> session, std::shared_ptr<gen::account::RegisterReq> request)
{
	gen::account::RegisterRes res;
	res.success = false;
	if (!CheckUser(request->nickname))
	{
		String uuid;
		res.success = Register(request->nickname, request->password, uuid);
		if (res.success)
			SendLog(uuid, std::static_pointer_cast<AccountSession>(session), gen::logs::REGISTER);
	}
	session->Send(&res, true);
}

void Procedure::HandleCheck(std::shared_ptr<Session> session, std::shared_ptr<gen::account::CheckNicknameReq> request)
{
	gen::account::CheckNicknameRes res;
	res.exists = CheckUser(request->nickname);
	session->Send(&res, true);
}

bool Procedure::CheckUser(String nickname)
{
	auto conn = GEngine->GetDBConnectionPool()->Pop();
	if (conn)
	{
		bool num = false;
		auto stmt = conn->CreateStatement<1, 1>(TEXT("CALL SP_CheckUser(?)"));
		stmt.SetParameter(0, nickname.c_str());
		stmt.Bind(0, num);

		bool res = stmt.ExecuteQuery();
		res &= stmt.Next();

		GEngine->GetDBConnectionPool()->Push(conn);

		if (res) return num;
		else return false;
	}
	return false;
}

std::optional<String> Procedure::Login(String nickname, String pwdhash)
{
	auto conn = GEngine->GetDBConnectionPool()->Pop();
	if (conn)
	{
		WCHAR uuid[37] = L"";
		auto stmt = conn->CreateStatement<2, 1>(TEXT("CALL SP_Login(?, ?)"));
		stmt.SetParameter(0, nickname.c_str());
		stmt.SetParameter(1, pwdhash.c_str());
		stmt.Bind(0, uuid);

		bool res = stmt.ExecuteQuery();
		res &= stmt.Next();

		GEngine->GetDBConnectionPool()->Push(conn);	

		if (res) return uuid;
		else return std::nullopt;
	}
	return std::nullopt;
}

bool Procedure::Register(String nickname, String pwdhash, String& uuid)
{
	auto conn = GEngine->GetDBConnectionPool()->Pop();
	if (conn)
	{
		uuid = UUIDv4();
		auto stmt = conn->CreateStatement<2, 0>(std::format(TEXT("CALL SP_Register('{}', ?, ?)"), uuid));
		stmt.SetParameter(0, nickname.c_str());
		stmt.SetParameter(1, pwdhash.c_str());

		bool res = stmt.ExecuteQuery();

		GEngine->GetDBConnectionPool()->Push(conn);

		return res;
	}
	return false;
}

bool Procedure::Logout(std::shared_ptr<Session> session, String uuid)
{
	auto accountSession = std::static_pointer_cast<AccountSession>(session);
	if (m_loginUserCheck[uuid]) {
		Console::Debug(Category::AccountServer, TEXT("user logout"));

		m_loginUserCheck[uuid] = false;

		SendLog(uuid, accountSession, gen::logs::LOGOUT);
		return true;
	}
	return false;
}

void Procedure::SendLog(String uid, std::shared_ptr<AccountSession> session, gen::logs::ELoginType type)
{
	auto accountSession = std::static_pointer_cast<AccountSession>(session);
	auto logSession = LogSession::Get();

	gen::logs::SecurityLog secuLog;
	secuLog.uid = uid;
	secuLog.ipAddress = ToUnicodeString(accountSession->GetEndpoint().getAddress().toString());
	secuLog.loginType = type;
	logSession->Send(&secuLog, true);
}