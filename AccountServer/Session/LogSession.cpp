#include "pch.h"
#include "LogSession.hpp"
#include "generated/logs/Protocol.gen.hpp"

std::shared_ptr<LogSession> LogSession::s_instance = nullptr;

std::shared_ptr<LogSession> LogSession::Get()
{
	return s_instance;
}

void LogSession::OnConnected(net::Endpoint endpoint)
{
	m_endpoint = endpoint;
	s_instance = std::static_pointer_cast<LogSession>(shared_from_this());

	gen::logs::SystemLog sysLog;
	sysLog.category = gen::logs::START;
	sysLog.serverName = TEXT("Account Server");
	Send(&sysLog);
}

void LogSession::OnDisconnected(net::Endpoint)
{
}

void LogSession::OnReceive(std::span<char>, int)
{
}

void LogSession::OnFail(Failure)
{
}

net::Endpoint LogSession::GetEndpoint() const
{
	return m_endpoint;
}
