// DoneOderInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "DoneOderInfo.h"
#include "afxdialogex.h"


// DoneOderInfo �Ի���

IMPLEMENT_DYNAMIC(DoneOderInfo, CDialogEx)

DoneOderInfo::DoneOderInfo(CString m_product,CString m_num,CWnd* pParent /*=NULL*/)
	: CDialogEx(DoneOderInfo::IDD, pParent)
	, product(m_product)
	, num(m_num)
{

}

DoneOderInfo::~DoneOderInfo()
{
}

void DoneOderInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, product);
	DDX_Text(pDX, IDC_EDIT3, num);
}


BEGIN_MESSAGE_MAP(DoneOderInfo, CDialogEx)
END_MESSAGE_MAP()


// DoneOderInfo ��Ϣ�������
