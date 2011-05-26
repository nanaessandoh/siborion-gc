#include <pic.h>
#include 	<string.h> 

extern void Read_Sms_Nom(void);
extern void Trans_Str_CR(const char *s);


#include	"include/var.c"
#include	"delay.c"
#include	"include/init.c"
#include	"include/reg.c"
//#include	"include/func.c"
//#include	"include/priem.c"
//#include	"include/pered.c"
#include	"include/up_sim300.h"
#include	"sim300.h"
#include	"include/int.c"
//#include	"include/dallas.h"



//__CONFIG    (WDTDIS & PWRTEN & MCLREN & BOREN & LVPDIS & DATUNPROT & HS); 

__CONFIG  (UNPROTECT &  UNPROTECT & UNPROTECT & BOREN & PWRTEN & WDTDIS & HS & MCLRDIS);


void main(void)
{

Init();
RS_Init();

//ON=10;
WAIT_ANSWER=20;
WAIT_RESTART=Max_Wait_Answer;

In1_Tmp=In1;
In2_Tmp=In2;

for (;;)
	{


	if (MS03)
		{

		CLRWDT();

		if (ALARM_DO&ALARM_MASK_DIAL)
			{Led1=0;}
		else
			{Led1=1;}


		if (!Rx)
			{
			if (RX_DELAY<20)
				{
				RX_DELAY++;
				if (RX_DELAY==20)
					{
//					ON=10;
					PwrKey=1;
					DelayMs(250);
					DelayMs(250);
					DelayMs(250);
					DelayMs(250);
					DelayMs(250);
					DelayMs(250);
					DelayMs(250);
					DelayMs(250);
					DelayMs(250);
					DelayMs(250);
					DelayMs(250);
					DelayMs(250);
					PwrKey=0;
					}
				}
			}
		else
			{RX_DELAY=0;}
			
		


		MS03=0;

//		if (ON>0)
//			{
//			ON--;
//			if (ON>0)
//				{PwrKey=1;}
//			else
//				{PwrKey=0;}
//			}
//		else

//			{
			if (!(REGIM==REGIM_TMP))
				{
				REGIM_TMP=REGIM;
				WAIT_RESTART=Max_Wait_Answer;
				if (REGIM<=Wait_Reg)
					{WAIT_RESTART=60;}
				}
			else
				{
				if (WAIT_RESTART>0)
					{WAIT_RESTART--;}
				else
					{
					WAIT_RESTART=Max_Wait_Answer;
					if (REGIM>Wait1)
						{
						REGIM=Ath;
						WAIT_ANSWER=0;
						}
					else
						{
						PwrKey=1;
						DelayMs(250);
						DelayMs(250);
						DelayMs(250);
						PwrKey=0;
						DelayMs(250);
						DelayMs(250);
						DelayMs(250);
						DelayMs(250);
						DelayMs(250);
						DelayMs(250);

						REGIM=Echo_Off;
						}
					}
				}

			if (WAIT_ANSWER==0)
				{Peredacha();}
			else
				{
				WAIT_ANSWER--;
				if ((strstr(RESIV,&ALLSTR[_OK])) || strstr(RESIV,&ALLSTR[_ERROR]) || strstr(RESIV,&ALLSTR[_BUSY]) || strstr(RESIV, &ALLSTR[_NO_CAR]) || strstr(RESIV,&ALLSTR[_ECHO_OFF]) || strstr(RESIV,&ALLSTR[_SMS_TEXT]) || strstr(RESIV, &ALLSTR[_RING]) || strstr(RESIV,&ALLSTR[_RES_SMS]))
					{Priem();}
				}
//			}
		}



	if (MS71)
		{
		MS71=0;
		if (En_Transmit)
			{
//			Led1=1;
			TXREG=(TRANSMIT[Kol_Transmit]);
			if ((TRANSMIT[Kol_Transmit]==0x0D)||(TRANSMIT[Kol_Transmit]==0x1A))
				{En_Transmit=0;}
			Kol_Transmit++;
			}
		else
			{
//			Led1=0;
			}
		}
	}
}


