#define TRIS_A		0b11111101
#define TRIS_B		0b10101111
#define TRIS_C		0b11111000

#define Out1	RC0
#define Out2	RC1
#define PwrKey	RC2
#define Led1	RA1

#define Rx	RB5


#define In1	RA0
#define In2	RA3


static bit In1_Tmp;
static bit In2_Tmp;

static bit MS03;
static bit Alarm_Start;
static bit MS71;
//static bit Do_Transmit;  //Флаг на начало передачи
static bit En_Transmit;  //Флаг на передачу
static bit Do_Resiv;
static bit Timer;
//static bit Soft_Tx;
static bit Soft_Rx;       // Идет прием по софтовому входу
static bit Soft_Rx_Ready; // Прием по софтовому входу завершен!!!
static bit Tmp_Rx;
static bit Pre_Read_Sms;
//static bit Alarm;

static bit Led;

static bit Check_Reg;

//unsigned char NO_ANSWER; //Модуль не ответил :(( ++
//unsigned char bank1 ON;  //Если >0 то включаем PwrKey на 0.5 сек
unsigned char bank1 DEL;
unsigned char bank1 DEL_TIM;
unsigned char bank1 DEL_TIM71;
unsigned char bank1 RES_SMS_NOM[3];
unsigned char bank1 Kol_Resiv;
unsigned char bank2 RESIV[80];
unsigned char bank1 TRANSMIT[32];
//unsigned char bank1 PH_ALARM[32];
unsigned char bank1 REGIM;
unsigned char bank1 REGIM_TMP;
unsigned char bank1 Kol_Transmit;
unsigned char bank1 OUT1_RST;
unsigned char bank1 OUT2_RST;
unsigned char bank1 PHONE_NOM;
unsigned char bank1 SMS_SENT_DO;  //Эти смс ужо отправленны, их можно удалять

unsigned char bank1 WAIT_ANSWER;
//unsigned char bank1 WAIT_TIMEOUT;

unsigned char bank1 WAIT_RESTART;

unsigned char bank1 SOFT_TXREG;
unsigned char bank1 SOFT_RXREG;


unsigned char bank1 KOL_SOFT_TRANSMIT;
unsigned char bank1 KOL_SOFT_RESIV_BIT;
unsigned char bank1 NOM_BIT_TX;

unsigned char bank1 ALARM;
unsigned char bank1 ALARM_DO;
unsigned char bank1 PHONE_NOM;
unsigned char bank1 PHONE_NOM_DIAL;
//unsigned int  bank1 ALARM_DELAY;

unsigned char bank1 RX_DELAY;


unsigned int  bank1 ALARM_PAUSE;
unsigned int  bank1 ALARM_CUR_PAUSE;


unsigned int  bank1 DEL_IN_1;
unsigned int  bank1 DEL_IN_2;


//unsigned char SMS_NOM;

#define Echo_Off   0   //Выключаем эхо
#define Dial_Check 1   //Включаем режим дозвона с подтверждением
#define Text_On    2   //Включаем текстовый режим
#define Dial_In    3   //Включаем отображение входящих номеров
#define Wait_Reg   4   //Ждем регистрации в сети
#define Read_Nom   5   //Считываем номера Alarm-ов
#define Wait 	   7   //Ждемс че-нить (время от времени простукиваем AT)
#define Wait1 	   8   //Ждемс че-нить (время от времени простукиваем AT)
#define DialWait   9   //Ждем соединения....
#define SmsWait    10  //Ждем приглашения для отправки смс...
#define Dial_Wait_Discon 11
#define Dial_Ans   12
#define Dial_Ans_Wait  13
#define SmsSent    14
#define SmsCom     15
#define SmsDel     16
#define Ath  	   20

/*
const char *AT         = "AT";
const char *PHONE_NAME = "Tel1\000\000\000\000Tel2\000\000\000\000";
const char *DTMF       = "AT+VTS=\"0\"";
const char *SMS_ALARM  = "Alarm1\000\000Alarm2\000\000Power\000";
const char *InCom_Sms  = "On1\000\000On2\000\000Off1\000Off2\000Rst\000\000";

#define Max_Phone_Nom  1
*/
//#define Wait_No_Meandr 450
/*
#define Max_Wait_Answer 250
*/
