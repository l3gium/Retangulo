#pragma once

#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include <vector>

class Database
{
	public:
		Database();
		~Database();

		bool connect(const std::string& connectionString);
		void disconnect();
		bool executeQuery(const std::string& sql);

		int executeCountQuery(const std::string& sql);
		std::vector<int> executeSelectQuery(const std::string& sql);

	private:
		SQLHENV hEnv;
		SQLHDBC hDbc;
};