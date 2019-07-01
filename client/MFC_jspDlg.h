
// MFC_jspDlg.h : 头文件
//

#pragma once
#include <vector>
#include "Packdef.h"
#include "MecPropety.h"
#include "EditJob.h"
#include "afxcmn.h"
#include "Matter.h"
#include "OrederManger.h"

// CMFC_jspDlg 对话框
class CMFC_jspDlg : public CDialogEx
{
// 构造
public:
	CMFC_jspDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MAINDLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	Login *logindlg;
	afx_msg void OnBnClickedButton5();
	char* CStringToChar(CString str);
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton1();
	MecPropety* mec;
	EditJob* editjob;
	CBitmap m_Back;
	Matter *matter;
	OrederManger* orderman;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
};
