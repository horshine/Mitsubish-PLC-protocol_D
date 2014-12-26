
/********************************************************************************

  File:    DigitalClock.h"
  Author:  Mt.Hu (hmt-abc@163.com)
  Date:    2008/4/28

  Note:    Please include the comment if you use the file in your project

********************************************************************************/

// DigitalClock.cpp : implementation file
//

#include "stdafx.h"
#include "DigitalClock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDigitalClock

CDigitalClock::CDigitalClock()
{	
	m_crBk = RGB(0,0,0);//::GetSysColor(COLOR_BTNFACE);		//初始设置背景色为系统背景色
	m_crText = ::GetSysColor(COLOR_BTNTEXT);	//初始设置字体颜色为系统字体颜色
	m_nAlign = 1;
	m_nWidth = 0;	
	m_nHour = 0;
	m_nMinute = 0;
	m_nSecond = 0;
	m_nSpace = 5;
	m_nXmargin = 10;
	m_nYmargin = 4;	
	m_StrLength = 0;
	m_PointLength = 0;
	m_DataIG=_T("");
	m_DataDF=_T("");
	m_FlagP=FALSE;
	
}

CDigitalClock::~CDigitalClock()
{
}


BEGIN_MESSAGE_MAP(CDigitalClock, CStatic)
	//{{AFX_MSG_MAP(CDigitalClock)
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDigitalClock message handlers


void CDigitalClock::DrawSection1(int nLeft)
{
	if (m_memDC.m_hDC!=NULL)
	{
		CPoint point[4];
		point[0].x=nLeft+(int)(0.1*m_nWidth);
		point[0].y=m_nYmargin;

		point[1].x=nLeft+(int)(0.9*m_nWidth);
		point[1].y=m_nYmargin;

		point[2].x=nLeft+(int)(0.7*m_nWidth);
		point[2].y=(int)(0.2*m_nWidth)+m_nYmargin;

		point[3].x=nLeft+(int)(0.3*m_nWidth);
		point[3].y=(int)(0.2*m_nWidth)+m_nYmargin;

		CBrush br(m_crText);
		CRgn rgn;
		rgn.CreatePolygonRgn(point,4,ALTERNATE);
		m_memDC.FillRgn(&rgn,&br);

		br.DeleteObject();
		rgn.DeleteObject();
		
		m_memDC.MoveTo(point[0]);
		m_memDC.LineTo(point[1]);
		
		m_memDC.MoveTo(point[1]);
		m_memDC.LineTo(point[2]);
		
		m_memDC.MoveTo(point[2]);
		m_memDC.LineTo(point[3]);
		
		m_memDC.MoveTo(point[3]);
		m_memDC.LineTo(point[0]);			
	}	
}

void CDigitalClock::DrawSection2(int nLeft)
{
	if (m_memDC.m_hDC!=NULL)
	{
		CPoint point[5];
		point[0].x=nLeft+m_nWidth;
		point[0].y=(int)(0.1*m_nWidth)+m_nYmargin;

		point[1].x=nLeft+m_nWidth;
		point[1].y=(int)(0.8*m_nWidth)+m_nYmargin;

		point[2].x=nLeft+(int)(0.9*m_nWidth);
		point[2].y=(int)(0.9*m_nWidth)+m_nYmargin;

		point[3].x=nLeft+(int)(0.8*m_nWidth);
		point[3].y=(int)(0.8*m_nWidth)+m_nYmargin;

		point[4].x=nLeft+(int)(0.8*m_nWidth);
		point[4].y=(int)(0.3*m_nWidth)+m_nYmargin;

		CBrush br(m_crText);
		CRgn rgn;
		rgn.CreatePolygonRgn(point,5,ALTERNATE);
		m_memDC.FillRgn(&rgn,&br);

		br.DeleteObject();
		rgn.DeleteObject();

		m_memDC.MoveTo(point[0]);
		m_memDC.LineTo(point[1]);
		
		m_memDC.MoveTo(point[1]);
		m_memDC.LineTo(point[2]);
		
		m_memDC.MoveTo(point[2]);
		m_memDC.LineTo(point[3]);
		
		m_memDC.MoveTo(point[3]);
		m_memDC.LineTo(point[4]);
		
		m_memDC.MoveTo(point[4]);
		m_memDC.LineTo(point[0]);
	}

	
}

