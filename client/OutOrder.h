#pragma once


// OutOrder �Ի���

class OutOrder : public CDialogEx
{
	DECLARE_DYNAMIC(OutOrder)

public:
	OutOrder(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~OutOrder();

// �Ի�������
	enum { IDD = IDD_OUTORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString id;
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
};
