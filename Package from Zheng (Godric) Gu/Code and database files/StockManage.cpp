// StockManage.cpp : implementation file
//

#include "stdafx.h"
#include "BookManage.h"
#include "StockManage.h"
#include "StockDlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStockManage dialog
extern _ConnectionPtr m_pCon;  
extern _RecordsetPtr m_pRs; 
extern _CommandPtr m_pCom;

extern int PID;

CStockManage::CStockManage(CWnd* pParent /*=NULL*/)
	: CDialog(CStockManage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStockManage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStockManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStockManage)
	DDX_Control(pDX, IDC_STOCK_TAB, m_StockTab);
	//}}AFX_DATA_MAP
}

//公共对象...
CStockManage p_stock;

BEGIN_MESSAGE_MAP(CStockManage, CDialog)
	//{{AFX_MSG_MAP(CStockManage)
	ON_NOTIFY(TCN_SELCHANGE, IDC_STOCK_TAB, OnSelchangeStockTab)
	ON_COMMAND(ID_EXIT, OnExitStock)
	ON_COMMAND(ID_ADD_SUPPLY, OnAddSupply)
	ON_COMMAND(ID_MINU_SUPPLY, OnMinuSupply)
	ON_COMMAND(ID_CHOOSE_SUPPLY, OnChooseSupply)
	ON_COMMAND(ID_CLEAR, OnClear)
	ON_COMMAND(ID_SAVE, OnSave)
	ON_COMMAND(ID_DISPLAY, OnDisplay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockManage message handlers
BOOL CStockManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	stockdlg1 = new CStockDlg1();
	stockdlg2 = new CStockDlg2();
	//将对话框贴在标签上...
	stockdlg1->Create(IDD_STOCK_DIALOG1,&m_StockTab);
	stockdlg2->Create(IDD_STOCK_DIALOG2,&m_StockTab);

	m_StockTab.InsertItem(0,"STOCK RECORD",0);
	m_StockTab.InsertItem(1,"SUPPLIER INFO",1);
	m_StockTab.SetMinTabWidth(100);
	m_StockTab.SetCurSel(PID);
	DoTab(PID);

	bit=0;
	HasSupp = FALSE;
	return TRUE;
}

void CStockManage::SetDlgState(CWnd *pWnd, BOOL bShow)
{
	pWnd->EnableWindow(bShow);
	if(bShow)
	{
		pWnd->ShowWindow(SW_SHOW);
		pWnd->CenterWindow();
	}
	else
		pWnd->ShowWindow(SW_HIDE);
}

void CStockManage::DoTab(int nPid)
{
	if(nPid > 1) nPid = 1;
	if(nPid < 0) nPid =	0;
	
	BOOL iPid[2];
	iPid[0]=iPid[1]=FALSE;
	iPid[nPid]=TRUE;

	SetDlgState(stockdlg1,iPid[0]);
	SetDlgState(stockdlg2,iPid[1]);
}
//单击标签触发换页...
void CStockManage::OnSelchangeStockTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int select = m_StockTab.GetCurSel();
	if(select >= 0)
		DoTab(select);
	*pResult = 0;
}

void CStockManage::OnExitStock() 
{
	// TODO: Add your command handler code here
	EndDialog(0);
}

//增加供应商信息...
void CStockManage::OnAddSupply() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	stockdlg2->UpdateData(TRUE);
	if(stockdlg2->m_ISBN.IsEmpty()||stockdlg2->m_Name.IsEmpty()||stockdlg2->m_Author.IsEmpty()
		||stockdlg2->m_Price.IsEmpty()||stockdlg2->m_Count.IsEmpty()||stockdlg2->m_Supply.IsEmpty())
	{
		MessageBox("SUPPLY INFO CAN'T BE EMPTY","WARNING!");
		return;
	}
	int index = stockdlg2->m_StockSupplyList.InsertItem
		(stockdlg2->m_StockSupplyList.GetItemCount(),stockdlg2->m_ISBN);
	stockdlg2->m_StockSupplyList.SetItemText(index,1,stockdlg2->m_Name);
	stockdlg2->m_StockSupplyList.SetItemText(index,2,stockdlg2->m_Author);
	stockdlg2->m_StockSupplyList.SetItemText(index,3,stockdlg2->m_Supply);
	stockdlg2->m_StockSupplyList.SetItemText(index,4,stockdlg2->m_Price);
	stockdlg2->m_StockSupplyList.SetItemText(index,5,stockdlg2->m_Count);
}

//删减供应商信息...
void CStockManage::OnMinuSupply() 
{
	// TODO: Add your command handler code here
	if(stockdlg2->delIndex < 0||stockdlg2->delIndex > stockdlg2->m_StockSupplyList.GetItemCount())
	{
		MessageBox("SELECT THE INFO TO DELETE","WARNING!");
		return;
	}
	stockdlg2->m_StockSupplyList.DeleteItem(stockdlg2->delIndex);
	stockdlg2->delIndex = -1;
}

