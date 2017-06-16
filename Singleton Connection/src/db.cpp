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

static int c_callback(void *data, int _argc, char ** _argv, char ** _columns)
{
	query_result * result = reinterpret_cast<query_result *>(data);
	return result->callback(_argc, _argv, _columns);
}

query_result query(const connection & _conn,
                   const std::string & _query)
{
    auto db = _conn.db_handle;
    if (db != nullptr)
    {
        char *err = nullptr;
        query_result result;
        const auto ret = sqlite3_exec(db, _query.c_str(), c_callback, &result, &err);
        if (SQLITE_OK != ret)
        {
            std::cout << "Error while querying : "
                      << sqlite3_errmsg(db) << std::endl;
            sqlite3_free(err);
        }
		return result;
    }
	return query_result();
}

query_result::query_result(int _count,
                           const char ** _argv,
                           const char ** _columns)
{
    for (int i = 0; i < _count; ++i)
    {
        //result[_columns[i]] = _argv[i] ? _argv[i] : "NULL";
    }
}

std::string query_result::operator[](const std::string _key)
{
    return std::string();
}

int query_result::callback(int _argc,
                           char ** _argv,
                           char ** _colnames)
{
	std::cout << "query_result::callback called with parameters: "
		<< _argc << std::endl;
	std::vector<std::string> row;
    for (int i = 0; i < _argc; ++i)
    {
		std::cout << _colnames[i] << " : " << _argv[i] << std::endl;
		row.push_back(_argv[i] ? _argv[i] : "NULL");
    }
	data.push_back(row);
    return 0;
}

std::ostream& operator<<(std::ostream& _os,
                         const query_result & _result)
{
    for (const auto& row : _result.data)
    {
		for (const auto& field : row)
		{
			std::cout << field << " | ";
		}
		std::cout << std::endl;
    }
    return _os;
}