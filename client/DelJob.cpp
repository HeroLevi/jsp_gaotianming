// DelJob.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "DelJob.h"
#include "afxdialogex.h"


// DelJob 对话框

IMPLEMENT_DYNAMIC(DelJob, CDialogEx)

DelJob::DelJob(CWnd* pParent /*=NULL*/)
	: CDialogEx(DelJob::IDD, pParent)
	, jobid(_T(""))
	, sedid(_T(""))
{

}

DelJob::~DelJob()
{
}

void DelJob::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, jobid);
	DDX_Text(pDX, IDC_EDIT2, sedid);
}


BEGIN_MESSAGE_MAP(DelJob, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DelJob::OnBnClickedButton1)
END_MESSAGE_MAP()


// DelJob 消息处理程序

char* DelJob::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//函数功能：将字符串从wchar_t*转换成char*，即从unicode字符转换成多字节字符
    return pstr;
}

//删除工件
void DelJob::OnBnClickedButton1()
{
	UpdateData();
	DELJOB_RQ delrq;
	delrq.m_nType = _DEF_PROTOCOL_DELJOB_RQ;
	char* t = CStringToChar(jobid);
	delrq.id = *t -'0';
	t = CStringToChar(sedid);
	delrq.seq = *t - '0';
	theApp.GetKernel()->SendData((char*)&delrq,sizeof(delrq));
}
