// PLC_Dapk.cpp : implementation file
//

#include <stdafx.h>
#include <math.h>
#include "PLC_Dapk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
//global variant section 
UINT g_PLCkey=KEY_default;					//define the global key default value 
bool g_Pswitch=false;
CCriticalSection	g_Csection;











/////////////////////////////////////////////////////////////////////////////
// PLC_Dapk

PLC_Dapk::PLC_Dapk()
{
}




PLC_Dapk::~PLC_Dapk()
{
}


// BEGIN_MESSAGE_MAP(PLC_Dapk, CWnd)
// 	//{{AFX_MSG_MAP(PLC_Dapk)
// 		// NOTE - the ClassWizard will add and remove mapping macros here.
// 	//}}AFX_MSG_MAP
// END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// PLC_Dapk message handlers


void PLC_Dapk::Ajs_formatToPLC(BYTE *data, int i)
{
   	BYTE b=i&0xf;
	data[3]=(b<10)?(b+0x30):(b+0x41-0xa);
	b=(i>>4)&0xf;
	data[2]=(b<10)?(b+0x30):(b+0x41-0xa);
	b=(i>>8)&0xf;
	data[1]=(b<10)?(b+0x30):(b+0x41-0xa);
	b=(i>>12)&0xf;
	data[0]=(b<10)?(b+0x30):(b+0x41-0xa);
		
}



void PLC_Dapk::Data_formatTOPLC(BYTE *data, int i)
{
	BYTE b=i&0xf;
	data[1]=(b<10)?(b+0x30):(b+0x41-0xa);
	b=(i>>4)&0xf;
	data[0]=(b<10)?(b+0x30):(b+0x41-0xa);
	b=(i>>8)&0xf;
	data[3]=(b<10)?(b+0x30):(b+0x41-0xa);
	b=(i>>12)&0xf;
	data[2]=(b<10)?(b+0x30):(b+0x41-0xa);
	
}


void PLC_Dapk::Load_CKCode(BYTE *Pdes, BYTE *Pscr, int len)//添加校验码
{
	int a=0;
	for(int i=0;i<len;i++)
	{
		a+=(*(Pscr+i));
	}

 	Load_CKCode_BitMov(Pdes,a);
}


void PLC_Dapk::Load_CKCode_BitMov(BYTE *data, int i)   //check code move bit
{
	char b=i&0xf;
	data[1]=(b<10)?(b+0x30):(b+0x41-0xa);
	b=(i>>4)&0xf;
	data[0]=(b<10)?(b+0x30):(b+0x41-0xa);
}


//////////////////////////////////////////////////////////////////////////
// GetDate_fromArray(BYTE* rd_data,long lenth)
//* rd_data :               the resource for data array  
//long lenth                the lenth of recieved array 
//------------------------------------------------------------------------
//the function is using for abstract the data from the fame
//this function could return a double value  
//////////////////////////////////////////////////////////////////////////
double PLC_Dapk::GetDate_fromArray(BYTE* rd_data,long lenth)
{
	BYTE dl_data[4];
	BYTE pre_data[4];
	double pow_numb;
	
	for (int j=0;j<4;j++)                     //剔除杂码
	{
		pre_data[j]=rd_data[j+1];
	}
	
	//////////////////////////////////////////////////////////////////////////
	dl_data[1]=(pre_data[0]<0x40)?(pre_data[0]-0x30):(pre_data[0]-0x41+0x0a);
	dl_data[0]=(pre_data[1]<0x40)?(pre_data[1]-0x30):(pre_data[1]-0x41+0x0a);
	dl_data[3]=(pre_data[2]<0x40)?(pre_data[2]-0x30):(pre_data[2]-0x41+0x0a);
	dl_data[2]=(pre_data[3]<0x40)?(pre_data[3]-0x30):(pre_data[3]-0x41+0x0a);	
	
	
	for (int i=0;i<4;i++)
	{
		dl_data[i]=dl_data[i]&0xf;
	}
	
	pow_numb=dl_data[3]*pow(16,3)+dl_data[2]*pow(16,2)+dl_data[1]*16+dl_data[0];
	return pow_numb;

}




