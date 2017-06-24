
// tradePadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "tradePad.h"
#include "tradePadDlg.h"
#include "afxdialogex.h"
#include "TradeLib.h"
//#include "trade.h"
#include "DataPaser.h"
#include "ShareQuotation.h"
#include "TradeLogger.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern ShareQuotation quotation;

// CtradePadDlg 对话框



CtradePadDlg::CtradePadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRADEPAD_DIALOG, pParent)
	, m_strCode(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtradePadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHARE, m_list_share);
	DDX_Control(pDX, IDC_EDIT_CODE, m_edit_code);
	DDX_Text(pDX, IDC_EDIT_CODE, m_strCode);
	DDV_MaxChars(pDX, m_strCode, 6);
}

BEGIN_MESSAGE_MAP(CtradePadDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CtradePadDlg::OnBnClickedBtnClear)

	ON_BN_CLICKED(IDC_BTN_BUY, &CtradePadDlg::OnBnClickedBtnBuy)
END_MESSAGE_MAP()


// CtradePadDlg 消息处理程序

BOOL CtradePadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	// TODO: 在此添加额外的初始化代码

	////Create image list
	//m_imagelist.Create(IDB_BITMAP, 16, ILC_COLOR4, RGB(255, 255, 255));
	//m_imagelistLarge.Create(IDB_BITMAP_LARGE, 32, ILC_COLOR4, RGB(255, 255, 255));
	//	
	//m_list.SetImageList(&m_imagelist, LVSIL_SMALL);
	//m_list.SetImageList(&m_imagelistLarge, LVSIL_NORMAL);


	//-----------------------------------------------------
	//LONG lStyle;
	//lStyle = GetWindowLong(m_list_share.m_hWnd, GWL_STYLE);//获取当前窗口style
	//lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	//lStyle |= LVS_REPORT; //设置style
	//SetWindowLong(m_list_share.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_list_share.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_list_share.SetExtendedStyle(dwStyle); //设置扩展风格

	m_list_share.InsertColumn(0, _T("code"), LVCFMT_LEFT, 80); //添加列名
	m_list_share.InsertColumn(1, _T("name"), LVCFMT_LEFT, 80);
	m_list_share.InsertColumn(2, _T("可用"), LVCFMT_LEFT, 80);
	m_list_share.InsertColumn(3, _T("现价"), LVCFMT_LEFT, 1200);

	//m_list_share.SetColumnWidth(0, 80); //设置列宽
	quotation.init(_T("TdxHqApi.dll"));
	quotation.connect("218.75.75.20", 443);
	yhLib.init(_T("trade_yhzq.dll"));
	yhLib.login("219.143.214.206", 443);

	yhLib.selfTest();
	//logger.print();
	ShareInfo *pShareInfo;
	char buff[20];
	for (yhLib.it = yhLib.freeShares.begin(); yhLib.it != yhLib.freeShares.end(); yhLib.it++)
	{
		pShareInfo = yhLib.it->second;
		int n = m_list_share.InsertItem(0, (LPCTSTR)(pShareInfo->code));
		m_list_share.SetItemText(n, 1, (LPCTSTR)(pShareInfo->name));
		m_list_share.SetItemText(n, 2, (LPCTSTR)(pShareInfo->strFreeNum));
		m_list_share.SetItemText(n, 3, (LPCTSTR)(pShareInfo->strClose));

	}

	//for (int i = 0; i<5; i++)
	//{
	//	int n = m_list_share.InsertItem(0, _T("code"));
	//	m_list_share.SetItemText(n, 1, _T("code"));
	//	m_list_share.SetItemText(n, 2, _T("code"));
	//	m_list_share.SetItemText(n, 3,_T("code"));
	//}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtradePadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtradePadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CtradePadDlg::OnBnClickedBtnClear()
{
	// TODO: 在此添加控件通知处理程序代码
	yhLib.clearShare();
}



void CtradePadDlg::OnBnClickedBtnBuy()
{
	// TODO: 在此添加控件通知处理程序代码
	LPCSTR pcode = m_strCode.GetString();
	//yhLib.buy(m_strCode.GetString();)
}
