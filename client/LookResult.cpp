// LookResult.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "LookResult.h"
#include "afxdialogex.h"


// LookResult �Ի���

IMPLEMENT_DYNAMIC(LookResult, CDialogEx)

LookResult::LookResult(CString m_time,CString m_product,CString m_num,CWnd* pParent /*=NULL*/)
	: CDialogEx(LookResult::IDD, pParent)
	, time(m_time)
	, product(m_product)
	, num(m_num)
{

}

LookResult::~LookResult()
{
}

void LookResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, time);
	DDX_Text(pDX, IDC_EDIT1, product);
	DDX_Text(pDX, IDC_EDIT3, num);
}


BEGIN_MESSAGE_MAP(LookResult, CDialogEx)
END_MESSAGE_MAP()


// LookResult ��Ϣ�������
