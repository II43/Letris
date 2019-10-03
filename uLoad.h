#if !defined(AFX_ULOAD_H__680FF32D_818B_11D4_81CF_B5F69B07C538__INCLUDED_)
#define AFX_ULOAD_H__680FF32D_818B_11D4_81CF_B5F69B07C538__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// uLoad.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// uLoad dialog

class uLoad : public CDialog
{
// Construction
public:
	CString FileName;
	uLoad(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(uLoad)
	enum { IDD = IDD_LOAD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(uLoad)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(uLoad)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ULOAD_H__680FF32D_818B_11D4_81CF_B5F69B07C538__INCLUDED_)
