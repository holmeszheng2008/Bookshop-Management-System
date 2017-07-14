// StasticDlg3.cpp : implementation file
//

#include "stdafx.h"
#include "BookManage.h"
#include "StasticDlg3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStasticDlg3 dialog
extern _ConnectionPtr m_pCon;  
extern _RecordsetPtr m_pRs; 
extern _CommandPtr m_pCom;

CStasticDlg3::CStasticDlg3(CWnd* pParent /*=NULL*/)
	: CDialog(CStasticDlg3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStasticDlg3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStasticDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStasticDlg3)
	DDX_Control(pDX, IDC_VENDS_LIST, m_VendsList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStasticDlg3, CDialog)
	//{{AFX_MSG_MAP(CStasticDlg3)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStasticDlg3 message handlers
BOOL CStasticDlg3::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD dwStyle=GetWindowLong(m_VendsList.GetSafeHwnd(),GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;
	dwStyle|=LVS_REPORT;
	SetWindowLong(m_VendsList.GetSafeHwnd(),GWL_STYLE,dwStyle);

	m_VendsList.InsertColumn(0,"ISBN",LVCFMT_LEFT,80);
	m_VendsList.InsertColumn(1,"BOOKNAME",LVCFMT_LEFT,130);
	m_VendsList.InsertColumn(2,"AUTHOR",LVCFMT_LEFT,90);
	m_VendsList.InsertColumn(3,"BOOKCONCERN",LVCFMT_LEFT,130);
	m_VendsList.InsertColumn(4,"LABEL",LVCFMT_LEFT,90);
	m_VendsList.InsertColumn(5,"PRICE",LVCFMT_LEFT,80);
	m_VendsList.InsertColumn(6,"COUNT",LVCFMT_LEFT,80);
	m_VendsList.InsertColumn(7,"TOTAL PRICE",LVCFMT_LEFT,80);

	m_VendsList.SetExtendedStyle(LVS_EX_GRIDLINES);
    ::SendMessage(m_VendsList.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
      LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	ShowVends();
	return TRUE;
}

void CStasticDlg3::ShowVends()
{
	m_pRs->raw_Close();
	CString sql;
	sql.Format("select * from bm_BookSummry order by soldcount desc");
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	int index = 0;
	int x=0;
	m_VendsList.DeleteAllItems();
	while(!m_pRs->adoEOF && x<10)
	{
		++x;
		index = m_VendsList.InsertItem(m_VendsList.GetItemCount(),
			(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)0)->Value);
		for(int col = 1;col <8;col++)
			m_VendsList.SetItemText(index,col,(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)col)->Value);
		m_pRs->MoveNext();
	}
}
