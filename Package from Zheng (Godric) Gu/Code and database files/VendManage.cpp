// VendManage.cpp : implementation file
//

#include "stdafx.h"
#include "BookManage.h"
#include "VendManage.h"
#include "VendDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVendManage dialog
extern _ConnectionPtr m_pCon;  
extern _RecordsetPtr m_pRs; 
extern _CommandPtr m_pCom;

extern int PID;

CVendManage::CVendManage(CWnd* pParent /*=NULL*/)
	: CDialog(CVendManage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVendManage)
	m_strAuthor = _T("");
	m_strBookname = _T("");
	m_strC = _T("");
	//}}AFX_DATA_INIT
}


void CVendManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVendManage)
	DDX_Control(pDX, IDC_PUCHE_LIST, m_PucheList);
	DDX_Control(pDX, IDC_STORAGE_LIST, m_StorageList);
	DDX_Text(pDX, IDC_EDIT_AUTHOR, m_strAuthor);
	DDX_Text(pDX, IDC_EDIT_BOOKNAME, m_strBookname);
	DDX_Text(pDX, IDC_EDIT_C, m_strC);
	//}}AFX_DATA_MAP
}

CVendManage p_vend;

BEGIN_MESSAGE_MAP(CVendManage, CDialog)
	//{{AFX_MSG_MAP(CVendManage)
	ON_COMMAND(ID_EXIT, OnExitVend)
	ON_COMMAND(ID_ADDBOOK, OnAddbook)
	ON_NOTIFY(NM_CLICK, IDC_STORAGE_LIST, OnClickStorageList)
	ON_NOTIFY(NM_CLICK, IDC_PUCHE_LIST, OnClickPucheList)
	ON_COMMAND(ID_MINUSBOOK, OnMinusbook)
	ON_COMMAND(ID_PUCHE, OnPuche)
	ON_COMMAND(ID_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVendManage message handlers
BOOL CVendManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	//初始化书单列表框...
	DWORD dwStyle=GetWindowLong(m_StorageList.GetSafeHwnd(),GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;
	dwStyle|=LVS_REPORT;
	SetWindowLong(m_StorageList.GetSafeHwnd(),GWL_STYLE,dwStyle);

	m_StorageList.InsertColumn(0,"ISBN",LVCFMT_LEFT,80);
	m_StorageList.InsertColumn(1,"BOOKNAME",LVCFMT_LEFT,130);
	m_StorageList.InsertColumn(2,"AUTHOR",LVCFMT_LEFT,90);
	m_StorageList.InsertColumn(3,"BOOKCONCERN",LVCFMT_LEFT,130);
	m_StorageList.InsertColumn(4,"LABEL",LVCFMT_LEFT,90);
	m_StorageList.InsertColumn(5,"PRICE",LVCFMT_LEFT,80);
	m_StorageList.InsertColumn(6,"COUNT",LVCFMT_LEFT,80);

	m_StorageList.SetExtendedStyle(LVS_EX_GRIDLINES);
    ::SendMessage(m_StorageList.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
      LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	//初始化选书单...
	dwStyle=GetWindowLong(m_PucheList.GetSafeHwnd(),GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;
	dwStyle|=LVS_REPORT;
	SetWindowLong(m_PucheList.GetSafeHwnd(),GWL_STYLE,dwStyle);

	m_PucheList.InsertColumn(0,"ISBN",LVCFMT_LEFT,80);
	m_PucheList.InsertColumn(1,"BOOKNAME",LVCFMT_LEFT,130);
	m_PucheList.InsertColumn(2,"AUTHOR",LVCFMT_LEFT,90);
	m_PucheList.InsertColumn(3,"BOOKCONCERN",LVCFMT_LEFT,130);
	m_PucheList.InsertColumn(4,"LABEL",LVCFMT_LEFT,90);
	m_PucheList.InsertColumn(5,"PRICE",LVCFMT_LEFT,80);
	m_PucheList.InsertColumn(6,"COUNT",LVCFMT_LEFT,80);

	m_PucheList.SetExtendedStyle(LVS_EX_GRIDLINES);
	::SendMessage(m_PucheList.m_hWnd,LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);
	//显示现有图书
	ShowStorage();
	m_AddIndex = -1;
	m_DelIndex = -1;
	return TRUE;
}

void CVendManage::OnExitVend() 
{
	// TODO: Add your command handler code here
	EndDialog(0);
}

void CVendManage::ShowStorage()
{
	m_pRs->raw_Close();
	CString sql;
	sql.Format("select * from bm_BookStorage");
	m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	int index = 0;
	m_StorageList.DeleteAllItems();
	while (!m_pRs->adoEOF)
	{
		index = m_StorageList.InsertItem(m_StorageList.GetItemCount(),
			(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)0)->Value);
		for (int col = 1;col <8;col++)
			m_StorageList.SetItemText(index,col,(TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)col)->Value);
		m_pRs->MoveNext();
	}
}
//选书添加到选书单
void CVendManage::OnAddbook() 
{
	// TODO: Add your command handler code here
	if(m_AddIndex < 0)
		return;
	CVendDlg cv;
	cv.DoModal();
	if(!cv.getcount)
		return;
	if(str_to_int(cv.m_PucheCount) > str_to_int(m_StorageList.GetItemText(m_AddIndex,6)))
	{
		MessageBox("OUT OF STORAGE","ERROR!");
		return;
	}
	int index = m_PucheList.InsertItem(m_PucheList.GetItemCount(),
			m_StorageList.GetItemText(m_AddIndex,0));
	for(int i=1;i<6;i++)
		m_PucheList.SetItemText(index,i,m_StorageList.GetItemText(m_AddIndex,i));
	m_PucheList.SetItemText(index,6,cv.m_PucheCount);
}

void CVendManage::OnClickStorageList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_AddIndex = m_StorageList.GetSelectionMark();
	*pResult = 0;
}

