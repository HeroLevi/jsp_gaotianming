#pragma once


// DelJob �Ի���

class DelJob : public CDialogEx
{
	DECLARE_DYNAMIC(DelJob)

public:
	DelJob(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DelJob();

// �Ի�������
	enum { IDD = IDD_DELJOB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
	CString jobid;
	CString sedid;
};
