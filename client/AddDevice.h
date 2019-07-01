#pragma once
#include "Packdef.h"
#include "afxwin.h"

// AddDevice 对话框

class AddDevice : public CDialogEx
{
	DECLARE_DYNAMIC(AddDevice)

public:
	AddDevice(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddDevice();

// 对话框数据
	enum { IDD = IDD_ADDMEC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
	CString id;
	CString type;
	CString year;
	CComboBox box_type;
	afx_msg void OnCbnDropdownCombo1();
};
