#include "pch.h"
#include "LogSession.hpp"

std::shared_ptr<LogSession> LogSession::s_instance = nullptr;

std::shared_ptr<LogSession> LogSession::Get()
{
	return s_instance;
}

void LogSession::onConnected()
{
	s_instance = std::static_pointer_cast<LogSession>(shared_from_this());
}

void LogSession::onDisconnected()
{
}

void LogSession::onReceive(std::span<char>, int)
{
}

void LogSession::onFail(Failure)
{
}
