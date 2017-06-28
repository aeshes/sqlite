#include <iostream>

#include "sqlite3.h"
#include "db.h"
#include "workers.h"

#pragma comment(lib, "./lib/sqlite3.lib")


int main()
{
	employee e(2);
	std::cout << "Experience: " << e.work_experience()
              << ", Salary: "   << e.salary() << std::endl;

	request req;
	req.execute("SELECT * FROM workers WHERE worker_id = 1");
	std::cout << req.value(0) << std::endl;
	std::cout << req.value(1) << std::endl;
	std::cout << req.value(2) << std::endl;

	request r("SELECT * FROM workers");
	while (r.has_next())
	{
		std::cout << r.value(1) << std::endl;
		r.next_row();
	}
}