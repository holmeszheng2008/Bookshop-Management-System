// StasticDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "BookManage.h"
#include "StasticDlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStasticDlg2 dialog
extern _ConnectionPtr m_pCon;  
extern _RecordsetPtr m_pRs; 
extern _CommandPtr m_pCom;

CStasticDlg2::CStasticDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CStasticDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStasticDlg2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStasticDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStasticDlg2)
	DDX_Control(pDX, IDC_VENDBYDAY_LIST, m_VendDayList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStasticDlg2, CDialog)
	//{{AFX_MSG_MAP(CStasticDlg2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStasticDlg2 message handlers
BOOL CStasticDlg2::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD dwStyle=GetWindowLong(m_VendDayList.GetSafeHwnd(),GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;
	dwStyle|=LVS_REPORT;
	SetWindowLong(m_VendDayList.GetSafeHwnd(),GWL_STYLE,dwStyle);

	m_VendDayList.InsertColumn(0,"ISBN",LVCFMT_LEFT,80);
	m_VendDayList.InsertColumn(1,"BOOKNAME",LVCFMT_LEFT,130);
	m_VendDayList.InsertColumn(2,"AUTHOR",LVCFMT_LEFT,90);
	m_VendDayList.InsertColumn(3,"BOOKCOCERN",LVCFMT_LEFT,130);
	m_VendDayList.InsertColumn(4,"LABEL",LVCFMT_LEFT,90);
	m_VendDayList.InsertColumn(5,"PRICE",LVCFMT_LEFT,80);
	m_VendDayList.InsertColumn(6,"COUNT",LVCFMT_LEFT,80);
	m_VendDayList.InsertColumn(7,"TOTAL PRICE",LVCFMT_LEFT,80);

	m_VendDayList.SetExtendedStyle(LVS_EX_GRIDLINES);
    ::SendMessage(m_VendDayList.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
      LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	ShowVendDay();
	return TRUE;
}

void CStasticDlg2::ShowVendDay()
{
	m_pRs->raw_Close();
	CString sql;
	sql.Format("select * from bm_BookSummry");
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	int index = 0;
	m_VendDayList.DeleteAllItems();
	while(!m_pRs->adoEOF)
	{
		index = m_VendDayList.InsertItem(m_VendDayList.GetItemCount(),
			(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)0)->Value);
		for(int col = 1;col <8;col++)
			m_VendDayList.SetItemText(index,col,(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)col)->Value);
		m_pRs->MoveNext();
	}
}