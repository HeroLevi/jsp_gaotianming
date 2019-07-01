// DONEORDER.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "DONEORDER.h"
#include "afxdialogex.h"


// DONEORDER 对话框

IMPLEMENT_DYNAMIC(DONEORDER, CDialogEx)

DONEORDER::DONEORDER(CWnd* pParent /*=NULL*/)
	: CDialogEx(DONEORDER::IDD, pParent)
	, id(_T(""))
{

}

DONEORDER::~DONEORDER()
{
}

void DONEORDER::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, id);
}


BEGIN_MESSAGE_MAP(DONEORDER, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON8, &DONEORDER::OnBnClickedButton8)
END_MESSAGE_MAP()


// DONEORDER 消息处理程序

char* DONEORDER::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//函数功能：将字符串从wchar_t*转换成char*，即从unicode字符转换成多字节字符
    return pstr;
}

//根据编号查找订单
void DONEORDER::OnBnClickedButton8()
{
	UpdateData();
	char* t = CStringToChar(id);
	ORDERDONE_RQ odrq;
	odrq.m_nType = _DEF_PROTOCOL_ORDERWAIT_RQ;
	odrq.id = *t - '0';
	theApp.GetKernel()->SendData((char*)&odrq,sizeof(odrq));
}
