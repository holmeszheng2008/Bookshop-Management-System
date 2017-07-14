#if !defined(AFX_STASTICMANAGE_H__84630933_D9C6_4D50_9A96_30D37ECB565C__INCLUDED_)
#define AFX_STASTICMANAGE_H__84630933_D9C6_4D50_9A96_30D37ECB565C__INCLUDED_

#include "StasticDlg1.h"	// Added by ClassView
#include "StasticDlg2.h"	// Added by ClassView
#include "StasticDlg3.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StasticManage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStasticManage dialog

class CStasticManage : public CDialog
{
// Construction
public:
	void DoTab(int nPid);
	void SetDlgState(CWnd *pWnd, BOOL bShow);
	CStasticDlg3 *stasticdlg3;
	CStasticDlg2 *stasticdlg2;
	CStasticDlg1 *stasticdlg1;
	CStasticManage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStasticManage)
	enum { IDD = IDD_STASTIC_DIALOG };
	CTabCtrl	m_StasticTab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStasticManage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStasticManage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeStasticTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnExitStastic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STASTICMANAGE_H__84630933_D9C6_4D50_9A96_30D37ECB565C__INCLUDED_)
