#pragma once


// MatterInfo 对话框

class MatterInfo : public CDialogEx
{
	DECLARE_DYNAMIC(MatterInfo)

public:
	MatterInfo(CString m_Left,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MatterInfo();

// 对话框数据
	enum { IDD = IDD_MATTERINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString Left;
};
