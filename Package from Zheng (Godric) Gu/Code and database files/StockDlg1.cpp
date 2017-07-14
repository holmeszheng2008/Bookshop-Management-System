// StockDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "BookManage.h"
#include "StockDlg1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStockDlg1 dialog

extern _ConnectionPtr m_pCon;  
extern _RecordsetPtr m_pRs; 
extern _CommandPtr m_pCom;

CStockDlg1::CStockDlg1(CWnd* pParent /*=NULL*/)
	: CDialog(CStockDlg1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStockDlg1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStockDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStockDlg1)
	DDX_Control(pDX, IDC_STOCK_LIST, m_StockList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStockDlg1, CDialog)
	//{{AFX_MSG_MAP(CStockDlg1)
	ON_NOTIFY(NM_CLICK, IDC_STOCK_LIST, OnClickStockList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockDlg1 message handlers
BOOL CStockDlg1::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD dwStyle=GetWindowLong(m_StockList.GetSafeHwnd(),GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;
	dwStyle|=LVS_REPORT;
	SetWindowLong(m_StockList.GetSafeHwnd(),GWL_STYLE,dwStyle);

	m_StockList.InsertColumn(0,"SERIAL NO.",LVCFMT_LEFT,80);
	m_StockList.InsertColumn(1,"STOCKING DATE",LVCFMT_LEFT,80);
	m_StockList.InsertColumn(2,"ISBN",LVCFMT_LEFT,100);
	m_StockList.InsertColumn(3,"BOOKNAME",LVCFMT_LEFT,130);
	m_StockList.InsertColumn(4,"AUTHOR",LVCFMT_LEFT,90);
	m_StockList.InsertColumn(5,"BOOKCONCERN",LVCFMT_LEFT,130);
	m_StockList.InsertColumn(6,"LABEL",LVCFMT_LEFT,90);
	m_StockList.InsertColumn(7,"PRICE",LVCFMT_LEFT,80);
	m_StockList.InsertColumn(8,"COUNT",LVCFMT_LEFT,80);

	m_StockList.SetExtendedStyle(LVS_EX_GRIDLINES);
    ::SendMessage(m_StockList.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
      LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	ShowStock();
	return TRUE;
}

//显示进货记录...
void CStockDlg1::ShowStock()
{
	m_pRs->raw_Close();
	CString sql;
	sql.Format("select * from bm_BookStock");
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	int index = 0;
	m_StockList.DeleteAllItems();
	while (!m_pRs->adoEOF)
	{
		index = m_StockList.InsertItem(m_StockList.GetItemCount(),
			(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)0)->Value);
		for(int col = 1;col <9;col++)
			m_StockList.SetItemText(index,col,(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)col)->Value);
		m_pRs->MoveNext();
	}
}

void CStockDlg1::OnClickStockList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
