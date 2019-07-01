#ifndef _IKERNEL_H
#define _IKERNEL_H

class IKernel
{
public:
	IKernel(){}
	virtual ~IKernel(){}
public:
	virtual bool Open() = 0;
	virtual void Close() = 0;
	virtual void DealData(int sock,char* szbuf) = 0;
};

#endif
