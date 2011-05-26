#include <pic.h>
#include "init.h"
#include "gsm.h"

__CONFIG  (UNPROTECT &  UNPROTECT & UNPROTECT & BOREN & PWRTEN & WDTDIS & HS & MCLRDIS);

unsigned char REGIM;

void main(void)
{
Init();
RS_Init();

//REGIM = GSM_KOM[0].Delay;

for (;;)
	{
//	AddByte(REGIM);
	}
}


