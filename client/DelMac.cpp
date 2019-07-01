// DelMac.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "DelMac.h"
#include "afxdialogex.h"


// DelMac �Ի���

IMPLEMENT_DYNAMIC(DelMac, CDialogEx)

DelMac::DelMac(CWnd* pParent /*=NULL*/)
	: CDialogEx(DelMac::IDD, pParent)
	, macid(_T(""))
{

}

DelMac::~DelMac()
{
}

void DelMac::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, macid);
}


BEGIN_MESSAGE_MAP(DelMac, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DelMac::OnBnClickedButton1)
END_MESSAGE_MAP()


// DelMac ��Ϣ�������

char* DelMac::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//�������ܣ����ַ�����wchar_t*ת����char*������unicode�ַ�ת���ɶ��ֽ��ַ�
    return pstr;
}

//�Ƴ�����
void DelMac::OnBnClickedButton1()
{
	UpdateData();
	DELMAC_RQ delrq;
	delrq.m_nType = _DEF_PROTOCOL_DELMAC_RQ;
	char* t = CStringToChar(macid);
	delrq.id = *t - '0';
	theApp.GetKernel()->SendData((char*)&delrq,sizeof(delrq));
}
