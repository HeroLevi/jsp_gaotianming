#pragma once
#include "afxwin.h"


// Order �Ի���

class Order : public CDialogEx
{
	DECLARE_DYNAMIC(Order)

public:
	Order(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Order();

// �Ի�������
	enum { IDD = IDD_ORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
