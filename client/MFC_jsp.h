
// MFC_jsp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "TCPKernel.h"
#include "MFC_jspDlg.h"

// CMFC_jspApp:
// �йش����ʵ�֣������ MFC_jsp.cpp
//

class CMFC_jspApp : public CWinApp
{
public:
	CMFC_jspApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
private:
	IKernel *m_pKernel;
public:
	IKernel * GetKernel()
	{
		return m_pKernel;
	}
	CMFC_jspDlg *dlg;
	
};

extern CMFC_jspApp theApp;