void CDigitalClock::DrawSection3(int nLeft)
{
	if (m_memDC.m_hDC!=NULL)
	{
		CPoint point[5];
		point[0].x=nLeft+m_nWidth;
		point[0].y=(int)(1.1*m_nWidth)+m_nYmargin;

		point[1].x=nLeft+m_nWidth;
		point[1].y=(int)(1.8*m_nWidth)+m_nYmargin;

		point[2].x=nLeft+(int)(0.8*m_nWidth);
		point[2].y=(int)(1.6*m_nWidth)+m_nYmargin;

		point[3].x=nLeft+(int)(0.8*m_nWidth);
		point[3].y=(int)(1.1*m_nWidth)+m_nYmargin;

		point[4].x=nLeft+(int)(0.9*m_nWidth);
		point[4].y=m_nWidth+m_nYmargin;

		CBrush br(m_crText);
		CRgn rgn;
		rgn.CreatePolygonRgn(point,5,ALTERNATE);
		m_memDC.FillRgn(&rgn,&br);

		br.DeleteObject();
		rgn.DeleteObject();

		m_memDC.MoveTo(point[0]);
		m_memDC.LineTo(point[1]);
		
		m_memDC.MoveTo(point[1]);
		m_memDC.LineTo(point[2]);
		
		m_memDC.MoveTo(point[2]);
		m_memDC.LineTo(point[3]);
		
		m_memDC.MoveTo(point[3]);
		m_memDC.LineTo(point[4]);
		
		m_memDC.MoveTo(point[4]);
		m_memDC.LineTo(point[0]);
	}
		
}

void CDigitalClock::DrawSection4(int nLeft)
{	
	if (m_memDC.m_hDC!=NULL)
	{
		CPoint point[4];
		point[0].x=nLeft+(int)(0.1*m_nWidth);
		point[0].y=(int)(1.9*m_nWidth)+m_nYmargin;

		point[1].x=nLeft+(int)(0.9*m_nWidth);
		point[1].y=(int)(1.9*m_nWidth)+m_nYmargin;

		point[2].x=nLeft+(int)(0.7*m_nWidth);
		point[2].y=(int)(1.7*m_nWidth)+m_nYmargin;

		point[3].x=nLeft+(int)(0.3*m_nWidth);
		point[3].y=(int)(1.7*m_nWidth)+m_nYmargin;		

		CBrush br(m_crText);
		CRgn rgn;
		rgn.CreatePolygonRgn(point,4,ALTERNATE);
		m_memDC.FillRgn(&rgn,&br);

		br.DeleteObject();
		rgn.DeleteObject();

		m_memDC.MoveTo(point[0]);
		m_memDC.LineTo(point[1]);
		
		m_memDC.MoveTo(point[1]);
		m_memDC.LineTo(point[2]);
		
		m_memDC.MoveTo(point[2]);
		m_memDC.LineTo(point[3]);
		
		m_memDC.MoveTo(point[3]);
		m_memDC.LineTo(point[0]);		
	
	}

}

