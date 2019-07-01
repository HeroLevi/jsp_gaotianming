// OrederManger.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "OrederManger.h"
#include "afxdialogex.h"


// OrederManger 对话框

IMPLEMENT_DYNAMIC(OrederManger, CDialogEx)

OrederManger::OrederManger(CWnd* pParent /*=NULL*/)
	: CDialogEx(OrederManger::IDD, pParent)
{

}

OrederManger::~OrederManger()
{
}

void OrederManger::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(OrederManger, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &OrederManger::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &OrederManger::OnBnClickedButton1)
END_MESSAGE_MAP()


// OrederManger 消息处理程序

//未处理订单
void OrederManger::OnBnClickedButton2()
{
	waitorder = new WaitOrder;
	waitorder->DoModal();
}

//已处理订单
void OrederManger::OnBnClickedButton1()
{
	doneorder = new DONEORDER;
	doneorder->DoModal();
}
