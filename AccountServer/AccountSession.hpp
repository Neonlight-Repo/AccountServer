#pragma once

#include "Network/Session.hpp"

class AccountSession : public Session
{
public:
    virtual void onConnected();
    virtual void onDisconnected();
    virtual void onReceive(std::span<char>, int);
    virtual void onFail(Failure);
};

