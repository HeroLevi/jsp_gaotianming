#pragma once

#include "AddMatter.h"
#include "DelMatter.h"
#include "SelectMatter.h"
// Matter �Ի���

class Matter : public CDialogEx
{
	DECLARE_DYNAMIC(Matter)

public:
	Matter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Matter();

// �Ի�������
	enum { IDD = IDD_Matter };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	AddMatter* addmatter;
	DelMatter* delmatter;
	SelectMatter* selectmatter;
};
