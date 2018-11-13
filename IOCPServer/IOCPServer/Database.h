#pragma once

#include "stdafx.h"
#include <sql.h>
#include <sqlext.h>



class Database
{

public:
	int id;

	//SQLWCHAR name[20];
	//SQLWCHAR password[20];


	CHAR name[20];
	CHAR password[20];


	SQLLEN idLen;
	SQLLEN nameLen;
	SQLLEN passwordLen;


public:
	SQLHENV		hEnv; // ȯ�� �ڵ�
	SQLHDBC		hDbc; // ���� �ڵ��� ������
	SQLHSTMT	hStmt;

	SQLWCHAR* ODBC_NAME;
	SQLWCHAR* ODBC_ID;
	SQLWCHAR* ODBC_PW;

public:
	Database();
	~Database();

	bool DBConnect();
	bool DBDisConnect();

	void AttributeBind();

	bool Insert(int id, const WCHAR* name, const WCHAR* password);

	bool Delete(int id);

	bool Match(const char* name, const char* password);


	void Show();
};

