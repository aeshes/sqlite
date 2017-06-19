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

query_result query(const connection & _conn,
                   const std::string & _query);

template <typename T, typename Del = std::default_delete<T>>
inline auto raii_ptr(T* t, Del&& del = std::default_delete<T>)
{
	return std::unique_ptr<T, Del> {t, del};
}

class connection
{
    friend query_result query(const connection & _conn,
                              const std::string & _query);
    using handle = sqlite3 *;
public:
    static connection & connect(const std::string & _dbfile);
	static handle get() { return db_handle; }

private:
    connection(const std::string & _dbfile);
    connection(const connection & _conn)             = default;
    connection & operator=(const connection & _conn) = default;

    static handle db_handle;
};

class query_result
{
public:
    query_result() = default;
    friend std::ostream& operator<<(std::ostream& _os,
                                    const query_result & _result);
	std::string operator[](const std::string _key) const;

    int callback(int _argc,
                 char ** _argv,
                 char ** _colnames);
private:
    std::vector<std::vector<std::string>> result;
    std::map<std::string, std::size_t> fields_and_indexes;
};

#endif
