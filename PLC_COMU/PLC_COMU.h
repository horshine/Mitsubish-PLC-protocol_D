// PLC_COMU.h : main header file for the PLC_COMU application
//

#if !defined(AFX_PLC_COMU_H__C028AE3B_1114_4F79_8CD4_0F2BB1DCF1C2__INCLUDED_)
#define AFX_PLC_COMU_H__C028AE3B_1114_4F79_8CD4_0F2BB1DCF1C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPLC_COMUApp:
// See PLC_COMU.cpp for the implementation of this class
//

class CPLC_COMUApp : public CWinApp
{
public:
	CPLC_COMUApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPLC_COMUApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPLC_COMUApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLC_COMU_H__C028AE3B_1114_4F79_8CD4_0F2BB1DCF1C2__INCLUDED_)
