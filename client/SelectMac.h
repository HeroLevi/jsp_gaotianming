#pragma once


// SelectMac �Ի���

class SelectMac : public CDialogEx
{
	DECLARE_DYNAMIC(SelectMac)

public:
	SelectMac(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SelectMac();

// �Ի�������
	enum { IDD = IDD_SELECTMAC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
	CString macid;
};