void CVendManage::OnClickPucheList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_DelIndex = m_PucheList.GetSelectionMark();
	*pResult = 0;
}

void CVendManage::OnMinusbook() 
{
	// TODO: Add your command handler code here
	if(m_DelIndex < 0)
		return;
	m_PucheList.DeleteItem(m_DelIndex);
}
//确定购买
void CVendManage::OnPuche() 
{
	// TODO: Add your command handler code here
	if(m_PucheList.GetItemCount() < 1)
	{
		MessageBox("PLEASE SELECT BOOKS FIRST","提示!");
		return;
	}
	CString sql;
	float cost = 0;
	for(int i=0;i<m_PucheList.GetItemCount();i++)
	{
		//更新库存
		sql.Format("select * from bm_BookStorage where ISBN='%s'",
			m_PucheList.GetItemText(i,0));
		m_pRs->raw_Close();
		m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
		int newcount = str_to_int((TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)6)->Value)-
			str_to_int(m_PucheList.GetItemText(i,6));
		sql.Format("update bm_BookStorage set storecount='%d' where ISBN='%s'",
			newcount,m_PucheList.GetItemText(i,0));
		m_pRs->raw_Close();
		m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
		//更新备用库存
		sql.Format("select * from bm_BookStorage_r where ISBN='%s'",
			m_PucheList.GetItemText(i,0));
		m_pRs->raw_Close();
		m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
		sql.Format("update bm_BookStorage_r set storecount='%d' where ISBN='%s'",
			newcount,m_PucheList.GetItemText(i,0));
		m_pRs->raw_Close();
		m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
		//更新销售表
		CString time;
		GetDate(time);
		sql.Format("insert into bm_BookSold values (%d,%d,'%s','%s','%s','%s',%f,%d)",
			str_to_int(time),str_to_int(m_PucheList.GetItemText(i,0)),
			m_PucheList.GetItemText(i,1),
			m_PucheList.GetItemText(i,2),
			m_PucheList.GetItemText(i,3),
			m_PucheList.GetItemText(i,4),
			str_to_float(m_PucheList.GetItemText(i,5)),
			str_to_int(m_PucheList.GetItemText(i,6)));
		m_pRs->raw_Close();
		m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
		//更新销售榜
		sql.Format("select * from bm_BookSummry where ISBN='%s'",m_PucheList.GetItemText(i,0));
		m_pRs->raw_Close();
		m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);		
		if(m_pRs->RecordCount > 0)
		{
			int newcount = str_to_int((TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)6)->Value)
					+str_to_int(m_PucheList.GetItemText(i,6));
			float newsummry = (float)(str_to_float((TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)5)->Value)*newcount);
			sql.Format("update bm_BookSummry set soldcount='%d',soldsummry='%f' where ISBN='%s'",
				newcount,newsummry,m_PucheList.GetItemText(i,0));
			cost += (float)(str_to_float((TCHAR*)(_bstr_t)m_pRs->GetFields()->GetItem((long)5)->Value)
				*str_to_int(m_PucheList.GetItemText(i,6)));
		}
		else
		{
			float x = (float)(str_to_float(m_PucheList.GetItemText(i,5))
				*str_to_int(m_PucheList.GetItemText(i,6)));
			cost += x;
			sql.Format("insert into bm_BookSummry values (%d,'%s','%s','%s','%s',%f,%d,%f)",
				str_to_int(m_PucheList.GetItemText(i,0)),
				m_PucheList.GetItemText(i,1),
				m_PucheList.GetItemText(i,2),
				m_PucheList.GetItemText(i,3),
				m_PucheList.GetItemText(i,4),
				str_to_float(m_PucheList.GetItemText(i,5)),
				str_to_int(m_PucheList.GetItemText(i,6)),x);
		}
		m_pRs->raw_Close();
		m_pRs->Open((_variant_t)sql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	}
	m_StorageList.DeleteAllItems();
	ShowStorage();
	sql.Format("%f",cost);
	sql.TrimRight();
	MessageBox("TRANSACTION SUCCESSFULLY...\nAMOUNT："+sql+"DOLLARS\n","WARNING!");
}