//all of the function upside is using for generic a fame for PLC
//////////////////////////////////////////////////////////////////////////





















//////////////////////////////////////////////////////////////////////////
//produce a shakehands code for PLC

void  PLC_Dapk::API_shakehands(CByteArray *parray )
{
	BYTE byte_tmp=0x05;
    parray->Add(byte_tmp);
}

//////////////////////////////////////////////////////////////////////////
//API_Filldata(CByteArray *parray,int pajs，bool ioput,int pdata)
//----------------------------------------------------------------------
//CByteArray *parray           a pointer to a cbtearray class that will return 
// int pasj						the address to be send 
// int ioput					the data type ,decided read or write data from plc
// int pdata					the data which will be write into plc
//////////////////////////////////////////////////////////////////////////
void PLC_Dapk::API_Filldata(CByteArray *parray,int pajs,bool ioput,int pdata)
{
	if (ioput)    //true
	{
		Filldata_Write(parray,pajs,pdata);
	}

	else         //false
	{
		Filldata_Read(parray,pajs);
	}


}




//////////////////////////////////////////////////////////////////////////
//Filldata_Read(CByteArray * parray, int pajs)函数参数介绍
//------------------------------------------------------------------------
//* parray :               return the packaged data array 
//int ajs：                the going to query the PLC address 。
//------------------------------------------------------------------------
//the function is a interface for package a fame for PLC query the D type register 
//////////////////////////////////////////////////////////////////////////
void PLC_Dapk::Filldata_Read(CByteArray * parray, int pajs)
{
	 BYTE commstr[255];   // define  the store the array data 

	 //////////////////////////////////////////////////////////////////////////
    //package  data 
		commstr[0]=0x02;   //报文开始
		commstr[1]=0x30;	//读

		//------------------------------------------------------------------
		//address transfer to the requested format 
		int addressH=0x1000+pajs*2;           //first transfer 					
		Ajs_formatToPLC(&commstr[2],addressH);//second transfer 

        // define the lenth of the fame 
		commstr[6]=0x30;	
		commstr[7]=0x32;			//写入数量2，D即站32位
		commstr[8]=0x03;            //报文结束
		
		// produce the check code for the fame 
		Load_CKCode(&commstr[9],&commstr[1],8);			//得到效验码

	//////////////////////////////////////////////////////////////////////////

        //transfer data type from BYTE to CBYTEARRAY
		for(int i=0; i<11; i++)
		{
			parray->Add(commstr[i]);
		}

}





//////////////////////////////////////////////////////////////////////////
//Filldata_Write(CByteArray * parray, int pajs,int pdata=0)函数参数介绍
//------------------------------------------------------------------------
//* parray :               return the packaged data array 
//int ajs：                the going to query the PLC address 。
// pdata:                  the variant to be set the register ,the default value is 0
//------------------------------------------------------------------------
//the function is a interface for package a fame for PLC query the D type register 
//////////////////////////////////////////////////////////////////////////
void PLC_Dapk::Filldata_Write(CByteArray * parray, int pajs,int pdata)
{

	BYTE commstr[255];   // define  the store the array data 

	//////////////////////////////////////////////////////////////////////////
	//begin to package data into the byte type array 

	commstr[0]=0x02;			//the head of the fame 
	commstr[1]=0x31;			//write operation symbol 

	//--------------------------------------------------
    int addressH=pajs*2+0x1000;
	Ajs_formatToPLC(&commstr[2],addressH);//2,3,4,5地址
	
	commstr[6]=0x30;	
	commstr[7]=0x32;			//写入数量2，D即站32位
	
	Data_formatTOPLC(&commstr[8],pdata);		//load data into the array 
	commstr[12]=0x03;			
	Load_CKCode(&commstr[13],&commstr[1],12);	//计算和效验

	//////////////////////////////////////////////////////////////////////////

	for(int i=0; i<15; i++)
	{
		parray->Add(commstr[i]);
	}
	

}



