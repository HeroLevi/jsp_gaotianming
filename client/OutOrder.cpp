// OutOrder.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "OutOrder.h"
#include "afxdialogex.h"


// OutOrder �Ի���

IMPLEMENT_DYNAMIC(OutOrder, CDialogEx)

OutOrder::OutOrder(CWnd* pParent /*=NULL*/)
	: CDialogEx(OutOrder::IDD, pParent)
	, id(_T(""))
{

}

OutOrder::~OutOrder()
{
}

void OutOrder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id);
}


BEGIN_MESSAGE_MAP(OutOrder, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &OutOrder::OnBnClickedButton1)
END_MESSAGE_MAP()


// OutOrder ��Ϣ�������

char* OutOrder::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//�������ܣ����ַ�����wchar_t*ת����char*������unicode�ַ�ת���ɶ��ֽ��ַ�
    return pstr;
}

//�˶���
void OutOrder::OnBnClickedButton1()
{
	OUTORDER_RQ odrq;
	odrq.m_nType = _DEF_PROTOCOL_OUTORDER_RQ;
	UpdateData();
	char* t = CStringToChar(id);
	odrq.id = *t - '0';
	theApp.GetKernel()->SendData((char*)&odrq,sizeof(odrq));
}
