#include <pic.h>
#include <string.h>
#include "gsm.h"
#include "system.h"
#include "main.h"

#define ToOk 1
#define ToError 0
#define S2 200
#define S1 100


unsigned char CurOk;
unsigned char CurError;
signed   char CurTrans;
unsigned char CurTimeOut;
unsigned char RegimTmp;
unsigned char CurRepeat;
unsigned char RestartCount;
unsigned char RestartDelay;
unsigned char ErrorCount;


struct Gsm_Kom 
{
    unsigned const char *At;
    unsigned const char *Ok;
    unsigned const char *Error;
    unsigned const char TimeOut;  //
    //    unsigned const char Pause;
    unsigned const char Repeat;
    unsigned const char RegimOk;
    unsigned const char RegimError;

};

const struct Gsm_Kom GSM_KOM[]  =  
{
    {//ATE0
        "ATE0\r\n",
        "OK",
        "ERROR",
        10,
        //        2,
        10,
        1,
        0,
    },

{//ATE0
        "ATE0\015",
        "OK",
        "ERROR",
        10,
        //        2,
        10,
        2,
        1,
    },
};


void ChangeRegim(unsigned char Val)
{
    if (Val == ToOk)
        {REGIM = GSM_KOM[REGIM].RegimOk; ErrorCount = 0;}
    else
        {REGIM = GSM_KOM[REGIM].RegimError; ErrorCount++;}

    CurOk = CurError = CurTrans = 0;
}

void ChangeRegimMain(unsigned char Val)
{
    if (Val == ToOk)
        {REGIM = GSM_KOM[REGIM].RegimOk; ErrorCount = 0;}
    else
        {REGIM = GSM_KOM[REGIM].RegimError; ErrorCount++;}

    CurOk = CurError = CurTrans = 0;
}

unsigned char AddByteOk(unsigned char Val)
{
    unsigned char cTmp;
    if (GSM_KOM[REGIM].Ok[CurOk]==Val)
    {
        CurOk++;
        if (CurOk >= strlen(GSM_KOM[REGIM].Ok))
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
    if (GSM_KOM[REGIM].Error[CurError]==Val)
    {
        CurError++;
        if (CurError >= strlen(GSM_KOM[REGIM].Error))
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
    if (AddByteOk(Val) == 2)
        ChangeRegim(ToOk);
    else
    {
        if (AddByteError(Val) == 2)
            ChangeRegim(ToError);
    }
}

unsigned char strlen_main(const char * s)
{
    register const char *   cp;

    cp = s;
    while (*cp++)
        continue;
    return cp-s-1;
}

unsigned char Power(void)
{
    if(ErrorCount > 10)
	{
        RestartDelay = S2;
        ErrorCount = 0;
	}

    if(RestartDelay > 0)
    {
        RestartDelay--;
        if((RestartDelay > S1) && (RestartDelay < S2))
            PwrKey = 1;
        else
            PwrKey = 0;
        if(RestartDelay==0)
        {CurRepeat = REGIM = RestartCount = 0;}
        return 0; 
    }
    else
    {
        if(Rx)
            RestartCount = 0;
        else
        {
            RestartCount++;
            if(RestartCount == S1)
                RestartDelay = S2;
        }
    }
return 1;
}

void Transmit(void)
{
    if(!Power())
	return;

    if (RegimTmp != REGIM)
    {
        RegimTmp = REGIM;
        CurRepeat = 0;
    }

    if (CurTrans >= 0)
    {
        if (CurTrans >= strlen_main(GSM_KOM[REGIM].At))
        {
            CurTimeOut = 0;
            CurTrans = (-1);
        }
        else
        {
            if (TXIF & TRMT)
                TXREG = GSM_KOM[REGIM].At[CurTrans++];
        }
    }
    else
    {
        CurTimeOut++;
        if (CurTimeOut >= GSM_KOM[REGIM].TimeOut)
        {
            CurTrans = 0;
            CurRepeat++;
            if (CurRepeat >= GSM_KOM[REGIM].Repeat)
                ChangeRegimMain(ToError);
        }
    }
}

