#pragma once


// DelJob 对话框

class DelJob : public CDialogEx
{
	DECLARE_DYNAMIC(DelJob)

public:
	DelJob(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DelJob();

// 对话框数据
	enum { IDD = IDD_DELJOB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
	CString jobid;
	CString sedid;
};
