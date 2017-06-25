#include "workers.h"


employee::employee(int _id)
{
	request req("SELECT firstname, lastname, base_rate, hire_date FROM workers WHERE worker_id = " + std::to_string(_id));

	id = _id;
	firstname = req.value(0);
	lastname  = req.value(1);
	base_rate = std::stod(req.value(2));
}

int employee::work_experience()
{
	auto& db = connection::connect();
	request req("SELECT DATE('now') - (SELECT hire_date FROM workers where worker_id = " + std::to_string(id) + ")");
	return std::stoi(req.value(0));
}

double employee::salary()
{
    double extra_pay_percents = 0.03 * work_experience();
    double extra_pay = extra_pay_percents < 0.3 ? base_rate * extra_pay_percents
                                                : base_rate * 0.3;
	return base_rate + extra_pay;
}