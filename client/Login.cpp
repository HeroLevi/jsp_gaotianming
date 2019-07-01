// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Captcha.h"
// Login 对话框

IMPLEMENT_DYNAMIC(Login, CDialogEx)

Login::Login(CWnd* pParent /*=NULL*/)
	: CDialogEx(Login::IDD, pParent)
	, username(_T(""))
	, password(_T(""))
{
	m_kernel = theApp.GetKernel();
	regdlg = new Register;
	m_update = new UpdatePass;
	flag1 = false;
	flag2 = false;
	//m_Back.LoadBitmap(IDB_LoginBack);
}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, username);
	DDX_Text(pDX, IDC_EDIT3, password);
	DDX_Control(pDX, IDC_CHECK1, m_autoLogin);
	DDX_Control(pDX, IDC_CHECK2, m_remem);
	DDX_Control(pDX, IDC_COMBO1, m_subList);

}


BEGIN_MESSAGE_MAP(Login, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON4, &Login::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Login::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_CHECK1, &Login::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &Login::OnBnClickedCheck2)
	ON_CBN_DROPDOWN(IDC_COMBO1, &Login::OnCbnDropdownCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &Login::OnBnClickedButton3)

	ON_BN_CLICKED(IDC_BUTTON1, &Login::OnBnClickedButton1)
END_MESSAGE_MAP()


// Login 消息处理程序

void Login::OnDestroy()
{
	CDialogEx::OnDestroy();
	PostQuitMessage(0);
}

//退出对话框
void Login::OnClose()
{
	if(!((TCPKernel*)theApp.GetKernel())->havelogin)
		exit(0);
	CDialogEx::OnClose();
}

//登录
void Login::OnBnClickedButton4()
{
	UpdateData();
	LOGIN_RQ loginrq;
	loginrq.m_nType = _DEF_PROTOCOL_LOGIN_RQ;
	loginrq.flag = _manager;
	WideCharToMultiByte(CP_ACP,0,username,-1,loginrq.username,sizeof(loginrq.username),0,0);
	WideCharToMultiByte(CP_ACP,0,password,-1,loginrq.password,sizeof(loginrq.password),0,0);
	
	//生成验证码
	Captcha *captcha = new Captcha;
	captcha->DoModal();
	theApp.GetKernel()->SendData((char*)&loginrq,sizeof(loginrq));
}

//注册
void Login::OnBnClickedButton5()
{
	regdlg->DoModal();
}

//自动登录
void Login::OnBnClickedCheck1()
{
	m_remem.SetCheck(BST_CHECKED);//记住密码变为选中状态
	flag1 = true;
	flag2 = true;
}

//记住密码
void Login::OnBnClickedCheck2()
{
	//如果自动登录被选中，触发这个Button
	//自动登录状态变为非选中状态
	int state = ((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	
	if(1 == state)
	{
		m_autoLogin.SetCheck(BST_UNCHECKED);//自动登录变为非选中状态
		flag1 = false;
		flag2 = false;
		
		return;
	}
	flag2 = true;
}

//账号下拉菜单
void Login::OnCbnDropdownCombo1()
{
	m_subList.ResetContent();//清理下拉框列表

	m_subList.SetItemHeight(0, 0);//设置下拉选项高度

	/*m_cbExample.SetFont(pFont, 1);*/

	if (!PathFileExists(_T(".\\UserInfo.ini")))//判断文件是否存在
	{
		return;
	}

	CString strFileName = _T(".\\UserInfo.ini");
	CString szLine = _T("");

	//打开文件
	CStdioFile  file;

	file.Open(strFileName, CFile::modeRead);

	//逐行读取字符串
	while (file.ReadString(szLine))
	{
		//查找逗号
		char a = ',';
		size_t pos = szLine.Find(a);
		CString username = szLine.Left(pos);//截取用户名
		if (username.GetLength()!=0)
		{
			m_subList.AddString(username);//显示到combobox控件上
		}
	}

	//关闭文件
	file.Close();
}

//修改密码
void Login::OnBnClickedButton3()
{
	m_update->DoModal();
}

//以普通用户身份登录
void Login::OnBnClickedButton1()
{
	UpdateData();
	LOGIN_RQ loginrq;
	loginrq.m_nType = _DEF_PROTOCOL_LOGIN_RQ;
	loginrq.flag = _commonuser;
	WideCharToMultiByte(CP_ACP,0,username,-1,loginrq.username,sizeof(loginrq.username),0,0);
	WideCharToMultiByte(CP_ACP,0,password,-1,loginrq.password,sizeof(loginrq.password),0,0);
	Captcha *captcha = new Captcha;
	captcha->DoModal();
	theApp.GetKernel()->SendData((char*)&loginrq,sizeof(loginrq));
}
