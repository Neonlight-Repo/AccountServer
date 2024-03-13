#include "pch.h"
#include "AccountServer.hpp"
#include "Database/DBConnectionPool.hpp"

Engine* GEngine;

AccountServer::AccountServer()
{
	GEngine = new Engine;
	GEngine->GetDBConnectionPool()->Connect(10, TEXT(
		"DRIVER={MySQL ODBC 8.3 Unicode Driver};"
		"SERVER=localhost;"
		"PORT=3307;"
		"DATABASE=HazardDB;"
		"USER=root;"
		"PASSWORD=1234;"
		"OPTION=3;"
	));
}


AccountServer::~AccountServer()
{
	delete GEngine;
}
