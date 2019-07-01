#pragma once
#include "afxwin.h"


// MacInfo 对话框

class MacInfo : public CDialogEx
{
	DECLARE_DYNAMIC(MacInfo)

public:
	MacInfo(CString m_type,CString m_year,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MacInfo();

// 对话框数据
	enum { IDD = IDD_MACINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit type_ctl;
	CString type;
	CString year;
};
