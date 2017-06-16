#ifndef DB_H
#define DB_H

#include <iostream>
#include <string>
#include <map>
#include <memory>

#include "sqlite3.h"


class connection;
class query_result;

void query(const connection & _conn,
           const std::string & _query);

class connection
{
    friend void query(const connection & _conn,
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
    query_result(int _count,
                 const char ** _argv,
                 const char ** _columns);
    std::string operator[](const std::string _key);
private:
    std::map<std::string, std::string> result;
};

#endif
