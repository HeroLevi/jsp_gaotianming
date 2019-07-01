// SelectMatter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "SelectMatter.h"
#include "afxdialogex.h"


// SelectMatter �Ի���

IMPLEMENT_DYNAMIC(SelectMatter, CDialogEx)

SelectMatter::SelectMatter(CWnd* pParent /*=NULL*/)
	: CDialogEx(SelectMatter::IDD, pParent)
	, id(_T(""))
{

}

SelectMatter::~SelectMatter()
{
}

void SelectMatter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id);
}


BEGIN_MESSAGE_MAP(SelectMatter, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &SelectMatter::OnBnClickedButton1)
END_MESSAGE_MAP()


// SelectMatter ��Ϣ�������

char* SelectMatter::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//�������ܣ����ַ�����wchar_t*ת����char*������unicode�ַ�ת���ɶ��ֽ��ַ�
    return pstr;
}


//��ѯ����
void SelectMatter::OnBnClickedButton1()
{
	UpdateData();
	SELECTMATTER_RQ smrq;
	smrq.m_nType = _DEF_PROTOCOL_SELECTMATTER_RQ;
	char* t = CStringToChar(id);
	smrq.id = *t - '0';
	theApp.GetKernel()->SendData((char*)&smrq,sizeof(smrq));
}
