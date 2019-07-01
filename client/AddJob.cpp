// AddJob.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "AddJob.h"
#include "afxdialogex.h"


// AddJob 对话框

IMPLEMENT_DYNAMIC(AddJob, CDialogEx)

AddJob::AddJob(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddJob::IDD, pParent)
	, job_num(_T(""))
	, seq(_T(""))
	, mec_num(_T(""))
	, time(_T(""))
	, num(0)
	, type(_T(""))
{

}

AddJob::~AddJob()
{
}

void AddJob::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, job_num);
	DDX_Text(pDX, IDC_EDIT8, seq);
	DDX_Text(pDX, IDC_EDIT5, mec_num);
	DDX_Text(pDX, IDC_EDIT9, time);
	DDX_CBString(pDX, IDC_COMBO1, type);
	DDX_Control(pDX, IDC_COMBO1, box_type);
}


BEGIN_MESSAGE_MAP(AddJob, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &AddJob::OnBnClickedButton1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &AddJob::OnCbnDropdownCombo1)
END_MESSAGE_MAP()


// AddJob 消息处理程序

char* AddJob::CStringToChar(CString str)
{
    const size_t strsize = (str.GetLength() + 1)*2;
    char* pstr = new char[strsize];
    size_t sz = 0;
    wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);  
	//函数功能：将字符串从wchar_t*转换成char*，即从unicode字符转换成多字节字符
    return pstr;
}

//添加工件完成
void AddJob::OnBnClickedButton1()
{
	UpdateData();
	ADDJOB_RQ addrq;
	addrq.m_nType = _DEF_PROTOCOL_ADDJOB_RQ;
	char* t = CStringToChar(job_num);
	addrq.jobi = *t - '0';
	t = CStringToChar(mec_num);
	addrq.meci = *t - '0';
	t = CStringToChar(time);
	addrq.time = *t - '0';
	t = CStringToChar(seq);
	addrq.seq = *t - '0';
	t = CStringToChar(type);
	addrq.type = *t - '0';
	theApp.GetKernel()->SendData((char*)&addrq,sizeof(addrq));
}


//工件类型下拉菜单
void AddJob::OnCbnDropdownCombo1()
{
	box_type.ResetContent();//清理下拉框列表

	box_type.SetItemHeight(0, 0);//设置下拉选项高度

	/*m_cbExample.SetFont(pFont, 1);*/

	if (!PathFileExists(_T(".\\JobInfo.ini")))//判断文件是否存在
	{
		return;
	}

	CString strFileName = _T(".\\JobInfo.ini");
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
