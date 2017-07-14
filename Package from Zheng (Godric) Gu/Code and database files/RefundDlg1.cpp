// RefundDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "BookManage.h"
#include "RefundDlg1.h"
#include "RefundManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRefundDlg1 dialog
extern _ConnectionPtr m_pCon;  
extern _RecordsetPtr m_pRs; 
extern _CommandPtr m_pCom;

extern CRefundManage p_refund;

CRefundDlg1::CRefundDlg1(CWnd* pParent /*=NULL*/)
	: CDialog(CRefundDlg1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRefundDlg1)
	m_ISBN = _T("");
	m_Count = _T("");
	m_Name = _T("");
	//}}AFX_DATA_INIT
}


void CRefundDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRefundDlg1)
	DDX_Text(pDX, IDC_REFUND_ISBN, m_ISBN);
	DDX_Text(pDX, IDC_REFUND_COUNT, m_Count);
	DDX_Text(pDX, IDC_REFUND_NAME, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRefundDlg1, CDialog)
	//{{AFX_MSG_MAP(CRefundDlg1)
	ON_BN_CLICKED(IDC_REFUND_ENTER, OnRefundEnter)
	ON_BN_CLICKED(IDC_REFUND_CLEAR, OnRefundClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRefundDlg1 message handlers

void CRefundDlg1::OnRefundEnter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_ISBN.IsEmpty()||m_Count.IsEmpty())
	{
		MessageBox("ISBN OR COUNT CAN'T BE EMPTY","提示!");
		return;
	}
	CString sql;
	sql.Format("select * from bm_BookSold where ISBN='%d'",str_to_int(m_ISBN));
	m_pRs->raw_Close();
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	//先在销售表中找，有的话再删减
	if(m_pRs->RecordCount < 1)
	{
		MessageBox("BOOK INFO WRONG!","ERROR!");
		return;
	}
	//寻找存储表中对应项
	sql.Format("select * from bm_BookStorage where ISBN='%d'",str_to_int(m_ISBN));
	m_pRs->raw_Close();
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);

	int tmp = str_to_int(m_Count) + 
			str_to_int((TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)6)->Value);
	//获取当前时间...
	CString time;
	GetDate(time);
	//更新退货记录
	sql.Format("insert into bm_BookRefund values(%d,%d,'%s','%s','%s','%s',%d,%d)",
		str_to_int(time),
		str_to_int(m_ISBN),
		(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)1)->Value,
		(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)2)->Value,
		(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)3)->Value,
		(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)4)->Value,
		str_to_int((TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)5)->Value),
		str_to_int(m_Count));
	m_pRs->raw_Close();
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	//更新库存
	sql.Format("update bm_BookStorage set storecount='%d' where ISBN='%d'",tmp,str_to_int(m_ISBN));
	m_pRs->raw_Close();
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);	
	//更新备用库存
	sql.Format("update bm_BookStorage_r set storecount='%d' where ISBN='%d'",tmp,str_to_int(m_ISBN));
	m_pRs->raw_Close();
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);	

	MessageBox("REFUND SUCCESSFULLY!","WARNING!");
	//重画报表
	OnRefundClear();
	p_refund.refunddlg2->ShowRefund();
}
//清除输入的信息
void CRefundDlg1::OnRefundClear() 
{
	// TODO: Add your control notification handler code here
	m_ISBN.Empty();
	m_Name.Empty();
	m_Count.Empty();
	UpdateData(FALSE);
}
