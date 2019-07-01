// Order.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "Order.h"
#include "afxdialogex.h"
#include "Packdef.h"

// Order �Ի���

IMPLEMENT_DYNAMIC(Order, CDialogEx)

Order::Order(CWnd* pParent /*=NULL*/)
	: CDialogEx(Order::IDD, pParent)
	, time(_T(""))
	, num(_T(""))
	, product(_T("1"))
	, order_id(_T(""))
{

}

Order::~Order()
{
}

void Order::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT5, time);
	DDX_Text(pDX, IDC_EDIT4, num);
	DDX_CBString(pDX, IDC_COMBO1, product);
	DDX_Control(pDX, IDC_COMBO1, sublst);
	DDX_Text(pDX, IDC_EDIT8, order_id);
}


BEGIN_MESSAGE_MAP(Order, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &Order::OnBnClickedButton1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &Order::OnCbnDropdownCombo1)
END_MESSAGE_MAP()


// Order ��Ϣ�������


void Order::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	theApp.GetMainWnd()->PostMessage(WM_CLOSE);
	CDialogEx::OnClose();
}

void Order::OnDestroy()
{
	CDialogEx::OnDestroy();
	//PostQuitMessage(0);
	// TODO: �ڴ˴������Ϣ����������
}

char* Order::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//�������ܣ����ַ�����wchar_t*ת����char*������unicode�ַ�ת���ɶ��ֽ��ַ�
    return pstr;
}

//�´ﶩ��
void Order::OnBnClickedButton1()
{
	UpdateData();
	DOWNORDER_RQ dorq;
	dorq.m_nType = _DEF_PROTOCOL_DOWNORDER_RQ;
	char* t = CStringToChar(time);
	dorq.time = *t - '0';
	t = CStringToChar(order_id);
	dorq.id= *t - '0';
	t = CStringToChar(product);
	dorq.product= *t - '0';
	t = CStringToChar(num);
	dorq.num= *t - '0';
	theApp.GetKernel()->SendData((char*)&dorq,sizeof(dorq));
	AfxMessageBox(L"�µ��ɹ�");
}

//�����˵�
void Order::OnCbnDropdownCombo1()
{
	sublst.ResetContent();//�����������б�

	sublst.SetItemHeight(0, 0);//��������ѡ��߶�

	/*m_cbExample.SetFont(pFont, 1);*/

	if (!PathFileExists(_T(".\\product.ini")))//�ж��ļ��Ƿ����
	{
		return;
	}

	CString strFileName = _T(".\\product.ini");
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
			sublst.AddString(m_type);//��ʾ��combobox�ؼ���
		}
	}

	//�ر��ļ�
	file.Close();
}
