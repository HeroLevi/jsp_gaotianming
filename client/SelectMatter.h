#pragma once


// SelectMatter �Ի���

class SelectMatter : public CDialogEx
{
	DECLARE_DYNAMIC(SelectMatter)

public:
	SelectMatter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SelectMatter();

// �Ի�������
	enum { IDD = IDD_SELECTMATTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
	CString id;
};
