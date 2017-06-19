#include <iostream>

#include "sqlite3.h"
#include "db.h"
#include "workers.h"

#pragma comment(lib, "./lib/sqlite3.lib")


int main()
{
	auto& conn = connection::connect("data.dblite");
	auto result = query(conn, "SELECT * FROM workers");

	std::cout << result << std::endl;

	employee e;
	e.get_by_id(1);

	employee d(1);
}