#pragma once
#include "afxwin.h"


// MacInfo �Ի���

class MacInfo : public CDialogEx
{
	DECLARE_DYNAMIC(MacInfo)

public:
	MacInfo(CString m_type,CString m_year,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MacInfo();

// �Ի�������
	enum { IDD = IDD_MACINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit type_ctl;
	CString type;
	CString year;
};
