#include "pch.h"
#include "AccountServer.hpp"
#include "Database/DBConnectionPool.hpp"

Engine* GEngine;

AccountServer::AccountServer()
{
	GEngine = new Engine;
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
}


AccountServer::~AccountServer()
{
	delete GEngine;
}
