#include "pch.h"
#include "generated/account/ServerPacketHandler.gen.hpp"
#include "LoginProc.hpp"

using namespace gen;

bool account::PacketHandler::LoginReqPacketHandler(Session* session, TSharedPtr<LoginReq> packet)
{
	LoginProc::Get()->Run(&LoginProc::HandleLogin, session, packet);
	return false;
}

bool account::PacketHandler::LogoutReqPacketHandler(Session* session, TSharedPtr<LogoutReq> packet)
{
	LoginProc::Get()->Run(&LoginProc::HandleLogout, session, packet);
	return false;
}

bool account::PacketHandler::RegisterReqPacketHandler(Session* session, TSharedPtr<RegisterReq> packet)
{
	LoginProc::Get()->Run(&LoginProc::HandleRegister, session, packet);
	return false;
}

bool account::PacketHandler::CheckNicknameReqPacketHandler(Session* session, TSharedPtr<CheckNicknameReq> packet)
{
	LoginProc::Get()->Run(&LoginProc::HandleCheck, session, packet);
	return false;
}

