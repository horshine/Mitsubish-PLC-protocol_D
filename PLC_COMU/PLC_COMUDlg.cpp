// PLC_COMUDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PLC_COMU.h"
#include "PLC_COMUDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//================================================
//
CMSComm CPLC_COMUDlg::m_com;			// define the static variant 

CByteArray			BArray_hi;
CByteArray			BArray_read;
CByteArray			BArray_write;






/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPLC_COMUDlg dialog

CPLC_COMUDlg::CPLC_COMUDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPLC_COMUDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPLC_COMUDlg)
	m_intAjs = 0;
	m_intData = 0;
	m_Note = _T("");
	m_ckWT=false;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPLC_COMUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPLC_COMUDlg)
	DDX_Control(pDX, IDC_EDIT_DATA, m_edtData);
	DDX_Control(pDX, IDC_EDIT_AJS, m_edtAjs);
	DDX_Text(pDX, IDC_EDIT_AJS, m_intAjs);
	DDX_Text(pDX, IDC_EDIT_DATA, m_intData);
	DDX_Text(pDX, IDC_EDIT_NOTE, m_Note);
	DDX_Control(pDX, IDC_MSCOMM1, m_com);

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPLC_COMUDlg, CDialog)
	//{{AFX_MSG_MAP(CPLC_COMUDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_CONFIRM, OnBtnConfirm)
	ON_BN_CLICKED(IDC_BTN_PORT, OnBtnPort)
	ON_BN_CLICKED(IDC_RDI_ISRD0, OnRdiIsrd0)
	ON_BN_CLICKED(IDC_RDI_ISRD1, OnRdiIsrd1)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPLC_COMUDlg message handlers

BOOL CPLC_COMUDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	Initial_UI();
// 	m_com.SubclassDlgItem(IDC_MSCOMM1,this);



	m_edtData.SetLimitText(4);
	m_edtAjs.SetLimitText(4);

	// set the default check radio read 
// 	CheckRadioButton(IDC_RDI_ISRD0,IDC_RDI_ISRD1,IDC_RDI_ISRD1);
	((CButton *)GetDlgItem(IDC_RDI_ISRD1))->SetCheck(TRUE);

	BYTE b_hi=0x05;
	BArray_hi.Add(b_hi);





	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPLC_COMUDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPLC_COMUDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPLC_COMUDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CPLC_COMUDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CPLC_COMUDlg)
	ON_EVENT(CPLC_COMUDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()





void CPLC_COMUDlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	//////////////////////////////////////////////////////////////////////////
	// part one retrieve data transfer
	VARIANT variant_inp;
    COleSafeArray safearray_inp;
    LONG len,k;
    BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integerthat is not signed.
    CString strtemp;
    if(m_com.GetCommEvent()==2) //事件值为2表示接收缓冲区内有字符
    {             ////////以下你可以根据自己的通信协议加入处理代码
        variant_inp=m_com.GetInput(); //读缓冲区
        safearray_inp=variant_inp; //VARIANT型变量转换为ColeSafeArray型变量
        len=safearray_inp.GetOneDimSize(); //得到有效数据长度
        for(k=0;k<len;k++)
            safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组
    }
	
	//////////////////////////////////////////////////////////////////////////
	//	variant transport 
	KillTimer(g_PLCkey);
	int ikey=g_PLCkey;
	g_Pswitch=true;					//open the gate to allow the data to send out
	double idouble[1];				// define a array to retrieve the retrieve data
	int 	idata;
	//////////////////////////////////////////////////////////////////////////
	//	PLC data processing 
	UINT	iMSG=m_PLCDpke.API_analiseArray(rxdata,len,ikey,idouble);
	idata=(int)idouble[0];				//	transfer data from an array to a datatype ,to 
	//optimize memory , improve software 's security 
	//======================================================================
	//retrieve data dispose in various ways
	
	COM_Dispose(iMSG,ikey,idata);
}



