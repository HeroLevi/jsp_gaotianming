#pragma once
#include "DONEORDER.h"
#include "WaitOrder.h"
// OrederManger �Ի���

class OrederManger : public CDialogEx
{
	DECLARE_DYNAMIC(OrederManger)

public:
	OrederManger(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~OrederManger();

// �Ի�������
	enum { IDD = IDD_OREDERMANGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	DONEORDER * doneorder;
	WaitOrder* waitorder;
};
