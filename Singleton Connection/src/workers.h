#ifndef WORKERS_H
#define WORKERS_H

#include <string>
#include <ctime>

#include "db.h"

class worker
{
	friend int worker_callback(void *, int, char **, char **);
public:
	virtual ~worker() = default;
	virtual void get_by_id(int _id) = 0;
	virtual int experience(int _id) = 0;

protected:
	virtual int callback(int _argc,
		char ** _argv,
		char ** _colnames) = 0;
	std::string firstname;
	std::string lastname;
	std::time_t hire_date;
	double      base_rate;
};

class employee : public worker
{
public:
	employee() = default;
	employee(int _id);
	void get_by_id(int _id) override;
	int experience(int _id) override;

private:
	int callback(int _argc,
		char ** _argv,
		char ** _colnames) override;
};

#endif