//////////////////////////////////////////////////////////////////////////
//API_analiseArray(BYTE * parrybyte ,long lenth,bool ioput,double *backfig)
//-----------------------------------------------------------------------
//BYTE * parrybyte				convent into byte
//long lenth					the lenth of array
//bool ioput					the type of data ,decide the dealing way
//double *backfig				retrieve the figure from the array 
//this function is used for 1 abstract data form the array ,2 to mark the statue 

UINT PLC_Dapk::API_analiseArray(BYTE * parrybyte ,long lenth,UINT pkey,double *backfig)
{

	//=================================================
	// key match check 

	if (pkey<500)
	{
		AfxMessageBox("fatal error ,the key is illegal ");
		return PLC_KEYERROR;
	}




//////////////////////////////////////////////////////////////////////////
//  a protection for check the key 	
	bool ioput;
	if (pkey>=1000&&pkey<5000||pkey==KEY_hi)			//write data 
	{
		ioput=true;
	}
	if (pkey>=5000&&pkey<=10000)			// read data 
	{
		ioput=false;
	}

	if (lenth==1)
	{
		//write data condition 
		if (ioput)                 //true
		{
			switch(*parrybyte)
			{
			case 0x06:
				return PLC_SUCCESS;
				break;

			case 0x15:
				return PLC_NEGTIVE;
				break;
				
			default:
				return PLC_UNKNOW;
				break;
			}
		}
		//////////////////////////////////////////////////////////////////////////
		//the conditon read data ,but retrieve a single data 
	else
	{
		return PLC_UNKNOW;
	}

	}



	//////////////////////////////////////////////////////////////////////////
    // retrieve a serial btye ,to abstract figure from the array 

	if (lenth>1)
	{

		if (!ioput)          // false, read data form plc
		{
		   UINT iMSG;		
		   iMSG=API_checkCode(parrybyte,lenth);
		   if (iMSG!=PLC_SUCCESS)
		   {
			   return iMSG;
		   }

// 		   double pdouble;
			  backfig[0]=GetDate_fromArray(parrybyte,lenth);
// 			  backfig=&pdouble;

		   return PLC_SUCCESS;

		}

		else
		{
			return PLC_UNKNOW;
		}

	}


	//////////////////////////////////////////////////////////////////////////
	return PLC_EXCPTION;           //if this happen ,this would be exception 

}





//////////////////////////////////////////////////////////////////////////
//API_checkCode(const BYTE * barray, int lenth, bool MSGshow)函数参数介绍
//------------------------------------------------------------------------
//* barray :               the recieved array to be checked  
//int ajs：                the lenth of recieved array to be match the legal lenth
// bool MSGshow:           the bool variant decide on whether use the box to warming
//------------------------------------------------------------------------
//the function is a interface for package a fame for PLC query the D type register 
//////////////////////////////////////////////////////////////////////////

UINT  PLC_Dapk::API_checkCode( BYTE * barray, int lenth, bool MSGshow)
{
	int is_error=0;               
	int  legal_lenth=8;           //the define legal lenth  

	//judge the received array 's lenth match the requested lenth==8
	if (lenth!=legal_lenth)
	{
		is_error=PLC_OVERLENTH;		
	}


	//////////////////////////////////////////////////////////////////////////
	//check  code 
	else
	{
		BYTE *pbyte=new BYTE[20];
	
 		Load_CKCode(&pbyte[0],&barray[1],lenth-3);    //calculate the check code 

		//match the check code 
		for (int j=0;j<2;j++)
		{
			if (pbyte[j]!=barray[lenth-2+j])
			{
				is_error=PLC_CRC;
			}
		}   
		// release the pointer and it's stack
		delete pbyte;
		pbyte=NULL;
		is_error=PLC_SUCCESS;

	}

	if (MSGshow)
	{
		// API_errorShow()
	}

	return is_error;

}



