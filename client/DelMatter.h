#pragma once


// DelMatter �Ի���

class DelMatter : public CDialogEx
{
	DECLARE_DYNAMIC(DelMatter)

public:
	DelMatter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DelMatter();

// �Ի�������
	enum { IDD = IDD_DELMATTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
	CString matterid;
	CString num;
};
