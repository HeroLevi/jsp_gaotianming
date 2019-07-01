#ifndef _INET_H
#define _INET_H

#include <sys/socket.h>

class INet 
{
public:
	INet(){}
	virtual ~INet(){}
public:
	virtual bool InitNetWork() = 0;
	virtual void UnInitNetWork() = 0;
	virtual bool SendData(int sock,char* szbuf,int nlen) = 0;
};

#endif
