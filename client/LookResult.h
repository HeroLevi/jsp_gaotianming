#pragma once


// LookResult 对话框

class LookResult : public CDialogEx
{
	DECLARE_DYNAMIC(LookResult)

public:
	LookResult(CString m_time,CString m_product,CString m_num,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LookResult();

// 对话框数据
	enum { IDD = IDD_WAITRESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString time;
	CString product;
	CString num;
};
