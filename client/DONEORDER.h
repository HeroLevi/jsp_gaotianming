#pragma once


// DONEORDER �Ի���

class DONEORDER : public CDialogEx
{
	DECLARE_DYNAMIC(DONEORDER)

public:
	DONEORDER(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DONEORDER();

// �Ի�������
	enum { IDD = IDD_ORDERDONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton8();
	char* CStringToChar(CString str);
	CString id;
};
