#pragma once


// LookResult �Ի���

class LookResult : public CDialogEx
{
	DECLARE_DYNAMIC(LookResult)

public:
	LookResult(CString m_time,CString m_product,CString m_num,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LookResult();

// �Ի�������
	enum { IDD = IDD_WAITRESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString time;
	CString product;
	CString num;
};
