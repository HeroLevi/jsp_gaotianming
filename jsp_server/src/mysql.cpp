#include "mysql.h"

MySql::MySql()
{
	sock = new MYSQL;
	mysql_init(sock);
}

MySql::~MySql()
{
	if(sock)
	{
		delete sock;
		sock = NULL;
	}
}

bool MySql::ConnectMySql(char* host,char* user,char* password,char* db)
{
	if(!mysql_real_connect(sock,host,user,password,db,0,NULL,CLIENT_MULTI_STATEMENTS))
		return false;
	return true;
}

void MySql::DestroyMySql()
{
	mysql_close(sock);
}

bool MySql::SelectMySql(char* szSql,int nColumn,list<string>& lstStr)
{
	if(mysql_query(sock,szSql))
		return false;
	results = mysql_store_result(sock);

	if(NULL == results)
		return false;
	while(record = mysql_fetch_row(results))
	{
		for(int i=0;i<nColumn;i++)
		{
			lstStr.push_back(record[i]);
		}   
	}   
	mysql_free_result(results);
	return true;
}

bool MySql::UpdateMySql(char* szSql)
{
	if(!szSql)
		return false;
	do
	{
		results = mysql_store_result(sock);
		mysql_free_result(results);
	}while(!mysql_next_result(sock));

	if(mysql_query(sock,szSql))
	{
		cout<<mysql_error(sock)<<endl;
		return false;
	}
	return true;
}
