
// MFC_jspDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// CMFC_jspDlg �Ի���

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


// CMFC_jspDlg ��Ϣ�������

BOOL CMFC_jspDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	if(!theApp.GetKernel()->Open())
	{
		AfxMessageBox(_T("����������ʧ��"));
		exit(0);
		return FALSE;
	}
	logindlg = new Login;
	logindlg->Create(IDD_lOGIN);
	logindlg->ShowWindow(SW_SHOW);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFC_jspDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CMFC_jspDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//�������˳�
void CMFC_jspDlg::OnClose()
{	
	BYEBYE_RQ brq;
	brq.m_nType = _DEF_PROTOCOL_BYEBYE_RQ;
	strcpy_s(brq.username,_DEF_SIZE,((TCPKernel*)theApp.GetKernel())->thisname);
	theApp.GetKernel()->SendData((char*)&brq,sizeof(brq));
	this->DestroyWindow();
	CDialogEx::OnClose();
}

//��������
void CMFC_jspDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

//�ַ�ת��
char* CMFC_jspDlg::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//�������ܣ����ַ�����wchar_t*ת����char*������unicode�ַ�ת���ɶ��ֽ��ַ�
    return pstr;
}

//��ʼ����
void CMFC_jspDlg::OnBnClickedButton5()
{
	WORK_RQ wrq;
	wrq.m_nType = _DEF_PROTOCOL_WORK_RQ;
	wrq.start = 1;
	theApp.GetKernel()->SendData((char*)&wrq,sizeof(wrq));
}

//��������ͼ
void CMFC_jspDlg::OnBnClickedButton7()
{
	//����������ͽ���ͼƬ�ļ���Ϣ
	GetGtt_RQ m_gtt;
	m_gtt.m_nType = _DEF_PROTOCOL_GETGTT_RQ;
	theApp.GetKernel()->SendData((char*)&m_gtt,sizeof(m_gtt));
}

//�༭�����豸
void CMFC_jspDlg::OnBnClickedButton1()
{
	mec = new MecPropety;
	mec->DoModal();
}

//�༭����
void CMFC_jspDlg::OnBnClickedButton2()
{
	editjob = new EditJob;
	editjob->DoModal();
}

//���Ϲ���
void CMFC_jspDlg::OnBnClickedButton3()
{
	matter = new Matter;
	matter->DoModal();
}

//���ѹ�������
void CMFC_jspDlg::OnBnClickedButton4()
{
	WORK_RQ dfs;
	dfs.m_nType = _DEF_PROTOCOL_WORK_RQ;
	dfs.start = 1;
	theApp.GetKernel()->SendData((char*)&dfs,sizeof(dfs));
}

//��������
void CMFC_jspDlg::OnBnClickedButton6()
{
	orderman = new OrederManger;
	orderman->DoModal();
}
