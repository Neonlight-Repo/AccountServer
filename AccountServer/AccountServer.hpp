#pragma once

MAKE_LOG_CATEGORY(AccountServer);
class AccountServer
{
public:
	AccountServer();
	~AccountServer();
};

static AccountServer AccountServerInstance;