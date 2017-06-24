
// tradePadDlg.cpp : ʵ���ļ�
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

// CtradePadDlg �Ի���



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


// CtradePadDlg ��Ϣ�������

BOOL CtradePadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	////Create image list
	//m_imagelist.Create(IDB_BITMAP, 16, ILC_COLOR4, RGB(255, 255, 255));
	//m_imagelistLarge.Create(IDB_BITMAP_LARGE, 32, ILC_COLOR4, RGB(255, 255, 255));
	//	
	//m_list.SetImageList(&m_imagelist, LVSIL_SMALL);
	//m_list.SetImageList(&m_imagelistLarge, LVSIL_NORMAL);


	//-----------------------------------------------------
	//LONG lStyle;
	//lStyle = GetWindowLong(m_list_share.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	//lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	//lStyle |= LVS_REPORT; //����style
	//SetWindowLong(m_list_share.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = m_list_share.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	m_list_share.SetExtendedStyle(dwStyle); //������չ���

	m_list_share.InsertColumn(0, _T("code"), LVCFMT_LEFT, 80); //�������
	m_list_share.InsertColumn(1, _T("name"), LVCFMT_LEFT, 80);
	m_list_share.InsertColumn(2, _T("����"), LVCFMT_LEFT, 80);
	m_list_share.InsertColumn(3, _T("�ּ�"), LVCFMT_LEFT, 1200);

	//m_list_share.SetColumnWidth(0, 80); //�����п�
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtradePadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtradePadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CtradePadDlg::OnBnClickedBtnClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	yhLib.clearShare();
}



void CtradePadDlg::OnBnClickedBtnBuy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LPCSTR pcode = m_strCode.GetString();
	//yhLib.buy(m_strCode.GetString();)
}
