// MacInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "MacInfo.h"
#include "afxdialogex.h"


// MacInfo 对话框

IMPLEMENT_DYNAMIC(MacInfo, CDialogEx)

MacInfo::MacInfo(CString m_type,CString m_year,CWnd* pParent /*=NULL*/)
	: CDialogEx(MacInfo::IDD, pParent)
	, type(m_type)
	, year(m_year)
{

}

MacInfo::~MacInfo()
{
}

void MacInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, type_ctl);
	DDX_Text(pDX, IDC_EDIT1, type);
	DDX_Text(pDX, IDC_EDIT3, year);
}


BEGIN_MESSAGE_MAP(MacInfo, CDialogEx)
END_MESSAGE_MAP()


// MacInfo 消息处理程序
