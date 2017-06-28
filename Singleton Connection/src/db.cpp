#include "db.h"

sqlite3 * open_db(const std::string _dbfile)
{
	sqlite3 * db = nullptr;
	if (sqlite3_open(_dbfile.c_str(), &db))
	{
		std::cout << "Error in open_db: " << sqlite3_errmsg(db) << std::endl;
	}
	return db;
}

void close_db(sqlite3 * _db)
{
	sqlite3_close(_db);
}

connection::connection(const std::string & _dbfile)
{
	db_handle = open_db(_dbfile);
}

connection & connection::connect(const std::string & _dbfile)
{
    static connection instance(_dbfile);
    return instance;
}

sqlite3* connection::db_handle = nullptr;


static int callback(void *data, int _argc, char ** _argv, char ** _colnames)
{
	query_result * result = reinterpret_cast<query_result *>(data);
	return result->callback(_argc, _argv, _colnames);
}

query_result query(const connection & _conn,
                   const std::string & _query)
{
    auto db = _conn.db_handle;
	query_result result;

    if (db != nullptr)
    {
        char *err = nullptr;
        const auto ret = sqlite3_exec(db, _query.c_str(), callback, &result, &err);
        if (SQLITE_OK != ret)
        {
            std::cout << "Error while querying : "
                      << sqlite3_errmsg(db) << std::endl;
            sqlite3_free(err);
        }
    }
	return result;
}

int query_result::callback(int _argc,
                           char ** _argv,
                           char ** _colnames)
{
    std::vector<std::string> row;
    for (int i = 0; i < _argc; ++i)
    {
        row.push_back(_argv[i] ? _argv[i] : "NULL");
		fields_and_indexes[_colnames[i]] = i;
    }
	result.push_back(row);
    return 0;
}

std::ostream& operator<<(std::ostream& _os,
                         const query_result & _result)
{
    for (const auto& row : _result.result)
    {
		for (const auto& field : row)
		{
			std::cout << field << " | ";
		}
		std::cout << std::endl;
    }
    return _os;
}

std::string query_result::operator[](const std::string _key) const
{
    return result[0][fields_and_indexes.at(_key)];
}

static int request_callback(void * _data,
	int _argc,
	char ** _argv,
	char ** _colnames)
{
	request * q = reinterpret_cast<request *>(_data);
	return q->callback(_argc, _argv, _colnames);
}

void request::execute(const std::string & _sql) noexcept
{
	char * err = nullptr;
	auto & db = connection::connect();

	const auto ret = sqlite3_exec(db.get(), _sql.c_str(), request_callback, this, &err);
	if (SQLITE_OK != ret)
	{
		std::cout << sqlite3_errmsg(db.get()) << std::endl;
		sqlite3_free(err);
	}
}

bool request::has_next() noexcept
{
	return row_pointer < table.size();
}

void request::next_row() noexcept
{
    ++row_pointer;
}

void request::reset() noexcept
{
	row_pointer = 0;
}

void request::check_index(std::size_t _index, const std::string & _msg)
{
	if (_index >= table[row_pointer].size())
		throw std::out_of_range(_msg);
}

std::string request::value(std::size_t _index)
{
	check_index(_index, "query::value : index out of range");
	return table[row_pointer][_index];
}

int request::callback(int _argc,
	char ** _argv,
	char ** _colnames)
{
	row_type row;
	for (int i = 0; i < _argc; ++i)
		row.emplace_back(_argv[i] ? _argv[i] : "NULL");
    table.push_back(row);
	return 0;
}