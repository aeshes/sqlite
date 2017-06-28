#include "workers.h"


employee::employee(int _id) noexcept
{
	request req("SELECT firstname, lastname, base_rate, hire_date FROM workers WHERE worker_id = " + std::to_string(_id));

	id = _id;
	firstname = req.value(0);
	lastname  = req.value(1);
	base_rate = std::stod(req.value(2));
}

int employee::work_experience() noexcept
{
    auto& db = connection::connect();
    request req("SELECT DATE('now') - (SELECT hire_date FROM workers where worker_id = " + std::to_string(id) + ")");
    return std::stoi(req.value(0));
}

double employee::salary() noexcept
{
    double extra_pay_percents = 0.03 * work_experience();
    double extra_pay = extra_pay_percents < 0.3 ? base_rate * extra_pay_percents
                                                : base_rate * 0.3;
    return base_rate + extra_pay;
}

int head::work_experience() noexcept
{
    auto& db = connection::connect();
    request req("SELECT DATE('now') - (SELECT hire_date FROM workers where worker_id = " + std::to_string(id) + ")");
    return std::stoi(req.value(0));
}

double head::calc_salary(double _exp_coeff, double _sub_coeff, double _extra_pay_limit) noexcept
{
    double extra_pay_percents = _exp_coeff * work_experience();
    double extra_pay = extra_pay_percents < _extra_pay_limit ? base_rate * extra_pay_percents
                                                             : base_rate * _extra_pay_limit;
    return base_rate + extra_pay;
}
