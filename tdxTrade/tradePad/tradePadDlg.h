
// tradePadDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CtradePadDlg 对话框
class CtradePadDlg : public CDialogEx
{
// 构造
public:
	CtradePadDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRADEPAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_share;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedButton2();
	CEdit m_edit_code;
	afx_msg void OnBnClickedBtnBuy();
	CString m_strCode;
};
