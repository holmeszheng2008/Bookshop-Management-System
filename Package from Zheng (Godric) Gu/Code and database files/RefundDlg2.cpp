// RefundDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "BookManage.h"
#include "RefundDlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRefundDlg2 dialog

extern _ConnectionPtr m_pCon;  
extern _RecordsetPtr m_pRs; 
extern _CommandPtr m_pCom;

CRefundDlg2::CRefundDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CRefundDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRefundDlg2)
	//}}AFX_DATA_INIT
}


void CRefundDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRefundDlg2)
	DDX_Control(pDX, IDC_REFUND_LIST, m_RefundList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRefundDlg2, CDialog)
	//{{AFX_MSG_MAP(CRefundDlg2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRefundDlg2 message handlers
BOOL CRefundDlg2::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD dwStyle=GetWindowLong(m_RefundList.GetSafeHwnd(),GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;
	dwStyle|=LVS_REPORT;
	SetWindowLong(m_RefundList.GetSafeHwnd(),GWL_STYLE,dwStyle);

	m_RefundList.InsertColumn(0,"SERIAL NO",LVCFMT_LEFT,80);
	m_RefundList.InsertColumn(1,"REFUND DATE",LVCFMT_LEFT,110);
	m_RefundList.InsertColumn(2,"ISBN",LVCFMT_LEFT,100);
	m_RefundList.InsertColumn(3,"BOOKNAME",LVCFMT_LEFT,130);
	m_RefundList.InsertColumn(4,"AUTHOR",LVCFMT_LEFT,90);
	m_RefundList.InsertColumn(5,"BOOKCONCERN",LVCFMT_LEFT,130);
	m_RefundList.InsertColumn(6,"LABEL",LVCFMT_LEFT,90);
	m_RefundList.InsertColumn(7,"PRICE",LVCFMT_LEFT,80);
	m_RefundList.InsertColumn(8,"COUNT",LVCFMT_LEFT,80);

	m_RefundList.SetExtendedStyle(LVS_EX_GRIDLINES);
    ::SendMessage(m_RefundList.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
      LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	ShowRefund();
	return TRUE;
}

//显示进货记录...
void CRefundDlg2::ShowRefund()
{
	m_pRs->raw_Close();
	CString sql;
	sql.Format("select * from bm_BookRefund");
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	int index = 0;
	m_RefundList.DeleteAllItems();
	while (!m_pRs->adoEOF)
	{
		index = m_RefundList.InsertItem(m_RefundList.GetItemCount(),
			(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)0)->Value);
		for (int col = 1;col <9;col++)
			m_RefundList.SetItemText(index,col,(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)col)->Value);
		m_pRs->MoveNext();
	}
}