// LookOrder.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "LookOrder.h"
#include "afxdialogex.h"


// LookOrder �Ի���

IMPLEMENT_DYNAMIC(LookOrder, CDialogEx)

LookOrder::LookOrder(CWnd* pParent /*=NULL*/)
	: CDialogEx(LookOrder::IDD, pParent)
	, id(_T(""))
{

}

LookOrder::~LookOrder()
{
}

void LookOrder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id);
}


BEGIN_MESSAGE_MAP(LookOrder, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &LookOrder::OnBnClickedButton1)
END_MESSAGE_MAP()


// LookOrder ��Ϣ�������

char* LookOrder::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//�������ܣ����ַ�����wchar_t*ת����char*������unicode�ַ�ת���ɶ��ֽ��ַ�
    return pstr;
}

//���Ҷ���
void LookOrder::OnBnClickedButton1()
{
	UpdateData();
	char* t = CStringToChar(id);
	ORDERDONE_RQ odrq;
	odrq.m_nType = _DEF_PROTOCOL_ORDERDONE_RQ;
	odrq.id = *t - '0';
	theApp.GetKernel()->SendData((char*)&odrq,sizeof(odrq));
}
