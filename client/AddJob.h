#pragma once
#include "Packdef.h"
#include <vector>
#include "afxwin.h"
// AddJob �Ի���

class AddJob : public CDialogEx
{
	DECLARE_DYNAMIC(AddJob)

public:
	AddJob(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddJob();

// �Ի�������
	enum { IDD = IDD_ADDJOB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char* CStringToChar(CString str);
	CString job_num;//�������
	CString seq;//����
	CString mec_num;//ʹ�û���
	CString time;//ʹ��ʱ��
	int num;
	CString type;
	CComboBox box_type;
	afx_msg void OnCbnDropdownCombo1();
};
