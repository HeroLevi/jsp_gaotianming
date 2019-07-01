// MatterInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "MatterInfo.h"
#include "afxdialogex.h"


// MatterInfo 对话框

IMPLEMENT_DYNAMIC(MatterInfo, CDialogEx)

MatterInfo::MatterInfo(CString m_Left,CWnd* pParent /*=NULL*/)
	: CDialogEx(MatterInfo::IDD, pParent)
	, Left(m_Left)
{

}

MatterInfo::~MatterInfo()
{
}

void MatterInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Left);
}


BEGIN_MESSAGE_MAP(MatterInfo, CDialogEx)
END_MESSAGE_MAP()


// MatterInfo 消息处理程序

