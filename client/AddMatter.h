#pragma once


// AddMatter �Ի���

class AddMatter : public CDialogEx
{
	DECLARE_DYNAMIC(AddMatter)

public:
	AddMatter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddMatter();

// �Ի�������
	enum { IDD = IDD_ADDMATTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString id;
	CString num;
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
};
