// LookOrder.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "LookOrder.h"
#include "afxdialogex.h"


// LookOrder 对话框

IMPLEMENT_DYNAMIC(LookOrder, CDialogEx)

LookOrder::LookOrder(CWnd* pParent /*=NULL*/)
	: CDialogEx(LookOrder::IDD, pParent)
	, id(_T(""))
{

}

LookOrder::~LookOrder()
{
}

void LookOrder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id);
}


BEGIN_MESSAGE_MAP(LookOrder, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &LookOrder::OnBnClickedButton1)
END_MESSAGE_MAP()


// LookOrder 消息处理程序

char* LookOrder::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//函数功能：将字符串从wchar_t*转换成char*，即从unicode字符转换成多字节字符
    return pstr;
}

//查找订单
void LookOrder::OnBnClickedButton1()
{
	UpdateData();
	char* t = CStringToChar(id);
	ORDERDONE_RQ odrq;
	odrq.m_nType = _DEF_PROTOCOL_ORDERDONE_RQ;
	odrq.id = *t - '0';
	theApp.GetKernel()->SendData((char*)&odrq,sizeof(odrq));
}
