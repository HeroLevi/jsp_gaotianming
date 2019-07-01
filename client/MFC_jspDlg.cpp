
// MFC_jspDlg.cpp : 实现文件
//
#pragma warning( disable : 4996)
#include "stdafx.h"
#include "MFC_jsp.h"
#include "MFC_jspDlg.h"
#include "afxdialogex.h"
#include "Login.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMFC_jspDlg 对话框

CMFC_jspDlg::CMFC_jspDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC_jspDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON);
}

void CMFC_jspDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CMFC_jspDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON5, &CMFC_jspDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFC_jspDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC_jspDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC_jspDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC_jspDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFC_jspDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFC_jspDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CMFC_jspDlg 消息处理程序

BOOL CMFC_jspDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	// TODO: 在此添加额外的初始化代码
	if(!theApp.GetKernel()->Open())
	{
		AfxMessageBox(_T("服务器链接失败"));
		exit(0);
		return FALSE;
	}
	logindlg = new Login;
	logindlg->Create(IDD_lOGIN);
	logindlg->ShowWindow(SW_SHOW);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC_jspDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC_jspDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CMFC_jspDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//主窗口退出
void CMFC_jspDlg::OnClose()
{	
	BYEBYE_RQ brq;
	brq.m_nType = _DEF_PROTOCOL_BYEBYE_RQ;
	strcpy_s(brq.username,_DEF_SIZE,((TCPKernel*)theApp.GetKernel())->thisname);
	theApp.GetKernel()->SendData((char*)&brq,sizeof(brq));
	this->DestroyWindow();
	CDialogEx::OnClose();
}

//窗体销毁
void CMFC_jspDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

//字符转换
char* CMFC_jspDlg::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//函数功能：将字符串从wchar_t*转换成char*，即从unicode字符转换成多字节字符
    return pstr;
}

//开始工作
void CMFC_jspDlg::OnBnClickedButton5()
{
	WORK_RQ wrq;
	wrq.m_nType = _DEF_PROTOCOL_WORK_RQ;
	wrq.start = 1;
	theApp.GetKernel()->SendData((char*)&wrq,sizeof(wrq));
}

//导出甘特图
void CMFC_jspDlg::OnBnClickedButton7()
{
	//向服务器发送接收图片文件消息
	GetGtt_RQ m_gtt;
	m_gtt.m_nType = _DEF_PROTOCOL_GETGTT_RQ;
	theApp.GetKernel()->SendData((char*)&m_gtt,sizeof(m_gtt));
}

//编辑机器设备
void CMFC_jspDlg::OnBnClickedButton1()
{
	mec = new MecPropety;
	mec->DoModal();
}

//编辑工件
void CMFC_jspDlg::OnBnClickedButton2()
{
	editjob = new EditJob;
	editjob->DoModal();
}

//物料管理
void CMFC_jspDlg::OnBnClickedButton3()
{
	matter = new Matter;
	matter->DoModal();
}

//深搜工作请求
void CMFC_jspDlg::OnBnClickedButton4()
{
	WORK_RQ dfs;
	dfs.m_nType = _DEF_PROTOCOL_WORK_RQ;
	dfs.start = 1;
	theApp.GetKernel()->SendData((char*)&dfs,sizeof(dfs));
}

//订单管理
void CMFC_jspDlg::OnBnClickedButton6()
{
	orderman = new OrederManger;
	orderman->DoModal();
}
