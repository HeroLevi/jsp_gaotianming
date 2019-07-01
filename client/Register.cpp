// Register.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "Register.h"
#include "afxdialogex.h"


// Register �Ի���

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


// Register ��Ϣ�������

//ע��
void Register::OnBnClickedButton1()
{
	UpdateData();
	if(m_password.IsEmpty())
	{
		if(MessageBox(L"����������") == IDOK)
		{
			return;
		}
	}
	if(m_duppassword.IsEmpty())
	{
		if(MessageBox(L"��ȷ������" ) == IDOK)
		{
			return;
		}
	}

	if(m_password != m_duppassword)
	{
		
		if(MessageBox(L"�����������벻ƥ��") == IDOK)
		{
			return;
		}
	}
	if(m_find.IsEmpty())
	{
		if(MessageBox(L"�����벢�μ��һ���,�����޷��޸������Լ��һ�����") == IDOK)
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
