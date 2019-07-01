#include "TCPKernel.h"

const ulong population_number = 20; 
const ulong times = 5;
const ulong N = 200;

int machine;          //机器数量
int job;              //工件数量
int process;          //任务总数
int chromosome_size;  //染色体长度


const class Probability {        //概率
	public:
		const double cross = 0.95;   //交叉概率
		const double mutation = 0.05;//变异概率
} probability;

class Matrix {              //矩阵
	public:
		int Machine[N][N] = {}; //job process => machine
		int Time[N][N] = {};    //job process => time
		int Process[N][N] = {}; //job machine => process
		Matrix() {
			fill(Machine[0], Machine[0] + N * N, -1);
			fill(Process[0], Process[0] + N * N, -1);
			fill(Time[0], Time[0] + N * N, 0);
		}
} matrix;

class Gene {     //基因
	public:
		string chromosome = string(static_cast<ulong>(job * machine), '0'); //染色体
		int fitness = 0;                                                    //适应度

		explicit Gene(int fitness) { this->fitness = fitness; };

		Gene() = default;

		Gene(const Gene &other) {
			chromosome = other.chromosome;
			fitness = other.fitness;
		}

		Gene &operator=(const Gene &other) = default;

		bool operator==(const Gene &other) const {
			return chromosome == other.chromosome && fitness == other.fitness;
		}

		bool operator<(const Gene &other) const {
			return chromosome < other.chromosome;
		}
};

vector<Gene> populations;       //种群

class Store {
	public:
		int machineWorkTime[N] = {}; //机器工作时间
		int processIds[N] = {};      //对应任务的工序
		int endTime[N][N] = {};      //job process => endtime
		int startTime[N][N] = {};    //job process => starttime
		Store() = default;

		Store(const Store &other) {
			copy(begin(other.machineWorkTime), end(other.machineWorkTime), begin(machineWorkTime));
			copy(begin(other.processIds), end(other.processIds), begin(processIds));
			copy(other.endTime[0], other.endTime[0] + N * N, endTime[0]);
			copy(other.startTime[0], other.startTime[0] + N * N, startTime[0]);
		}

		Store &operator=(const Store &other) {
			copy(begin(other.machineWorkTime), end(other.machineWorkTime), begin(machineWorkTime));
			copy(begin(other.processIds), end(other.processIds), begin(processIds));
			copy(other.endTime[0], other.endTime[0] + N * N, endTime[0]);
			copy(other.startTime[0], other.startTime[0] + N * N, startTime[0]);
			return *this;
		}
};

/**
 * 产生 start到end的随机整数
 * @param start
 * @param end
 * @return
 */
ulong randint(ulong start, ulong end) {
	return rand() % (end - start + 1) + start;
}

/**
 * 产生 0 到 end的随机整数
 * @param end
 * @return
 */
ulong randint(ulong end) {
	return rand() % (end + 1);
}

/**
 * char => int
 * @param ch
 * @return
 */
int Int(char ch) {
	return ch - '0';
}

/**
 *int => char
 * @param i
 * @return
 */
char Char(int i) {
	return static_cast<char>(i + '0');
}

/**
 * 将vector填充整数
 * @param v
 * @param length
 * @param except
 */
void generateVector(vector<int> &v, int length, int except = -1) {
	for (int i = 0; i < length; i++) {
		if (except != -1 && i == except) 
			continue;
		v.push_back(i);
	}
	cout<<"generateVector run end"<<endl;
}

/**
 * 计算适应度
 * @param gene
 * @param store
 */
void calculateFitness(Gene &gene, Store &store) {
	int fulfillTime = 0;
	for (char i : gene.chromosome) {
		int jobId = Int(i) - 1,
			processId = store.processIds[jobId],
			machineId = matrix.Machine[jobId][processId],
			time = matrix.Time[jobId][processId];
			//	cout<<"jobId:"<<processId<<endl;
			//	cout<<"processId:"<<processId<<endl;
			//	cout<<"machineId:"<<machineId<<endl;
			//	cout<<"time:"<<time<<endl;

			store.processIds[jobId]++;
			store.startTime[jobId][processId] = processId == 0 ? store.machineWorkTime[machineId] : max(store.endTime[jobId][processId - 1],       store.machineWorkTime[machineId]);
			store.machineWorkTime[machineId] = store.startTime[jobId][processId] + time;
			store.endTime[jobId][processId] = store.machineWorkTime[machineId];
			if (store.machineWorkTime[machineId] > fulfillTime) {
				fulfillTime = store.machineWorkTime[machineId];
			}
	}
	gene.fitness = fulfillTime;
}

/**
 * 初始化种群
 * @param genes 
 * @param population 
 */
