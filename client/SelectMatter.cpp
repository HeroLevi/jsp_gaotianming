// SelectMatter.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "SelectMatter.h"
#include "afxdialogex.h"


// SelectMatter 对话框

IMPLEMENT_DYNAMIC(SelectMatter, CDialogEx)

SelectMatter::SelectMatter(CWnd* pParent /*=NULL*/)
	: CDialogEx(SelectMatter::IDD, pParent)
	, id(_T(""))
{

}

SelectMatter::~SelectMatter()
{
}

void SelectMatter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id);
}


BEGIN_MESSAGE_MAP(SelectMatter, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &SelectMatter::OnBnClickedButton1)
END_MESSAGE_MAP()


// SelectMatter 消息处理程序

char* SelectMatter::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//函数功能：将字符串从wchar_t*转换成char*，即从unicode字符转换成多字节字符
    return pstr;
}


//查询物料
void SelectMatter::OnBnClickedButton1()
{
	UpdateData();
	SELECTMATTER_RQ smrq;
	smrq.m_nType = _DEF_PROTOCOL_SELECTMATTER_RQ;
	char* t = CStringToChar(id);
	smrq.id = *t - '0';
	theApp.GetKernel()->SendData((char*)&smrq,sizeof(smrq));
}