//选择供应商************************************************************
void CStockManage::OnChooseSupply() 
{
	int row;
	if(HasSupp)
	{
		MessageBox("SUPPLY INFO ALREADY EXISTS\nCLEAR FIRST BEFORE GENERATE","WARNING!");
		return;
	}
	// TODO: Add your command handler code here
	for(row=0;row<stockdlg2->m_StockSupplyList.GetItemCount();row++)
	{
		int j;
		//有同种书要比较成本
		for(j=0;j<bit;j++)
			if(supply[j].ISBN == str_to_int(stockdlg2->m_StockSupplyList.GetItemText(row,0)))
			{
				//同种书选择成本低的
				if(supply[j].cost > str_to_float(stockdlg2->m_StockSupplyList.GetItemText(row,4)))
				{
					supply[j].ISBN = str_to_int(stockdlg2->m_StockSupplyList.GetItemText(row,0));
					supply[j].bookname = stockdlg2->m_StockSupplyList.GetItemText(row,1);
					supply[j].author = stockdlg2->m_StockSupplyList.GetItemText(row,2);
					supply[j].bookconcern = stockdlg2->m_StockSupplyList.GetItemText(row,3);
					supply[j].cost = str_to_float(stockdlg2->m_StockSupplyList.GetItemText(row,4));
					supply[j].supplycount = str_to_int(stockdlg2->m_StockSupplyList.GetItemText(row,5));
					break;;
				}
				else
					break;
			}
		if(j < bit)
			continue;
		//新的类型书就直接添加
		supply[bit].ISBN = str_to_int(stockdlg2->m_StockSupplyList.GetItemText(row,0));
		supply[bit].bookname = stockdlg2->m_StockSupplyList.GetItemText(row,1);
		supply[bit].author = stockdlg2->m_StockSupplyList.GetItemText(row,2);
		supply[bit].bookconcern = stockdlg2->m_StockSupplyList.GetItemText(row,3);
		supply[bit].cost = str_to_float(stockdlg2->m_StockSupplyList.GetItemText(row,4));
		supply[bit].supplycount = str_to_int(stockdlg2->m_StockSupplyList.GetItemText(row,5));
		++bit;
	}
	CString tmp;
	stockdlg2->m_StockSupplyList.DeleteAllItems();
	for(row=0;row<bit;row++)
	{
		//在控件中显示被选的供应商信息
		tmp.Format("%d",supply[row].ISBN);
		int index = stockdlg2->m_StockSupplyList.InsertItem
			(stockdlg2->m_StockSupplyList.GetItemCount(),tmp);
		stockdlg2->m_StockSupplyList.SetItemText(index,1,supply[row].bookname);
		stockdlg2->m_StockSupplyList.SetItemText(index,2,supply[row].author);
		stockdlg2->m_StockSupplyList.SetItemText(index,3,supply[row].bookconcern);
		tmp.Format("%f",supply[row].cost);
		stockdlg2->m_StockSupplyList.SetItemText(index,4,tmp);
		tmp.Format("%d",supply[row].supplycount);
		stockdlg2->m_StockSupplyList.SetItemText(index,5,tmp);
	}
	MessageBox("SUPPLY LIST GENERATED","WARNING!");
	HasSupp = TRUE;
}

void CStockManage::OnClear() 
{
	// TODO: Add your command handler code here	
	stockdlg2->m_ISBN.Empty();
	stockdlg2->m_Name.Empty();
	stockdlg2->m_Author.Empty();
	stockdlg2->m_Supply.Empty();
	stockdlg2->m_Price.Empty();
	stockdlg2->m_Count.Empty();
	stockdlg2->UpdateData(FALSE);

	stockdlg2->m_StockSupplyList.DeleteAllItems();
	//供应商记录量置零...
	bit=0;
	HasSupp = FALSE;
}

