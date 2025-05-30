#include "Database.h"
#include <iostream>

Database::Database() : hEnv(SQL_NULL_HENV), hDbc(SQL_NULL_HDBC) {}

Database::~Database() 
{
	disconnect();
}

bool Database::connect(const std::string& connectionString)
{
	SQLRETURN ret;

	// 1. Aloca o handle de ambiente
	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return false;

	// 2. Configura o atributo do ambiente
	ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return false;

	// 3. Aloca o handle de conexão
	ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return false;

	ret = SQLDriverConnectA(
		hDbc,
		NULL,
		(SQLCHAR*)connectionString.c_str(),
		SQL_NTS,
		NULL,
		0,
		NULL,
		SQL_DRIVER_NOPROMPT
	);

	if (ret == SQL_ERROR) {
		SQLCHAR sqlState[6], message[256];
		SQLINTEGER nativeError;
		SQLSMALLINT textLength;
		SQLGetDiagRecA(
			SQL_HANDLE_DBC,
			hDbc,
			1,
			sqlState,
			&nativeError,
			message,
			sizeof(message),
			&textLength
		);
		std::cout << "SQLSTATE: " << sqlState << std::endl;
		std::cout << "Error message: " << message << std::endl;
	}

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) 
		return true;
	
	return false;
}

void Database::disconnect()
{
	if (hDbc != SQL_NULL_HDBC)
	{
		SQLDisconnect(hDbc);
		SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	}

	if (hEnv != SQL_NULL_HENV)
		SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}

bool Database::executeQuery(const std::string& sql) {
	SQLHSTMT hStmt;
	SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	if (ret != SQL_SUCCESS) return false;

	ret = SQLExecDirectA(hStmt, (SQLCHAR*)sql.c_str(), SQL_NTS);
	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
}