void CPLC_COMUDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	static int tick_counts=0;

	switch(nIDEvent)
	{
		case KEY_hi:
			//////////////////////////////////////////////////////////////////////////
			// the timer frequency time shoud set smaller than 20ms
			tick_counts++;
			KillTimer(KEY_hi);				// stop loop ,

			//==================================================
			// this part is used for PLC connection test 
			// check whether the PLC had been power on ,or the 
			// cable connect well 
			if (tick_counts>20)
			{
				tick_counts=0;
				KillTimer(KEY_hi);	// stop the connection testing 
				// close the port , enforce the user open it again 
				OnBtnPort();
				//=======================
				// make a remark on the interface board 
				m_Note="port connection  failed!!!\r\nplease check  whether the PLC had setup \
or the cable had connected well ";
				UpdateData(false);
				//=======================
				return ;
			}
			
			else
			{
			//====================================================
			// for no response solution 
			// send the hand again ,open the switch ,and reset the key 			
			g_Pswitch=true;					// enforce the switch open 
							// to make sure the data could send out again 			
			Send_Figure(&BArray_hi,KEY_hi,200);			// 200 is for testing 
			return ;
			}


			break;


		case KEY_read:

			KillTimer(KEY_read);
			// for all the data send by hand . there is not too much data 
			// directly open the switch would not cause danger for the software 
			g_Pswitch=true;
			
			// resend the data again to disclosure the data dismiss 
			//situation . read data had priority compare with write data 
			Send_Figure(&BArray_read,KEY_read,200,true);

			break;
			
		case KEY_write:

			KillTimer(KEY_write);
			// for all the data send by hand . there is not too much data 
			// directly open the switch would not cause danger for the software 
			g_Pswitch=true;
			
			// resend the data again to disclosure the data dismiss 
			//situation . read data had priority compare with write data 
			Send_Figure(&BArray_write,KEY_write,150,false);

			break;

		default:
			break;
	}



	CDialog::OnTimer(nIDEvent);
}


void CPLC_COMUDlg::OnBtnConfirm() 
{
	// TODO: Add your control notification handler code here

	//=====================================
	// prevent the port not open to send data situation 
	// ensure the port had opened 
	if (!m_com.GetPortOpen())
	{
	m_Note="operation unavailable !!!\r\n \
please open the port first before send data operation  ";
	UpdateData(false);
	return ;
	}
	//=====================================

	UpdateData(true);			// get the interface value to the variant 

	if (!Check_InputNumb())
	{
		m_Note="the input adress is illegal \r\n please enter a unzore \
positive  integer ";
		//==============================
		// initialize the input data 
		m_intAjs=0;
		m_intData=0;
		//==============================
		UpdateData(false);
		GetDlgItem(IDC_EDIT_AJS)->SetFocus();
		return ;
	}
	
	// this function take response for load array ,and send data 
	SendComm_Data();
	UI_lampControl(1);

	// remark the operation 
	m_Note="specified data had been send into the register !!!";
	UpdateData(false);



}



void CPLC_COMUDlg::OnBtnPort() 
{
	// TODO: Add your control notification handler code here
	static bool bOpenport=false;
	
	//////////////////////////////////////////////////////////////////////////
	// judge the port statue ,to open or close the com port 
	if (!bOpenport)				// open comm port
	{
		bOpenport=true;
		UI_SetPortBtn(true);
		//===============================
		if (SetCommPort(true))
		{
			m_Note="port open successful !!!";
			UpdateData(false);

			//===========================
			// PLC connection test , declare the operation 

			Send_Figure(&BArray_hi,KEY_hi,20);
			//===========================
			

		}
		// if port open failed , recover the former appearance 
		else
		{
			bOpenport=false;
			UI_SetPortBtn(false);
			m_Note="port open failed  !!!";
			UpdateData(false);

		}

	}

	//////////////////////////////////////////////////////////////////////////
	// close the port 
	else
	{
		bOpenport=false;
		UI_SetPortBtn(false);

		SetCommPort(false);
		m_Note="port closed !!!";
		UpdateData(false);

		// initialize the lamp appearance when port closed 
		UI_lampControl(0);


	}

}









////////////////////////////////////////////////////////////////////////
//



