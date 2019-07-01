#pragma once


// JobInfo 对话框

class JobInfo : public CDialogEx
{
	DECLARE_DYNAMIC(JobInfo)

public:
	JobInfo(CString m_usemac,CString m_time,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~JobInfo();

// 对话框数据
	enum { IDD = IDD_JOBINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString usemac;
	CString time;
};
