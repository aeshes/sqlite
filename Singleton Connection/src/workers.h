#ifndef WORKERS_H
#define WORKERS_H

#include <string>
#include <ctime>
#include <memory>
#include <set>

#include "db.h"

class worker
{
public:
	virtual ~worker() = default;
	virtual int work_experience() = 0;
	virtual double salary()       = 0;

protected:
	int         id;
	std::string firstname;
	std::string lastname;
	std::time_t hire_date;
	double      base_rate;
};

class employee : public worker
{
public:
	employee() noexcept = default;
	explicit employee(int _id) noexcept;
	int work_experience() noexcept override;
	double salary()       noexcept override;
};

class head : public worker
{
// Abstract class for all workers that can have subordinates
protected:
    int work_experience() noexcept override;
	double calc_salary(double _exp_coeff, double _sub_coeff, double _extra_pay_limit) noexcept;

	using pointer_type = std::shared_ptr<worker>;
	using storage_type = std::set<pointer_type>;

	storage_type subs;
};

class manager : public worker
{
public:
    manager() noexcept = default;
    explicit manager(int _id) noexcept;
    int work_experience() noexcept override;
    double salary()       noexcept override;
};

#endif
