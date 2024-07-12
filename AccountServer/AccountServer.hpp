#pragma once

#include "Subsystem/GameInstance.hpp"

MAKE_LOG_CATEGORY(AccountServer);
struct AccountServer final : GameInstance
{
	AccountServer();
	~AccountServer();

	void Run() override;
};

static AccountServer* AccountServerInstance;