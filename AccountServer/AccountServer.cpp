#include "pch.h"
#include "AccountServer.hpp"
#include "Session/AccountSession.hpp"
#include "Session/LogSession.hpp"

#include "Network/Server.hpp"
#include "Network/Client.hpp"

Engine* GEngine;
Database* GDatabase;

AccountServer::AccountServer()
{
	GEngine = new Engine;
	GDatabase = new Database;
}


AccountServer::~AccountServer()
{
	delete GEngine;
	delete GDatabase;
}

void AccountServer::Run()
{
	GEngine->Initialize();
	GDatabase->Initialize();

	GDatabase->SetDatabaseProfile(TEXT("AccountAdmin"), TEXT("qwE!r6800@"), TEXT("AccountDB"));
	GDatabase->CreateConnection();

	auto logEndpoint = Endpoint(IpAddress::Loopback, 1225);
	auto endpoint = Endpoint(net::IpAddress::Loopback, 1207);
	try {
		auto client = Client::Open<LogSession>();
		auto server = Server::Open<AccountSession>();
		client->Run(logEndpoint);
		server->Run(endpoint);

		Console::Log(Category::AccountServer, TEXT("Account Server is running on ") + ToUnicodeString(endpoint.toString()));

		GEngine->Run(1);
	}
	catch (std::exception& e) {
		Console::Error(Category::AccountServer, ToUnicodeString(e.what()));
	}
}