void CDigitalClock::DrawSection5(int nLeft)
{
	if (m_memDC.m_hDC!=NULL)
	{
		CPoint point[5];
		point[0].x=nLeft;
		point[0].y=(int)(1.1*m_nWidth)+m_nYmargin;

		point[1].x=nLeft;
		point[1].y=(int)(1.8*m_nWidth)+m_nYmargin;

		point[2].x=nLeft+(int)(0.2*m_nWidth);
		point[2].y=(int)(1.6*m_nWidth)+m_nYmargin;

		point[3].x=nLeft+(int)(0.2*m_nWidth);
		point[3].y=(int)(1.1*m_nWidth)+m_nYmargin;

		point[4].x=nLeft+(int)(0.1*m_nWidth);
		point[4].y=m_nWidth+m_nYmargin;

		CBrush br(m_crText);
		CRgn rgn;
		rgn.CreatePolygonRgn(point,5,ALTERNATE);
		m_memDC.FillRgn(&rgn,&br);

		br.DeleteObject();
		rgn.DeleteObject();

		m_memDC.MoveTo(point[0]);
		m_memDC.LineTo(point[1]);
		
		m_memDC.MoveTo(point[1]);
		m_memDC.LineTo(point[2]);
		
		m_memDC.MoveTo(point[2]);
		m_memDC.LineTo(point[3]);
		
		m_memDC.MoveTo(point[3]);
		m_memDC.LineTo(point[4]);
		
		m_memDC.MoveTo(point[4]);
		m_memDC.LineTo(point[0]);
	}


}

void CDigitalClock::DrawSection6(int nLeft)
{
	if (m_memDC.m_hDC!=NULL)
	{
		CPoint point[5];
		point[0].x=nLeft;
		point[0].y=(int)(0.1*m_nWidth)+m_nYmargin;

		point[1].x=nLeft;
		point[1].y=(int)(0.8*m_nWidth)+m_nYmargin;

		point[2].x=nLeft+(int)(0.1*m_nWidth);
		point[2].y=(int)(0.9*m_nWidth)+m_nYmargin;

		point[3].x=nLeft+(int)(0.2*m_nWidth);
		point[3].y=(int)(0.8*m_nWidth)+m_nYmargin;

		point[4].x=nLeft+(int)(0.2*m_nWidth);
		point[4].y=(int)(0.3*m_nWidth)+m_nYmargin;

		CBrush br(m_crText);
		CRgn rgn;
		rgn.CreatePolygonRgn(point,5,ALTERNATE);
		m_memDC.FillRgn(&rgn,&br);

		br.DeleteObject();
		rgn.DeleteObject();

		m_memDC.MoveTo(point[0]);
		m_memDC.LineTo(point[1]);
		
		m_memDC.MoveTo(point[1]);
		m_memDC.LineTo(point[2]);
		
		m_memDC.MoveTo(point[2]);
		m_memDC.LineTo(point[3]);
		
		m_memDC.MoveTo(point[3]);
		m_memDC.LineTo(point[4]);
		
		m_memDC.MoveTo(point[4]);
		m_memDC.LineTo(point[0]);
	}

}

void CDigitalClock::DrawSection7(int nLeft)
{
	if (m_memDC.m_hDC!=NULL)
	{
		CPoint point[6];
		point[0].x=nLeft+(int)(0.3*m_nWidth);
		point[0].y=(int)(0.9*m_nWidth)+m_nYmargin;

		point[1].x=nLeft+(int)(0.7*m_nWidth);
		point[1].y=(int)(0.9*m_nWidth)+m_nYmargin;

		point[2].x=nLeft+(int)(0.8*m_nWidth);
		point[2].y=m_nWidth+m_nYmargin;

		point[3].x=nLeft+(int)(0.7*m_nWidth);
		point[3].y=(int)(1.1*m_nWidth)+m_nYmargin;

		point[4].x=nLeft+(int)(0.3*m_nWidth);
		point[4].y=(int)(1.1*m_nWidth)+m_nYmargin;

		point[5].x=nLeft+(int)(0.2*m_nWidth);
		point[5].y=m_nWidth+m_nYmargin;

		CBrush br(m_crText);
		CRgn rgn;
		rgn.CreatePolygonRgn(point,6,ALTERNATE);
		m_memDC.FillRgn(&rgn,&br);

		br.DeleteObject();
		rgn.DeleteObject();

		m_memDC.MoveTo(point[0]);
		m_memDC.LineTo(point[1]);
		
		m_memDC.MoveTo(point[1]);
		m_memDC.LineTo(point[2]);
		
		m_memDC.MoveTo(point[2]);
		m_memDC.LineTo(point[3]);
		
		m_memDC.MoveTo(point[3]);
		m_memDC.LineTo(point[4]);
		
		m_memDC.MoveTo(point[4]);
		m_memDC.LineTo(point[5]);
		
		m_memDC.MoveTo(point[5]);
		m_memDC.LineTo(point[0]);/**/
	}

}

