// AddMatter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "AddMatter.h"
#include "afxdialogex.h"


// AddMatter �Ի���

IMPLEMENT_DYNAMIC(AddMatter, CDialogEx)

AddMatter::AddMatter(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddMatter::IDD, pParent)
	, id(_T(""))
	, num(_T(""))
{

}

AddMatter::~AddMatter()
{
}

void AddMatter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id);
	DDX_Text(pDX, IDC_EDIT3, num);
}


BEGIN_MESSAGE_MAP(AddMatter, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &AddMatter::OnBnClickedButton1)
END_MESSAGE_MAP()


// AddMatter ��Ϣ�������

char* AddMatter::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//�������ܣ����ַ�����wchar_t*ת����char*������unicode�ַ�ת���ɶ��ֽ��ַ�
    return pstr;
}

//���
void AddMatter::OnBnClickedButton1()
{
	UpdateData();
	ADDMATTER_RQ adrq;
	adrq.m_nType = _DEF_PROTOCOL_ADDMATTER_RQ;
	char *t = CStringToChar(id);
	adrq.id = *t - '0';
	t = CStringToChar(num);
	adrq.num = *t - '0';
	theApp.GetKernel()->SendData((char*)&adrq,sizeof(adrq));
	AfxMessageBox(L"��ӳɹ�");
}
