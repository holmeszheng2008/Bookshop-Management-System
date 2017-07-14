// BookManageDlg0.cpp : implementation file
//

#include "stdafx.h"
#include "BookManage.h"
#include "ADDDlg.h"
#include "BookManageDlg0.h"
#include "BookManageDlg.h"
#include "StockManage.h"
#include "RefundManage.h"
#include "StasticManage.h"
#include "VendManage.h"
#include "Login.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern _ConnectionPtr m_pCon;  
extern _RecordsetPtr m_pRs; 
extern _CommandPtr m_pCom;

extern BOOL loginflag;
extern CString m_user;
extern int userpow;

extern int PID1 = 0;
extern BOOL loginflag;

extern CStockManage p_stock;
extern CRefundManage p_refund;
extern CStasticManage p_stastic;
extern CVendManage p_vend;

class CAboutDlg1 : public CDialog
{
public:
	CAboutDlg1();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg1::CAboutDlg1() : CDialog(CAboutDlg1::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg1, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBookManageDlg dialog

CBookManageDlg0::CBookManageDlg0(CWnd* pParent /*=NULL*/)
	: CDialog(CBookManageDlg0::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBookManageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBookManageDlg0::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBookManageDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBookManageDlg0, CDialog)
	//{{AFX_MSG_MAP(CBookManageDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_ADD, OnADD)
	ON_COMMAND(ID_ABOUT, OnAbout)
	ON_COMMAND(ID_EXIT, OnExit)
	ON_COMMAND(ID_STOCK_RECORD, OnStockRecord)
	ON_COMMAND(ID_SUPPLY_PRICE, OnSupplyPrice)
	ON_COMMAND(ID_REFUND_RECORD, OnRefundRecord)
	ON_COMMAND(ID_REFUND_OPERA, OnRefundOpera)
	ON_COMMAND(ID_VEND_RECORD, OnVendRecord)
	ON_COMMAND(ID_VEND_BYDAY, OnVendByday)
	ON_COMMAND(ID_VEND_LIST, OnVendList)
	ON_COMMAND(ID_VEND_CONSOLE, OnVendConsole)
	ON_COMMAND(ID_ADDOPERA, OnAddopera)
	ON_COMMAND(ID_CHANGEUSR, OnCHANGEUSR)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBookManageDlg message handlers

BOOL CBookManageDlg0::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetInfor();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBookManageDlg0::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg1 dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBookManageDlg0::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBookManageDlg0::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBookManageDlg0::SetInfor()
{
	CString tmp = "OPERATOR: ";
	GetDlgItem(IDC_OPERA_STATIC)->SetWindowText(tmp+m_user);
	CTime t = CTime::GetCurrentTime();
	tmp.Empty();
	tmp.Format("TIME: %d//%d//%d",t.GetYear(),t.GetMonth(),t.GetDay());
	GetDlgItem(IDC_TIME_STATIC)->SetWindowText(tmp);
}

//关于添加用户--完成...
void CBookManageDlg0::OnADD() 
{
	// TODO: Add your command handler code here
	CADDDlg ca;
	ca.DoModal();
}
//关于帮助--完成...
void CBookManageDlg0::OnAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg1 ca;
	ca.DoModal();
}
//退出系统--完成...
void CBookManageDlg0::OnExit() 
{
	// TODO: Add your command handler code here
	exit(0);
}
//显示进货记录
void CBookManageDlg0::OnStockRecord() 
{
	// TODO: Add your command handler code here
	PID1 = 0;
	p_stock.DoModal();
}
//供应商报价
void CBookManageDlg0::OnSupplyPrice() 
{
	// TODO: Add your command handler code here
	PID1 = 1;
	p_stock.DoModal();
}
//退货业务办理
void CBookManageDlg0::OnRefundOpera() 
{
	// TODO: Add your command handler code here
	PID1 = 0;
	p_refund.DoModal();
}
//显示退货记录
void CBookManageDlg0::OnRefundRecord() 
{
	// TODO: Add your command handler code here
	PID1 = 1;
	p_refund.DoModal();
}
//显示销售记录
void CBookManageDlg0::OnVendRecord() 
{
	// TODO: Add your command handler code here
	PID1 = 0;
	p_stastic.DoModal();
}
//显示日销售量
void CBookManageDlg0::OnVendByday() 
{
	// TODO: Add your command handler code here
	PID1 = 1;
	p_stastic.DoModal();
}
//显示销售排行榜
void CBookManageDlg0::OnVendList() 
{
	// TODO: Add your command handler code here
	PID1 = 2;
	p_stastic.DoModal();
}
//调用销售控制台
void CBookManageDlg0::OnVendConsole() 
{
	// TODO: Add your command handler code here
	p_vend.DoModal();
}
void CBookManageDlg0::OnCHANGEUSR() 
{
		EndDialog(0);
		CLogin login;
		login.DoModal();
	
	if(loginflag)
	{
		if(userpow==1)
		{
			CBookManageDlg dlg;
			
			dlg.DoModal();	
		}
		else
		{
			CBookManageDlg0 dlg;
			
			dlg.DoModal();	
		}
	}
}
void CBookManageDlg0::OnAddopera() 
{
	// TODO: Add your command handler code here
	
}
