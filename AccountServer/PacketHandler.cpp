#include "pch.h"
#include "generated/account/ServerPacketHandler.gen.hpp"
#include "Database/Procedure.hpp"

using namespace gen;

bool account::PacketHandler::LoginReqPacketHandler(std::shared_ptr<Session> session, TSharedPtr<LoginReq> packet)
{
	Procedure::Get()->Launch(&Procedure::HandleLogin, session, *packet);
	return false;
}

bool account::PacketHandler::RegisterReqPacketHandler(TSharedPtr<Session> session, TSharedPtr<RegisterReq> packet)
{
	Procedure::Get()->Launch(&Procedure::HandleRegister, session, *packet);
	return false;
}
