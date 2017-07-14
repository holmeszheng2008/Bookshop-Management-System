#if !defined(AFX_ADDDLG_H__3A6622F3_BCFF_4982_9F81_7DDAF847D22F__INCLUDED_)
#define AFX_ADDDLG_H__3A6622F3_BCFF_4982_9F81_7DDAF847D22F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ADDDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CADDDlg dialog

class CADDDlg : public CDialog
{
// Construction
public:
	CADDDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CADDDlg)
	enum { IDD = IDD_ADD };
	CString	m_USERNAME;
	CString	m_PASSPORT;
	int pow;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADDDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CADDDlg)
	afx_msg void OnCollate();
	afx_msg void OnQuit();
	afx_msg void On1();
	afx_msg void On0();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDDLG_H__3A6622F3_BCFF_4982_9F81_7DDAF847D22F__INCLUDED_)
