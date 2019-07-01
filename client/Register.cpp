// Register.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "Register.h"
#include "afxdialogex.h"


// Register 对话框

IMPLEMENT_DYNAMIC(Register, CDialogEx)

Register::Register(CWnd* pParent /*=NULL*/)
	: CDialogEx(Register::IDD, pParent)
	, m_username(_T(""))
	, m_password(_T(""))
	, m_duppassword(_T(""))
	, m_find(_T(""))
{

}

Register::~Register()
{
}

void Register::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDX_Text(pDX, IDC_EDIT9, m_password);
	DDX_Text(pDX, IDC_EDIT14, m_duppassword);
	DDX_Text(pDX, IDC_EDIT8, m_find);
}


BEGIN_MESSAGE_MAP(Register, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Register::OnBnClickedButton1)
END_MESSAGE_MAP()


// Register 消息处理程序

//注册
void Register::OnBnClickedButton1()
{
	UpdateData();
	if(m_password.IsEmpty())
	{
		if(MessageBox(L"请输入密码") == IDOK)
		{
			return;
		}
	}
	if(m_duppassword.IsEmpty())
	{
		if(MessageBox(L"请确认密码" ) == IDOK)
		{
			return;
		}
	}

	if(m_password != m_duppassword)
	{
		
		if(MessageBox(L"两次输入密码不匹配") == IDOK)
		{
			return;
		}
	}
	if(m_find.IsEmpty())
	{
		if(MessageBox(L"请输入并牢记找回码,否则无法修改密码以及找回密码") == IDOK)
		{
			return;
		}
	}
	REGISTER_RQ regrq;
	regrq.m_nType = _DEF_PROTOCOL_REGISTER_RQ;
	WideCharToMultiByte(CP_ACP,0,m_username,-1,regrq.username,sizeof(regrq.username),0,0);
	WideCharToMultiByte(CP_ACP,0,m_password,-1,regrq.password,sizeof(regrq.password),0,0);
	WideCharToMultiByte(CP_ACP,0,m_find,-1,regrq.find,sizeof(regrq.find),0,0);
	theApp.GetKernel()->SendData((char*)&regrq,sizeof(regrq));
}
