// DelMac.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "DelMac.h"
#include "afxdialogex.h"


// DelMac 对话框

IMPLEMENT_DYNAMIC(DelMac, CDialogEx)

DelMac::DelMac(CWnd* pParent /*=NULL*/)
	: CDialogEx(DelMac::IDD, pParent)
	, macid(_T(""))
{

}

DelMac::~DelMac()
{
}

void DelMac::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, macid);
}


BEGIN_MESSAGE_MAP(DelMac, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DelMac::OnBnClickedButton1)
END_MESSAGE_MAP()


// DelMac 消息处理程序

char* DelMac::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//函数功能：将字符串从wchar_t*转换成char*，即从unicode字符转换成多字节字符
    return pstr;
}

//移除机器
void DelMac::OnBnClickedButton1()
{
	UpdateData();
	DELMAC_RQ delrq;
	delrq.m_nType = _DEF_PROTOCOL_DELMAC_RQ;
	char* t = CStringToChar(macid);
	delrq.id = *t - '0';
	theApp.GetKernel()->SendData((char*)&delrq,sizeof(delrq));
}
