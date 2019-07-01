#pragma once


// SelectMatter 对话框

class SelectMatter : public CDialogEx
{
	DECLARE_DYNAMIC(SelectMatter)

public:
	SelectMatter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SelectMatter();

// 对话框数据
	enum { IDD = IDD_SELECTMATTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
	CString id;
};
