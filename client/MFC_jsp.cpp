
// MFC_jsp.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "MFC_jsp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFC_jspApp

BEGIN_MESSAGE_MAP(CMFC_jspApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CMFC_jspApp 构造

CMFC_jspApp::CMFC_jspApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	m_pKernel = new TCPKernel;
}

// 唯一的一个 CMFC_jspApp 对象

CMFC_jspApp theApp;


// CMFC_jspApp 初始化

BOOL CMFC_jspApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	SetRegistryKey(_T("高天明"));

	dlg = new CMFC_jspDlg;
	m_pMainWnd = dlg;
	return dlg->Create(IDD_MAINDLG);
}

