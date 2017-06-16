#include <iostream>

#include "sqlite3.h"
#include "db.h"

#pragma comment(lib, "./lib/sqlite3.lib")


int main()
{
	auto& conn = connection::connect("data.dblite");
	auto result = query(conn, "SELECT * FROM position");

	std::cout << result << std::endl;
}