#pragma once

#include <Network/Session.hpp>

class LogSession : public Session
{
public:
    static std::shared_ptr<LogSession> Get();
public:
    virtual void onConnected();
    virtual void onDisconnected();
    virtual void onReceive(std::span<char>, int);
    virtual void onFail(Failure);
private:
    static std::shared_ptr<LogSession> s_instance;
};
