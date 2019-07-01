// EditJob.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_jsp.h"
#include "EditJob.h"
#include "afxdialogex.h"


// EditJob �Ի���

IMPLEMENT_DYNAMIC(EditJob, CDialogEx)

EditJob::EditJob(CWnd* pParent /*=NULL*/)
	: CDialogEx(EditJob::IDD, pParent)
{
	addjob = new AddJob;
	updatejob = new UpdateJob;
	selectjob = new SelectJob;
	deljob = new DelJob;
}

EditJob::~EditJob()
{
}

void EditJob::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EditJob, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &EditJob::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &EditJob::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &EditJob::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &EditJob::OnBnClickedButton4)
END_MESSAGE_MAP()


// EditJob ��Ϣ�������

//��ӹ���
void EditJob::OnBnClickedButton2()
{
	addjob->DoModal();
}

//��ѯ����
void EditJob::OnBnClickedButton1()
{
	selectjob->DoModal();
}

//ɾ������
void EditJob::OnBnClickedButton3()
{
	deljob->DoModal();
}

//�޸Ĺ�����Ϣ
void EditJob::OnBnClickedButton4()
{
	updatejob->DoModal();
}
