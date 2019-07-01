// SelectJob.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "SelectJob.h"
#include "afxdialogex.h"


// SelectJob �Ի���

IMPLEMENT_DYNAMIC(SelectJob, CDialogEx)

SelectJob::SelectJob(CWnd* pParent /*=NULL*/)
	: CDialogEx(SelectJob::IDD, pParent)
	, jobid(_T(""))
	, seqid(_T(""))
{

}

SelectJob::~SelectJob()
{
}

void SelectJob::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, jobid);
	DDX_Text(pDX, IDC_EDIT3, seqid);
}


BEGIN_MESSAGE_MAP(SelectJob, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &SelectJob::OnBnClickedButton1)
END_MESSAGE_MAP()


// SelectJob ��Ϣ�������

char* SelectJob::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//�������ܣ����ַ�����wchar_t*ת����char*������unicode�ַ�ת���ɶ��ֽ��ַ�
    return pstr;
}


//������ѯ
void SelectJob::OnBnClickedButton1()
{
	UpdateData();
	SELECTJOB_RQ sjobrq;
	sjobrq.m_nType = _DEF_PROTOCOL_SELECTJOB_RQ;
	char* t = CStringToChar(jobid);
	sjobrq.id = *t - '0';
	t = CStringToChar(seqid);
	sjobrq.seq = *t - '0';
	theApp.GetKernel()->SendData((char*)&sjobrq,sizeof(sjobrq));
}
