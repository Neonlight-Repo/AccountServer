#include "pch.h"
#include "AccountSession.hpp"
#include "generated/account/ServerPacketHandler.gen.hpp"

void AccountSession::OnConnected(net::Endpoint)
{
}

void AccountSession::OnDisconnected(net::Endpoint)
{
}

void AccountSession::OnReceive(std::span<char> buffer, int len)
{
	gen::account::PacketHandler::handlePacket(shared_from_this(), buffer);
}

void AccountSession::OnFail(Failure cause)
{
}
