#ifndef DB_H
#define DB_H

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>

#include "sqlite3.h"


class connection;
class query_result;

query_result query(const connection & _conn,
                   const std::string & _query);

class connection
{
    friend query_result query(const connection & _conn,
                              const std::string & _query);
    using handle = sqlite3 *;
public:
    static connection & connect(const std::string & _dbfile);

private:
    connection(const std::string & _dbfile);
    connection(const connection & _conn)             = default;
    connection & operator=(const connection & _conn) = default;

    static connection * conn;
    static handle db_handle;
};

class query_result
{
public:
	query_result() = default;
    query_result(int _count,
                 const char ** _argv,
                 const char ** _columns);
    std::string operator[](const std::string _key);
    friend std::ostream& operator<<(std::ostream& _os,
                                    const query_result & _result);

    int callback(int _argc,
                 char ** _argv,
                 char ** _colnames);
private:
	std::vector<std::vector<std::string>> data;
};

#endif
