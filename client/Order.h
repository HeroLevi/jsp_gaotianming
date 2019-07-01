#pragma once
#include "afxwin.h"


// Order 对话框

class Order : public CDialogEx
{
	DECLARE_DYNAMIC(Order)

public:
	Order(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Order();

// 对话框数据
	enum { IDD = IDD_ORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	CString time;
	CString num;
	CString product;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnDropdownCombo1();
	char* CStringToChar(CString str);
	CComboBox sublst;
	CString order_id;
};
