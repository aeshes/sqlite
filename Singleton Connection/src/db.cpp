#include "db.h"

connection::connection(const std::string & _dbfile)
{
    if (sqlite3_open(_dbfile.c_str(), &db_handle))
    {
        std::cout << "Error while opening DB: "
                  << sqlite3_errmsg(db_handle) << std::endl;
    }
}

connection & connection::connect(const std::string & _dbfile)
{
    static connection instance(_dbfile);
    return instance;
}

connection* connection::conn = nullptr;
sqlite3*    connection::db_handle = nullptr;


static int callback(void *data, int argc, char ** argv, char ** columns)
{
    std::cout << (const char *)data << std::endl;

    for (int i = 0; i < argc; ++i)
    {
        std::cout << columns[i] << " : " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;

    return 0;
}

void query(const connection & _conn,
           const std::string & _query)
{
    auto db = _conn.db_handle;
    if (db != nullptr)
    {
        char *err = nullptr;
        std::shared_ptr<query_result> result;
        const char *data = "callback called";
        const auto ret = sqlite3_exec(db, _query.c_str(), callback, (void *)data, &err);
        if (SQLITE_OK != ret)
        {
            std::cout << "Error while querying : "
                      << sqlite3_errmsg(db) << std::endl;
            sqlite3_free(err);
        }
    }
}

query_result::query_result(int _count,
                           const char ** _argv,
                           const char ** _columns)
{
    for (int i = 0; i < _count; ++i)
    {
        result[_columns[i]] = _argv[i] ? _argv[i] : "NULL";
    }
}

std::string query_result::operator[](const std::string _key)
{
    return result.at(_key);
}