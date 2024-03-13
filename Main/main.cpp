#include "pch.h"

#include "Session/AccountSession.hpp"
#include "Session/LogSession.hpp"

#include "Network/Server.hpp"
#include "Network/Client.hpp"

using namespace std;

int main()
{
	auto serverEndpoint = Endpoint(net::IpAddress::Loopback, 1207);
	auto logServerEndpoint = Endpoint(net::IpAddress::Loopback, 1225);
	try {
		auto server = Server::Open<AccountSession>();
		auto client = Client::Open<LogSession>();
		server->Run(serverEndpoint);
		client->Run(logServerEndpoint);

		Console::Log(LogAccountServer, Log, L"Account Server is running on " + action::ToUnicodeString(serverEndpoint.toString()));

		GEngine->ExecuteIocpLogic(thread::hardware_concurrency(), true);
	}
	catch (exception& e) {
		Console::Log(LogAccountServer, Error, action::ToUnicodeString(e.what()));
	}
}