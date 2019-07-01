#pragma once


// DelMac 对话框

class DelMac : public CDialogEx
{
	DECLARE_DYNAMIC(DelMac)

public:
	DelMac(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DelMac();

// 对话框数据
	enum { IDD = IDD_DELMAC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
	CString macid;
};