void CPLC_COMUDlg::COM_Dispose(UINT pMSE,UINT Pkey,int pinterger)
{
	CString str_digit;


	//===================================================================
	// dispatch different message current 
	switch(Pkey)
	{
	
		//=====================================================
		// connection test 
	case KEY_hi:
		
		if (pMSE==PLC_SUCCESS)
		{	
			//==========================
			// show connection statue in the interface statue board 
			m_Note="port 1 had been opened \r\n \
port info : port 1  ' 9600, 7, e, 1' '";
			UpdateData(false);

		}
		// usually ,if connection failed ,there will be not response 
		// but for the old plc ,there could be possible 
		else
		{
			static int hi_counts=0;
			hi_counts++;
			
			// software will detect whether the PLC working well in 20*20 ms
			if (hi_counts<20)
			{
// 				SetTimer(KEY_hi,20,NULL);
				// prevent the spam data storm
				// before the trigger put on ,do nothing ,just wait 
				return;

			}
			else
			{
				// if the data storm had come ,only kill the program 
				// could helpful 
				hi_counts=0;
				ASSERT(1!=1);
			}

		}
		break;
		//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//
	case KEY_read:

		if (pMSE==PLC_SUCCESS)
		{
			//==============================
			// show retrieved data correct 
			// display the data on the digital box
			UI_lampControl(2);
			str_digit.Format("%d",pinterger);
			m_edtNumbDIG.SetText(str_digit);
			m_Note="read data successful !!!";
			UpdateData(false);

			//==============================
		}

		//	it's possible the communication signal interrupt 
		if (pMSE==PLC_CRC)
		{
			//==============================
			// resend the data query again 
			SetTimer(KEY_read,200,NULL);

			//==============================

		}

		// for the third kind error 
		if(pMSE!=PLC_CRC&&pMSE!=PLC_SUCCESS)
		{
			//==============================
			// show retrieved data error 
			UI_lampControl(2,false);
			m_Note="read data failed  !!!";
			UpdateData(false);
			
			//==============================
		}

		break;
		//////////////////////////////////////////////////////////////////////////
		

	//////////////////////////////////////////////////////////////////////////
	case KEY_write:

		if (pMSE==PLC_SUCCESS)
		{	
			//=============================
			// show the retrieved correct 
			UI_lampControl(2);
			m_Note="write  data successful !!!";
			UpdateData(false);

			//=============================
		}
		else
		{
			//=============================
			// show the retrieved error, do nothing  
			UI_lampControl(2,false);
			m_Note="write  data failed  !!!";
			UpdateData(false);

			//=============================

		}
		break;
		//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	default:
		ASSERT(1!=1);
		AfxMessageBox("warming : the key was unvaluable!!!\
			please check the send_figure function to ensure using the legal key  ");
			
		break;

	}




}




bool  CPLC_COMUDlg::Send_Figure(CByteArray *pbytearray,UINT pkey,\
								int waitime/* =500  */, bool Is_Privilege/* =false  */,CMSComm *comm/* =&m_com */ )
								
{	
	//=====================================
	// prevent the port not open to send data situation 
	if (!m_com.GetPortOpen())
	{
		m_Note="operation unavailable !!!\r\n \
please open the port before using the Send_Figure() function  ";
		UpdateData(false);
		return false;
	}
	//=====================================


	static bool s_privilege=false;		//define the static privilege variant 
	
	//check whether the privilege key had opened
	if (Is_Privilege)					
	{
		s_privilege=true;				// activate the the privilege key 
	}
	
	//set the filter to ensure the privilege data get through first
	if (!Is_Privilege&&s_privilege)
	{
		return false;
	}
	
	//setup  timer to tick time
	SetTimer(pkey,waitime,NULL);
	
	// dependent on the switch ,whether to get into the next step 
	if (!g_Pswitch)
	{
		return false;
	}
	
	//////////////////////////////////////////////////////////////////////////
	// enter the criticalsection 
	
	g_Csection.Lock();
	
	// to prevent the data slip into the section 
	if (!g_Pswitch)
	{
		g_Csection.Unlock();			// quickly get out the criticalsection 
		return false;				
	}
	
	//set the switch off.to closure the other application 
	g_Pswitch=false;
	g_PLCkey=pkey;
	
	comm->SetOutput(COleVariant(*(pbytearray)));
	
	//////////////////////////////////////////////////////////////////////////
	g_Csection.Unlock();
	s_privilege=false;
	
	return true;
	
}



bool CPLC_COMUDlg::SetCommPort(bool bOpenPort)
{
	// judge the port setting order 
	if (bOpenPort)
	{
	//////////////////////////////////////////////////////////////////////////
	// before set the comm statue ,it need to close the port first 
		if (m_com.GetPortOpen())
		{
			m_com.SetPortOpen(false);
		}
		m_com.SetCommPort(1);                	//设置端口变量
		m_com.SetSettings("9600,e,7,1");    	//
		m_com.SetInputMode(1);
		m_com.SetRThreshold(1);		        //接收一个字符变做出响应
		m_com.SetInputLen(0);               	//一次性取出字符的个数，为0时将所有缓冲区字符取出
		m_com.SetPortOpen(true);

		//================================
		// judge the port statue in case the port had been occupied 
		if (m_com.GetPortOpen())
		{
			return true;
		}
		else
		{	
			return false;
		}
	//////////////////////////////////////////////////////////////////////////
	}

	//======================================
	// clos the port 
	else 
	{
		m_com.SetPortOpen(false);
		return true;
	}



}



