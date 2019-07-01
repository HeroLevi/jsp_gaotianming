#pragma once
#include "DONEORDER.h"
#include "WaitOrder.h"
// OrederManger 对话框

class OrederManger : public CDialogEx
{
	DECLARE_DYNAMIC(OrederManger)

public:
	OrederManger(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~OrederManger();

// 对话框数据
	enum { IDD = IDD_OREDERMANGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	DONEORDER * doneorder;
	WaitOrder* waitorder;
};
