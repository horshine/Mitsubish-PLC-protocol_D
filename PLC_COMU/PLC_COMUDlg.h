// PLC_COMUDlg.h : header file
//

#if !defined(AFX_PLC_COMUDLG_H__DFB3D874_8725_4877_BDBF_5D53A0C7993F__INCLUDED_)
#define AFX_PLC_COMUDLG_H__DFB3D874_8725_4877_BDBF_5D53A0C7993F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//===========================
// introduce head file 
#include "PLC_Dapk.h"
#include "mscomm.h"
#include "BtnST.h"
#include "DigitalClock.h"



/////////////////////////////////////////////////////////////////////////////
// CPLC_COMUDlg dialog

class CPLC_COMUDlg : public CDialog
{
// Construction
public:
	CPLC_COMUDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPLC_COMUDlg)
	enum { IDD = IDD_PLC_COMU_DIALOG };
	CEdit	m_edtData;
	CEdit	m_edtAjs;
	int		m_intAjs;
	int		m_intData;
	CString	m_Note;
	bool	m_ckWT;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPLC_COMUDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	public:
		//==================================================
		// public function region
		
		// initialize the UI when software setup 
		void Initial_UI(void);




		//==================================================
		// public variant region 
		PLC_Dapk m_PLCDpke;
		CButtonST	m_btnPort;
		CButtonST	m_btnSend;
		CDigitalClock	m_edtNumbDIG;
		CFont		m_font;
		CFont		m_fntNote;

		static   CMSComm m_com;	









	private:

		//==================================================
		// private function  region 
	
		//===================================================
		// dispose the retrieved data 
		//-------------------------------------------------- 
		//UINT pMSE					judge whether retrieved data correct 
		//UINT Pkey					judge the data belong 
		//int pinterger				retrieved data from the PLC, 
		void	COM_Dispose(UINT pMSE,UINT Pkey,int pinterger);

		//===================================================================
		//	PLC com port data send out function 
		//Send_Figure(CByteArray *pbytearray,UINT pkey,int waitime=500 
		//				bool Is_Privilege=false ,CMSComm *comm=&m_com );
		// --------------------------------------------------------------
		//CByteArray *pbytearray:		the element going to send tou 
		//UINT pkey:					the flag to mark the send out data type 
		//int waitime=500				the timer to tick the time 
		//bool Is_Privilege=false		the priority  to be sended
		//CMSComm *comm=&m_com			choose the comm port to send 
		bool	Send_Figure(CByteArray *pbytearray,UINT pkey,int waitime=500 ,\
			bool Is_Privilege=false ,CMSComm *comm=&m_com );

		//=================================================================
		// according the enter parameter ,to set the comm port open or closed 
		bool SetCommPort(bool bOpenPort);
	
		//=================================================================
		// set the bottom of the portopen appearance ,depend on the order 
		void UI_SetPortBtn(bool bOpen);

		//=================================================================
		// check the enter number whether legal 
		bool Check_InputNumb();

		//=================================================================
		// load the data into specified data type for PLC communication 
		// send data at the same time 
		void SendComm_Data();

		//=================================================================
		//  control the UI appearance ,the data fluent steps
		// it had three kind statue , initialize statue , send data statue 
		// and the receive data statue 
		//--------------------------------------------------------------
		// UINT iStatue				judge the UI control statue 
		//bool isOK=true			for the statue 2 judgment  retrieved 
		//							data OK or not 
		void UI_lampControl(UINT iStatue,bool isOK=true);



	//========================
	// private variant region 



// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPLC_COMUDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnConfirm();
	afx_msg void OnBtnPort();
	afx_msg void OnRdiIsrd0();
	afx_msg void OnRdiIsrd1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLC_COMUDLG_H__DFB3D874_8725_4877_BDBF_5D53A0C7993F__INCLUDED_)
