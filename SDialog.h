#if !defined(AFX_SDIALOG_H__A1711B64_6EB4_11D4_81CF_C85D0C61A836__INCLUDED_)
#define AFX_SDIALOG_H__A1711B64_6EB4_11D4_81CF_C85D0C61A836__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SDialog dialog

class SDialog : public CDialog
{
// Construction
public:	
	SDialog(CWnd* pParent); // standard constructor
	//BOOL Create();
// Dialog Data
	//{{AFX_DATA(SDialog)
	enum { IDD = IDD_SDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	//CString Artist,Album;
	int x,y,Shape,Direction;
protected:
	CWnd* SParentWindow;
	// Generated message map functions
	//{{AFX_MSG(SDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDIALOG_H__A1711B64_6EB4_11D4_81CF_C85D0C61A836__INCLUDED_)