void CVendManage::OnClear() 
{
	// TODO: Add your command handler code here
	m_PucheList.DeleteAllItems();
}

void CVendManage::OnButtonFind() 
{
	UpdateData();
	CString strSql;
	strSql="select * from bm_BookStorage where bookname like '%"+m_strBookname+"%' and author like '%"+m_strAuthor
		+"%' and bookconcern like '%"+m_strC+"%'";
//	strSql="select * from bm_BookStorage where bookname='%"+m_strBookname+"%'";
	m_pRs->raw_Close();
	m_pRs->Open((_variant_t)strSql,m_pCon.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	m_StorageList.DeleteAllItems();
	int i=0;
	while(!m_pRs->adoEOF)
	{
	m_StorageList.InsertItem(i,(TCHAR*)(_bstr_t)m_pRs->GetCollect("ISBN"));
	m_StorageList.SetItemText(i,1,(TCHAR*)(_bstr_t)m_pRs->GetCollect("bookname"));
	m_StorageList.SetItemText(i,2,(TCHAR*)(_bstr_t)m_pRs->GetCollect("author"));
	m_StorageList.SetItemText(i,3,(TCHAR*)(_bstr_t)m_pRs->GetCollect("bookconcern"));
	m_StorageList.SetItemText(i,4,(TCHAR*)(_bstr_t)m_pRs->GetCollect("label"));
	m_StorageList.SetItemText(i,5,(TCHAR*)(_bstr_t)m_pRs->GetCollect("price"));
	m_StorageList.SetItemText(i,6,(TCHAR*)(_bstr_t)m_pRs->GetCollect("storecount"));
	i++;
	m_pRs->MoveNext();
	}
}
