#if !defined(AFX_STASTICDLG2_H__F3331EC2_BCEF_4BF9_B802_B4D96544C956__INCLUDED_)
#define AFX_STASTICDLG2_H__F3331EC2_BCEF_4BF9_B802_B4D96544C956__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StasticDlg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStasticDlg2 dialog

class CStasticDlg2 : public CDialog
{
// Construction
public:
	CStasticDlg2(CWnd* pParent = NULL);   // standard constructor
	void ShowVendDay();

// Dialog Data
	//{{AFX_DATA(CStasticDlg2)
	enum { IDD = IDD_STASTIC_DIALOG2 };
	CListCtrl	m_VendDayList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStasticDlg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStasticDlg2)
	virtual BOOL OnInitDialog();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STASTICDLG2_H__F3331EC2_BCEF_4BF9_B802_B4D96544C956__INCLUDED_)
