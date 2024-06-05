#include "pch.h"
#include "AccountSession.hpp"
#include "generated/account/ServerPacketHandler.gen.hpp"
#include "Database/Procedure.hpp"
#include "LogSession.hpp"


AccountSession::AccountSession() : uuid(std::nullopt)
{

}

AccountSession::~AccountSession()
{
}

void AccountSession::OnConnected(net::Endpoint endpoint)
{
	m_sock;
}

void AccountSession::OnDisconnected(net::Endpoint endpoint)
{
	auto uid = uuid;
	auto sharedThis = shared_from_this();
	Procedure::Get()->Launch([uid, sharedThis, endpoint] {
		Console::Log(Category::AccountServer, Info, TEXT("Disconnected " + action::ToUnicodeString(endpoint.toString())));
		if (uid.has_value())
			Procedure::Get()->Logout(sharedThis, uid.value());
	});
}

void AccountSession::OnReceive(std::span<char> buffer, int)
{
	uint16 id = *reinterpret_cast<uint16*>(buffer.data());
	gen::account::PacketHandler::HandlePacket(shared_from_this(), id, buffer);
}

void AccountSession::OnFail(Failure)
{
}

net::Endpoint AccountSession::GetEndpoint() const
{
	return m_endpoint;
}
