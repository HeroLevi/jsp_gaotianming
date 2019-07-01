#pragma once


// DoneOderInfo 对话框

class DoneOderInfo : public CDialogEx
{
	DECLARE_DYNAMIC(DoneOderInfo)

public:
	DoneOderInfo(CString m_product,CString m_num,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DoneOderInfo();

// 对话框数据
	enum { IDD = IDD_DONERESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString product;
	CString num;
};
