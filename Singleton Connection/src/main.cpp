#include <iostream>

#include "sqlite3.h"
#include "db.h"

#pragma comment(lib, "./lib/sqlite3.lib")


int main()
{
	auto& conn = connection::connect("data.dblite");
	query(conn, "SELECT * FROM workers WHERE worker_id = 1");
}