// GTT.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "GTT.h"
#include "afxdialogex.h"


// GTT 对话框

IMPLEMENT_DYNAMIC(GTT, CDialogEx)

GTT::GTT(CWnd* pParent /*=NULL*/)
	: CDialogEx(GTT::IDD, pParent)
{
	pWnd = NULL;
}

GTT::~GTT()
{
}

void GTT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GTT, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// GTT 消息处理程序

void GTT::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	UpdateWindow();
	int height, width;
	if(pWnd != NULL)
		return;
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CDialogEx::OnPaint()
	pWnd = (CStatic*)GetDlgItem(IDC_STATIC); // 得到 Picture Control 句柄
	CImage image;
	image.Load(_T("C:\\Users\\Levi\\Desktop\\大三下课程设计\\gantt2.png"));
	height = image.GetHeight();
	width = image.GetWidth();
	HBITMAP hBmp = image.Detach();
	pWnd->SetBitmap(hBmp);
	pWnd->SetWindowPos(NULL, 
					   0, 
					   0, 
					   width, 
					   height, 
					   SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
//
//	UpdateWindow();
//int height, width;
//CRect rect;//定义矩形类
//CRect rect1;
//CImage image; //创建图片类
//image.Load(_T("1.jpg"));
//height = image.GetHeight();
//width = image.GetWidth();
//
//
//m_ctrlPic.GetClientRect(&rect); //获得pictrue控件所在的矩形区域
//CDC *pDc = m_ctrlPic.GetDC();//获得pictrue控件的Dc
//SetStretchBltMode(pDc->m_hDC,STRETCH_HALFTONE); 
//image.StretchBlt(pDc->m_hDC,rect,SRCCOPY);
//ReleaseDC(pDc);//释放picture控件的Dc


}


void GTT::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	pWnd = NULL;
	CDialogEx::OnClose();
}
