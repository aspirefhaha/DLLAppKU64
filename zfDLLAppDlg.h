// zfDLLAppDlg.h : header file
//
#include "masKUApi.h"

#if !defined(AFX_ZFDLLAPPDLG_H__5297DCDD_F7B6_46DA_B45D_399A8E956081__INCLUDED_)
#define AFX_ZFDLLAPPDLG_H__5297DCDD_F7B6_46DA_B45D_399A8E956081__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CZfDLLAppDlg dialog

class CZfDLLAppDlg : public CDialog
{
// Construction
public:
	CZfDLLAppDlg(CWnd* pParent = NULL);	// standard constructor
	void PrintOut(const char *format, ...);

	BOOL ZFUSetSN(unsigned char *devSN);
// Dialog Data
	//{{AFX_DATA(CZfDLLAppDlg)
	enum { IDD = IDD_ZFDLLAPP_DIALOG };
	UINT	m_pid;
	UINT	m_vid;
	int		m_radio;
	MASKU_INFO zfUsb;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZfDLLAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CZfDLLAppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpenUSB();
	afx_msg void OnCloseUSB();
	afx_msg void OnGetCDDVD();
	afx_msg void OnGetDiskInfoAll();
	afx_msg void OnSetDiskInfoAll();
	afx_msg void OnWriteHide();
	afx_msg void OnReadHide();
	afx_msg void OnUpdateISO();
	virtual void OnCancel();
	afx_msg void OnClear();
	afx_msg void OnCOSErase();
	afx_msg void OnIsoRoute();
	afx_msg void OnWriteHide2();
	afx_msg void OnReadHide2();
	afx_msg void OnGetTime();
	afx_msg void OnSetTime();
	afx_msg void OnPwdVerify();
	afx_msg void OnPwdChange();
	afx_msg void OnPwdErr();
	afx_msg void OnPwdChange2();
	afx_msg void OnButton2();
	afx_msg void OnWriteHide3();
	afx_msg void OnPwdChange4();
	afx_msg void OnCancel2();
	afx_msg void OnGetTime2();
	afx_msg void OnWriteHide4();
	afx_msg void OnWriteHide5();
	afx_msg void OnWriteHide6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedWritehide7();
	afx_msg void OnBnClickedReadhide3();
	afx_msg void OnBnClickedGetcddvd2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnEnChangeCdCapacity();
	afx_msg void OnEnChangeUCapacity();
	afx_msg void OnEnChangeSCapacity();
	afx_msg void OnEnChangeHCapacity();
	afx_msg void OnClose();
	afx_msg void OnBnClickedColFp();
	afx_msg void OnBnClickedUpImg();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedCipid();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg LRESULT OnUPos(WPARAM, LPARAM);


public:
	BOOL m_bIsTestQuit;
	BOOL m_bIsWriteQuit;
private:
	HANDLE hTestThread;
	HANDLE hWriteThread;
public:
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZFDLLAPPDLG_H__5297DCDD_F7B6_46DA_B45D_399A8E956081__INCLUDED_)
