#pragma once

#include "Network/Session.hpp"

class AccountSession : public Session
{
public:
    AccountSession();
    ~AccountSession();
public:
    virtual void OnConnected(net::Endpoint);
    virtual void OnDisconnected(net::Endpoint);
    virtual void OnReceive(std::span<char>, int);
    virtual void OnFail(Failure);
public:
    net::Endpoint GetEndpoint() const;
public:
    std::optional<String> uuid;
private:
    net::Endpoint m_endpoint;
};

