// SelectMac.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "SelectMac.h"
#include "afxdialogex.h"


// SelectMac 对话框

IMPLEMENT_DYNAMIC(SelectMac, CDialogEx)

SelectMac::SelectMac(CWnd* pParent /*=NULL*/)
	: CDialogEx(SelectMac::IDD, pParent)
	, macid(_T(""))
{

}

SelectMac::~SelectMac()
{
}

void SelectMac::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, macid);
}


BEGIN_MESSAGE_MAP(SelectMac, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &SelectMac::OnBnClickedButton1)
END_MESSAGE_MAP()


// SelectMac 消息处理程序

char* SelectMac::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//函数功能：将字符串从wchar_t*转换成char*，即从unicode字符转换成多字节字符
    return pstr;
}

//查询
void SelectMac::OnBnClickedButton1()
{
	UpdateData();
	SELECTMAC_RQ srq;
	srq.m_nType = _DEF_PROTOCOL_SELECTMAC_RQ;
	char* t = CStringToChar(macid);
	srq.id = *t - '0';
	theApp.GetKernel()->SendData((char*)&srq,sizeof(srq));
}
