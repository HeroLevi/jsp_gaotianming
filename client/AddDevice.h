#pragma once
#include "Packdef.h"
#include "afxwin.h"

// AddDevice �Ի���

class AddDevice : public CDialogEx
{
	DECLARE_DYNAMIC(AddDevice)

public:
	AddDevice(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddDevice();

// �Ի�������
	enum { IDD = IDD_ADDMEC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