void initializePopulation(vector<Gene> &genes, int population) {
	set<Gene> gs;
	for (int i = 0; i < population; i++)
	{
		vector<int> index_list;
		generateVector(index_list, job * machine);
		cout<<"job:"<<job<<endl;
		cout<<"machine:"<<machine<<endl;

		Gene gene;
		for (int j = 1; j <= job; j++) {
			for (int k = 0; k < machine; k++) {
				ulong index = randint(index_list.size() - 1);
				int value = index_list[index];
				index_list.erase(index_list.begin() + index);
				if (matrix.Process[j - 1][k] != -1)
					gene.chromosome[value] = Char(j);
			}
		}
		remove_if(gene.chromosome.begin(), gene.chromosome.end(), [](char v) -> bool { return v == '0'; });
		gene.chromosome.resize(static_cast<ulong>(chromosome_size));
		Store store;
		calculateFitness(gene, store);
		gs.insert(gene);
	}
	insert_iterator<vector<Gene>> insert_vector(genes, genes.begin());
	copy(gs.begin(), gs.end(), insert_vector);
}

/**
 * 基因突变
 * @param gene 
 * @param n 
 */
void geneticMutation(Gene &gene, int n = 2) {
	vector<int> index_list;
	generateVector(index_list, chromosome_size);
	for (int i = 0; i < n; i++) {
		ulong first = randint(0, index_list.size() - 1);
		index_list.erase(index_list.begin() + first);
		ulong second = randint(0, index_list.size() - 1);
		swap(gene.chromosome[first], gene.chromosome[second]);
	}
	Store store;
	calculateFitness(gene, store);
}

/**
 * 基因交叉
 * @param first 
 * @param second 
 * @return 
 */
pair<Gene, Gene> orderCrossover(Gene &first, Gene &second) {
	function<Gene(Gene &, Gene &)> generateChild = [](Gene &first, Gene &second) -> Gene {
		vector<int> index_list;
		generateVector(index_list, chromosome_size);

		ulong start = randint(0, index_list.size() - 1);
		index_list.erase(index_list.begin() + start);
		ulong end = randint(0, index_list.size() - 1);

		string middle = first.chromosome.substr(start, end - start),
			   t = middle,
			   k = second.chromosome;
		for (char &it : t) {
			for (unsigned int i = 0; i < k.size(); i++) {
				if (k[i] == it) {
					k.erase(k.begin() + i);
					break;
				}
			}
		}
		Gene child;
		child.chromosome = k.substr(0, start) + middle + k.substr(start, k.length() - start);
		Store store;
		calculateFitness(child, store);
		return child;
	};
	pair<Gene, Gene> child;
	child.first = generateChild(first, second);
	child.second = generateChild(second, first);
	return child;
}

/**
 * 选择个体
 * @param n 
 * @return 
 */
Gene selectIndividual(int n = 3) {
	vector<int> index_list;
	generateVector(index_list, population_number);
	vector<Gene> simple;
	for (int i = 0; i < n; i++) {
		ulong index = randint(index_list.size() - 1);
		index_list.erase(index_list.begin() + index);
		simple.push_back(populations[index]);
	}
	Gene best_gene(0xffffff);
	for (int i = 1; i < n; i++) {
		if (simple[i].fitness < best_gene.fitness) {
			best_gene = simple[i];
		}
	}
	return best_gene;
}

TCPKernel::TCPKernel()
{
	num = 0;
	m_pTCPNet = new TCPNet(this);
	m_threadpool = ThreadPool::GetInstance();
}

TCPKernel::~TCPKernel()
{
	if(m_pTCPNet)
	{
		delete m_pTCPNet;
		m_pTCPNet = NULL;
	}
}