void CDigitalClock::Draw2Dot(int nLeft)
{
	if (m_memDC.m_hDC!=NULL)
	{
		CBrush br(m_crText);				

		CRect rect;
		rect.SetRect(nLeft+(int)(0.3*m_nWidth),(int)(0.4*m_nWidth)+m_nYmargin,
			nLeft+(int)(0.6*m_nWidth),(int)(0.7*m_nWidth)+m_nYmargin);
		m_memDC.Ellipse(rect);
		CRgn rgn1;
		rgn1.CreateEllipticRgn(rect.left,rect.top,rect.right,rect.bottom);
		m_memDC.FillRgn(&rgn1,&br);

		rect.OffsetRect(0,(int)(0.8*m_nWidth)+m_nYmargin);
		m_memDC.Ellipse(rect);
		CRgn rgn2;
		rgn2.CreateEllipticRgn(rect.left,rect.top,rect.right,rect.bottom);
		m_memDC.FillRgn(&rgn2,&br);

		br.DeleteObject();
		rgn1.DeleteObject();
		rgn2.DeleteObject();
	}
}

void CDigitalClock::SetBkColor(COLORREF crBk)
{
	m_crBk = crBk;	

	//DrawTimer();
	DrawText();
}

void CDigitalClock::SetTextColor(COLORREF crText)
{
	m_crText = crText;
	
	//DrawTimer();
	DrawText();
}

void CDigitalClock::SetAlign(int nAlign)
{
	m_nAlign = nAlign;
	
	//DrawTimer();
	DrawText();
}

COLORREF CDigitalClock::GetBkColor()
{
	return m_crBk;
}

COLORREF CDigitalClock::GetTextColor()
{
	return m_crText;
}

int CDigitalClock::GetAlign()
{
	return m_nAlign;
}

void CDigitalClock::SetClock(int nHour, int nMinute, int nSecond)
{
	m_nHour = nHour;
	m_nMinute = nMinute;
	m_nSecond = nSecond;

	DrawTimer();	
}

void CDigitalClock::SetText(CString str)
{
	CString strn;
	m_PointLength=0;//str.Find(".");
	m_StrLength=str.GetLength();
	///////////////判断输入的是不是数字/////////////////////////
	LPTSTR p = str.GetBuffer(m_StrLength);
	str.ReleaseBuffer();
	char *pstr=p;
	if(!pstr)
	{
		return ;
	}
	for(UINT i=0;i<strlen(pstr)-1;i++)
	{
		if(pstr[i]!=46)		//点
		{
			if(pstr[i]!=45)	//负号
			{
				if(pstr[i]<48 || pstr[i]>57)
					return;						
			}
		}
		else
			m_PointLength=i+1;			//如果是小数点
	}
	/////////////////////////是数字进行下面的处理
	if(0==m_PointLength)	//判断字符串中是否有小数点,如果不是
	{
		//m_StrLength=str.GetLength();
		//strn=str.Left(m_PointLength);
		//strn=str.Mid(str.GetLength()-1);
		m_DataIG=str.Mid(0,m_StrLength);
		m_DataDF=_T("");	//str.Mid(m_PointLength+1,m_StrLength-m_PointLength);
		m_PointLength=0;
		m_FlagP=FALSE;
		//AfxMessageBox(m_DataIG);
	}
	else
	{
		m_PointLength--;
		m_DataIG=str.Mid(0,m_PointLength);							//小数点前面部分
		m_DataDF=str.Mid(m_PointLength+1,m_StrLength-m_PointLength);//小数点后面部分
		m_FlagP=TRUE;
		//AfxMessageBox(m_DataIG);
	}
	DrawText();
}

