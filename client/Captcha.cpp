// Captcha.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "Captcha.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
#include <random>
using namespace std;

// Captcha 对话框

IMPLEMENT_DYNAMIC(Captcha, CDialogEx)

Captcha::Captcha(CWnd* pParent /*=NULL*/)
	: CDialogEx(Captcha::IDD, pParent)
	, m_captcha(_T("请输入验证码"))
{
	pWnd = NULL;
}

Captcha::~Captcha()
{
}

void Captcha::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_captcha);
}


BEGIN_MESSAGE_MAP(Captcha, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON2, &Captcha::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &Captcha::OnBnClickedButton1)
END_MESSAGE_MAP()


// Captcha 消息处理程序


void Captcha::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if(pWnd != NULL)
		return;
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CDialogEx::OnPaint()

	fstream _file;
	_file.open("C:\\Users\\Levi\\Desktop\\大三下课程设计\\VerificationCode.bmp",ios::in);
	if(!_file)
	{
		return;
	}
	_file.close();
	pWnd = (CStatic*)GetDlgItem(IDC_STATIC); // 得到 Picture Control 句柄
	CImage image;
	image.Load(_T("C:\\Users\\Levi\\Desktop\\大三下课程设计\\VerificationCode.bmp"));
	HBITMAP hBmp = image.Detach();
	pWnd->SetBitmap(hBmp);
	pWnd->SetWindowPos(NULL, 
					   0, 
					   0, 
					   120, 
					   30, 
					   SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
}

//提交
void Captcha::OnBnClickedButton2()
{
	FILE* fp;
	fopen_s(&fp,"C:\\Users\\Levi\\Desktop\\大三下课程设计\\VerificationCode.txt","w+");
	char buf[8];
	fread_s(buf,8,1,1,fp);

	fclose(fp);
}

//看不清楚换一张
void Captcha::OnBnClickedButton1()
{
	srand((unsigned int)time(0));
	FILE* fp;
	fopen_s(&fp,"C:\\Users\\Levi\\Desktop\\大三下课程设计\\VerificationCode.txt","w+");
	char buf = 0;
	for(int i=0;i<8;i++)
	{
		buf = rand()%30 - '0';
		fwrite(&buf,1,1,fp);
	}
	fclose(fp);
	WinExec("cmd /c C:\\Users\\Levi\\Desktop\\大三下课程设计\\Valid.bat",SW_HIDE);
	pWnd = NULL;
	OnPaint();
}