//协议映射表
	BEGIN_PROTOCOL_MAP
	PM(_DEF_PROTOCOL_LOGIN_RQ,&TCPKernel::LoginRq)//登录
	PM(_DEF_PROTOCOL_WORK_RQ,&TCPKernel::WorkRq)//遗传算法工作
	PM(_DEF_PROTOCOL_DOWNORDER_RQ,&TCPKernel::DownOrder)//下订单
	PM(_DEF_PROTOCOL_ADDJOB_RQ,&TCPKernel::AddJob)//添加工件
	PM(_DEF_PROTOCOL_UPDATEJOB_RQ,&TCPKernel::UpdateJob)//更新工件
	PM(_DEF_PROTOCOL_ADDMEC_RQ,&TCPKernel::AddMec)//添加机器
	PM(_DEF_PROTOCOL_UPDATEMEC_RQ,&TCPKernel::UpdateMec)//更新机器
	PM(_DEF_PROTOCOL_GETGTT_RQ,&TCPKernel::Getggt)//获取甘特图
	PM(_DEF_PROTOCOL_REGISTER_RQ,&TCPKernel::RegisterRq)//注册
	PM(_DEF_PROTOCOL_UPDATEPASS_RQ,&TCPKernel::Updatepass)//更新密码
	PM(_DEF_PROTOCOL_BYEBYE_RQ,&TCPKernel::ByeBye)//下线通知
	PM(_DEF_PROTOCOL_DFS_RQ,&TCPKernel::DFS)//深搜工作
	PM(_DEF_PROTOCOL_ADDMATTER_RQ,&TCPKernel::AddMatter)//添加物料
	PM(_DEF_PROTOCOL_DELMAC_RQ,&TCPKernel::DelMac)//删除机器
	PM(_DEF_PROTOCOL_SELECTMAC_RQ,&TCPKernel::SelectMac)//查询机器
	PM(_DEF_PROTOCOL_SELECTJOB_RQ,&TCPKernel::SelectJob)//查询工件
	PM(_DEF_PROTOCOL_DELJOB_RQ,&TCPKernel::DelJob)//移除工件对应工序
	PM(_DEF_PROTOCOL_DELMATTER_RQ,&TCPKernel::DelMatter)//调拨物料
	PM(_DEF_PROTOCOL_SELECTMATTER_RQ,&TCPKernel::SelectMatter)//查找物料
	PM(_DEF_PROTOCOL_ORDERDONE_RQ,&TCPKernel::DoneOrderS)//查看已处理订单
	PM(_DEF_PROTOCOL_ORDERWAIT_RQ,&TCPKernel::Look)//看未处理订单
	PM(_DEF_PROTOCOL_OUTORDER_RQ,&TCPKernel::OutOrder)//退单
	PM(_DEF_PROTOCOL_UPDATEORDER_RQ,&TCPKernel::UpdateOrder)//修改订单
	END_PROTOCOL_MAP

