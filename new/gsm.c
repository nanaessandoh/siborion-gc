#include "gsm.h"
#include <string.h>

extern unsigned char REGIM;

unsigned char CurOk;
unsigned char CurError;
signed char CurTransmit;

struct Gsm_Kom 
{
	unsigned const char *At;
	unsigned const char *Ok;
	unsigned const char *Error;
	unsigned const char TimeOut;
	unsigned const char Pause;
	unsigned const char Repeat;
	unsigned const char RegimOk;
	unsigned const char RegimError;
};

const struct Gsm_Kom GSM_KOM[]  =  
{
	{//ATE0
	"ATE0\015",
	"OK",
	"ERROR",
	1,
	2,
	10,
	1,
	0,
	},

	{//ATE0
	"ATE0\015",
	"OK",
	"ERROR",
	1,
	2,
	10,
	2,
	1,
	},
};

unsigned char AddByteOk(unsigned char Val)
{
	unsigned char cTmp;
	if(GSM_KOM[REGIM].Ok[CurOk]==Val)
	{
		CurOk++;
		if(CurOk >= strlen(GSM_KOM[REGIM].Ok))
			cTmp = 2;
		else
			cTmp = 1;
	}
	else
	{
		CurOk = 0;
		cTmp = 0;
	}
	return cTmp;
}

unsigned char AddByteError(unsigned char Val)
{
	unsigned char cTmp;
	if(GSM_KOM[REGIM].Error[CurError]==Val)
	{
		CurError++;
		if(CurError >= strlen(GSM_KOM[REGIM].Error))
			cTmp = 2;
		else
			cTmp = 1;
	}
	else
	{
		CurOk = 0;
		cTmp = 0;
	}
	return cTmp;
}

void AddByte(unsigned char Val)
{
	if(AddByteOk(Val) == 2)
	{
		REGIM = GSM_KOM[REGIM].RegimOk;
		CurOk = CurError = 0;
	}
	else
	{
		if(AddByteError(Val) == 2)
		{
			REGIM = GSM_KOM[REGIM].RegimError;
			CurOk = CurError = 0;
		}
	}
}

void Transmit(void)
{
  if(CurTrans >= 0)
  {
    if(CurTrans >= strlen(GSM_KOM[REGIM].At)
      CurTrans = (-1);
    else
    {
      if(!TXIF)
      {
        TXREG = GSM_KOM[REGIM].At[CurTrans];
        
      }
    }
  }
}
