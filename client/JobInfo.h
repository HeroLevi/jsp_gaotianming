#pragma once


// JobInfo �Ի���

class JobInfo : public CDialogEx
{
	DECLARE_DYNAMIC(JobInfo)

public:
	JobInfo(CString m_usemac,CString m_time,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~JobInfo();

// �Ի�������
	enum { IDD = IDD_JOBINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString usemac;
	CString time;
};
