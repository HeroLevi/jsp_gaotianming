#pragma once


// Captcha �Ի���

class Captcha : public CDialogEx
{
	DECLARE_DYNAMIC(Captcha)

public:
	Captcha(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Captcha();

// �Ի�������
	enum { IDD = IDD_CAPTCHA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_captcha;
	CStatic* pWnd;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
