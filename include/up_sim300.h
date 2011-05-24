#define Sms_In_En   1  
#define Dial_In_En  1

const char *AT         = "AT";
const char *PHONE_NAME = "Tel1\000\000\000\000Tel2\000\000\000\000";
const char *DTMF       = "AT+VTS=\"0\"";
const char *SMS_ALARM  = "Alarm1\000\000Alarm2\000\000Power\000";
const char *InCom_Sms  = "On1\000\000On2\000\000Off1\000Off2\000Rst\000\000";
unsigned char bank1 ALARM_MASK_DIAL;
unsigned char  CUR_TASK; //Текущая задача
unsigned char  CUR_OP;   //Текущая опция


#define Max_Phone_Nom  1
#define Max_Wait_Answer 250

unsigned char Resiv_Ring(void) //Принят входящий звонок
{
if ((strstr(RESIV,&PHONE_NAME[0]))||(strstr(RESIV,&PHONE_NAME[8])))  
	{return 1;}
else
	{return 0;}
}

unsigned char Resiv_Sms(void) //Принято СМС читаем его номер
{
Read_Sms_Nom();
return 1;
}

void Read_And_Com_Sms(void)  //Прочитана входящая СМС - делаем выводы
{
if ((strstr(RESIV,&PHONE_NAME[0]))||(strstr(RESIV,&PHONE_NAME[8])))  
	{
	if (strstr(RESIV,&InCom_Sms[0]))
		{
//		Led1=1;
		Out1=1;
		}

	if (strstr(RESIV,&InCom_Sms[5]))
		{
//		Led2=1;
		Out2=1;
		}	

	if (strstr(RESIV,&InCom_Sms[10]))
		{
//		Led1=0;
		Out1=0;
		}

	if (strstr(RESIV,&InCom_Sms[15]))
		{
//		Led2=0;
		Out2=0;
		}

	if (strstr(RESIV,&InCom_Sms[20]))
		{
		OUT1_RST=3;
		OUT2_RST=3;
//		ALARM_DELAY=Wait_No_Meandr;
		}
	}
}



unsigned char Alarm_Com(void)  // Функция постоянно вызывается когда модель в режиме ожидания  
//в младшем разряде 0bxxxx xxxx
//                    Номер номера для отправки SMS
//		           Номер номера для отправки голосовых сообщений
//в старшем разряде 0bxxxxxxxx
//		      Номер отправляемых СМС или голосовых сообщений.


{
unsigned char i=0;
unsigned char j=0;

ALARM=(ALARM_DO&ALARM_MASK_DIAL);

if (ALARM==0)
	{return(0);}
else
	{
	if (ALARM_PAUSE==0)
		{
		PHONE_NOM_DIAL++;
		PHONE_NOM_DIAL&=0b00000111;

		if (Alarm_Start)
			{
			Alarm_Start=0;
			PHONE_NOM_DIAL=0;
			}

		while (!(ALARM&(1<<PHONE_NOM_DIAL)))
			{
			PHONE_NOM_DIAL++;
			PHONE_NOM_DIAL&=0b00000111;

			if (PHONE_NOM_DIAL==6)
				{
				ALARM_CUR_PAUSE++;
				ALARM_PAUSE=ALARM_CUR_PAUSE;
				}
			}
	
		if (PHONE_NOM_DIAL<=1)
			{
			return (PHONE_NOM_DIAL+1);
			}
		else
			{
			CUR_OP=0;
			if (ALARM&0b00001100)
				{CUR_OP|=0b00000001;}
			if (ALARM&0b00110000)
				{CUR_OP|=0b00000010;}

			return (((PHONE_NOM_DIAL&0b00000001)+1)<<4);
			}
		}
	else
		{
		ALARM_PAUSE--;;
		return (0);
		}
	}
}


void Sms_Sent_Ok(void)  //СМС удачно отправлена
{
if (CUR_OP&0b00000001)
	{ALARM_DO&=(255-(0b00000100<<((CUR_TASK>>4)-1)));}

if (CUR_OP&0b00000010)
	{ALARM_DO&=(255-(0b00010000<<((CUR_TASK>>4)-1)));}
}



void Dial_Ok(void)   //Дозвон по номеру осуществлен
{
if ((strstr(RESIV,&PHONE_NAME[0])) || (strstr(RESIV,&PHONE_NAME[8])))
	{
	ALARM_DO&=0b11111100;			
	REGIM=Dial_Wait_Discon;
	}
else
	{REGIM=Ath;}
}


void Dial_Wait_Com(void) //Исходящее соединение установлено... Можем делать что хотим
{
Trans_Str_CR(DTMF);
//En_Transmit=1;
}


void Dial_Ans_Com(void)  //Входящее соединение установлено... Можем делать что хотим
{
/*
if ((ALARM_DELAY>0) && (!In2))
	{Trans_Str_CR(DTMF);}
else
	{Trans_Str_CR(AT);}
*/
//En_Transmit=1;
}
              
