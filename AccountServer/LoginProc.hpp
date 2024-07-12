#pragma once

#include <Functor.hpp>
#include <generated/account/Protocol.gen.hpp>
#include <generated/logs/Protocol.gen.hpp>

class LoginProc : public Runnable<LoginProc>
{
public:
	static std::shared_ptr<LoginProc> Get()
	{
		static auto instance = std::make_shared<LoginProc>();
		return instance;
	}
public:	
	void HandleLogin(Session* session, std::shared_ptr<gen::account::LoginReq> request);
	void HandleLogout(Session* session, std::shared_ptr<gen::account::LogoutReq> request);
	void HandleRegister(Session* session, std::shared_ptr<gen::account::RegisterReq> request);
	void HandleCheck(Session* session, std::shared_ptr<gen::account::CheckNicknameReq> request);
public:
	bool CheckUser(String nickname);
	std::optional<String> Login(String nickname, String pwdhash);
	bool Register(String nickname, String pwdhash, String& uuid);
	bool Logout(Session* session, String uuid);
	void SendLog(String uid, Session* session, gen::logs::ELoginType type);
	HashMap<String, bool> m_loginUserCheck;
};
