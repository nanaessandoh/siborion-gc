#include <pic.h>
#include "gsm.h"
#include "main.h"

unsigned char DEL_TIM71;

void interrupt
Int(void)
{
unsigned char cTmp;
if (RCIF)
	{
	RCIF=0;
	if (FERR == 1)
		{
		AddByte(RCREG);
		AddByte(RCREG);
	        }
	if (OERR == 1)
		{CREN = 0; CREN = 1;}
	AddByte(RCREG);
	}


if (T0IF)
	{
	T0IF=0;
	DEL_TIM71++;
	if (DEL_TIM71==0)
		MS71=1;
	}

if (INTF)
	{INTF=0;}

if (RABIF)
	{RABIF=0;}


if (TMR1IF)
	{TMR1IF=0;}
}
