#pragma once

#include "stdafx.h"
#include <sql.h>
#include <sqlext.h>


//상속 받아서 확장시키는게 좋겠지만
//귀찮으니 때려박자

// 귀찮으니 한글입력안됨

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
	SQLHENV		hEnv; // 환경 핸들
	SQLHDBC		hDbc; // 연결 핸들의 포인터
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

