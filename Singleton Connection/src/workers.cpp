#include "workers.h"

static int worker_callback(void * param,
	int _argc,
	char ** _argv,
	char ** _colnames)
{
	worker * w = reinterpret_cast<worker *>(param);
	return w->callback(_argc, _argv, _colnames);
}

employee::employee(int _id)
{
	std::string sql = "SELECT * FROM workers WHERE worker_id = " + std::to_string(_id);
	auto result = query(connection::connect(), sql);
	std::cout << result << std::endl;

	firstname = result["firstname"];
	lastname  = result["lastname"];
}

void employee::get_by_id(int _id)
{
	auto& db = connection::connect("data.dblite");
	char *err = nullptr;
	std::string sql = "SELECT firstname FROM workers WHERE worker_id = " + std::to_string(_id);
	const int ret = sqlite3_exec(db.get(), sql.c_str(), worker_callback, this, &err);
	if (SQLITE_OK != ret)
	{
		std::cout << "Error in employee::get_by_id: " << sqlite3_errmsg(db.get()) << std::endl;
	}
}

int employee::experience(int _id)
{
	auto& db = connection::connect();
	request req("SELECT DATE('now') - (SELECT hire_date FROM workers where worker_id = " + std::to_string(_id) + ")");
	return std::stoi(req.value(0));
}

int employee::callback(int _argc,
	char ** _argv,
	char ** _colnames)
{
	std::cout << "return from employee::callback: " << *_argv << std::endl;
	return 0;
}