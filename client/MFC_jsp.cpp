
// MFC_jsp.cpp : ����Ӧ�ó��������Ϊ��
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

// CMFC_jspApp ����

CMFC_jspApp::CMFC_jspApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	m_pKernel = new TCPKernel;
}

// Ψһ��һ�� CMFC_jspApp ����

CMFC_jspApp theApp;


// CMFC_jspApp ��ʼ��

BOOL CMFC_jspApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	SetRegistryKey(_T("������"));

	dlg = new CMFC_jspDlg;
	m_pMainWnd = dlg;
	return dlg->Create(IDD_MAINDLG);
}

