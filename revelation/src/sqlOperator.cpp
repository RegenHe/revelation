#include "sqlOperator.h"

SqliteOperator::SqliteOperator()
{
	mSqlite = nullptr;
}

SqliteOperator::~SqliteOperator()
{
	if (mSqlite != nullptr)
	{
		sqlite3_close_v2(mSqlite);
		mSqlite = nullptr;
	}
}

int SqliteOperator::openDB(const std::string& path)
{
	return sqlite3_open(path.c_str(), &mSqlite);
}

void SqliteOperator::closeDB()
{
	if (mSqlite != nullptr)
	{
		sqlite3_close_v2(mSqlite);
		mSqlite = nullptr;
	}
}

int SqliteOperator::createTab(const std::string& sql)
{
	char* szMsg = NULL;
	return sqlite3_exec(mSqlite, sql.c_str(), NULL, NULL, &szMsg);
}

int SqliteOperator::Insert(const std::string& sql)
{
	if (sql.empty()) return -1;

	char* zErrMsg = NULL;
	int ret = sqlite3_exec(mSqlite, sql.c_str(), NULL, NULL, &zErrMsg);
	if (zErrMsg)
	{
		sqlite3_free(zErrMsg);
	}
	return ret;
}

int SqliteOperator::Delete(const std::string& sql)
{
	int nCols = 0;
	int nRows = 0;
	char** azResult = NULL;
	char* errMsg = NULL;
	int result = sqlite3_get_table(mSqlite, sql.c_str(), &azResult, &nRows, &nCols, &errMsg);
	if (result != SQLITE_OK)
	{
		return false;
	}
	if (azResult)
	{
		sqlite3_free_table(azResult);
	}
	if (errMsg)
	{
		sqlite3_free(errMsg);
	}
	return true;
}

int SqliteOperator::Update(const std::string& sql)
{
	char* zErrMsg = NULL;

	int ret = sqlite3_exec(mSqlite, sql.c_str(), NULL, NULL, &zErrMsg);
	if (zErrMsg)
	{
		sqlite3_free(zErrMsg);
	}
	return ret;
}

sqlUser SqliteOperator::query(const std::string& sql)
{
	sqlite3_stmt* stmt = NULL;
	int result = sqlite3_prepare_v2(mSqlite, sql.c_str(), -1, &stmt, NULL);
	sqlUser ret;
	if (result == SQLITE_OK)
	{
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			ret.id = sqlite3_column_int(stmt, 0);
			ret.provinceId = (const char*)(sqlite3_column_text(stmt, 1));
			ret.provinceName = (const char*)(sqlite3_column_text(stmt, 2));
			ret.cityeName = (const char*)(sqlite3_column_text(stmt, 3));
			ret.name = (const char*)(sqlite3_column_text(stmt, 4));
			ret.describe = (const char*)(sqlite3_column_text(stmt, 5));

			break;
		}
	}
	return ret;
}

std::vector<sqlUser> SqliteOperator::queryAll(const std::string& sql)
{
	sqlite3_stmt* stmt = NULL;
	int result = sqlite3_prepare_v2(mSqlite, sql.c_str(), -1, &stmt, NULL);
	std::vector<sqlUser> ret;
	if (result == SQLITE_OK)
	{

		sqlUser temp;
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			temp.id = sqlite3_column_int(stmt, 0);
			temp.provinceId = (const char*)(sqlite3_column_text(stmt, 1));
			temp.provinceName = (const char*)(sqlite3_column_text(stmt, 2));
			temp.cityeName = (const char*)(sqlite3_column_text(stmt, 3));
			temp.name = (const char*)(sqlite3_column_text(stmt, 4));
			temp.describe = (const char*)(sqlite3_column_text(stmt, 5));
			ret.push_back(temp);

		}
	}
	return ret;
}
