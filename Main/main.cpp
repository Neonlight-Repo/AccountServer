#include "pch.h"

#include "Session/AccountSession.hpp"
#include "Session/LogSession.hpp"

#include "Network/Server.hpp"
#include "Network/Client.hpp"

using namespace std;

int main()
{
	auto logServerEndpoint = Endpoint(net::IpAddress::Loopback, 1225);
	try {
		auto client = Client::Open<LogSession>();
		client->Run(logServerEndpoint);

		GEngine->ExecuteThread(2, 2);
	}
	catch (exception& e) {
		Console::Log(Category::AccountServer, Error, action::ToUnicodeString(e.what()));
	}
}