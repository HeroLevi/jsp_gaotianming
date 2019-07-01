#pragma once
#include "Packdef.h"
#include <vector>
#include "afxwin.h"
// AddJob 对话框

class AddJob : public CDialogEx
{
	DECLARE_DYNAMIC(AddJob)

public:
	AddJob(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddJob();

// 对话框数据
	enum { IDD = IDD_ADDJOB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
	CString job_num;//工件编号
	CString seq;//工序
	CString mec_num;//使用机器
	CString time;//使用时间
	int num;
	CString type;
	CComboBox box_type;
	afx_msg void OnCbnDropdownCombo1();
};
