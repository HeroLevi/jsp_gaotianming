#pragma once
#include "AddJob.h"
#include "UpdateJob.h"
#include "SelectJob.h"
#include "DelJob.h"
// EditJob �Ի���

class EditJob : public CDialogEx
{
	DECLARE_DYNAMIC(EditJob)

public:
	EditJob(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~EditJob();

// �Ի�������
	enum { IDD = IDD_EDITJOB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
