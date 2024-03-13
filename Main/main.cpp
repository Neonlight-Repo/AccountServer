#include "pch.h"
#include "AccountSession.hpp"
#include "Network/Server.hpp"
#include "AccountServer.hpp"

using namespace std;

int main()
{
	auto ep = Endpoint(net::IpAddress::Loopback, 1207);
	try {
		auto server = Server::Open<AccountSession>();
		server->Run(ep);

		Console::Log(LogAccountServer, Log, L"Account server is running on " + action::ToUnicodeString(ep.toString()));

		GEngine->ExecuteIocpLogic(std::thread::hardware_concurrency(), true);
	}
	catch (exception& e) {
	}
}