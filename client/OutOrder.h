#pragma once


// OutOrder 对话框

class OutOrder : public CDialogEx
{
	DECLARE_DYNAMIC(OutOrder)

public:
	OutOrder(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~OutOrder();

// 对话框数据
	enum { IDD = IDD_OUTORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString id;
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
};
