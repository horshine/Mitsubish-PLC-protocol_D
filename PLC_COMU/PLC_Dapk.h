/************************************************************************/
/*                            PLC_Dapk  class                           */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
//PLC_Dapk class 
// copyrights   hesiyuan  2013-07-19
//this class is used in the PLC2PC communication .
//it's function is package the datapackage more convenient 
//you can use it for free ,but you cannot change author 
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLC_DAPK_H__CF3D7FE9_9986_40BC_B0B2_32F6096B51C3__INCLUDED_)
#define AFX_PLC_DAPK_H__CF3D7FE9_9986_40BC_B0B2_32F6096B51C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <afxmt.h>

// PLC_Dapk.h : header file
//////////////////////////////////////////////////////////////////////////
//define the global error message 
//this definition without data type,belong unsafe data 

#define		PLC_SUCCESS		0X00
#define		PLC_CRC			0X01
#define		PLC_OVERLENTH	0X02
#define		PLC_OVERTIMER	0X03
#define		PLC_NEGTIVE		0X04
#define		PLC_EXCPTION	0X05
#define		PLC_UNKNOW		0X06
#define		PLC_KEYERROR	0X07



//////////////////////////////////////////////////////////////////////////
// definition the global match key for PLC ,the extended key will depend on 
//the key to control the timer ,data type , data retrieve data dealing 
extern UINT g_PLCkey;	
											
const UINT KEY_default=0;
const UINT KEY_hi=500;
const UINT KEY_write=1000;			//the write key zoom is 1000-4999
const UINT KEY_read=5000;			// the read key zoom is 5000-10000

//////////////////////////////////////////////////////////////////////////
extern bool g_Pswitch;
extern CCriticalSection g_Csection;




/////////////////////////////////////////////////////////////////////////////
// PLC_Dapk window

class PLC_Dapk 
{
// Construction
public:
	PLC_Dapk();

// Attributes
public:
	//API ZOOM
	UINT	API_analiseArray(BYTE * parrybyte ,long lenth,UINT pkey,double *backfig);
	void	API_Filldata(CByteArray *parray,int  pajs,bool ioput,int pdata=0);
	void	API_shakehands(CByteArray * parray);
	UINT    API_checkCode( BYTE * barray, int lenth, bool MSGshow=false);
	UINT	API_GetData(BYTE* rd_data,long lenth,double * preturn);
	void	API_errorShow(int sympol);


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PLC_Dapk)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~PLC_Dapk();

	// Generated message map functions

private:
	//function zoom 

	void Filldata_Read(CByteArray * parray, int pajs);
	void Filldata_Write(CByteArray * parray, int pajs,int pdata=0);
	double GetDate_fromArray(BYTE* rd_data,long lenth);
	void Ajs_formatToPLC(BYTE *data, int i );
	void Data_formatTOPLC(BYTE *data, int i);
	void Load_CKCode(BYTE *Pdes, BYTE *Pscr, int len);
	void Load_CKCode_BitMov(BYTE *data, int i);




// 	void string2char(char* ,CString , int);
// 	void int2char(char *,int );
// 	void valueAscii24bit(char *, int );
// 	void HexToDec(CString , int *);
// 
// 	void absj_data(char*,long);




protected:
	//{{AFX_MSG(PLC_Dapk)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLC_DAPK_H__CF3D7FE9_9986_40BC_B0B2_32F6096B51C3__INCLUDED_)
