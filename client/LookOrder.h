#pragma once


// LookOrder 对话框

class LookOrder : public CDialogEx
{
	DECLARE_DYNAMIC(LookOrder)

public:
	LookOrder(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LookOrder();

// 对话框数据
	enum { IDD = IDD_LOOKORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString id;
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
};
