#ifndef DB_H
#define DB_H

#include <iostream>
#include <string>

#include "sqlite3.h"


class connection;

void query(const connection & _conn,
           const std::string & _query);

class connection
{
	friend void query(const connection & _conn,
                      const std::string & _query);
	using handle = sqlite3 *;
public:
	static connection * connect(const std::string & _dbfile);
	static handle get();

protected:
	connection(const std::string & _dbfile);
	connection(const connection & _conn)             = default;
	connection & operator=(const connection & _conn) = default;
	virtual ~connection()                            = default;

	static connection * conn;
	static handle db_handle;
};

#endif
