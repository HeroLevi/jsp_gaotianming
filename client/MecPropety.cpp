// MecPropety.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "MecPropety.h"
#include "afxdialogex.h"


// MecPropety 对话框

IMPLEMENT_DYNAMIC(MecPropety, CDialogEx)

MecPropety::MecPropety(CWnd* pParent /*=NULL*/)
	: CDialogEx(MecPropety::IDD, pParent)
{
	add = new AddDevice;
	update = new UpdateDevice;
	selectmac = new SelectMac;
	delmac = new DelMac;
}

MecPropety::~MecPropety()
{
}

void MecPropety::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MecPropety, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MecPropety::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &MecPropety::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MecPropety::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &MecPropety::OnBnClickedButton4)
END_MESSAGE_MAP()


// MecPropety 消息处理程序

//查询设备
void MecPropety::OnBnClickedButton1()
{
	selectmac->DoModal();
}

//添加设备
void MecPropety::OnBnClickedButton2()
{
	add->DoModal();
}

//删除设备
void MecPropety::OnBnClickedButton3()
{
	delmac->DoModal();
}

//修改设备
void MecPropety::OnBnClickedButton4()
{
	update->DoModal();
}
