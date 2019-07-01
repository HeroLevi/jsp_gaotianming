#pragma once


// DONEORDER 对话框

class DONEORDER : public CDialogEx
{
	DECLARE_DYNAMIC(DONEORDER)

public:
	DONEORDER(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DONEORDER();

// 对话框数据
	enum { IDD = IDD_ORDERDONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton8();
	char* CStringToChar(CString str);
	CString id;
};
