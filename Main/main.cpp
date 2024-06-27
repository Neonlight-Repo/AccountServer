#include "pch.h"
#include "AccountServer.hpp"

int main()
{
	AccountServerInstance = new AccountServer;
	AccountServerInstance->Run();

	delete AccountServerInstance;
}