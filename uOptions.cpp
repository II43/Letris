// uOptions.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "utetris.h"
#include "uOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// uOptions dialog


uOptions::uOptions(CWnd* pParent /*=NULL*/)
	: CDialog(uOptions::IDD, pParent)
{
	Speed = 0;
	Shape = 0x1100;
	//{{AFX_DATA_INIT(uOptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void uOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(uOptions)
	DDX_Text(pDX,IDC_SPEEDEDIT,Speed);
    DDV_MaxChars(pDX,Speed,4);
	DDX_Text(pDX,IDC_NEXTSHAPEEDIT,Shape);
    DDV_MaxChars(pDX,Shape,4);
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(uOptions, CDialog)
	//{{AFX_MSG_MAP(uOptions)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// uOptions message handlers
