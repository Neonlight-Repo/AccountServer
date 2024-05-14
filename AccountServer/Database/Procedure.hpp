#pragma once

#include <Thread/JobSerializer.hpp>
#include <generated/account/Protocol.gen.hpp>
#include <generated/logs/Protocol.gen.hpp>

class Procedure : public JobSerializer
{
public:
	static std::shared_ptr<Procedure> Get()
	{
		static auto instance = std::make_shared<Procedure>();
		return instance;
	}
public:	
	void HandleLogin(std::shared_ptr<Session> session, std::shared_ptr<gen::account::LoginReq> request);
	void HandleLogout(std::shared_ptr<Session> session, std::shared_ptr<gen::account::LogoutReq> request);
	void HandleRegister(std::shared_ptr<Session> session, std::shared_ptr<gen::account::RegisterReq> request);
	void HandleCheck(std::shared_ptr<Session> session, std::shared_ptr<gen::account::CheckNicknameReq> request);
public:
	bool CheckUser(String nickname);
	std::optional<String> Login(String nickname, String pwdhash);
	bool Register(String nickname, String pwdhash, String& uuid);
	bool Logout(std::shared_ptr<Session> session, String uuid);
	void SendLog(String uid, std::shared_ptr<class AccountSession> session, gen::logs::ELoginType type);
	HashMap<String, bool> m_loginUserCheck;
};
