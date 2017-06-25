#ifndef WORKERS_H
#define WORKERS_H

#include <string>
#include <ctime>

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
	employee() = default;
	explicit employee(int _id);
	int work_experience() override;
	double salary()       override;
};

#endif
