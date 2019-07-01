#ifndef _PACKDEF_H
#define _PACKDEF_H
#include <vector>

#define SERVER_IP   "192.168.43.47"
#define _DEFPORT    2019
typedef char   PackType;

struct JSP
{
	int mec;//机器号
	int time;//工作时间
};


#define BEGIN_PROTOCOL_MAP static const ProtocolMap m_ProtocolMapEntries[]= \
{

#define END_PROTOCOL_MAP 	{0,0} \
};

#define PM(X,Y)  {X,Y},

//自定义宏
#define _DEF_SIZE 64


#define _register_userexists     0
#define _register_success         1

#define _login_usernotexists      0
#define _login_passworderr       1
#define _login_success           2
#define _user_logining           3

#define _commonuser 0
#define _manager 1
//协议
#define _DEF_PROTOCOL_BASE		50

//登陆协议
#define _DEF_PROTOCOL_LOGIN_RQ	_DEF_PROTOCOL_BASE+1
#define _DEF_PROTOCOL_LOGIN_RS	_DEF_PROTOCOL_BASE+2

//工作请求协议
#define _DEF_PROTOCOL_WORK_RQ	_DEF_PROTOCOL_BASE+3
#define _DEF_PROTOCOL_WORK_RS	_DEF_PROTOCOL_BASE+4

//下单协议

#define _DEF_PROTOCOL_DOWNORDER_RQ	_DEF_PROTOCOL_BASE+5
#define _DEF_PROTOCOL_DOWNORDER_RS	_DEF_PROTOCOL_BASE+6

//添加工件协议
#define _DEF_PROTOCOL_ADDJOB_RQ	_DEF_PROTOCOL_BASE+7
#define _DEF_PROTOCOL_ADDJOB_RS	_DEF_PROTOCOL_BASE+8

//更新工件信息协议
#define _DEF_PROTOCOL_UPDATEJOB_RQ	_DEF_PROTOCOL_BASE+9
#define _DEF_PROTOCOL_UPDATEJOB_RS	_DEF_PROTOCOL_BASE+10

//添加机器信息协议
#define _DEF_PROTOCOL_ADDMEC_RQ	_DEF_PROTOCOL_BASE+11
#define _DEF_PROTOCOL_ADDMEC_RS	_DEF_PROTOCOL_BASE+12

//更新设备协议
#define _DEF_PROTOCOL_UPDATEMEC_RQ	_DEF_PROTOCOL_BASE+13
#define _DEF_PROTOCOL_UPDATEMEC_RS	_DEF_PROTOCOL_BASE+14

//导出甘特图协议
#define _DEF_PROTOCOL_GETGTT_RQ	_DEF_PROTOCOL_BASE+15
#define _DEF_PROTOCOL_GETGTT_RS	_DEF_PROTOCOL_BASE+16

//注册协议
#define _DEF_PROTOCOL_REGISTER_RQ _DEF_PROTOCOL_BASE +17
#define _DEF_PROTOCOL_REGISTER_RS _DEF_PROTOCOL_BASE +18

//修改密码
#define _DEF_PROTOCOL_UPDATEPASS_RQ _DEF_PROTOCOL_BASE +19
#define _DEF_PROTOCOL_UPDATEPASS_RS _DEF_PROTOCOL_BASE +20

//下线
#define _DEF_PROTOCOL_BYEBYE_RQ _DEF_PROTOCOL_BASE +21
#define _DEF_PROTOCOL_BYEBYE_RS _DEF_PROTOCOL_BASE +22

//深搜算法
#define _DEF_PROTOCOL_DFS_RQ _DEF_PROTOCOL_BASE +23
#define _DEF_PROTOCOL_DFS_RS _DEF_PROTOCOL_BASE +24

#define _DEF_PROTOCOL_ADDMATTER_RQ _DEF_PROTOCOL_BASE +25
#define _DEF_PROTOCOL_ADDMATTER_RS _DEF_PROTOCOL_BASE +26

#define _DEF_PROTOCOL_DELMAC_RQ _DEF_PROTOCOL_BASE+27
#define _DEF_PROTOCOL_DELMAC_RS _DEF_PROTOCOL_BASE+28

#define _DEF_PROTOCOL_SELECTMAC_RQ _DEF_PROTOCOL_BASE+29
#define _DEF_PROTOCOL_SELECTMAC_RS _DEF_PROTOCOL_BASE+30

#define _DEF_PROTOCOL_SELECTJOB_RQ _DEF_PROTOCOL_BASE+31
#define _DEF_PROTOCOL_SELECTJOB_RS _DEF_PROTOCOL_BASE+32

#define _DEF_PROTOCOL_DELJOB_RQ _DEF_PROTOCOL_BASE+33
#define _DEF_PROTOCOL_DELJOB_RS _DEF_PROTOCOL_BASE+34

#define _DEF_PROTOCOL_DELMATTER_RQ _DEF_PROTOCOL_BASE+35
#define _DEF_PROTOCOL_DELMATTER_RS _DEF_PROTOCOL_BASE+36

#define _DEF_PROTOCOL_SELECTMATTER_RQ _DEF_PROTOCOL_BASE+37
#define _DEF_PROTOCOL_SELECTMATTER_RS _DEF_PROTOCOL_BASE+38