void CPLC_COMUDlg::UI_SetPortBtn(bool bOpen)
{
	// according the bottom statue ,to set the bottom contract statue 
	if (bOpen)
	{
		GetDlgItem(IDC_BTN_PORT)->SetWindowText("关闭串口");
		m_btnPort.SetBitmaps(IDB_RED,RGB(255,255,255));
	}
	// port closed , 
	else 
	{
		GetDlgItem(IDC_BTN_PORT)->SetWindowText("打开串口");
		m_btnPort.SetBitmaps(IDB_GREEN,RGB(255,255,255));
	}

}


bool CPLC_COMUDlg::Check_InputNumb()
{
	//////////////////////////////////////////////////////////////////////////
	if (m_ckWT)
	{
		// check address legislation 
		if (m_intAjs==0)
		{
			return false;
		}

		//========================
		// check the input data legislation 

		//========================
		
		//  the end is the result 
		return true;
	}



	//////////////////////////////////////////////////////////////////////////
	// read statue 
	if (!m_ckWT)
	{
		// check address legislation 
		if (m_intAjs==0)
		{
			return false;
		}
		
		//  the end is the result 
		return true;
	}

}

void CPLC_COMUDlg::OnRdiIsrd0() 
{
	// TODO: Add your control notification handler code here
	//  write data statue 
	m_ckWT=true;
	
	// NO necessary 
	// 	((CButton *)GetDlgItem(IDC_RDI_ISRD1))->SetCheck(TRUE);	
	
	//========================================
	// initialize UI 
	UI_lampControl(0);
	
	//========================================


}



void CPLC_COMUDlg::OnRdiIsrd1() 
{
	// TODO: Add your control notification handler code here
	// true , read data from PLC
	m_ckWT=false;

	// NO necessary 
// 	((CButton *)GetDlgItem(IDC_RDI_ISRD1))->SetCheck(TRUE);	
	
	//========================================
	// initialize UI 
	UI_lampControl(0);

	//========================================


}


void CPLC_COMUDlg::SendComm_Data()
{	
	if (m_ckWT)
	{
		// clean the old  array box,for an new one 
		BArray_write.RemoveAll();
		m_PLCDpke.API_Filldata(&BArray_write,m_intAjs,true,m_intData);
	
		// write data transmission is simplify no need for the priority 
		Send_Figure(&BArray_write,KEY_write,100);


	}

	else
	{
		// clean the old  array box,for an new one 

		BArray_read.RemoveAll();
		m_PLCDpke.API_Filldata(&BArray_read,m_intAjs,false);

		// take priority for ensure the quality of transmission 
		Send_Figure(&BArray_read,KEY_read,150,true);

	}

	


}


void CPLC_COMUDlg::UI_lampControl(UINT iStatue,bool isOK)
{
	// declare the icon handle for the lamp  
	HICON h_icnSend=NULL;
	HICON h_icnRecv=NULL;

	switch(iStatue)
	{

	//////////////////////////////////////////////////////////////////////////
	// initialize statue 
	case 0:
		h_icnSend=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_GRAY));
		h_icnRecv=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_GRAY));
		((CStatic*)GetDlgItem(IDC_ICON_SEND))->SetIcon(h_icnSend);
		((CStatic*)GetDlgItem(IDC_ICON_RECV))->SetIcon(h_icnRecv);

		GetDlgItem(IDC_STATIC_DATA)->ShowWindow(SW_HIDE);

		if (m_ckWT)
		{
			GetDlgItem(IDC_EDIT_DATA)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_INFO)->ShowWindow(SW_SHOW);
		}
		else
		{
			GetDlgItem(IDC_EDIT_DATA)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_INFO)->ShowWindow(SW_HIDE);
		}

		break;


		//////////////////////////////////////////////////////////////////////////
		// send data statue 
	case 1:
		// send data lamp green
		h_icnSend=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_GREEN));
		h_icnRecv=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_GRAY));
		((CStatic*)GetDlgItem(IDC_ICON_SEND))->SetIcon(h_icnSend);
		((CStatic*)GetDlgItem(IDC_ICON_RECV))->SetIcon(h_icnRecv);


		GetDlgItem(IDC_STATIC_DATA)->ShowWindow(SW_HIDE);
		// when read data situation ,the information of notification hide 
		// for the loop of read data .if need to hide 
		if (!m_ckWT)
		{
			GetDlgItem(IDC_STATIC_INFO)->ShowWindow(SW_HIDE);

		}

		
		break;


		//////////////////////////////////////////////////////////////////////////
		// retrieved  statue 
	case 2:
		// if data retrieved , data must be send outside 
		h_icnSend=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_GREEN));
	
		//////////////////////////////////////////////////////////////////////////
		// good data retrieved 
		if (isOK)
		{
			h_icnRecv=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_GREEN));

		}
		// error data retrieved 
		else
		{
			h_icnRecv=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_RED));
		}

		((CStatic*)GetDlgItem(IDC_ICON_SEND))->SetIcon(h_icnSend);
		((CStatic*)GetDlgItem(IDC_ICON_RECV))->SetIcon(h_icnRecv);

		//////////////////////////////////////////////////////////////////////////
		
		// when read data situation ,the information of notification hide 
		// for  read statue , digital box and info title show 
		if (!m_ckWT&&isOK)
		{
			GetDlgItem(IDC_STATIC_DATA)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_INFO)->ShowWindow(SW_SHOW);		
		}
		break;

	default:
		ASSERT(1!=1);
		break;

	}
}



