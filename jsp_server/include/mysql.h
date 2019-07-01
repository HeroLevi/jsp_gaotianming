#ifndef _MYSQL_H
#define _MYSQL_H

#include <mysql/mysql.h>
#include <list>
#include <string.h>
#include <iostream>
using namespace std;
class MySql
{
	public:
		MySql();
		~MySql();
	public:
		bool ConnectMySql(char* host,char* user,char* password,char* db);
		void DestroyMySql();
		bool SelectMySql(char* szSql,int nColumn,list<string>& lstStr);
		bool UpdateMySql(char* szSql);
	private:
		MYSQL* sock;
		MYSQL_RES *results;
		MYSQL_ROW record;
};

#endif
