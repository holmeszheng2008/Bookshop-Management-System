// StasticDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "BookManage.h"
#include "StasticDlg1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStasticDlg1 dialog
extern _ConnectionPtr m_pCon;  
extern _RecordsetPtr m_pRs; 
extern _CommandPtr m_pCom;

CStasticDlg1::CStasticDlg1(CWnd* pParent /*=NULL*/)
	: CDialog(CStasticDlg1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStasticDlg1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStasticDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStasticDlg1)
	DDX_Control(pDX, IDC_VEND_LIST, m_VendList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStasticDlg1, CDialog)
	//{{AFX_MSG_MAP(CStasticDlg1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStasticDlg1 message handlers
BOOL CStasticDlg1::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD dwStyle=GetWindowLong(m_VendList.GetSafeHwnd(),GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;
	dwStyle|=LVS_REPORT;
	SetWindowLong(m_VendList.GetSafeHwnd(),GWL_STYLE,dwStyle);

	m_VendList.InsertColumn(0,"SERIAL NO.",LVCFMT_LEFT,80);
	m_VendList.InsertColumn(1,"SOLD DATE",LVCFMT_LEFT,110);
	m_VendList.InsertColumn(2,"ISBN",LVCFMT_LEFT,100);
	m_VendList.InsertColumn(3,"BOOKNAME",LVCFMT_LEFT,130);
	m_VendList.InsertColumn(4,"AUTHOR",LVCFMT_LEFT,90);
	m_VendList.InsertColumn(5,"BOOKCONCERN",LVCFMT_LEFT,130);
	m_VendList.InsertColumn(6,"LABEL",LVCFMT_LEFT,90);
	m_VendList.InsertColumn(7,"PRICE",LVCFMT_LEFT,80);
	m_VendList.InsertColumn(8,"COUNT",LVCFMT_LEFT,80);

	m_VendList.SetExtendedStyle(LVS_EX_GRIDLINES);
    ::SendMessage(m_VendList.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
      LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	ShowVend();
	return TRUE;
}

void CStasticDlg1::ShowVend()
{
	m_pRs->raw_Close();
	CString sql;
	sql.Format("select * from bm_BookSold");
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	int index = 0;
	m_VendList.DeleteAllItems();
	while (!m_pRs->adoEOF)
	{
		index = m_VendList.InsertItem(m_VendList.GetItemCount(),
			(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)0)->Value);
		for(int col = 1;col <9;col++)
			m_VendList.SetItemText(index,col,(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)col)->Value);
		m_pRs->MoveNext();
	}
}
