// AV_Dialog.cpp : implementation file
//

#include "stdafx.h"
#include "AV_Dialog.h"
#include "afxdialogex.h"


// AV_Dialog dialog

IMPLEMENT_DYNAMIC(AV_Dialog, CDialog)

AV_Dialog::AV_Dialog(CWnd* pParent /*=NULL*/)
	: CDialog(AV_Dialog::IDD, pParent)
{

}

AV_Dialog::~AV_Dialog()
{
}

void AV_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AV_Dialog, CDialog)
END_MESSAGE_MAP()


// AV_Dialog message handlers