void CDigitalClock::DrawHour()
{
	int nLeft=m_nXmargin;
	if (m_nHour<10)
	{
		DrawSingleNumber(0,nLeft);
		nLeft+=m_nWidth+m_nSpace;
		DrawSingleNumber(m_nHour,nLeft);
	}
	else
	{
		TCHAR *c=new TCHAR[10];
		_itoa(m_nHour,c,10);
		int num1=c[0]-48;
		int num2=c[1]-48;
		DrawSingleNumber(num1,nLeft);
		nLeft+=m_nWidth+m_nSpace;
		DrawSingleNumber(num2,nLeft);
	}
	nLeft+=m_nWidth;
	Draw2Dot(nLeft);	
}

void CDigitalClock::DrawMinute()
{
	int nLeft=m_nXmargin+3*m_nWidth+m_nSpace;
	if (m_nMinute<10)
	{
		DrawSingleNumber(0,nLeft);
		nLeft+=m_nWidth+m_nSpace;
		DrawSingleNumber(m_nMinute,nLeft);
	}
	else
	{
		TCHAR c[10]={0};		
		_itoa(m_nMinute,c,10);		
		int num1=c[0]-48;
		int num2=c[1]-48;
		DrawSingleNumber(num1,nLeft);
		nLeft+=m_nWidth+m_nSpace;
		DrawSingleNumber(num2,nLeft);		
	}
}

void CDigitalClock::DrawSecond()
{
	int nLeft=m_nXmargin+6*m_nWidth+2*m_nSpace;
	if (m_nSecond<10)
	{
		DrawSingleNumber(0,nLeft);
		nLeft+=(int)(1.4*m_nWidth);
		DrawSingleNumber(m_nSecond,nLeft);
	}
	else
	{
		TCHAR *c=new TCHAR[10];
		_itoa(m_nSecond,c,10);
		int num1=c[0]-48;
		int num2=c[1]-48;
		DrawSingleNumber(num1,nLeft);
		nLeft+=m_nWidth+m_nSpace;
		DrawSingleNumber(num2,nLeft);	
	}
}

void CDigitalClock::DrawTimer()
{	
	if (m_memDC.m_hDC!=NULL)
	{	
		
		GetClientRect(&m_rect);		
		
		m_nWidth = (int)(m_rect.Height()-2*m_nYmargin)/2;
		if (0 == m_nAlign)
		{			
			m_nXmargin = m_nYmargin;
		}
		else if (2 == m_nAlign)
		{			
			m_nXmargin = m_rect.Width()-8*m_nWidth-3*m_nSpace-m_nYmargin;
		}
		else
		{
			m_nXmargin = (int)(m_rect.Width()-8*m_nWidth-3*m_nSpace)/2;
		}
		

		m_memDC.FillSolidRect(m_rect,m_crBk);

		CPen pen(PS_SOLID,1,m_crText);
		CPen* pOldPen=m_memDC.SelectObject(&pen);

		DrawHour();
		DrawMinute();
		DrawSecond();

		Invalidate();
		
		m_memDC.SelectObject(pOldPen);
		pen.DeleteObject();
	}
}

