#pragma once

#include "TCPKernel.h"
#include "resource.h"
#include "Register.h"
#include "afxwin.h"
#include "UpdatePass.h"
// Login 对话框

class Login : public CDialogEx
{
	DECLARE_DYNAMIC(Login)

public:
	Login(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Login();

// 对话框数据
	enum { IDD = IDD_lOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
