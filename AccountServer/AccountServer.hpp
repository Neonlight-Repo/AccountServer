#pragma once

MAKE_LOG_CATEGORY(AccountServer);
struct AccountServer final
{
	AccountServer();
	~AccountServer();

	void Run();
};

static AccountServer* AccountServerInstance;