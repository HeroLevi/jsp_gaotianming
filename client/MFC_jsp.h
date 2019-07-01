
// MFC_jsp.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "TCPKernel.h"
#include "MFC_jspDlg.h"

// CMFC_jspApp:
// 有关此类的实现，请参阅 MFC_jsp.cpp
//

class CMFC_jspApp : public CWinApp
{
public:
	CMFC_jspApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

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