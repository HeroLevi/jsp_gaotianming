#pragma once


// LookOrder �Ի���

class LookOrder : public CDialogEx
{
	DECLARE_DYNAMIC(LookOrder)

public:
	LookOrder(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LookOrder();

// �Ի�������
	enum { IDD = IDD_LOOKORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString id;
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
};
