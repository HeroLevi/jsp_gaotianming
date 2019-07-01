// JobInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "JobInfo.h"
#include "afxdialogex.h"


// JobInfo 对话框

IMPLEMENT_DYNAMIC(JobInfo, CDialogEx)

JobInfo::JobInfo(CString m_usemac,CString m_time,CWnd* pParent /*=NULL*/)
	: CDialogEx(JobInfo::IDD, pParent)
	, usemac(m_usemac)
	, time(m_time)
{

}

JobInfo::~JobInfo()
{
}

void JobInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, usemac);
	DDX_Text(pDX, IDC_EDIT3, time);
}


BEGIN_MESSAGE_MAP(JobInfo, CDialogEx)
END_MESSAGE_MAP()


// JobInfo 消息处理程序
