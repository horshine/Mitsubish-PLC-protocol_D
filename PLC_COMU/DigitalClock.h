
/********************************************************************************

  File:    DigitalClock.h"
  Author:  Mt.Hu (hmt-abc@163.com)
  Date:    2008/4/28

  Note:    Please include the comment if you use the file in your project

********************************************************************************/

//#if !defined(AFX_DIGITALCLOCK_H__6308EC19_76C9_4BE5_8F53_B4DBB7B11340__INCLUDED_)
//#define AFX_DIGITALCLOCK_H__6308EC19_76C9_4BE5_8F53_B4DBB7B11340__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ALIGN_LEFT    0;
#define ALIGN_CENTER  1;
#define ALIGN_RIGHT   2;


/////////////////////////////////////////////////////////////////////////////
// CDigitalClock window

class CDigitalClock : public CStatic
{
// Construction
public:
	CDigitalClock();

// Attributes
public:	
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDigitalClock)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:	
	virtual ~CDigitalClock();
	
	COLORREF GetTextColor();
	COLORREF GetBkColor();
	int GetSpace();
	int GetAlign();

	void SetClock(int nHour,int nMinute,int nSecond);
	void SetSpace(int nSpace);
	void SetTextColor(COLORREF crText);
	void SetBkColor(COLORREF crBk);
	void SetAlign(int nAlign);
	void SetText(CString str);
	void SetBitmapLamp(int n);

	// Generated message map functions
protected:
	//{{AFX_MSG(CDigitalClock)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:	
	
	void DrawSection1(int nLeft);
	void DrawSection2(int nLeft);
	void DrawSection3(int nLeft);
	void DrawSection4(int nLeft);
	void DrawSection5(int nLeft);
	void DrawSection6(int nLeft);
	void DrawSection7(int nLeft);
	void Draw2Dot(int nLeft);
	void DrawSingleNumber(int nNum,int nLeft);
	void DrawHour();
	void DrawMinute();
	void DrawSecond();
	void DrawTimer();
	void DrawText();
	void DrawDataIG();	//画整数部分
	void Draw1Dot();	//画小数点
	void DrawDataDF();	//画小数部分

	COLORREF m_crText;
	COLORREF m_crBk;
	CRect m_rect;	
	CDC m_memDC;
	int m_nAlign;		//设置字符的偏左，偏右还是中间	0是左，1是中间，2是右，默认值为1
	int m_nWidth;		//字宽
	int m_nHour;
	int m_nMinute;
	int m_nSecond;
	int m_nSpace;		//字间间隙
	int m_nXmargin;		//左边距
	int m_nYmargin;		//上边距
	int m_StrLength;	//字符长度
	int m_PointLength;	//点的位置
	CString m_DataIG;	//整数部分字符
	CString m_DataDF;	//小数部分字符
	BOOL m_FlagP;		//判断是否有小数点
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_DIGITALCLOCK_H__6308EC19_76C9_4BE5_8F53_B4DBB7B11340__INCLUDED_)
