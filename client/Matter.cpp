// Matter.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "Matter.h"
#include "afxdialogex.h"
#include "Packdef.h"

// Matter 对话框

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


// Matter 消息处理程序

//添加物料
void Matter::OnBnClickedButton1()
{
	addmatter->DoModal();
}

//查看物料
void Matter::OnBnClickedButton8()
{
	selectmatter->DoModal();
}

//删除物料
void Matter::OnBnClickedButton9()
{
	delmatter->DoModal();
}

