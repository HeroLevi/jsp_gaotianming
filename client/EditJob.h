#pragma once
#include "AddJob.h"
#include "UpdateJob.h"
#include "SelectJob.h"
#include "DelJob.h"
// EditJob 对话框

class EditJob : public CDialogEx
{
	DECLARE_DYNAMIC(EditJob)

public:
	EditJob(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~EditJob();

// 对话框数据
	enum { IDD = IDD_EDITJOB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
public:
	AddJob* addjob;
	UpdateJob* updatejob;
	SelectJob* selectjob;
	DelJob* deljob;
};
