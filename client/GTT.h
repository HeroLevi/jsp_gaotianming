#pragma once


// GTT �Ի���

class GTT : public CDialogEx
{
	DECLARE_DYNAMIC(GTT)

public:
	GTT(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GTT();

// �Ի�������
	enum { IDD = IDD_GTT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnClose();
	CStatic* pWnd;
};
