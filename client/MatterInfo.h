#pragma once


// MatterInfo �Ի���

class MatterInfo : public CDialogEx
{
	DECLARE_DYNAMIC(MatterInfo)

public:
	MatterInfo(CString m_Left,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MatterInfo();

// �Ի�������
	enum { IDD = IDD_MATTERINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString Left;
};
