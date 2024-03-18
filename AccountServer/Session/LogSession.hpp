#pragma once

#include <Network/Session.hpp>

class LogSession : public Session
{
public:
    static std::shared_ptr<LogSession> Get();
public:
    virtual void OnConnected(net::Endpoint);
    virtual void OnDisconnected(net::Endpoint);
    virtual void OnReceive(std::span<char>, int);
    virtual void OnFail(Failure);
private:
    static std::shared_ptr<LogSession> s_instance;
};
