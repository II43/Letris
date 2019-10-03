// uLoad.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "utetris.h"
#include "uLoad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// uLoad dialog


uLoad::uLoad(CWnd* pParent /*=NULL*/)
	: CDialog(uLoad::IDD, pParent)
{
	FileName = "utetris.sav";
	//{{AFX_DATA_INIT(uLoad)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void uLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(uLoad)
	DDX_Text(pDX,IDC_FILENAMEEDIT,FileName);
    DDV_MaxChars(pDX,FileName,28);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(uLoad, CDialog)
	//{{AFX_MSG_MAP(uLoad)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// uLoad message handlers
