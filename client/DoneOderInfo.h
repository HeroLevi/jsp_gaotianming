#pragma once


// DoneOderInfo �Ի���

class DoneOderInfo : public CDialogEx
{
	DECLARE_DYNAMIC(DoneOderInfo)

public:
	DoneOderInfo(CString m_product,CString m_num,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DoneOderInfo();

// �Ի�������
	enum { IDD = IDD_DONERESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString product;
	CString num;
};
