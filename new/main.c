#include <pic.h>
#include "init.h"
#include "gsm.h"
#include "main.h"

__CONFIG  (UNPROTECT &  UNPROTECT & UNPROTECT & BOREN & PWRTEN & WDTDIS & HS & MCLRDIS);

unsigned char REGIM;
unsigned char MS71;

void main(void)
{
Init();
RS_Init();

//REGIM = GSM_KOM[0].Delay;

for (;;)
	{
	if (MS71)
		{
		MS71=0;
		Transmit();
		}
	}
}


