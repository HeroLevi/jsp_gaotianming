#pragma once


// Captcha 对话框

class Captcha : public CDialogEx
{
	DECLARE_DYNAMIC(Captcha)

public:
	Captcha(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Captcha();

// 对话框数据
	enum { IDD = IDD_CAPTCHA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_captcha;
	CStatic* pWnd;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