// 保存进货信息
void CStockManage::OnSave() 
{
	// TODO: Add your command handler code here
	if(!HasSupp)
	{
		MessageBox("GENERATE SUPPLY INFO FIRST","ERROR!");
		return;
	}
	CString time,sql;
	GetDate(time);
	for(int i=0;i<bit;i++)
	{
		/*
		//将供应商信息插入到供应表bm_Supply
		sql.Format("insert into bm_Supply values (%d,%d,'%s','%s','%s',%f,%d)",
			str_to_int(time),supply[i].ISBN,supply[i].bookname,supply[i].author,
			supply[i].bookconcern,supply[i].cost,supply[i].supplycount);
		m_pRs->raw_Close();
		m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
		*/
		//保存到进货表bm_BookStock
		sql.Format("insert into bm_BookStock values (%d,%d,'%s','%s','%s','%s',%f,%d)",
			str_to_int(time),supply[i].ISBN,supply[i].bookname,supply[i].author,
			supply[i].bookconcern,"",supply[i].cost,supply[i].supplycount);
		m_pRs->raw_Close();
		m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
		//更新库存prime
		sql.Format("select * from bm_BookStorage where ISBN='%d'",supply[i].ISBN);
		m_pRs->raw_Close();
		m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
		//此书库中已有
		if(m_pRs->RecordCount > 0)
		{
			int newcount = supply[i].supplycount + str_to_int((TCHAR*)
				(_bstr_t)m_pRs->GetFields()->GetItem((long)6)->Value);
			sql.Format("update bm_BookStorage set storecount='%d',cost='%f' where ISBN='%d'",
				newcount,supply[i].cost,supply[i].ISBN);
		}
		//库中没有这本书，就插入信息
		else
			sql.Format("insert into bm_BookStorage values (%d,'%s','%s','%s','%s',%f,%d,%f)",
				supply[i].ISBN,supply[i].bookname,supply[i].author,supply[i].bookconcern,
				"",supply[i].cost*1.12,supply[i].supplycount,supply[i].cost);
		m_pRs->raw_Close();
		m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);

		//更新库存reserved
		sql.Format("select * from bm_BookStorage_r where ISBN='%d'",supply[i].ISBN);
		m_pRs->raw_Close();
		m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
		//此书库中已有
		if(m_pRs->RecordCount > 0)
		{
			int newcount = supply[i].supplycount + str_to_int((TCHAR*)
				(_bstr_t)m_pRs->GetFields()->GetItem((long)6)->Value);
			sql.Format("update bm_BookStorage_r set storecount='%d',cost='%f' where ISBN='%d'",
				newcount,supply[i].cost,supply[i].ISBN);
		}
		//库中没有这本书，就插入信息
		else
			sql.Format("insert into bm_BookStorage_r values (%d,'%s','%s','%s','%s',%f,%d,%f)",
			supply[i].ISBN,supply[i].bookname,supply[i].author,supply[i].bookconcern,
			"",supply[i].cost*1.12,supply[i].supplycount,supply[i].cost);
		m_pRs->raw_Close();
		m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	}
	MessageBox("FINISHED...","WARNING!");
	//在第一个对话框中回显信息
	stockdlg1->m_StockList.DeleteAllItems();
	stockdlg1->ShowStock();
}
//显示供应商数据库中的所有记录
void CStockManage::OnDisplay() 
{
	// TODO: Add your command handler code here
	OnClear();
	GetDataFromSlave1();
	GetDataFromSlave2();
	GetDataFromSlave3();
}
void CStockManage::GetDataFromSlave1()
{
	CString sql;
	sql.Format("select * from bm_Supply1");
	m_pRs->raw_Close();
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	if (m_pRs->RecordCount > 0)
	{
		int index = 0;
		//stockdlg2->m_StockSupplyList.DeleteAllItems();
		while (!m_pRs->adoEOF)
		{
			index = stockdlg2->m_StockSupplyList.InsertItem(stockdlg2->m_StockSupplyList.GetItemCount(),
				(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)1)->Value);
			for(int col = 2;col<8;col++)
				stockdlg2->m_StockSupplyList.SetItemText(index,col-2,(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)col)->Value);
			m_pRs->MoveNext();
		}
	}
	
}
void CStockManage::GetDataFromSlave2()
{
	CString sql;
	sql.Format("select * from bm_Supply2");
	m_pRs->raw_Close();
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	if (m_pRs->RecordCount > 0)
	{
		int index = 0;
		//stockdlg2->m_StockSupplyList.DeleteAllItems();
		while (!m_pRs->adoEOF)
		{
			index = stockdlg2->m_StockSupplyList.InsertItem(stockdlg2->m_StockSupplyList.GetItemCount(),
				(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)1)->Value);
			for(int col = 2;col<8;col++)
				stockdlg2->m_StockSupplyList.SetItemText(index,col-2,(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)col)->Value);
			m_pRs->MoveNext();
		}
	}
}
void CStockManage::GetDataFromSlave3()
{
	CString sql;
	sql.Format("select * from bm_Supply3");
	m_pRs->raw_Close();
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	if (m_pRs->RecordCount > 0)
	{
		int index = 0;
		//stockdlg2->m_StockSupplyList.DeleteAllItems();
		while (!m_pRs->adoEOF)
		{
			index = stockdlg2->m_StockSupplyList.InsertItem(stockdlg2->m_StockSupplyList.GetItemCount(),
				(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)1)->Value);
			for(int col = 2;col<8;col++)
				stockdlg2->m_StockSupplyList.SetItemText(index,col-2,(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)col)->Value);
			m_pRs->MoveNext();
		}
	}
}