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

double head::calc_salary(double _exp_coeff, double _extra_pay_limit) noexcept
{
    double extra_pay_percents = _exp_coeff * work_experience();
    double extra_pay = extra_pay_percents < _extra_pay_limit ? base_rate * extra_pay_percents
                                                             : base_rate * _extra_pay_limit;
    return base_rate + extra_pay;
}

void head::debug() noexcept
{
	std::cout << "ID = " << id << ", name = " << firstname << std::endl;
	std::cout << "exp = " << work_experience() << std::endl;
	std::cout << "salary = " << salary() << std::endl;
	std::cout << "employees:" << std::endl;

	for (const auto& e : employees)
	{
		std::cout << "id =  " << e->get_id() << std::endl;
	}
}

manager::manager(int _id) noexcept
{
	request req("SELECT firstname, lastname, base_rate, hire_date FROM workers WHERE worker_id = " + std::to_string(_id));

	id = _id;
	firstname = req.value(0);
	lastname = req.value(1);
	base_rate = std::stod(req.value(2));
	request employees_ids("SELECT inferior FROM subordinates WHERE superior = " + std::to_string(_id));
	while (employees_ids.has_next())
	{
		auto id = std::stoi(employees_ids.value(0));
		employees.insert(std::make_shared<employee>(id));
		employees_ids.next_row();
	}
}

int manager::work_experience() noexcept
{
	return 0;
}

double manager::salary() noexcept
{
	double base_pay = calc_salary(exp_coeff, extra_pay_limit);

	double salary_of_employees = 0.0;
	std::for_each(employees.cbegin(), employees.cend(),
		[&salary_of_employees](const pointer_type& emp)
        {
            salary_of_employees += emp->salary();
        });
	return base_pay + emp_coeff * salary_of_employees;
}