void CDigitalClock::DrawText()
{	
	if (m_memDC.m_hDC!=NULL)
	{	
		
		GetClientRect(&m_rect);		
		
		m_nWidth = (int)(m_rect.Height()-2*m_nYmargin)/2;
		if (0 == m_nAlign)
		{			
			m_nXmargin = m_nYmargin;
		}
		else if (2 == m_nAlign)
		{	
			if(m_FlagP)
				m_nXmargin =(int)( m_rect.Width()-(m_StrLength-1)*m_nWidth-0.6*m_nWidth-(m_StrLength-1)*m_nSpace-m_nYmargin);
			else
				m_nXmargin = m_rect.Width()-(m_StrLength)*(m_nWidth+m_nSpace)-m_nYmargin;
		}
		else
		{
			if(m_FlagP)
				m_nXmargin = (int)(m_rect.Width()-(m_StrLength-1)*m_nWidth-0.6*m_nWidth-(m_StrLength-1)*m_nSpace)/2;
			else
				m_nXmargin =(int)( m_rect.Width()-(m_StrLength)*(m_nWidth+m_nSpace))/2;
		}
		

		m_memDC.FillSolidRect(m_rect,m_crBk);

		CPen pen(PS_SOLID,1,m_crText);
		CPen* pOldPen=m_memDC.SelectObject(&pen);

		DrawDataIG();
		Draw1Dot();
		DrawDataDF();

		Invalidate();
		
		m_memDC.SelectObject(pOldPen);
		pen.DeleteObject();
	}
}

void CDigitalClock::DrawSingleNumber(int nNum,int nLeft)
{
	switch (nNum)
	{
	case 0:
		DrawSection1(nLeft);			
		DrawSection2(nLeft);
		DrawSection3(nLeft);
		DrawSection4(nLeft);
		DrawSection5(nLeft);
		DrawSection6(nLeft);
		break;
	case 1:		
		DrawSection2(nLeft);
		DrawSection3(nLeft);		
		break;
	case 2:
		DrawSection1(nLeft);
		DrawSection2(nLeft);
		DrawSection4(nLeft);
		DrawSection5(nLeft);
		DrawSection7(nLeft);
		break;
	case 3:
		DrawSection1(nLeft);
		DrawSection2(nLeft);
		DrawSection3(nLeft);
		DrawSection4(nLeft);		
		DrawSection7(nLeft);
		break;
	case 4:		
		DrawSection2(nLeft);
		DrawSection3(nLeft);		
		DrawSection6(nLeft);
		DrawSection7(nLeft);
		break;
	case 5:
		DrawSection1(nLeft);
		DrawSection3(nLeft);
		DrawSection4(nLeft);
		DrawSection6(nLeft);
		DrawSection7(nLeft);
		break;
	case 6:
		DrawSection1(nLeft);
		DrawSection3(nLeft);
		DrawSection4(nLeft);
		DrawSection5(nLeft);
		DrawSection6(nLeft);
		DrawSection7(nLeft);
		break;
	case 7:
		DrawSection1(nLeft);
		DrawSection2(nLeft);
		DrawSection3(nLeft);		
		break;
	case 8:
		DrawSection1(nLeft);
		DrawSection2(nLeft);
		DrawSection3(nLeft);
		DrawSection4(nLeft);
		DrawSection5(nLeft);
		DrawSection6(nLeft);
		DrawSection7(nLeft);
		break;
	case 9:
		DrawSection1(nLeft);
		DrawSection3(nLeft);
		DrawSection4(nLeft);
		DrawSection2(nLeft);
		DrawSection6(nLeft);
		DrawSection7(nLeft);
		break;
	default:
		break;
	}

}

void CDigitalClock::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	GetClientRect(&m_rect);		
	
	if (m_memDC.m_hDC==NULL)
	{
		m_nYmargin = (int)(0.1*m_rect.Height());
		CBitmap bmp;
		CBitmap* pOldBmp;

		m_memDC.CreateCompatibleDC(&dc);
		bmp.CreateCompatibleBitmap(&dc,m_rect.Width(),m_rect.Height());
		pOldBmp=m_memDC.SelectObject(&bmp);	
		DrawText();	
	}	
			
	dc.BitBlt(0,0,m_rect.Width(),m_rect.Height(),&m_memDC,0,0,SRCCOPY);	
	//
	
}

void CDigitalClock::SetSpace(int nSpace)
{
	m_nSpace = nSpace;

	DrawTimer();
}

int CDigitalClock::GetSpace()
{
	return m_nSpace;
}

