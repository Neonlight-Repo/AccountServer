#include "pch.h"
#include "AccountServer.hpp"
#include "Database/DBConnectionPool.hpp"
#include "Session/AccountSession.hpp"
#include "Session/LogSession.hpp"

#include "Network/Server.hpp"
#include "Network/Client.hpp"

Engine* GEngine;

AccountServer::AccountServer()
{
	GEngine = new Engine;
}


AccountServer::~AccountServer()
{
	delete GEngine;
}

void AccountServer::Run()
{
	GEngine->Initialize();

	GEngine->GetDBConnectionPool()->Connect(10, TEXT(
		"DRIVER={MySQL ODBC 8.3 Unicode Driver};"
		"SERVER=localhost;"
		"PORT=3306;"
		"DATABASE=AccountDB;"
		"USER=AccountAdmin;"
		"PASSWORD=qwE!r6800@;"
		"OPTION=3;"
	));

	auto logEndpoint = Endpoint(IpAddress::Loopback, 1225);
	auto endpoint = Endpoint(net::IpAddress::Loopback, 1207);
	try {
		auto client = Client::Open<LogSession>();
		auto server = Server::Open<AccountSession>();
		client->Run(logEndpoint);
		server->Run(endpoint);

		Console::Log(Category::AccountServer, TEXT("Account Server is running on ") + ToUnicodeString(endpoint.toString()));

		GEngine->ExecuteThread(2, 2);
	}
	catch (std::exception& e) {
		Console::Error(Category::AccountServer, ToUnicodeString(e.what()));
	}
}
