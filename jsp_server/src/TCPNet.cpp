#include "TCPNet.h"

IKernel* TCPNet::m_pKernel = NULL;

TCPNet::TCPNet(IKernel *pKernel)
{
	s_socket = 0;
	m_threadpool = ThreadPool::GetInstance();
	m_pKernel = pKernel;
}
TCPNet::~TCPNet()
{

}

void TCPNet::addfd(int epollfd,int fd)
{
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN;// | EPOLLET;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
}

bool TCPNet::InitNetWork()
{
	struct sockaddr_in saddr;
	bzero(&saddr,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(_DEFPORT);
	saddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	s_socket = socket(AF_INET,SOCK_STREAM,0);
	bind(s_socket,(struct sockaddr*)&saddr,sizeof(saddr));
	listen(s_socket,128);

	epoll_event events[MAX_EVENTS];
	epollfds = epoll_create(5);
	
	addfd(epollfds,s_socket);
	epollfd = epoll_create(5);
	int num;
	while(1)
	{
		num = epoll_wait(epollfds,events,EPOLLSIZE,-1);
		for(int i=0;i<num;i++)
		{
			struct sockaddr_in caddr;
			socklen_t size = sizeof(caddr);

			int c_socket = accept(s_socket,(struct sockaddr*)&caddr,&size);
			if(c_socket < 0)
			{
				cout<<"connect failed..."<<endl;
				continue;
			}
			else
			{
				cout<<"success!"<<endl;
			}
			addfd(epollfd,c_socket);
			m_threadpool->AddTask(Worker,(void*)this);
		}
	}
	return true;
}

void TCPNet::UnInitNetWork()
{

}

int flag =0;

void* TCPNet::Worker(void* arg)
{
	cout<<"work+1"<<endl;
	TCPNet* pthis = (TCPNet*)arg;
	epoll_event events[MAX_EVENTS];
	int num = 0;

	while(1)
	{	
		num = epoll_wait(pthis->epollfd,events,EPOLLSIZE,-1);

		for(int i=0;i<num;i++)
		{
			//如果用户退出，移除sockfd
			pthis->RecvUP(events[i],pthis->epollfd,events[i].data.fd);
		}
	}
}
void TCPNet::removefd(int epollfd,int fd) 
{
	epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,0);
	close(fd);
}

void TCPNet::RecvUP(epoll_event event,int epollfd,int c_socket)
{
	int RealReadNum;//真正读到的大小
	int nPackSize;//包大小
	char* psbuf = NULL;
	//while(1)
	{
		RealReadNum = recv(c_socket,(char*)&nPackSize,sizeof(int),0);
		if(RealReadNum <= 0)
		{
			//客户端下线或者错误
			removefd(epollfd,event.data.fd);
			return;
		}
		psbuf = new char[nPackSize];
		int noffset = 0;
		while(nPackSize)
		{
			RealReadNum = recv(c_socket,psbuf+noffset,nPackSize,0);
			noffset += RealReadNum;
			nPackSize -= RealReadNum;
		}
		m_pKernel->DealData(c_socket,psbuf);
		delete []psbuf;
		psbuf = NULL;
	}
}

bool TCPNet::SendData(int sock,char* szbuf,int nlen)
{
	if(!szbuf || nlen <=0)
		return false;

	//发送包大小
	if(send(sock,(const char*)&nlen,sizeof(int),0)<0)
		return false;
	//包内容
	if(send(sock,szbuf,nlen,0)<0)
		return false;
	DOWNORDER_RS *p = (DOWNORDER_RS*)szbuf;
	cout<<p->m_nType<<endl;
	return true;
}
