#include "pch.h"
#include "AccountSession.hpp"
#include "generated/account/ServerPacketHandler.gen.hpp"

void AccountSession::OnConnected(net::Endpoint endpoint)
{
	m_endpoint = endpoint;
	Console::Log(Category::AccountServer, Info, TEXT("Connected " + action::ToUnicodeString(endpoint.toString())));
}

void AccountSession::OnDisconnected(net::Endpoint endpoint)
{
	Console::Log(Category::AccountServer, Info, TEXT("Disconnected " + action::ToUnicodeString(endpoint.toString())));
}

void AccountSession::OnReceive(std::span<char> buffer, int)
{
	gen::account::PacketHandler::handlePacket(shared_from_this(), buffer);
}

void AccountSession::OnFail(Failure)
{
}

net::Endpoint AccountSession::GetEndpoint() const
{
	return m_endpoint;
}
