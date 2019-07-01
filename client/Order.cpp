// Order.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "Order.h"
#include "afxdialogex.h"
#include "Packdef.h"

// Order 对话框

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


// Order 消息处理程序


void Order::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	theApp.GetMainWnd()->PostMessage(WM_CLOSE);
	CDialogEx::OnClose();
}

void Order::OnDestroy()
{
	CDialogEx::OnDestroy();
	//PostQuitMessage(0);
	// TODO: 在此处添加消息处理程序代码
}

char* Order::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//函数功能：将字符串从wchar_t*转换成char*，即从unicode字符转换成多字节字符
    return pstr;
}

//下达订单
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
	AfxMessageBox(L"下单成功");
}

//下拉菜单
void Order::OnCbnDropdownCombo1()
{
	sublst.ResetContent();//清理下拉框列表

	sublst.SetItemHeight(0, 0);//设置下拉选项高度

	/*m_cbExample.SetFont(pFont, 1);*/

	if (!PathFileExists(_T(".\\product.ini")))//判断文件是否存在
	{
		return;
	}

	CString strFileName = _T(".\\product.ini");
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
			sublst.AddString(m_type);//显示到combobox控件上
		}
	}

	//关闭文件
	file.Close();
}
