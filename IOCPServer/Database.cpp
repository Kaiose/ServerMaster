#include "stdafx.h"
#include "Database.h"


Database::Database()
{
	
	ODBC_NAME	= (SQLWCHAR*)L"mysql_game";
	ODBC_ID = (SQLWCHAR*)L"root";
	ODBC_PW = (SQLWCHAR*)L"kinam1018";

}


Database::~Database()
{

}

bool Database::DBConnect() {
	
	// ȯ�� �ڵ��� �Ҵ��Ѵ�.
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS) {
		Log("SQL Handel Allocate Failed \n");
		return false;
	}

	// ���� ȯ�濡 ���� �Ӽ��� �����Ѵ�.
	if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS) {
		Log("SQL Set Env Attr Failed \n");
		return false;
	}

	// �����ڵ��� �����Ѵ�.
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS) {
		Log("SQL Handel Allocate Failed \n");
		return false;
	}


	// �����Ϳ� �����Ѵ�.
	if (SQLConnect(hDbc, ODBC_NAME, SQL_NTS, ODBC_ID, SQL_NTS, ODBC_PW, SQL_NTS) != SQL_SUCCESS) {
		Log("SQL Handle Connect Failed \n");
		return false;
	}
	// ��ɹ��ڵ��� �Ҵ��Ѵ�.
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
		Log("SQL Handel Allocate Failed \n");
		return false;
	}

	return true;
}

bool Database::DBDisConnect() {

	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if (hDbc) SQLDisconnect(hDbc);
	if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	return true;
}

void Database::AttributeBind() {
	SQLBindCol(hStmt, 1, SQL_INTEGER, &id, sizeof(id), &idLen);
	SQLBindCol(hStmt, 2, SQL_CHAR, name, sizeof(CHAR) * 20, &nameLen);
	SQLBindCol(hStmt, 3, SQL_CHAR, password, sizeof(CHAR) * 20, &passwordLen);

}
/*
	SQL���� ��������� ���ڵ��� ���ε�Ǹ�
	��ɹ�(statement)�� SQLExecDirect�� ����ȴ�.
	���� ������ ����Ǵ� ������ SQLPrepare()�� �غ��ϰ�,
	SQLExecute�� ����ؾ��ϴ� ���� ���ɸ鿡 �����ϴ�.

	����

	SQL���� �Ķ���� ��Ŀ���� �����ϸ�, ���ø����̼���
	SQLBindParameter() �� ȣ���Ͽ� �� ���ڵ��� ���ø����̼� ������
	Bind ��Ų��.

	���ڸ� Bind �ϱ�����SQLPrepare()�� �����ؾ��ϸ�,
	���ε� �Ŀ� SQLExecute()�� ������ �� �ִ�.

	���� ����� ��ɹ�(statement) �� SELECT ���̶�� 
	���� calum Count�� �˾ƺ��� ���� SQLNumResultCols()�� ȣ���Ѵ�.

	�� ���� SQLDescribeCol()�� �� ��� ���տ��� �����͸� �����´�.


	�� �� ���ø����̼� ������ ��� ������ ���� ���ε��ϴ�
	SQLBindCol()�� �̷� ������ ������.
	(�� �������� db�� Attribute �� �˰� �ֱ� ������ 
	������ ������ attribute�� �м��ϱ� ���ٴ� �׳� bind�� �������)


	���� SQLFetch() �� ȣ���Ͽ� ù��° �� �����͸� ��������
	SQLBindCol() �� ���ε� �� ������ �����͸� �����Ѵ�.
	�࿡ �� �����Ͱ� ������ SQLGetData()�� �� �� �ְ� ��� ȣ���� �� �� �ִ�.

	data�� fetch�� ���Ͽ� ������ ���Ŀ��� �ٸ� Statement��
	SQLPrepare() �� SQLExecute()�� ���� �����ϱ�����

	�ݵ�� SQLCloseCurser()�� ȣ���Ͽ� Ŀ���� �ݾ������.


	���� ���� ����� Statement �� INSERT, UPDATE, DELETE ���ٸ�
	SQLRowCount() �� ������ ���� ����� ������ �����´�.

	
	*/



bool Database::Insert(int id , const WCHAR* name, const WCHAR* password) {
	WCHAR InsertCommand[100] = { 0, };
	wsprintf(InsertCommand, L"INSERT INTO Account (id, name, password) VALUES (%d, '%s', '%s');", id, name, password);
	printf("%ws\n", InsertCommand);
	int ret = SQLExecDirect(hStmt, (SQLWCHAR*)InsertCommand, SQL_NTS);
	if (ret != SQL_SUCCESS) {
		Log("InsertFailed\n");
		if (hStmt) SQLCloseCursor(hStmt);
		return false;
	}

	if (hStmt) SQLCloseCursor(hStmt);

	return true;
}


bool Database::Delete(int id) {
	WCHAR DeleteCommand[100] = { 0, };
	wsprintf(DeleteCommand, L"DELETE FROM Account WHERE id=%d",id);
	printf("%ws\n", DeleteCommand);
	int ret = SQLExecDirect(hStmt, (SQLWCHAR*)DeleteCommand, SQL_NTS);
	if (ret != SQL_SUCCESS) {
		Log("DeleteFailed\n");
		if (hStmt) SQLCloseCursor(hStmt);
		return false;
	}

	if (hStmt) SQLCloseCursor(hStmt);
	return true;
}

bool Database::Match(const char* name, const char* password) {
	
	WCHAR MatchCommand[100] = { 0, };
	wsprintf(MatchCommand, L"Select * FROM Account");
	printf("%ws\n", MatchCommand);
	int ret = SQLExecDirect(hStmt, (SQLWCHAR*)MatchCommand, SQL_NTS);
	if (ret != SQL_SUCCESS) {
		Log("MatchFailed\n");
		if (hStmt) SQLCloseCursor(hStmt);
		return false;
	}

	printf("User name : %s\t Password : %s\n",  name, password);
	
	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		printf("%d\t%s\t%s\n", id, this->name, this->password);
		if (strcmp(this->name, name) == 0 && strcmp(this->password, password) == 0) {
			if (hStmt) SQLCloseCursor(hStmt);
			printf("Match Success! \n");
			return true;
		}
	}
	
	printf("Match Failed! \n");
	if (hStmt) SQLCloseCursor(hStmt);

	return false;
}

void Database::Show() {


	WCHAR ShowCommand[100] = { 0, };
	wsprintf(ShowCommand, L"Select * FROM Account");
	printf("%ws\n", ShowCommand);
	int ret = SQLExecDirect(hStmt, (SQLWCHAR*)ShowCommand, SQL_NTS);
	if (ret != SQL_SUCCESS) {
		Log("ShowFailed\n");
		if (hStmt) SQLCloseCursor(hStmt);
		return;
	}
	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		printf("%d\t %s\t %s \n", id, name, password);
	}


	if (hStmt) SQLCloseCursor(hStmt);
}

