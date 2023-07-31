#ifndef _SQL_OPERATOR_
#define _SQL_OPERATOR_

#include "sqlite3.h"
#include <string>
#include <map>
#include <vector>
#include <iostream>

struct sqlUser
{
	int id;
	std::string provinceId;
	std::string provinceName;
	std::string cityeName;
	std::string name;
	std::string describe;
};

class SqliteOperator
{
public:
	SqliteOperator();
	~SqliteOperator();

	int openDB(const std::string& path);
	void closeDB();

	int createTab(const std::string& sql);

	int Insert(const std::string& sql);
	int Delete(const std::string& sql);
	int Update(const std::string& sql);
	sqlUser query(const std::string& sql);
	std::vector<sqlUser> queryAll(const std::string& sql);

private:

private:
	sqlite3* mSqlite;
};



#endif // !_SQL_OPERATOR_
