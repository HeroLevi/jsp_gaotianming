
// MFC_jspDlg.h : ͷ�ļ�
//

#pragma once
#include <vector>
#include "Packdef.h"
#include "MecPropety.h"
#include "EditJob.h"
#include "afxcmn.h"
#include "Matter.h"
#include "OrederManger.h"

// CMFC_jspDlg �Ի���
class CMFC_jspDlg : public CDialogEx
{
// ����
public:
	CMFC_jspDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MAINDLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
