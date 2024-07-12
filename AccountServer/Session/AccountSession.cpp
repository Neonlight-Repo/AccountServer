#include "pch.h"
#include "AccountSession.hpp"
#include "generated/account/ServerPacketHandler.gen.hpp"
#include "LoginProc.hpp"
#include "LogSession.hpp"


AccountSession::AccountSession() : uuid(std::nullopt)
{

}

AccountSession::~AccountSession()
{
}

void AccountSession::OnConnected(net::Endpoint endpoint)
{
	Console::Log(Category::AccountServer, TEXT("Connected " + ToUnicodeString(endpoint.toString())));
}

void AccountSession::OnDisconnected(net::Endpoint endpoint)
{
	Console::Log(Category::AccountServer, TEXT("Disconnected " + ToUnicodeString(endpoint.toString())));
	if (uuid.has_value())
		LoginProc::Get()->Logout(this, uuid.value());
}

void AccountSession::OnReceive(std::span<char> buffer, int)
{
	gen::account::PacketHandler::HandlePacket(this, buffer);
}

void AccountSession::OnFail(Failure)
{
}

net::Endpoint AccountSession::GetEndpoint() const
{
	return m_endpoint;
}