//////////////////////////////////////////////////////////////////////////
//API_GetData(BYTE* rd_data,long lenth)函数参数介绍
//------------------------------------------------------------------------
//* rd_data :               the resource for data array  
//long lenth                the lenth of recieved array 
//------------------------------------------------------------------------
//the function is using for abstract the data from the fame
//this function could return a double value  
//////////////////////////////////////////////////////////////////////////
UINT  PLC_Dapk::API_GetData(BYTE* rd_data,long lenth,double *preturn)
{   
	UINT iserror=API_checkCode(rd_data,lenth);

    if (iserror!=PLC_SUCCESS)
    {
		return iserror;
    }

	*preturn=GetDate_fromArray(rd_data,lenth);

    return iserror;
	
}


void PLC_Dapk::API_errorShow(int sympol)
{
	switch(sympol)
	{
	case 0X00:
		AfxMessageBox("return sucessed!");
		break;
			
	case 0X05:
		AfxMessageBox("received array's lenth  don't match the  legal lenth,\r\n \
			please ensure the lenth fit regulation ");
		break;

	case 0X06:
		AfxMessageBox("the check code is error,\r\n \
			please check the send data array carefully");
		break;

	default:
		AfxMessageBox("unknow error, \r\n \
			please check the permit error coder whether legel");
		break;
	}
}






/************************************************************************/
/*                          待开发区                                    */
/************************************************************************/
// the following function is used for the lower layer development 
// 


/*       this is start prohibit

  
void PLC_Dapk::int2char(char *pbyte,int I_num)
{   //将读取字节个数转化成十六进制码
	if (I_num>256)
	{
		AfxMessageBox("输入字节数超出范围，\n请重新输入");
	}
	
	char pdata[2];
	for (int i=0;i<2;i++)
	{
		pdata[i]=(char)(I_num>>8-i*8)+(char)(0x30);
		*(pbyte+i)=pdata[i];                 //代码冗余，可省略
	}
	
}



//////////////////////////////////////////////////////////////////////////
//函数将整数转化成PLC码制的四个十六进制数
//
//
//
//////////////////////////////////////////////////////////////////////////






void PLC_Dapk::valueAscii24bit(char *data, int i)  //将写入数据转换成PLC数据
{
	char b=i&0xf;
	data[1]=(b<10)?(b+0x30):(b+0x41-0xa);
	b=(i>>4)&0xf;
	data[0]=(b<10)?(b+0x30):(b+0x41-0xa);
	b=(i>>8)&0xf;
	data[3]=(b<10)?(b+0x30):(b+0x41-0xa);
	b=(i>>12)&0xf;
	data[2]=(b<10)?(b+0x30):(b+0x41-0xa);
	b=(i>>16)&0xf;
	data[5]=(b<10)?(b+0x30):(b+0x41-0xa);
	b=(i>>20)&0xf;
	data[4]=(b<10)?(b+0x30):(b+0x41-0xa);
}



//////////////////////////////////////////////////////////////////////////
//将PLC制式的十六进制数还原成通用的十进制数
//int *i 为得到的整数指针
//
//
//
//////////////////////////////////////////////////////////////////////////

void PLC_Dapk::HexToDec(CString str, int *i)      //十六进制转换
{
	(*i)=0;				//由于传进来的是指针所以（*i）=表示赋值给它而不是赋地址。
	str.MakeUpper();        //把输入的字符如果为小写就转成大写
	int a=str.GetLength();	
	for (int z=0;z<a;z++)
	{
		char b=(str[z]-0x30)<10?(str[z]-0x30):(str[z]-0x41+10);		//转成16进制
		if(b>15||b<0)
		{
			(*i)=0;
			return;
		}
		(*i)+=(int)(b*pow(16,(a-z-1)));  //得到十进制数赋给i //pow是计算x的y次幂，16为x。
	}
	// 	return;
}



  void PLC_Dapk::string2char(char* pbyte,CString strtmp, int lenth)//将string转换成char
  {
  strtmp.MakeUpper();
  for (int j=0;j<lenth;j++)
  {
		pbyte[j]=char(strtmp.GetAt(j));
		}
		
		  
			
 }




*/  //this is the end 




