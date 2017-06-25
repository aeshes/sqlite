#ifndef DB_H
#define DB_H

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <ctime>

#include "sqlite3.h"


class connection;
class query_result;
class request;

#define DEFAULT_DB_NAME "data.dblite"

query_result query(const connection & _conn,
                   const std::string & _query);


class connection
{
    friend query_result query(const connection & _conn,
                              const std::string & _query);
    using handle = sqlite3 *;
public:
    static connection & connect(const std::string & _dbfile = DEFAULT_DB_NAME);
	static handle get() { return db_handle; }

private:
    connection(const std::string & _dbfile);
    connection(const connection & _conn)             = delete;
    connection & operator=(const connection & _conn) = delete;

    static handle db_handle;
};

class query_result
{
public:
    query_result() = default;
    friend std::ostream& operator<<(std::ostream& _os,
                                    const query_result & _result);
	std::string operator[](const std::string _key) const;
	std::string value(std::size_t _column);

    int callback(int _argc,
                 char ** _argv,
                 char ** _colnames);
private:
    std::vector<std::vector<std::string>> result;
    std::map<std::string, std::size_t> fields_and_indexes;
	std::size_t current_row = 0;
};

class request
{
	friend int request_callback(void *, int, char **, char **);

public:
	request() = default;
	request(const std::string & _sql)
		: sql{ _sql } { execute(_sql); }
	void execute(const std::string & _sql);
	std::string value(std::size_t _index);

private:
	std::string sql;
	std::vector<std::string> result;

	void check_index(std::size_t _index, const std::string & _msg);
	int callback(int _argc,
		char ** _argv,
		char ** _colnames);
};

#endif
