#pragma once


// SelectJob �Ի���

class SelectJob : public CDialogEx
{
	DECLARE_DYNAMIC(SelectJob)

public:
	SelectJob(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SelectJob();

// �Ի�������
	enum { IDD = IDD_SELECTJOB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
	CString jobid;
	CString seqid;
};
