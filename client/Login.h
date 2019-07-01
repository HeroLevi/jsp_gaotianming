#pragma once

#include "TCPKernel.h"
#include "resource.h"
#include "Register.h"
#include "afxwin.h"
#include "UpdatePass.h"
// Login �Ի���

class Login : public CDialogEx
{
	DECLARE_DYNAMIC(Login)

public:
	Login(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Login();

// �Ի�������
	enum { IDD = IDD_lOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnCbnDropdownCombo1();
	afx_msg void OnBnClickedButton3();
public:
	bool flag1;
	bool flag2;
	IKernel* m_kernel;
	Register* regdlg;
	UpdatePass* m_update;
	CButton m_autoLogin;
	CButton m_remem;
	CComboBox m_subList;
	CString username;
	CString password;
	afx_msg void OnBnClickedButton1();
};
