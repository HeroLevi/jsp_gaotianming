#pragma once


// DelMac �Ի���

class DelMac : public CDialogEx
{
	DECLARE_DYNAMIC(DelMac)

public:
	DelMac(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DelMac();

// �Ի�������
	enum { IDD = IDD_DELMAC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
	CString macid;
};
