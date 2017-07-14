// StockDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "BookManage.h"
#include "StockDlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStockDlg2 dialog


CStockDlg2::CStockDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CStockDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStockDlg2)
	m_Author = _T("");
	m_Count = _T("");
	m_ISBN = _T("");
	m_Name = _T("");
	m_Price = _T("");
	m_Supply = _T("");
	//}}AFX_DATA_INIT
}


void CStockDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStockDlg2)
	DDX_Control(pDX, IDC_SUPPLY_LIST, m_StockSupplyList);
	DDX_Text(pDX, IDC_STOCK_AUTHOR, m_Author);
	DDX_Text(pDX, IDC_STOCK_COUNT, m_Count);
	DDX_Text(pDX, IDC_STOCK_ISBN, m_ISBN);
	DDX_Text(pDX, IDC_STOCK_NAME, m_Name);
	DDX_Text(pDX, IDC_STOCK_PRICE, m_Price);
	DDX_Text(pDX, IDC_STOCK_SUPPLY, m_Supply);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStockDlg2, CDialog)
	//{{AFX_MSG_MAP(CStockDlg2)
	ON_NOTIFY(NM_CLICK, IDC_SUPPLY_LIST, OnClickSupplyList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockDlg2 message handlers
BOOL CStockDlg2::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD dwStyle=GetWindowLong(m_StockSupplyList.GetSafeHwnd(),GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;
	dwStyle|=LVS_REPORT;
	SetWindowLong(m_StockSupplyList.GetSafeHwnd(),GWL_STYLE,dwStyle);

	m_StockSupplyList.InsertColumn(0,"ISBN",LVCFMT_LEFT,80);
	m_StockSupplyList.InsertColumn(1,"BOOKNAME",LVCFMT_LEFT,130);
	m_StockSupplyList.InsertColumn(2,"AUTHOR",LVCFMT_LEFT,90);
	m_StockSupplyList.InsertColumn(3,"BOOKCONCERN",LVCFMT_LEFT,130);
	m_StockSupplyList.InsertColumn(4,"SUPPLY PRICE",LVCFMT_LEFT,80);
	m_StockSupplyList.InsertColumn(5,"COUNT",LVCFMT_LEFT,80);

	m_StockSupplyList.SetExtendedStyle(LVS_EX_GRIDLINES);
    ::SendMessage(m_StockSupplyList.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
      LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	delIndex = -1;
	return TRUE;
}

void CStockDlg2::OnClickSupplyList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	delIndex = m_StockSupplyList.GetSelectionMark();
	*pResult = 0;
}


