// DONEORDER.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "DONEORDER.h"
#include "afxdialogex.h"


// DONEORDER �Ի���

IMPLEMENT_DYNAMIC(DONEORDER, CDialogEx)

DONEORDER::DONEORDER(CWnd* pParent /*=NULL*/)
	: CDialogEx(DONEORDER::IDD, pParent)
	, id(_T(""))
{

}

DONEORDER::~DONEORDER()
{
}

void DONEORDER::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, id);
}


BEGIN_MESSAGE_MAP(DONEORDER, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON8, &DONEORDER::OnBnClickedButton8)
END_MESSAGE_MAP()


// DONEORDER ��Ϣ�������

char* DONEORDER::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//�������ܣ����ַ�����wchar_t*ת����char*������unicode�ַ�ת���ɶ��ֽ��ַ�
    return pstr;
}

//���ݱ�Ų��Ҷ���
void DONEORDER::OnBnClickedButton8()
{
	UpdateData();
	char* t = CStringToChar(id);
	ORDERDONE_RQ odrq;
	odrq.m_nType = _DEF_PROTOCOL_ORDERWAIT_RQ;
	odrq.id = *t - '0';
	theApp.GetKernel()->SendData((char*)&odrq,sizeof(odrq));
}