void CDigitalClock::DrawDataIG()
{
	int nLeft=m_nXmargin;
	int l=m_DataIG.GetLength();
	LPTSTR p = m_DataIG.GetBuffer(l);
	m_DataIG.ReleaseBuffer();
	char *pstr=p;
	if(!pstr)
	{
		return ;
	}
	for(UINT i=0;i<strlen(pstr);i++)
	{
		int num1=pstr[i]-48;
		if(-3==num1)
		//if(45==pstr[i])	//说明这个字符为负号
		{
			DrawSection7(nLeft);
			nLeft+=m_nWidth+m_nSpace;
		}
		else
		{
			DrawSingleNumber(num1,nLeft);
			nLeft+=m_nWidth+m_nSpace;
		}
	}

}

void CDigitalClock::Draw1Dot()
{
	if(m_FlagP)
	{
		int nLeft=(int)(m_nXmargin+(m_PointLength-1)*(m_nWidth+m_nSpace)+0.8*m_nWidth+m_nSpace);
		if (m_memDC.m_hDC!=NULL)
		{
			CBrush br(m_crText);				
			
			CRect rect;
			rect.SetRect(nLeft+(int)(0.3*m_nWidth),(int)(1.6*m_nWidth)+m_nYmargin,
				nLeft+(int)(0.6*m_nWidth),(int)(1.9*m_nWidth)+m_nYmargin);
			m_memDC.Ellipse(rect);
			CRgn rgn1;
			rgn1.CreateRectRgn(rect.left,rect.top,rect.right,rect.bottom);
			m_memDC.FillRgn(&rgn1,&br);
						
			br.DeleteObject();
			rgn1.DeleteObject();
		}
	}
	else
	return ;
}

void CDigitalClock::DrawDataDF()
{
	int nLeft=(int)(m_nXmargin+(m_PointLength)*(m_nWidth+m_nSpace)+0.5*m_nWidth+m_nSpace);
	int l=m_DataDF.GetLength();
	LPTSTR p = m_DataDF.GetBuffer(l);
	m_DataDF.ReleaseBuffer();
	char *pstr=p;
	if(!pstr)
	{
		return ;
	}
	for(UINT i=0;i<strlen(pstr);i++)
	{
		int num1=pstr[i]-48;
		DrawSingleNumber(num1,nLeft);
		nLeft+=m_nWidth+m_nSpace;
	}
}

void CDigitalClock::SetBitmapLamp(int n)
{
	if (m_memDC.m_hDC!=NULL)
	{	
		
		GetClientRect(&m_rect);	
		switch (n)
		{
		case 0:
			m_crText=RGB(106,106,106);
			break;
		case 1:
			m_crText=RGB(0,255,0);
			break;
		case 2:
			m_crText=RGB(255,255,0);
			break;
		case 3:
			m_crText=RGB(255,0,0);
			break;
		default:
			return;
		}
		
		m_memDC.FillSolidRect(m_rect,m_crBk);	//重画背景色
		CBrush br(m_crText);
		CPen pPen(PS_SOLID,1,RGB(135,135,120));	//RGB(135,135,120)
		CPen pPen2(PS_SOLID,1,RGB(255,255,255));
		//m_memDC.SelectObject(&pPen);
		//m_memDC.Ellipse(m_rect.left+1,m_rect.top+1,m_rect.right,m_rect.bottom);
		//m_memDC.SelectObject(&pPen2);
		//m_memDC.Ellipse(m_rect.left,m_rect.top,m_rect.right-2,m_rect.bottom-2);

		
		CRgn rgn;
		rgn.CreateEllipticRgn(m_rect.left,m_rect.top,m_rect.right,m_rect.bottom);
		m_memDC.FillRgn(&rgn,&br);
		br.DeleteObject();
		rgn.DeleteObject();
		pPen.DeleteObject();
		pPen2.DeleteObject();
		Invalidate();
		
	}
}
void CDigitalClock::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//MessageBox("1D");
	//DrawText();
	CStatic::OnTimer(nIDEvent);
}

BOOL CDigitalClock::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	//DrawText();
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
