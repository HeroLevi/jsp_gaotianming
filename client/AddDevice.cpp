// AddDevice.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "AddDevice.h"
#include "afxdialogex.h"


// AddDevice �Ի���

IMPLEMENT_DYNAMIC(AddDevice, CDialogEx)

AddDevice::AddDevice(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddDevice::IDD, pParent)
	, id(_T(""))
	, type(_T(""))
	, year(_T(""))
{

}

AddDevice::~AddDevice()
{
}

void AddDevice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, id);
	DDX_CBString(pDX, IDC_COMBO1, type);
	DDX_Text(pDX, IDC_EDIT3, year);
	DDX_Control(pDX, IDC_COMBO1, box_type);
}


BEGIN_MESSAGE_MAP(AddDevice, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &AddDevice::OnBnClickedButton1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &AddDevice::OnCbnDropdownCombo1)
END_MESSAGE_MAP()


// AddDevice ��Ϣ�������

//�ַ�ת��
char* AddDevice::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//�������ܣ����ַ�����wchar_t*ת����char*������unicode�ַ�ת���ɶ��ֽ��ַ�
    return pstr;
}

//����豸���
void AddDevice::OnBnClickedButton1()
{
	UpdateData();
	ADDMEC_RQ addrq;
	addrq.m_nType = _DEF_PROTOCOL_ADDMEC_RQ;
	char* t = CStringToChar(id);
	addrq.id = *t - '0';
	t = CStringToChar(type);
	addrq.type = *t - '0';
	t = CStringToChar(year);
	addrq.year = *t - '0';

	theApp.GetKernel()->SendData((char*)&addrq,sizeof(addrq));
}


void AddDevice::OnCbnDropdownCombo1()
{
	box_type.ResetContent();//�����������б�

	box_type.SetItemHeight(0, 0);//��������ѡ��߶�

	/*m_cbExample.SetFont(pFont, 1);*/

	if (!PathFileExists(_T(".\\MacInfo.ini")))//�ж��ļ��Ƿ����
	{
		return;
	}

	CString strFileName = _T(".\\MacInfo.ini");
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
