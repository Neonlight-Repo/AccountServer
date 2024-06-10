#include "pch.h"

#include "Session/AccountSession.hpp"
#include "Session/LogSession.hpp"

#include "Network/Server.hpp"
#include "Network/Client.hpp"

using namespace std;

int main()
{
	auto logEndpoint = Endpoint(IpAddress::Loopback, 1225);
	auto endpoint = Endpoint(net::IpAddress::Loopback, 1207);
	try {
		auto client = Client::Open<LogSession>();
		auto server = Server::Open<AccountSession>();
		client->Run(logEndpoint);
		server->Run(endpoint);

		GEngine->ExecuteThread(2, 2);

		getchar();
	}
	catch (exception& e) {
		Console::Log(Category::AccountServer, Error, ToUnicodeString(e.what()));
	}
}