#include "pch.h"
#include "Network/Server.hpp"
#include "Session/AccountSession.hpp"
#include "Session/LogSession.hpp"

#include "generated/logs/Protocol.gen.hpp"

LogSession* LogSession::s_instance = nullptr;

LogSession* LogSession::Get()
{
	return s_instance;
}

void LogSession::OnConnected(net::Endpoint endpoint)
{
	s_instance = this;
	gen::logs::SystemLog sysLog;
	sysLog.severity = gen::logs::ESeverity::INFO;
	sysLog.serverName = TEXT("Account Server");
	sysLog.message = TEXT("Server started");
	Send(&sysLog);
}

void LogSession::OnDisconnected(net::Endpoint)
{
	s_instance = nullptr;
}

void LogSession::OnReceive(std::span<char>, int)
{
}

void LogSession::OnFail(Failure fail)
{

}

net::Endpoint LogSession::GetEndpoint() const
{
	return m_endpoint;
}
