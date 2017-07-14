// ADDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BookManage.h"
#include "BookManageDlg.h"
#include "ADDDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CADDDlg dialog
extern _ConnectionPtr m_pCon;  
extern _RecordsetPtr m_pRs; 
extern _CommandPtr m_pCom;

CADDDlg::CADDDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CADDDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CADDDlg)
	m_USERNAME = _T("");
	m_PASSPORT = _T("");
	//}}AFX_DATA_INIT
}


void CADDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CADDDlg)
		DDX_Text(pDX, IDC_USERNAME, m_USERNAME);
		DDX_Text(pDX, IDC_PASSPORT, m_PASSPORT);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CADDDlg, CDialog)
	//{{AFX_MSG_MAP(CADDDlg)
		ON_BN_CLICKED(IDOK, OnCollate)
		ON_BN_CLICKED(IDCANCEL, OnQuit)
	ON_BN_CLICKED(IDC_RADIO1, On1)
	ON_BN_CLICKED(IDC_RADIO2, On0)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADDDlg message handlers
void CADDDlg::OnCollate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_USERNAME.IsEmpty() || m_PASSPORT.IsEmpty())
	{
		MessageBox("USERNAME OR PASSWORD CAN'T BE EMPTY!","WARNING!");
		return;
	}
	//搜索匹配的帐号...
	CString sql;
	sql.Format("select username from bm_OperaInfor where username='%s'",m_USERNAME);

	m_pRs->raw_Close();
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	//匹配成功之后打开主界面...
	if(m_pRs->RecordCount > 0)
	{
		MessageBox("USERNAME ALREADY EXISTS...","ERROR!");
		m_USERNAME.Empty();
		m_PASSPORT.Empty();
		UpdateData(FALSE);
	}
	else
	{
		sql.Format("insert into bm_OperaInfor values ('%s','%s',%d)",m_USERNAME,m_PASSPORT,pow);
		m_pRs->raw_Close();
		m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
		MessageBox("USERNAME ADDED SUCCESSFULLY.....","WARNING!");
		EndDialog(0);
		return;
	}
}

void CADDDlg::OnQuit() 
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}

void CADDDlg::On1() 
{
	pow=1;
	
}

void CADDDlg::On0() 
{
	pow=0;
	
}
