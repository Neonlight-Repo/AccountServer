#include "pch.h"
#include "AccountSession.hpp"
#include "generated/account/ServerPacketHandler.gen.hpp"

void AccountSession::onConnected()
{
}

void AccountSession::onDisconnected()
{
}

void AccountSession::onReceive(std::span<char> buffer, int len)
{
	gen::account::PacketHandler::handlePacket(shared_from_this(), buffer);
}

void AccountSession::onFail(Failure cause)
{
}
