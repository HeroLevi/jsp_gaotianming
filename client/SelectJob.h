#pragma once


// SelectJob 对话框

class SelectJob : public CDialogEx
{
	DECLARE_DYNAMIC(SelectJob)

public:
	SelectJob(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SelectJob();

// 对话框数据
	enum { IDD = IDD_SELECTJOB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
	CString jobid;
	CString seqid;
};
