#if !defined(AFX_USAVE_H__680FF32C_818B_11D4_81CF_B5F69B07C538__INCLUDED_)
#define AFX_USAVE_H__680FF32C_818B_11D4_81CF_B5F69B07C538__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// uSave.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// uSave dialog

class uSave : public CDialog
{
// Construction
public:
	CString FileName;
	uSave(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(uSave)
	enum { IDD = IDD_SAVE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(uSave)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(uSave)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USAVE_H__680FF32C_818B_11D4_81CF_B5F69B07C538__INCLUDED_)
