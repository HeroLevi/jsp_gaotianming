// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Captcha.h"
// Login �Ի���

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


// Login ��Ϣ�������

void Login::OnDestroy()
{
	CDialogEx::OnDestroy();
	PostQuitMessage(0);
}

//�˳��Ի���
void Login::OnClose()
{
	if(!((TCPKernel*)theApp.GetKernel())->havelogin)
		exit(0);
	CDialogEx::OnClose();
}

//��¼
void Login::OnBnClickedButton4()
{
	UpdateData();
	LOGIN_RQ loginrq;
	loginrq.m_nType = _DEF_PROTOCOL_LOGIN_RQ;
	loginrq.flag = _manager;
	WideCharToMultiByte(CP_ACP,0,username,-1,loginrq.username,sizeof(loginrq.username),0,0);
	WideCharToMultiByte(CP_ACP,0,password,-1,loginrq.password,sizeof(loginrq.password),0,0);
	
	//������֤��
	Captcha *captcha = new Captcha;
	captcha->DoModal();
	theApp.GetKernel()->SendData((char*)&loginrq,sizeof(loginrq));
}

//ע��
void Login::OnBnClickedButton5()
{
	regdlg->DoModal();
}

//�Զ���¼
void Login::OnBnClickedCheck1()
{
	m_remem.SetCheck(BST_CHECKED);//��ס�����Ϊѡ��״̬
	flag1 = true;
	flag2 = true;
}

//��ס����
void Login::OnBnClickedCheck2()
{
	//����Զ���¼��ѡ�У��������Button
	//�Զ���¼״̬��Ϊ��ѡ��״̬
	int state = ((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	
	if(1 == state)
	{
		m_autoLogin.SetCheck(BST_UNCHECKED);//�Զ���¼��Ϊ��ѡ��״̬
		flag1 = false;
		flag2 = false;
		
		return;
	}
	flag2 = true;
}

//�˺������˵�
void Login::OnCbnDropdownCombo1()
{
	m_subList.ResetContent();//�����������б�

	m_subList.SetItemHeight(0, 0);//��������ѡ��߶�

	/*m_cbExample.SetFont(pFont, 1);*/

	if (!PathFileExists(_T(".\\UserInfo.ini")))//�ж��ļ��Ƿ����
	{
		return;
	}

	CString strFileName = _T(".\\UserInfo.ini");
	CString szLine = _T("");

	//���ļ�
	CStdioFile  file;

	file.Open(strFileName, CFile::modeRead);

	//���ж�ȡ�ַ���
	while (file.ReadString(szLine))
	{
		//���Ҷ���
		char a = ',';
		size_t pos = szLine.Find(a);
		CString username = szLine.Left(pos);//��ȡ�û���
		if (username.GetLength()!=0)
		{
			m_subList.AddString(username);//��ʾ��combobox�ؼ���
		}
	}

	//�ر��ļ�
	file.Close();
}

//�޸�����
void Login::OnBnClickedButton3()
{
	m_update->DoModal();
}

//����ͨ�û���ݵ�¼
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
