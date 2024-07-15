#include "pch.h"
#include "AccountServer.hpp"

int main()
{
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(500ms); // Wait for LogServer

	AccountServerInstance = new AccountServer;
	AccountServerInstance->Run();

	delete AccountServerInstance;
}