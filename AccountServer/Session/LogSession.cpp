#include "pch.h"
#include "Network/Server.hpp"
#include "Session/AccountSession.hpp"
#include "Session/LogSession.hpp"
#include "Thread/ThreadManager.hpp"

#include "generated/logs/Protocol.gen.hpp"

std::shared_ptr<LogSession> LogSession::s_instance = nullptr;

std::shared_ptr<LogSession> LogSession::Get()
{
	return s_instance;
}

void LogSession::OnConnected(net::Endpoint endpoint)
{
	s_instance = std::static_pointer_cast<LogSession>(shared_from_this());
	gen::logs::SystemLog sysLog;
	sysLog.severity = gen::logs::ESeverity::INFO;
	sysLog.serverName = TEXT("Account Server");
	sysLog.message = TEXT("Server started");
	Send(&sysLog);
}

void LogSession::OnDisconnected(net::Endpoint)
{
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
