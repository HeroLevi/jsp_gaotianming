// Matter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "Matter.h"
#include "afxdialogex.h"
#include "Packdef.h"

// Matter �Ի���

IMPLEMENT_DYNAMIC(Matter, CDialogEx)

Matter::Matter(CWnd* pParent /*=NULL*/)
	: CDialogEx(Matter::IDD, pParent)
{
	addmatter = new AddMatter;
	delmatter = new DelMatter;
	selectmatter = new SelectMatter;
}

Matter::~Matter()
{
}

void Matter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Matter, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Matter::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON8, &Matter::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &Matter::OnBnClickedButton9)
END_MESSAGE_MAP()


// Matter ��Ϣ�������

//�������
void Matter::OnBnClickedButton1()
{
	addmatter->DoModal();
}

//�鿴����
void Matter::OnBnClickedButton8()
{
	selectmatter->DoModal();
}

//ɾ������
void Matter::OnBnClickedButton9()
{
	delmatter->DoModal();
}

