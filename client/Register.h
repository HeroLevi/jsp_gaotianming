#pragma once


// Register 对话框

class Register : public CDialogEx
{
	DECLARE_DYNAMIC(Register)

public:
	Register(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Register();

// 对话框数据
	enum { IDD = IDD_REGIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_username;
	CString m_password;
	CString m_duppassword;
	CString m_find;
};
