// Login.cpp : implementation file
//

#include "stdafx.h"
#include "BookManage.h"
#include "BookManageDlg.h"
#include "Login.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogin dialog

extern _ConnectionPtr m_pCon;  
extern _RecordsetPtr m_pRs; 
extern _CommandPtr m_pCom;

extern BOOL loginflag;
extern CString m_user;
extern int userpow;
CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogin)
	m_InputCode = _T("");
	m_InputName = _T("");
	//}}AFX_DATA_INIT
}


void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogin)
	DDX_Text(pDX, IDC_CODE, m_InputCode);
	DDX_Text(pDX, IDC_NAME, m_InputName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	//{{AFX_MSG_MAP(CLogin)
	ON_BN_CLICKED(IDC_OK, OnCollate)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogin message handlers
/* 登陆确认 */
void CLogin::OnCollate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_InputName.IsEmpty() || m_InputCode.IsEmpty())
	{
		MessageBox("USERNAME OR PASSWORD CAN'T BE EMPTY","WARNING!");
		return;
	}
	//搜索匹配的帐号...
	CString sql;
	sql.Format("select * from bm_OperaInfor where username='%s' and password='%s'",
			m_InputName,m_InputCode);

	m_pRs->raw_Close();
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	//匹配成功之后打开主界面...
	if(m_pRs->RecordCount > 0)
	{
		userpow = str_to_int((TCHAR*)(_bstr_t)m_pRs->GetCollect("userpow"));
		loginflag = TRUE;
		m_user = m_InputName;
		EndDialog(0);		
	}
	else
	{
		MessageBox("USERNAME OR PASSWORD ERROR","ERROR!");
		m_InputName.Empty();
		m_InputCode.Empty();
		UpdateData(FALSE);
		return;
	}
}

void CLogin::OnQuit() 
{
	// TODO: Add your control notification handler code here
	loginflag = FALSE;
	CDialog::OnCancel();
}

