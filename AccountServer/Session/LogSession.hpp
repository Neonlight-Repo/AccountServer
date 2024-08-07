#pragma once

#include <Network/Session.hpp>

class LogSession : public Session
{
public:
    static LogSession* Get();
public:
    virtual void OnConnected(net::Endpoint);
    virtual void OnDisconnected(net::Endpoint);
    virtual void OnReceive(std::span<char>, int);
    virtual void OnFail(Failure);
public:
    net::Endpoint GetEndpoint() const;
private:
    static LogSession* s_instance;
    net::Endpoint m_endpoint;
};
