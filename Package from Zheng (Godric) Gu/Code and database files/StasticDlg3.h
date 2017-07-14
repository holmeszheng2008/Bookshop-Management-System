#if !defined(AFX_STASTICDLG3_H__2B36DB91_51C8_436F_BEFF_A99AFEFDFE86__INCLUDED_)
#define AFX_STASTICDLG3_H__2B36DB91_51C8_436F_BEFF_A99AFEFDFE86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StasticDlg3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStasticDlg3 dialog

class CStasticDlg3 : public CDialog
{
// Construction
public:
	CStasticDlg3(CWnd* pParent = NULL);   // standard constructor
	void ShowVends();

// Dialog Data
	//{{AFX_DATA(CStasticDlg3)
	enum { IDD = IDD_STASTIC_DIALOG3 };
	CListCtrl	m_VendsList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStasticDlg3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStasticDlg3)
	virtual BOOL OnInitDialog();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STASTICDLG3_H__2B36DB91_51C8_436F_BEFF_A99AFEFDFE86__INCLUDED_)