void CPLC_COMUDlg::Initial_UI()
{

	//////////////////////////////////////////////////////////////////////////
	// button initialize region
	m_btnPort.SubclassDlgItem(IDC_BTN_PORT,this);
	m_btnPort.SetBitmaps(IDB_GREEN,RGB(255,255,255));
	m_btnPort.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnPort.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 50);
	m_btnPort.SetTooltipText("绿色：串口未打开\r\n红色：串口已打开");
	// 	m_btnPort.DrawTransparent(TRUE);

	
	m_btnSend.SubclassDlgItem(IDC_BTN_CONFIRM,this);
	m_btnSend.SetBitmaps(IDB_START64,RGB(255,255,255));
	m_btnSend.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSend.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 50);
	m_btnSend.SetTooltipText("单击发送查询");
	// 	m_btnPort.DrawTransparent(TRUE);

	// digital box data 
	m_edtNumbDIG.SubclassDlgItem(IDC_STATIC_DATA,this);
	m_edtNumbDIG.SetBkColor(RGB(255,255,180));
	m_edtNumbDIG.SetTextColor(RGB(255,0,0));
	
	// set font 
	// 	m_font.CreatePointFont(20,"宋体",NULL);
	m_font.CreateFont( 
		24,                        // nHeight
		0,                         // nWidth --if this value is 0 ,use the default system font size 
		0,                         // nEscapement
		0,                         // nOrientation
		FW_HEAVY,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality		
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"Myraid Pro");                 // lpszFacename
	
	m_fntNote.CreateFont( 
		15,                        // nHeight
		0,                         // nWidth --if this value is 0 ,use the default system font size 
		0,                         // nEscapement
		0,                         // nOrientation
		FW_HEAVY,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality		
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"Myraid Pro");           

	GetDlgItem(IDC_EDIT_AJS)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT_DATA)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT_NOTE)->SetFont(&m_fntNote);

	UI_lampControl(0);

}

HBRUSH CPLC_COMUDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here

	if( pWnd->GetSafeHwnd() == GetDlgItem(IDC_EDIT_AJS)->GetSafeHwnd() ||
		pWnd->GetSafeHwnd() == GetDlgItem(IDC_EDIT_DATA)->GetSafeHwnd())
// 		pWnd->GetSafeHwnd() == GetDlgItem(IDC_EDIT_NOTE)->GetSafeHwnd()) 
	{
		static HBRUSH hbrEdit = ::CreateSolidBrush( RGB(255, 255, 180) );	//set the global bk color 
// 		pDC->SetBkColor( RGB(255, 255, 180) );	// set txt bk color
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor( RGB(0, 0, 255) );	// set txt color 
		return hbrEdit;	
		
		
	}

	if( pWnd->GetSafeHwnd() == GetDlgItem(IDC_EDIT_NOTE)->GetSafeHwnd()) 
	{
		static HBRUSH hbrEdit = ::CreateSolidBrush( RGB(205, 250, 180) );	//set the global bk color 
		// 		pDC->SetBkColor( RGB(255, 255, 180) );	// set txt bk color
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor( RGB(255, 0, 0) );	// set txt color 
		return hbrEdit;	
		
		
	}






	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
