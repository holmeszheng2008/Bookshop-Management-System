// StasticManage.cpp : implementation file
//

#include "stdafx.h"
#include "BookManage.h"
#include "StasticManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStasticManage dialog
extern _ConnectionPtr m_pCon;  
extern _RecordsetPtr m_pRs; 
extern _CommandPtr m_pCom;

extern int PID;

CStasticManage::CStasticManage(CWnd* pParent /*=NULL*/)
	: CDialog(CStasticManage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStasticManage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStasticManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStasticManage)
	DDX_Control(pDX, IDC_STASTIC_TAB, m_StasticTab);
	//}}AFX_DATA_MAP
}

CStasticManage p_stastic;

BEGIN_MESSAGE_MAP(CStasticManage, CDialog)
	//{{AFX_MSG_MAP(CStasticManage)
	ON_NOTIFY(TCN_SELCHANGE, IDC_STASTIC_TAB, OnSelchangeStasticTab)
	ON_COMMAND(ID_EXIT, OnExitStastic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStasticManage message handlers
BOOL CStasticManage::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	stasticdlg1 = new CStasticDlg1();
	stasticdlg2 = new CStasticDlg2();
	stasticdlg3 = new CStasticDlg3();
	//将对话框贴在标签上...
	stasticdlg1->Create(IDD_STASTIC_DIALOG1,&m_StasticTab);
	stasticdlg2->Create(IDD_STASTIC_DIALOG2,&m_StasticTab);
	stasticdlg3->Create(IDD_STASTIC_DIALOG3,&m_StasticTab);

	m_StasticTab.InsertItem(0,"SOLD RECORD",0);
	m_StasticTab.InsertItem(1,"SOLD AMOUNT",1);
	m_StasticTab.InsertItem(2,"SOLD RANKING",2);
	m_StasticTab.SetMinTabWidth(100);
	m_StasticTab.SetCurSel(PID);
	DoTab(PID);
	return TRUE;
}

void CStasticManage::OnSelchangeStasticTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int select = m_StasticTab.GetCurSel();
	if(select >= 0)
		DoTab(select);
	*pResult = 0;
}

void CStasticManage::SetDlgState(CWnd *pWnd, BOOL bShow)
{
	pWnd->EnableWindow(bShow);
	if(bShow)
	{
		pWnd->ShowWindow(SW_SHOW);
		pWnd->CenterWindow();
	}
	else
		pWnd->ShowWindow(SW_HIDE);
}

void CStasticManage::DoTab(int nPid)
{
	if(nPid > 2) nPid = 2;
	if(nPid < 0) nPid =	0;
	
	BOOL iPid[3];
	iPid[0]=iPid[1]=iPid[2]=FALSE;
	iPid[nPid]=TRUE;

	SetDlgState(stasticdlg1,iPid[0]);
	SetDlgState(stasticdlg2,iPid[1]);
	SetDlgState(stasticdlg3,iPid[2]);
}

void CStasticManage::OnExitStastic() 
{
	// TODO: Add your command handler code here
	EndDialog(0);
}
