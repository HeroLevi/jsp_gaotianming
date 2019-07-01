#pragma once
#include "AddDevice.h"
#include "UpdateDevice.h"
#include "SelectMac.h"
#include "DelMac.h"
// MecPropety �Ի���

class MecPropety : public CDialogEx
{
	DECLARE_DYNAMIC(MecPropety)

public:
	MecPropety(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MecPropety();

// �Ի�������
	enum { IDD = IDD_PROPETY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
public:
	AddDevice *add;
	UpdateDevice *update;
	SelectMac* selectmac;
	DelMac* delmac;
};
