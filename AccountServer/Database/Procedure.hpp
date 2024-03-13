#pragma once

#include <Thread/JobSerializer.hpp>
#include <generated/account/Protocol.gen.hpp>

class Procedure : public JobSerializer
{
public:
	static std::shared_ptr<Procedure> Get()
	{
		static auto instance = std::make_shared<Procedure>();
		return instance;
	}
public:	
	void HandleLogin(std::shared_ptr<Session> session, gen::account::LoginReq request);
	void HandleRegister(std::shared_ptr<Session> session, gen::account::RegisterReq request);
private:
	bool CheckUser(String nickname);
	std::optional<String> Login(String nickname, String pwdhash);
	bool Register(String nickname, String pwdhash);
};