#define _DEF_PROTOCOL_ORDERDONE_RQ _DEF_PROTOCOL_BASE+39
#define _DEF_PROTOCOL_ORDERDONE_RS _DEF_PROTOCOL_BASE+40

#define _DEF_PROTOCOL_ORDERWAIT_RQ _DEF_PROTOCOL_BASE+41
#define _DEF_PROTOCOL_ORDERWAIT_RS _DEF_PROTOCOL_BASE+42

#define _DEF_PROTOCOL_OUTORDER_RQ _DEF_PROTOCOL_BASE+43
#define _DEF_PROTOCOL_OUTORDER_RS _DEF_PROTOCOL_BASE+44

#define _DEF_PROTOCOL_UPDATEORDER_RQ _DEF_PROTOCOL_BASE+45
#define _DEF_PROTOCOL_UPDATEORDER_RS _DEF_PROTOCOL_BASE+46

//#数据包#

struct UPDATEORDER_RQ
{
	PackType m_nType;
	int id;
	int time;
	int product;
	int num;
};

struct UPDATEORDER_RS
{
	PackType m_nType;
	int res;
};

struct OUTORDER_RQ
{
	PackType m_nType;
	int id;
};

struct OUTORDER_RS
{
	PackType m_nType;
	int res;
};

struct ORDERWAIT_RS
{
	PackType m_nType;
	int time;
	int num;
	int product;
};

struct ORDERDONE_RQ
{
	PackType m_nType;
	int id;
};

struct ORDERDONE_RS
{
	PackType m_nType;
	int num;
	int product;
};

struct SELECTMATTER_RQ
{
	PackType m_nType;
	int id;
};

struct SELECTMATTER_RS
{
	PackType m_nType;
	int num;//余量
};

struct DELMATTER_RQ
{
	PackType m_nType;
	int id;
	int num;
};

struct DELMATTER_RS
{
	PackType m_nType;
	int res;
};

struct DELJOB_RQ
{
	PackType m_nType;
	int id;
	int seq;
};

struct DELJOB_RS
{
	PackType m_nType;
	int res;
};

struct SELECTJOB_RQ
{
	PackType m_nType;
	int id;
	int seq;
};

struct SELECTJOB_RS
{
	PackType m_nType;
	int usemac;
	int time;
};

struct SELECTMAC_RQ
{
	PackType m_nType;
	int id;
};

struct SELECTMAC_RS
{
	PackType m_nType;
	int type;
	int year;
};

//移除机器
struct DELMAC_RQ
{
	PackType m_nType;
	int id;
};

struct DELMAC_RS
{
	PackType m_nType;

};


//添加物料
struct ADDMATTER_RQ
{
	PackType m_nType;
	int id;
	int num;
};

struct ADDMATTER_RS
{
	PackType m_nType;
};

//下订单

struct DOWNORDER_RQ
{
	PackType m_nType;
	int id;//编号
	int time;//限期
	int num;//需求数量
	int product;//产品种类
};

struct DOWNORDER_RS
{
	PackType m_nType;
	int res;
};

//下线
struct BYEBYE_RQ
{
	PackType m_nType;
	char username[_DEF_SIZE];
};

struct BYEBYE_RS
{
	PackType m_nType;
	
};

//修改密码
struct UPDATEPASS_RQ
{
	PackType m_nType;
	char username[_DEF_SIZE];
	char find[_DEF_SIZE];
	char pass[_DEF_SIZE];
	char duppass[_DEF_SIZE];
};

struct UPDATEPASS_RS
{
	PackType m_nType;
	char ack;
};

//注册请求
struct REGISTER_RQ
{
	PackType m_nType;
	char username[_DEF_SIZE];
	char password[_DEF_SIZE];
	char find[_DEF_SIZE];
};

struct REGISTER_RS
{
	PackType m_nType;
	char username[_DEF_SIZE];
	char m_szResult;
};

//获取甘特图文本
struct GetGtt_RQ
{
	PackType m_nType;
};

struct GetGtt_RS
{
	PackType m_nType;
	char buf[512];
};

//更新机器
struct UPDATEMEC_RQ
{
	PackType m_nType;
	int id;
	int year;
	int type;
};

struct UPDATEMEC_RS
{
	PackType m_nType;
	int result;
};

//添加机器
struct ADDMEC_RQ
{
	PackType m_nType;
	int id;
	int type;
	int year;
};

struct ADDMEC_RS
{
	PackType m_nType;
	int result;
};

//添加工件请求
struct ADDJOB_RQ
{
	PackType m_nType;
	int jobi;//工件号
	int seq;//工序号
	int meci;//机器号
	int time;//工作时间
	int type;//工件类型
};

struct ADDJOB_RS
{
	PackType m_nType;
	int type;//工件类型
	int result;
};

//登录
struct LOGIN_RQ
{
	PackType m_nType;
	int flag;
	char username[_DEF_SIZE];
	char password[_DEF_SIZE];
};

struct LOGIN_RS
{
	PackType m_nType;
	char username[_DEF_SIZE];
	char result;
	int flag;
};

//工作
struct WORK_RQ
{
	PackType m_nType;
	int start;
};

struct WORK_RS
{
	PackType m_nType;
	int result;
};


#endif