#pragma once


// SelectMac 对话框

class SelectMac : public CDialogEx
{
	DECLARE_DYNAMIC(SelectMac)

public:
	SelectMac(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SelectMac();

// 对话框数据
	enum { IDD = IDD_SELECTMAC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
	CString macid;
};
