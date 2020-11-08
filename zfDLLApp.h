// zfDLLApp.h : main header file for the ZFDLLAPP application
//

#if !defined(AFX_ZFDLLAPP_H__420740C1_B5C4_41D6_97B3_C27BA5CA2898__INCLUDED_)
#define AFX_ZFDLLAPP_H__420740C1_B5C4_41D6_97B3_C27BA5CA2898__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CZfDLLAppApp:
// See zfDLLApp.cpp for the implementation of this class
//

class CZfDLLAppApp : public CWinApp
{
public:
	CZfDLLAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZfDLLAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CZfDLLAppApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZFDLLAPP_H__420740C1_B5C4_41D6_97B3_C27BA5CA2898__INCLUDED_)
