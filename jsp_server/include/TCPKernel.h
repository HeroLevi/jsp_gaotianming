#ifndef _TCPKERNEL_H
#define _TCPKERNEL_H

#include "IKernel.h"
#include "mysql.h"
#include "ThreadPool.h"
#include "INet.h"
#include "Packdef.h"
#include "TCPNet.h"
#include <vector>
#include <pthread.h>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <functional>
#include <set>
#include <cstdlib>
#include <unistd.h>

using namespace std;

class TCPKernel;
typedef void (TCPKernel:: *PFUN)(int,char*);

struct ProtocolMap
{
	PackType m_nType;
	PFUN m_pfun;
};

class TCPKernel:public IKernel
{
public:
	TCPKernel();
	~TCPKernel();
public:
	bool Open();
	void Close();
	void DealData(int sock,char* szbuf);
public:
	void RegisterRq(int sock,char* szbuf);
	void AddMatter(int sock,char* szbuf);
	void LoginRq(int sock,char* szbuf);
	void Updatepass(int sock,char* szbuf);
	void ServHbRecv(int sock,char* szbuf);
	void WorkRq(int sock,char* szbuf);
	void AddJob(int sock,char* szbuf); 
	void UpdateJob(int sock,char* szbuf);
	void AddMec(int sock,char* szbuf);
	void UpdateMec(int sock,char* szbuf);
	void Getggt(int sock,char* szbuf);
	unsigned long get_file_size(const char*);
	void ByeBye(int sock,char* szbuf);
	void DownOrder(int sock,char* szbuf);
	void DFS(int sock,char* szbuf);
	void DelMac(int sock,char* szbuf);
	void SelectMac(int sock,char* szbuf);
	void SelectJob(int sock,char* szbuf);
	void DelJob(int sock,char* szbuf);
	void DelMatter(int sock,char* szbuf);
	void SelectMatter(int sock,char* szbuf);
	void DoneOrderS(int sock,char* szbuf);
	void Look(int sock,char* szbuf);
	void OutOrder(int sock,char* szbuf);
	void UpdateOrder(int sock,char* szbuf);
public:
	INet* m_pTCPNet;
	ThreadPool* m_threadpool;
	int servid[_DEF_SIZE];
	list<string> lstStr;
	vector<vector<JSP>> vec;
	vector<JSP> tmp;
	int num;
	vector<vector<char>> v;;
	pthread_mutex_t mutex;
public:
	MySql m_sql;
};

#endif
