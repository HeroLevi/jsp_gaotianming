// AddJob.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "AddJob.h"
#include "afxdialogex.h"


// AddJob �Ի���

IMPLEMENT_DYNAMIC(AddJob, CDialogEx)

AddJob::AddJob(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddJob::IDD, pParent)
	, job_num(_T(""))
	, seq(_T(""))
	, mec_num(_T(""))
	, time(_T(""))
	, num(0)
	, type(_T(""))
{

}

AddJob::~AddJob()
{
}

void AddJob::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, job_num);
	DDX_Text(pDX, IDC_EDIT8, seq);
	DDX_Text(pDX, IDC_EDIT5, mec_num);
	DDX_Text(pDX, IDC_EDIT9, time);
	DDX_CBString(pDX, IDC_COMBO1, type);
	DDX_Control(pDX, IDC_COMBO1, box_type);
}


BEGIN_MESSAGE_MAP(AddJob, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &AddJob::OnBnClickedButton1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &AddJob::OnCbnDropdownCombo1)
END_MESSAGE_MAP()


// AddJob ��Ϣ�������

char* AddJob::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//�������ܣ����ַ�����wchar_t*ת����char*������unicode�ַ�ת���ɶ��ֽ��ַ�
    return pstr;
}

//��ӹ������
void AddJob::OnBnClickedButton1()
{
	UpdateData();
	ADDJOB_RQ addrq;
	addrq.m_nType = _DEF_PROTOCOL_ADDJOB_RQ;
	char* t = CStringToChar(job_num);
	addrq.jobi = *t - '0';
	t = CStringToChar(mec_num);
	addrq.meci = *t - '0';
	t = CStringToChar(time);
	addrq.time = *t - '0';
	t = CStringToChar(seq);
	addrq.seq = *t - '0';
	t = CStringToChar(type);
	addrq.type = *t - '0';
	theApp.GetKernel()->SendData((char*)&addrq,sizeof(addrq));
}


//�������������˵�
void AddJob::OnCbnDropdownCombo1()
{
	box_type.ResetContent();//�����������б�

	box_type.SetItemHeight(0, 0);//��������ѡ��߶�

	/*m_cbExample.SetFont(pFont, 1);*/

	if (!PathFileExists(_T(".\\JobInfo.ini")))//�ж��ļ��Ƿ����
	{
		return;
	}

	CString strFileName = _T(".\\JobInfo.ini");
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
		CString m_type = szLine.Left(pos);//��ȡ�û���
		if (m_type.GetLength()!=0)
		{
			box_type.AddString(m_type);//��ʾ��combobox�ؼ���
		}
	}

	//�ر��ļ�
	file.Close();
}
