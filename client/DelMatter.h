#pragma once


// DelMatter 对话框

class DelMatter : public CDialogEx
{
	DECLARE_DYNAMIC(DelMatter)

public:
	DelMatter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DelMatter();

// 对话框数据
	enum { IDD = IDD_DELMATTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
	CString matterid;
	CString num;
};
