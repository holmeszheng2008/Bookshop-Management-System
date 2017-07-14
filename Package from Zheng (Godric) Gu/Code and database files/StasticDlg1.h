#if !defined(AFX_STASTICDLG1_H__74FF0BE7_0D8F_4CA2_B270_CB277802F70D__INCLUDED_)
#define AFX_STASTICDLG1_H__74FF0BE7_0D8F_4CA2_B270_CB277802F70D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StasticDlg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStasticDlg1 dialog

class CStasticDlg1 : public CDialog
{
// Construction
public:
	CStasticDlg1(CWnd* pParent = NULL);   // standard constructor
	void ShowVend();
// Dialog Data
	//{{AFX_DATA(CStasticDlg1)
	enum { IDD = IDD_STASTIC_DIALOG1 };
	CListCtrl	m_VendList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStasticDlg1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStasticDlg1)
	virtual BOOL OnInitDialog();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STASTICDLG1_H__74FF0BE7_0D8F_4CA2_B270_CB277802F70D__INCLUDED_)
