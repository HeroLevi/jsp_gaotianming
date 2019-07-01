#pragma once


// GTT 对话框

class GTT : public CDialogEx
{
	DECLARE_DYNAMIC(GTT)

public:
	GTT(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~GTT();

// 对话框数据
	enum { IDD = IDD_GTT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnClose();
	CStatic* pWnd;
};
