#ifndef _TCPNET_H
#define _TCPNET_H

#include "INet.h"
#include <arpa/inet.h>
#include <iostream>
#include <strings.h>
#include <sys/epoll.h>
#include "IKernel.h"
#include "TCPKernel.h"
#include "Packdef.h"

using namespace std;

#define MAX_EVENTS 1024
#define EPOLLSIZE 1024

class TCPNet:public INet
{
public:
	TCPNet(IKernel* pKernel);
	~TCPNet();
public:
	bool InitNetWork();
	void UnInitNetWork();
	bool SendData(int sock,char* szbuf,int nlen);
public:
	void RecvUP(epoll_event,int,int);
	void addfd(int epollfd,int fd);
	void removefd(int,int);
	static void* Worker(void* arg);
public:
	int s_socket;
	ThreadPool* m_threadpool;
	int epollfds;
	int epollfd;
	static IKernel *m_pKernel;
};

#endif
