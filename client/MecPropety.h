#pragma once
#include "AddDevice.h"
#include "UpdateDevice.h"
#include "SelectMac.h"
#include "DelMac.h"
// MecPropety 对话框

class MecPropety : public CDialogEx
{
	DECLARE_DYNAMIC(MecPropety)

public:
	MecPropety(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MecPropety();

// 对话框数据
	enum { IDD = IDD_PROPETY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
