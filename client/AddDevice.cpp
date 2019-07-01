// AddDevice.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "AddDevice.h"
#include "afxdialogex.h"


// AddDevice 对话框

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


// AddDevice 消息处理程序

//字符转换
char* AddDevice::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//函数功能：将字符串从wchar_t*转换成char*，即从unicode字符转换成多字节字符
    return pstr;
}

//添加设备完成
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
	box_type.ResetContent();//清理下拉框列表

	box_type.SetItemHeight(0, 0);//设置下拉选项高度

	/*m_cbExample.SetFont(pFont, 1);*/

	if (!PathFileExists(_T(".\\MacInfo.ini")))//判断文件是否存在
	{
		return;
	}

	CString strFileName = _T(".\\MacInfo.ini");
	CString szLine = _T("");

	//打开文件
	CStdioFile  file;

	file.Open(strFileName, CFile::modeRead);

	//逐行读取字符串
	while (file.ReadString(szLine))
	{
		//查找逗号
		char a = ',';
		size_t pos = szLine.Find(a);
		CString m_type = szLine.Left(pos);//截取用户名
		if (m_type.GetLength()!=0)
		{
			box_type.AddString(m_type);//显示到combobox控件上
		}
	}

	//关闭文件
	file.Close();
}
