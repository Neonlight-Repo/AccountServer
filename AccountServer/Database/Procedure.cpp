#include "pch.h"
#include "Procedure.hpp"
#include "Database/DBConnectionPool.hpp"
#include "Database/Statement.hpp"
#include "Network/Session.hpp"
#include "Session/LogSession.hpp"

#include "generated/logs/Protocol.gen.hpp"

std::shared_ptr<Procedure> GProcedure = std::make_shared<Procedure>();

void Procedure::HandleLogin(std::shared_ptr<Session> session, gen::account::LoginReq request)
{
	gen::account::LoginRes res;
	res.success = false;
	res.uuid = TEXT("");
	if (CheckUser(request.nickname))
	{
		auto uuid = Login(request.nickname, request.password);
		if (uuid.has_value())
		{
			res.uuid = uuid.value();
			res.success = true;

			gen::logs::SystemLog log;
			log.serverName = TEXT("AccountServer");

			auto logSession = LogSession::Get();
			//log.category = gen::logs::ESystemLog::;
			logSession->Send(&log);
		}
	}
	session->Send(&res);
}

void Procedure::HandleRegister(std::shared_ptr<Session> session, gen::account::RegisterReq request)
{
	gen::account::RegisterRes res;
	res.success = false;
	if (!CheckUser(request.nickname))
	{
		res.success = Register(request.nickname, request.password);
	}
	session->Send(&res);
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
		WCHAR uuid[36] = L"";
		auto stmt = conn->CreateStatement<2, 1>(TEXT("CALL SP_Login(?, ?)"));
		stmt.SetParameter(0, nickname.c_str());
		stmt.SetParameter(1, pwdhash.c_str());
		//stmt.SetParameter(2, action::ToUnicodeString(LogSession::Get()->GetEndpoint().getAddress().toString()).c_str());
		stmt.Bind(0, uuid);

		bool res = stmt.ExecuteQuery();
		res &= stmt.Next();

		GEngine->GetDBConnectionPool()->Push(conn);	

		Console::Log(LogAccountServer, Debug, TEXT("User logined."));

		if (res) return uuid;
		else return std::nullopt;
	}
	return std::nullopt;
}

bool Procedure::Register(String nickname, String pwdhash)
{
	auto conn = GEngine->GetDBConnectionPool()->Pop();
	if (conn)
	{
		auto stmt = conn->CreateStatement<2, 0>(std::format(TEXT("CALL SP_Register('{}', ?, ?)"), action::UUIDv4()));
		stmt.SetParameter(0, nickname.c_str());
		stmt.SetParameter(1, pwdhash.c_str());
		//stmt.SetParameter(3, action::ToUnicodeString(LogSession::Get()->GetEndpoint().getAddress().toString()).c_str());

		bool res = stmt.ExecuteQuery();

		GEngine->GetDBConnectionPool()->Push(conn);

		return res;
	}
	return false;
}
