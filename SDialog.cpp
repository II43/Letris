// SDialog.cpp : implementation file
//

#include "stdafx.h"
#include "hello.h"
#include "resource.h"
#include "SDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SDialog dialog


SDialog::SDialog(CWnd* pParent)
	: CDialog(SDialog::IDD, pParent)
{
	//ASSERT(pParent != NULL);
	SParentWindow = pParent;
	//{{AFX_DATA_INIT(SDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SDialog)
		
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SDialog, CDialog)
	//{{AFX_MSG_MAP(SDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SDialog message handlers

void SDialog::OnOK() 
{
	CEdit* ArtistEdit = (CEdit*) GetDlgItem(IDC_ARTISTEDIT);
	CEdit* AlbumEdit = (CEdit*) GetDlgItem(IDC_ALBUMEDIT);
	//ArtistEdit->GetWindowText(Shape);
	//AlbumEdit->GetWindowText(Direction);
	CDialog::OnOK();
	//((CMainWindow*)SParentWindow)->cx = 4;

}

