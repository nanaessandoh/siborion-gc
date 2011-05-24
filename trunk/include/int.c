#define DEL_IN 1


void interrupt
Int(void)
{
if (RCIF)
	{
	RCIF=0;
	if (FERR == 1)
		{
		RESIV[Kol_Resiv++]=RCREG;
		RESIV[Kol_Resiv++]=RCREG;
	        }

	if (OERR == 1)
		{CREN = 0; CREN = 1;}

	RESIV[Kol_Resiv]=RCREG;

	Kol_Resiv++;

	if (Pre_Read_Sms)
		{
		if (Kol_Resiv>=20)
			{
			Kol_Resiv=0;
			Pre_Read_Sms=0;
			KOL_SOFT_TRANSMIT=0;
			}
		}
	else
		{
		if (Kol_Resiv>=77)
			{
			Kol_Resiv=77;
	                RESIV[Kol_Resiv]=0;
			}
		}
	}



if (T0IF)
	{
	T0IF=0;
	DEL++;

	DEL_TIM71++;

	if (DEL_TIM71==0)
		{
		MS71=1;


		if (In1)
			{
			if (DEL_IN_1)
				{DEL_IN_1--;}
			else
				{In1_Tmp=1;}
			}
		else
			{
			if (DEL_IN_1<DEL_IN)			
				{DEL_IN_1++;}
			else
				{
				if (In1_Tmp)
					{
					In1_Tmp=0;
					if (ALARM==0)
						{Alarm_Start=1;}
					ALARM_DO|=0b00000011;
					ALARM_CUR_PAUSE=0;
					ALARM_PAUSE=0;
					}
				}
			}


		if (In2)
			{
			if (DEL_IN_2)
				{DEL_IN_2--;}
			else
				{In2_Tmp=1;}
			}
		else
			{
			if (DEL_IN_2<DEL_IN)			
				{DEL_IN_2++;}
			else
				{
				if (In2_Tmp)
					{
					In2_Tmp=0;
					if (ALARM==0)
						{Alarm_Start=1;}
					ALARM_DO|=0b00000011;
					ALARM_CUR_PAUSE=0;
					ALARM_PAUSE=0;
					}
				}
			}
		}

	if (DEL>=3)
		{
		DEL_TIM++;
		if (DEL_TIM==0)
			{MS03=1;}
		DEL=0;
		}
	}

if (INTF)
	{INTF=0;}

if (RABIF)
	{RABIF=0;}


if (TMR1IF)
	{TMR1IF=0;}
}