void TCPKernel::UpdateOrder(int sock,char* szbuf)
{
	UPDATEORDER_RQ *p = (UPDATEORDER_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select time from orderInfo where id = %d",p->id);
	m_sql.SelectMySql(szsql,1,lstStr);
	UPDATEORDER_RS rs;
	if(lstStr.size() > 0)
	{
		bzero(&szsql,sizeof(szsql));
		sprintf(szsql,"update orderInfo set time =%d,product=%d,num=%d where id = %d",p->time,p->product,p->num,p->id);
		m_sql.UpdateMySql(szsql);
		rs.res = 1;
	}
	else
	{
		rs.res = -1;
	}
	rs.m_nType = _DEF_PROTOCOL_UPDATEORDER_RS;
	lstStr.clear();
	m_pTCPNet->SendData(sock,(char*)&rs,sizeof(rs));
}

void TCPKernel::OutOrder(int sock,char* szbuf)
{
	OUTORDER_RQ* p = (OUTORDER_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select time from orderInfo where id = %d",p->id);
	m_sql.SelectMySql(szsql,1,lstStr);
	OUTORDER_RS rs;
	if(lstStr.size() > 0)
	{
		bzero(&szsql,sizeof(szsql));
		sprintf(szsql,"delete from orderInfo where id = %d",p->id);
		m_sql.UpdateMySql(szsql);
		rs.res = 1;
	}
	else
	{
		rs.res = -1;
	}
	rs.m_nType = _DEF_PROTOCOL_OUTORDER_RS;
	lstStr.clear();
	m_pTCPNet->SendData(sock,(char*)&rs,sizeof(rs));
}

void TCPKernel::Look(int sock,char* szbuf)
{
	ORDERDONE_RQ* p = (ORDERDONE_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select time from orderInfo where id = %d",p->id);
	m_sql.SelectMySql(szsql,1,lstStr);
	ORDERWAIT_RS rs;
	rs.m_nType = _DEF_PROTOCOL_ORDERWAIT_RS;
	if(lstStr.size() > 0)
	{
		rs.time = stoi(lstStr.front());
		bzero(&szsql,sizeof(szsql));
		lstStr.clear();
		sprintf(szsql,"select product from orderInfo where id = %d",p->id);
		m_sql.SelectMySql(szsql,1,lstStr);
		rs.product = stoi(lstStr.front());
		lstStr.clear();
		bzero(&szsql,sizeof(szsql));
		sprintf(szsql,"select num from orderInfo where id = %d",p->id);
		m_sql.SelectMySql(szsql,1,lstStr);
		rs.num = stoi(lstStr.front());
		lstStr.clear();
	}
	else
	{
		rs.time = -1;
		rs.product = -1;
		rs.num = -1;
	}
	m_pTCPNet->SendData(sock,(char*)&rs,sizeof(rs));
}

void TCPKernel::DoneOrderS(int sock,char* szbuf)
{
	ORDERDONE_RQ *p = (ORDERDONE_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select product from orderdone where id = %d",p->id);
	m_sql.SelectMySql(szsql,1,lstStr);
	ORDERDONE_RS rs;
	rs.m_nType = _DEF_PROTOCOL_ORDERDONE_RS;
	if(lstStr.size() > 0)
	{
		rs.product = stoi(lstStr.front());
		lstStr.clear();
		bzero(&szsql,sizeof(szsql));
		sprintf(szsql,"select num from orderdone where id = %d",p->id);
		m_sql.SelectMySql(szsql,1,lstStr);
		rs.num = stoi(lstStr.front());
		lstStr.clear();
	}
	else
	{
		rs.num = -1;
		rs.product = -1;
	}
	m_pTCPNet->SendData(sock,(char*)&rs,sizeof(rs));
}

//查询物料
void TCPKernel::SelectMatter(int sock,char* szbuf)
{
	SELECTMATTER_RQ* p = (SELECTMATTER_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select num from matter where id = %d",p->id);
	m_sql.SelectMySql(szsql,1,lstStr);
	SELECTMATTER_RS rs;
	rs.m_nType = _DEF_PROTOCOL_SELECTMATTER_RS;
	if(lstStr.size() >0)
	{
		rs.num = stoi(lstStr.front());
	}
	else
	{
		rs.num = -1;
	}
	lstStr.clear();
	m_pTCPNet->SendData(sock,(char*)&rs,sizeof(rs));
}

void TCPKernel::DelMatter(int sock,char* szbuf)
{
	DELMATTER_RQ* p = (DELMATTER_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select num from matter where id = %d",p->id);
	m_sql.SelectMySql(szsql,1,lstStr);
	DELMATTER_RS rs;
	rs.m_nType = _DEF_PROTOCOL_DELMATTER_RS;
	if(lstStr.size() > 0)
	{
		if(stoi(lstStr.front()) >= p->num)
		{
			int m_num = stoi(lstStr.front()) - p->num;
			bzero(&szsql,sizeof(szsql));
			sprintf(szsql,"update matter set num = %d where id = %d",m_num,p->id);
			m_sql.UpdateMySql(szsql);
			rs.res = 1;
		}
		else
		{
			rs.res = -1;//余量不足
		}
	}
	else
	{
		rs.res = 0;//没有这个物料
	}
	lstStr.clear();
	m_pTCPNet->SendData(sock,(char*)&rs,sizeof(rs));
}

void TCPKernel::DelJob(int sock,char* szbuf)
{
	DELJOB_RQ* p = (DELJOB_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select id from jobinfo where id = %d and seq = %d",p->id,p->seq);
	m_sql.SelectMySql(szsql,1,lstStr);
	DELJOB_RS rs;
	rs.m_nType = _DEF_PROTOCOL_DELJOB_RS;
	if(lstStr.size() > 0)
	{
		bzero(&szsql,sizeof(szsql));
		sprintf(szsql,"delete from jobinfo where id = %d and seq = %d",p->id,p->seq);
		m_sql.UpdateMySql(szsql);
		rs.res = 1;
	}
	else
	{
		rs.res = 0;
	}
	lstStr.clear();
	m_pTCPNet->SendData(sock,(char*)&rs,sizeof(rs));
}

void TCPKernel::SelectJob(int sock,char* szbuf)
{
	SELECTJOB_RQ* p = (SELECTJOB_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select usemec from jobinfo where id = %d and seq = %d",p->id,p->seq);
	m_sql.SelectMySql(szsql,1,lstStr);
	SELECTJOB_RS rs;
	rs.m_nType = _DEF_PROTOCOL_SELECTJOB_RS;
	if(lstStr.size() > 0)
	{
		rs.usemac = stoi(lstStr.front());
		lstStr.clear();
		bzero(&szsql,sizeof(szsql));
		sprintf(szsql,"select time from jobinfo where id = %d and seq = %d",p->id,p->seq);
		m_sql.SelectMySql(szsql,1,lstStr);
		rs.time = stoi(lstStr.front());
	}
	else
	{
		rs.usemac = -1;
		rs.time = -1;
	}
	lstStr.clear();
	m_pTCPNet->SendData(sock,(char*)&rs,sizeof(rs));
}

void TCPKernel::SelectMac(int sock,char* szbuf)
{
	SELECTMAC_RQ* p = (SELECTMAC_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select type from mecinfo where id = %d",p->id);
	cout<<"p->id"<<p->id<<endl;
	m_sql.SelectMySql(szsql,1,lstStr);
	SELECTMAC_RS rs;
	rs.m_nType = _DEF_PROTOCOL_SELECTMAC_RS;
	if(lstStr.size() > 0)
	{
		rs.type = stoi(lstStr.front());
		cout<<"rs.type"<<rs.type<<endl;
		lstStr.clear();
		bzero(&szsql,sizeof(szsql));
		sprintf(szsql,"select year from mecinfo where id = %d",p->id);
		m_sql.SelectMySql(szsql,1,lstStr);
		rs.year = stoi(lstStr.front());
	}
	else
	{
		rs.type = -1;
		rs.year = -1;
	}
	
	lstStr.clear();
	m_pTCPNet->SendData(sock,(char*)&rs,sizeof(rs));
}

void TCPKernel::DelMac(int sock,char* szbuf)
{
	DELMAC_RQ* p = (DELMAC_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"delete from mecinfo where id = %d",p->id);
	m_sql.UpdateMySql(szsql);
	DELMAC_RS rs;
	rs.m_nType = _DEF_PROTOCOL_DELMAC_RS;
	m_pTCPNet->SendData(sock,(char*)&rs,sizeof(rs));
}

void TCPKernel::AddMatter(int sock,char* szbuf)
{
	ADDMATTER_RQ *p = (ADDMATTER_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"insert into matter values(%d,%d)",p->id,p->num);
	m_sql.UpdateMySql(szsql);
	ADDMATTER_RQ rs;
	rs.m_nType = _DEF_PROTOCOL_ADDMATTER_RS;
	m_pTCPNet->SendData(sock,(char*)&rs,sizeof(rs));
}

void TCPKernel::DFS(int sock,char* szbuf)
{
	DFS_RQ* p = (DFS_RQ*)szbuf;
	(void*)p;	
	DFS_RS rs;
	rs.m_nType = _DEF_PROTOCOL_DFS_RS;
	rs.result = 1;
	m_pTCPNet->SendData(sock,(char*)&rs,sizeof(rs));
}

void TCPKernel::DownOrder(int sock,char* szbuf)
{
	DOWNORDER_RQ* dorq = (DOWNORDER_RQ*)szbuf;
	DOWNORDER_RS dors;
	char szsql[_DEF_SQLLEN];
	//去数据库检查是否物料和机器耐久是否足够

	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select* from matter");
	m_sql.SelectMySql(szsql,1,lstStr);
	lstStr.clear();

	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"insert into orderInfo values(%d,%d,%d,%d)",dorq->id,dorq->time,dorq->num,dorq->product);
	m_sql.UpdateMySql(szsql);
	dors.m_nType = _DEF_PROTOCOL_DOWNORDER_RS;
	dors.res = 1;
	m_pTCPNet->SendData(sock,(char*)&dors,sizeof(dors));
}

void TCPKernel::ByeBye(int sock,char* szbuf)
{
	BYEBYE_RQ* p = (BYEBYE_RQ*)szbuf;

	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select username from userinfo where username = '%s'",p->username);
	m_sql.SelectMySql(szsql,1,lstStr);

	if(lstStr.size() > 0)
	{
		bzero(&szsql,sizeof(szsql));
		sprintf(szsql,"delete from onlineuser where username = '%s'",p->username);
		m_sql.UpdateMySql(szsql);
	}
	lstStr.clear();

	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select username from managerinfo where username = '%s'",p->username);
	m_sql.SelectMySql(szsql,1,lstStr);

	if(lstStr.size() > 0)
	{
		bzero(&szsql,sizeof(szsql));
		sprintf(szsql,"delete from onlineuser where username = '%s'",p->username);
		m_sql.UpdateMySql(szsql);
	}
	lstStr.clear();
	BYEBYE_RS rs;
	rs.m_nType = _DEF_PROTOCOL_BYEBYE_RQ;
	m_pTCPNet->SendData(sock,(char*)&rs,sizeof(rs));
}

void TCPKernel::Updatepass(int sock,char* szbuf)
{
	UPDATEPASS_RQ* udpsrq = (UPDATEPASS_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	sprintf(szsql,"select '%s' from userinfo where username = '%s'",udpsrq->find,udpsrq->username);
	list<string> lstStr;
	m_sql.SelectMySql(szsql,1,lstStr);
	UPDATEPASS_RS udpsrs;
	udpsrs.m_nType = _DEF_PROTOCOL_UPDATEPASS_RS;

	//如果没有名字和对应的找回码
	if(lstStr.size() == 0)
	{
		udpsrs.ack = 0;
	}
	else
	{
		if(strcmp(udpsrq->pass,udpsrq->duppass) == 0)
		{
			udpsrs.ack = 2;
			char szsql[_DEF_SQLLEN];
			sprintf(szsql,"update userinfo set password = '%s' where username = '%s'",udpsrq->pass,udpsrq->username);
			m_sql.UpdateMySql(szsql);
		}
		else
		{
			udpsrs.ack = 1;
		}
	}
	m_pTCPNet->SendData(sock,(char*)&udpsrs,sizeof(udpsrs));
}


void TCPKernel::RegisterRq(int sock,char* szbuf)
{
	REGISTER_RQ *psrr = (REGISTER_RQ*)szbuf;

	char szsql[_DEF_SQLLEN];
	REGISTER_RS srr;
	srr.m_nType = _DEF_PROTOCOL_REGISTER_RS;
	memcpy(srr.username,psrr->username,_DEF_SIZE);

	list<string> lstStr;
	//查询数据库中是否有这个人
	sprintf(szsql,"select '%s' from userinfo where username = '%s'",psrr->username,psrr->username);
	m_sql.SelectMySql(szsql,1,lstStr);
	//如果没有可以插入
	if(lstStr.size() == 0)
	{
		srr.m_szResult = _register_success;
		sprintf(szsql,"insert into userinfo values('%s','%s','%s')",psrr->username,psrr->password,psrr->find);
		m_sql.UpdateMySql(szsql);
	}
	else
	{
		srr.m_szResult = _register_userexists;
	}
	m_pTCPNet->SendData(sock,(char*)&srr,sizeof(srr));
}


unsigned long TCPKernel::get_file_size(const char *filename)  
{  
	unsigned long size;  
	FILE* fp = fopen( filename, "rb" );  
	if(fp==NULL)  
	{  
		printf("ERROR: Open file %s failed.\n", filename);  
		return 0;  
	}  
	fseek( fp, SEEK_SET, SEEK_END );  
	size=ftell(fp);  
	fclose(fp);  
	return size;  

}
void TCPKernel::Getggt(int sock,char* szbuf)
{
	GetGtt_RS ps;
	//将文件发送给客户端

	int fd = open("local.txt",O_WRONLY|O_CREAT|O_TRUNC,0777);
	for(int i=0;i<512;i++)
	{
		ps.buf[i] = -1;
	}
	for(unsigned int i=0;i<v.size();i++)
	{
		vector<char> m_tmp;
		for(unsigned int j=0;j<v[i].size();j++)
		{
			cout<<v[i][j]-'\0'<<" ";
		}
		cout<<endl;
	}


	close(fd);
	fd = open("local.txt",O_RDONLY,0777);
	unsigned long size = get_file_size("local.txt");
	read(fd,ps.buf,size);
	close(fd);
	int i =0;
	while(ps.buf[i] != -1)
	{
		i++;
	}

	ps.m_nType = _DEF_PROTOCOL_GETGTT_RS;
	m_pTCPNet->SendData(sock,(char*)&ps,sizeof(ps));
}

void TCPKernel::UpdateMec(int sock,char* szbuf)
{
	UPDATEMEC_RQ* p = (UPDATEMEC_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select * from mecinfo where id = %d",p->id);
	m_sql.SelectMySql(szsql,1,lstStr);
	UPDATEMEC_RS ps;
	ps.m_nType = _DEF_PROTOCOL_UPDATEMEC_RS;
	if(lstStr.size() > 0)
	{
		bzero(&szsql,sizeof(szsql));
		sprintf(szsql,"update mecinfo set type=%d,year=%d where id = %d",p->type,p->year,p->id);
		m_sql.UpdateMySql(szsql);
		lstStr.clear();
		ps.result = 1;
	}
	else
	{
		ps.result = 0;
	}
	m_pTCPNet->SendData(sock,(char*)&ps,sizeof(ps));
}

void TCPKernel::AddMec(int sock,char* szbuf)
{
	ADDMEC_RQ* p = (ADDMEC_RQ*) szbuf;
	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select * from mecinfo where id = %d",p->id);
	ADDMEC_RS ps;
	ps.m_nType = _DEF_PROTOCOL_ADDMEC_RS;
	if(lstStr.size() > 0)
	{
		ps.result = 0;
		lstStr.clear();
	}
	else
	{
		bzero(&szsql,sizeof(szsql));
		sprintf(szsql,"insert into mecinfo values(%d,%d,%d)",p->id,p->type,p->year);
		m_sql.UpdateMySql(szsql);
		ps.result = 1;
	}
	m_pTCPNet->SendData(sock,(char*)&ps,sizeof(ps));
}

void TCPKernel::UpdateJob(int sock,char* szbuf)
{
	ADDJOB_RQ* p = (ADDJOB_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select * from jobinfo where id = %d",p->jobi);
	m_sql.SelectMySql(szsql,1,lstStr);
	ADDJOB_RS ps;
	ps.m_nType = _DEF_PROTOCOL_UPDATEJOB_RS;
	if(lstStr.size() > 0)
	{
		bzero(&szsql,sizeof(szsql));
		sprintf(szsql,"update jobinfo set type=%d ,usemec=%d, time=%d where id = %d and seq = %d",p->type,p->meci,p->time,p->jobi,p->seq);
		m_sql.UpdateMySql(szsql);
		ps.result = 1;
		m_pTCPNet->SendData(sock,(char*)&ps,sizeof(ps));
		lstStr.clear();
	}
	else
	{
		ps.result = 0;
		m_pTCPNet->SendData(sock,(char*)&ps,sizeof(ps));
	}
}

void TCPKernel::AddJob(int sock,char* szbuf)
{
	ADDJOB_RQ* p = (ADDJOB_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"insert into jobinfo values(%d,%d,%d,%d,%d)",p->jobi,p->type,p->seq,p->meci,p->time);
	m_sql.UpdateMySql(szsql);
	ADDJOB_RS ps;
	ps.m_nType = _DEF_PROTOCOL_ADDJOB_RS;
	ps.result = 1;
	ps.type = p->type;
	m_pTCPNet->SendData(sock,(char*)&ps,sizeof(ps));
}

void TCPKernel::WorkRq(int sock,char* szbuf)
{
	WORK_RQ * pslr = (WORK_RQ*)szbuf;
	if(!pslr->start)
		return;
	WORK_RS slr;
	slr.m_nType = _DEF_PROTOCOL_WORK_RS;

	//计算结果
	/******************************************************/
	srand(static_cast<uint>(time(nullptr)));
	chromosome_size = 0;

	v.clear();

	char szsql[_DEF_SQLLEN];
	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select count(distinct id) from jobinfo");
	m_sql.SelectMySql(szsql,1,lstStr);
	job = stoi(lstStr.front());//工件数
	lstStr.clear();

	bzero(&szsql,sizeof(szsql));
	sprintf(szsql,"select count(distinct id) from mecinfo");
	m_sql.SelectMySql(szsql,1,lstStr);
	machine = stoi(lstStr.front());//设备数

	lstStr.clear();


	for (int i = 0; i < job; i++) 
	{
		int p;
		cout << "input job" << i << " process:" << endl;

		bzero(&szsql,sizeof(szsql));
		sprintf(szsql,"select count(*) from jobinfo where id = %d",i+1);
		m_sql.SelectMySql(szsql,1,lstStr);
		p = stoi(lstStr.front());//工序数
		lstStr.clear();

		chromosome_size += p;
		if (process < p) 
			process = p;

		cout << "input machine and time:" << endl;

		list<string> lst;
		int flag = 1;
		list<string>::iterator ite;	
		list<string>::iterator itelst;

		for (int j = 0; j < p; j++) 
		{
			int m, t;
			if(flag)
			{	
				bzero(&szsql,sizeof(szsql));
				sprintf(szsql,"select usemec from jobinfo where id = %d",i+1);
				m_sql.SelectMySql(szsql,1,lstStr);


				bzero(&szsql,sizeof(szsql));
				sprintf(szsql,"select time from jobinfo where id = %d",i+1);
				m_sql.SelectMySql(szsql,1,lst);
				flag = 0;
				ite = lstStr.begin();
				itelst = lst.begin();
			}
			m = stoi(*ite);//机器

			t = stoi(*itelst);//时间

			matrix.Machine[i][j] = m;
			matrix.Time[i][j] = t;
			ite++;
			itelst++;
		}
		lstStr.clear();
	} 

	for (int i = 0; i < job; i++) {
		for (int j = 0; j < process; j++) {
			if (matrix.Machine[i][j] != -1)
				matrix.Process[i][matrix.Machine[i][j]] = j;
		}
	}


	initializePopulation(populations, population_number);    //初始化种群
	ulong n = times;

	while (n-- > 0) 
	{
		cout << "n = " << n << endl;
		double P = randint(0, 100) / 100.0;
		if (P < probability.mutation)
		{
			ulong index = randint(populations.size() - 1); 
			geneticMutation(populations[index]);
		} 
		else 
		{
			ulong size = populations.size();
			ulong m = size / 4;
			set<Gene> children;
			while (m-- > 0) 
			{
				Gene father = selectIndividual();
				Gene mother = selectIndividual();
				pair<Gene, Gene> child = orderCrossover(father, mother);
				children.insert(child.first);
				children.insert(child.second);
			}
			sort(populations.begin(), populations.end(),
					[](const Gene &a, const Gene &b) -> bool { return a.fitness < b.fitness; });
			populations.resize(size - size / 4);
			for (const auto &it : children) {
				populations.push_back(it);
			}
			sort(populations.begin(), populations.end());
			auto iter = unique(populations.begin(), populations.end());
			populations.resize(static_cast<ulong>(distance(populations.begin(), iter)));
		}
	}
	Gene best_gene(0xffffff);
	for (const auto &it : populations) {
		cout << "chromosome = " << it.chromosome << " " << it.fitness << endl;
		if (best_gene.fitness > it.fitness) {
			best_gene = it;
		}
	}

	Store store;
	cout << "result = " << best_gene.chromosome << " time = " << best_gene.fitness << endl;

	for(int z=0;z<job;z++)
	{
		vector<char> m_tmp;
		for(int s=0;s<best_gene.fitness;s++)
		{
			m_tmp.push_back(0);
		}
		v.push_back(m_tmp);
	}
	int fd = open("log",O_WRONLY|O_CREAT|O_APPEND,0777);
//	dup2(fd, STDIN_FILENO);
//	dup2(fd, STDOUT_FILENO);
//	dup2(fd, STDERR_FILENO);

	calculateFitness(best_gene, store);
	for (int i = 0; i < machine; i++) {
		cout << "machine" << i << " work time " << store.machineWorkTime[i] << endl;
	}


	for (int j = 0; j < job; j++) {
		for (int k = 0; k < process; k++) {
			if (matrix.Machine[j][k] != -1)
				cout << "job" << j << " process" << k << " machine" << matrix.Machine[j][k] << " start time="<< store.startTime[j][k] << " end time=" << store.endTime[j][k] << endl;

			for(int w=store.startTime[j][k];w<store.endTime[j][k];w++)
			{
				int g1 = matrix.Machine[j][k];
				v[g1][w] = j+1;
			}
		}
	}
	cout<<endl;
	close(fd);


	/*****************************************************/
	m_pTCPNet->SendData(sock,(char*)&slr,sizeof(slr));
}

void TCPKernel::LoginRq(int sock,char* szbuf)
{
	LOGIN_RQ * pslr = (LOGIN_RQ*)szbuf;
	char szsql[_DEF_SQLLEN];
	LOGIN_RS slr;
	slr.m_nType = _DEF_PROTOCOL_LOGIN_RS;
	memcpy(slr.username,pslr->username,_DEF_SIZE);
	slr.result = _login_usernotexists;

	bzero(&szsql,sizeof(szsql));
	if(pslr->flag)
	{
		sprintf(szsql,"select password from managerinfo where username = '%s'",pslr->username);
	}
	else
	{
		sprintf(szsql,"select password from userinfo where username = '%s'",pslr->username);
	}
	slr.flag = pslr->flag;
	m_sql.SelectMySql(szsql,1,lstStr);
	if(lstStr.size() > 0)
	{
		slr.result = _login_passworderr;
		string strpassword = lstStr.front();
		lstStr.pop_front();
		if(0 == strcmp(strpassword.c_str(),pslr->password))
		{
			lstStr.clear();
			bzero(&szsql,sizeof(szsql));
			sprintf(szsql,"select username from onlineuser where username = '%s'",pslr->username);
			m_sql.SelectMySql(szsql,1,lstStr);
			if(lstStr.size() > 0)
			{
				slr.result = _user_logining;
			}
			else
			{
				bzero(&szsql,sizeof(szsql));
				sprintf(szsql,"insert into onlineuser values('%s')",pslr->username);
				m_sql.UpdateMySql(szsql);
				slr.result = _login_success;
			}
		}
		lstStr.clear();
	}
	m_pTCPNet->SendData(sock,(char*)&slr,sizeof(slr));
}

bool TCPKernel::Open()
{
	pthread_mutex_init(&mutex,NULL);
	//连接数据库
	if(!m_sql.ConnectMySql((char*)"localhost",(char*)"root",(char*)"colin123",(char*)"jsp"))
	{
		return false;
	}

	//加载线程池
	if(!m_threadpool->InitThreadPool(100,2,100))
	{
		return false;
	}
	//连接网络
	if(!m_pTCPNet->InitNetWork())
	{
		return false;
	}
	return true;
}

void TCPKernel::Close()
{
	m_pTCPNet->UnInitNetWork();
	m_threadpool->DestroyThreadPool();
}

void TCPKernel::DealData(int sock,char* szbuf)
{
	PackType* pType = (PackType*)szbuf;
	int i =0;
	while(1)
	{
		if(m_ProtocolMapEntries[i].m_nType ==  *pType)
		{
			(this->*m_ProtocolMapEntries[i].m_pfun)(sock,szbuf);
			break;
		}
		else if(m_ProtocolMapEntries[i].m_nType ==0 || m_ProtocolMapEntries[i].m_pfun ==0)
			break;

		i++;
	}
}
