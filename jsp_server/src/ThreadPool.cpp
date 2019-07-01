#include "ThreadPool.h"

ThreadPool* ThreadPool::m_instance = NULL;
//构造
ThreadPool::ThreadPool()
{
	//cout<<"a"<<endl;
	this->shutdown = false;
	thread_alive = 0;
	thread_busy = 0;
	thread_kill = 0;

	queue_head = 0;
	queue_tail = 0;
	queue_cur = 0;
}
//析构
ThreadPool::~ThreadPool()
{
	delete[] arr_pthread_tid;
	delete[] task;
	bool flag = shutdown;
	for(;;)
	{
		if(shutdown)
			return;
		else
			while(__sync_bool_compare_and_swap(&shutdown,flag,true));
	}
	for(unsigned int i=0;i<thread_alive;i++)
		pthread_cond_signal(&not_empty);
	sleep(TIME_OUT);
	pthread_mutex_destroy(&lock_task);
	pthread_cond_destroy(&not_full);
	pthread_cond_destroy(&not_empty);
}

bool ThreadPool::InitThreadPool(int max,int min,int queue_max)
{
	int err;
	this->thread_max = max;
	this->thread_min = min;
	this->queue_max = queue_max;
	this->task = new task_t[queue_max];

	if(pthread_cond_init(&not_empty,NULL) != 0 || pthread_cond_init(&not_full,NULL))
	{
		perror("pthread_cond_init failed");
		return false;
	}
	this->arr_pthread_tid = new pthread_t[max];
	bzero(arr_pthread_tid,sizeof(pthread_t)*max);

	this->manage_tid = 0;
	//管理者线程
	if((err = pthread_create(&manage_tid,NULL,ManagerThreadPool,(void*)this) ) > 0)
	{
		//写入日志 todo
		cout<<"create pthread failed err = "<<strerror(err)<<endl;
		return false;
		//cout<<"q"<<endl;
	}

	for(int i=0;i<min;i++)
	{
		//消费者线程
		if((err = pthread_create(&arr_pthread_tid[i],NULL,ConsumeTask,(void*)this)) > 0)
		{
			cout<<"create thread["<<i<<"]"<<"failede err = "<<strerror(err)<<endl;
			return false;
		}
		++thread_alive;
	}
	return true;
}

//test over
bool ThreadPool::DestroyThreadPool()
{
	//cout<<"d"<<endl;
	if(m_instance)
	{
		delete m_instance;
		m_instance = NULL;
	}
	return true;
}

bool ThreadPool::AddTask(void* (*task)(void*),void* arg)
{
	//cout<<"e"<<endl;
	if(!task || shutdown)
		return false;
	pthread_mutex_lock(&lock_task);
	if(queue_cur == queue_max)
		pthread_cond_wait(&not_full,&lock_task);

	if(shutdown)
	{
		pthread_mutex_unlock(&lock_task);
		return false;
	}

	this->task[queue_head].arg = arg;
	this->task[queue_head].task = task;
	queue_head = (queue_head + 1) % queue_max;
	++queue_cur;

	pthread_cond_signal(&not_empty);
	pthread_mutex_unlock(&lock_task);
	return true;
}
/*static int z = 0;
pthread_mutex_t pt;
*/
void* ThreadPool::ConsumeTask(void* arg)
{
	/*pthread_mutex_lock(&pt);	
	z++;
	cout<<"z:"<<z<<endl;
	pthread_mutex_unlock(&pt);
	*/
	if(!arg)
		return NULL;
	ThreadPool* pthis = (ThreadPool*)arg;
	task_t m_task;
	while(!pthis->shutdown)
	{
		pthread_mutex_lock(&pthis->lock_task);
		if(!pthis->queue_cur)
			pthread_cond_wait(&pthis->not_empty,&pthis->lock_task);
		if(pthis->shutdown)
		{
			pthread_mutex_unlock(&pthis->lock_task);
			pthread_exit(NULL);
		}
		if((pthis->thread_kill>0) && (pthis->thread_alive >pthis->thread_min))
		{
			--pthis->thread_alive;
			--pthis->thread_kill;
			pthread_mutex_unlock(&pthis->lock_task);
			pthread_exit(NULL);
		}

		m_task.task = pthis->task[pthis->queue_tail].task;
		m_task.arg = pthis->task[pthis->queue_tail].arg;

		pthis->queue_tail = (pthis->queue_tail + 1) % pthis->queue_max;
		--pthis->queue_cur;

		pthread_cond_signal(&pthis->not_full);
		++pthis->thread_busy;
		pthread_mutex_unlock(&pthis->lock_task);

		(*m_task.task)(m_task.arg);

		pthread_mutex_lock(&pthis->lock_task);
		--pthis->thread_busy;
		pthread_mutex_unlock(&pthis->lock_task);
	}
	return NULL;
}

//判断线程死活 
bool ThreadPool::if_thread_alive(pthread_t pid)
{
	if((pthread_kill(pid,0)) == -1)
	{
		if(errno == ESRCH)
			return false;
	}
	return true;
}

void* ThreadPool::ManagerThreadPool(void* arg)
{
	//cout<<"g"<<endl;
	if(!arg)
		return NULL;
	ThreadPool* pthis = (ThreadPool*)arg;

	int alive;
	int busy;

	while(!pthis->shutdown)
	{
		//cout<<"a"<<endl;
		do{
			alive = pthis->thread_alive;
			busy = pthis->thread_busy;
		}while(!__sync_bool_compare_and_swap(&pthis->thread_busy,busy,busy) || !__sync_bool_compare_and_swap(&pthis->thread_alive,alive,alive));

		if(((float)busy / alive *100 >= (float)70) && (pthis->thread_max >= alive + pthis->thread_min))
		{
			int add = 0;
			for(unsigned int i=0;i<pthis->thread_max;i++)
			{
				pthread_mutex_lock(&pthis->lock_task);
				if(!(pthis->arr_pthread_tid[i]) || !pthis->if_thread_alive(pthis->arr_pthread_tid[i]))
				{
					if((pthread_create(&pthis->arr_pthread_tid[i],NULL,ConsumeTask,(void*)pthis)) > 0)
						return NULL;
					++pthis->thread_alive;
					++add;
				}
				pthread_mutex_unlock(&pthis->lock_task);

				if(add == _DEF_LIMIT)
					break;
			}
		}
		if((busy *2 < alive - busy) && ((unsigned int)alive > (unsigned int)pthis->thread_min))
		{
			pthread_mutex_lock(&pthis->lock_task);
			pthis->thread_kill = _DEF_LIMIT;
			pthread_mutex_unlock(&pthis->lock_task);
			for(int j=0;j<_DEF_LIMIT;j++)
			{
				pthread_cond_signal(&pthis->not_empty);
			}
		}
	
		//cout<<"alive thread num:"<<pthis->thread_alive<<endl;
		sleep(TIME_OUT);
	}
	return NULL;
}
