#pragma once

#include "AddMatter.h"
#include "DelMatter.h"
#include "SelectMatter.h"
// Matter 对话框

class Matter : public CDialogEx
{
	DECLARE_DYNAMIC(Matter)

public:
	Matter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Matter();

// 对话框数据
	enum { IDD = IDD_Matter };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	AddMatter* addmatter;
	DelMatter* delmatter;
	SelectMatter* selectmatter;
};
