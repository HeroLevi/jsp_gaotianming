// DelMatter.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "DelMatter.h"
#include "afxdialogex.h"


// DelMatter 对话框

IMPLEMENT_DYNAMIC(DelMatter, CDialogEx)

DelMatter::DelMatter(CWnd* pParent /*=NULL*/)
	: CDialogEx(DelMatter::IDD, pParent)
	, matterid(_T(""))
	, num(_T(""))
{

}

DelMatter::~DelMatter()
{
}

void DelMatter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, matterid);
	DDX_Text(pDX, IDC_EDIT13, num);
}


BEGIN_MESSAGE_MAP(DelMatter, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DelMatter::OnBnClickedButton1)
END_MESSAGE_MAP()


// DelMatter 消息处理程序

char* DelMatter::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//函数功能：将字符串从wchar_t*转换成char*，即从unicode字符转换成多字节字符
    return pstr;
}

//删除物料
void DelMatter::OnBnClickedButton1()
{
	UpdateData();
	DELMATTER_RQ dmrq;
	dmrq.m_nType = _DEF_PROTOCOL_DELMATTER_RQ;
	char* t = CStringToChar(matterid);
	dmrq.id = *t - '0';
	t = CStringToChar(num);
	dmrq.num = *t - '0';
	theApp.GetKernel()->SendData((char*)&dmrq,sizeof(dmrq));
}
