/**
 *  Display Command
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "prg_def.h"
#include "prg_func.h"

/*----- Defines -----*/
#define COMMAND_CODE_LENGHT		4
#define COMMAND_END_CHAR		'\n'

/*----- Function Prototypes -----*/
eCmdCode cmd_parse( void );
eCmdCode cmd_exec( void );
uint8_t cmd_comp(char *pcPattern);

/*----- Global Variables -----*/
char sCmdCode[COMMAND_CODE_LENGHT];
char sCmdData[USART_DATA_SIZE];

void cmd_init()
{
	usart_init(COMMAND_BAUDRATE);
}

eCmdCode cmd_check()
{
	eCmdCode eRetVal = eCMD_NONE;

	if(usart_get_lastchar() == COMMAND_END_CHAR)
	{
		eRetVal = cmd_parse();
	}

	return eRetVal;
}

eCmdCode cmd_parse()
{
	eCmdCode eRetVal = eCMD_NONE;
	uint16_t i;

	memset(&sCmdCode, 0, COMMAND_CODE_LENGHT);
	memset(&sCmdData, 0, USART_DATA_SIZE);

	for(i = 0; i < usart_nIndex - 1; i++)
	{
		if(i < COMMAND_CODE_LENGHT)
		{	/* Parse Command Code */
			sCmdCode[i] = usart_sMessage[i];
		}
		else
		{	/* Parse Command Data */
			sCmdData[i - COMMAND_CODE_LENGHT] = usart_sMessage[i];
		}
	}

	/*Check if command valid*/
	if(sCmdCode[0] != '\0' && sCmdCode[1] != '\0' && sCmdCode[2] != '\0' && sCmdCode[3] != '\0')
	{
		eRetVal = cmd_exec();
	}
	
	/* Empty usart message data */
	usart_message_clear();
	
	return eRetVal;
}

uint8_t cmd_comp(char *pcPattern)
{
	uint8_t bRetVal		= 0;
	uint8_t bOkCount	= 0;
	uint8_t	bCodeCount	= 0;

	for(bCodeCount = 0; bCodeCount < COMMAND_CODE_LENGHT; bCodeCount++)
	{	
		/* Matching command codes */
		if(sCmdCode[bCodeCount] == pcPattern[bCodeCount])
		{
			bOkCount++;
		}
	}

	/* Check if command pattern is matched */
	if(bOkCount == COMMAND_CODE_LENGHT)
	{
		bRetVal = 1;
	}

	return bRetVal;
}

eCmdCode cmd_exec()
{
	eCmdCode eRetVal = eCMD_NONE;

	if(cmd_comp(CODE_SETMSG01))
	{
		eRetVal = eCMD_UPDTMSG01;
	}
	else if(cmd_comp(CODE_SETMSG02))
	{
		eRetVal = eCMD_UPDTMSG02;
	}
	else if(cmd_comp(CODE_SETMSG03))
	{
		eRetVal = eCMD_UPDTMSG03;
	}
	else if(cmd_comp(CODE_SETMSG04))
	{
		eRetVal = eCMD_UPDTMSG04;
	}
	else if(cmd_comp(CODE_SETMSG05))
	{
		eRetVal = eCMD_UPDTMSG05;
	}
	else if(cmd_comp(CODE_GETMSG01))
	{
		eRetVal = eCMD_SENDMSG01;
	}
	else if(cmd_comp(CODE_GETMSG02))
	{
		eRetVal = eCMD_SENDMSG02;
	}
	else if(cmd_comp(CODE_GETMSG03))
	{
		eRetVal = eCMD_SENDMSG03;
	}
	else if(cmd_comp(CODE_GETMSG04))
	{
		eRetVal = eCMD_SENDMSG04;
	}
	else if(cmd_comp(CODE_GETMSG05))
	{
		eRetVal = eCMD_SENDMSG05;
	}
	else if(cmd_comp(CODE_SETBRIGH))
	{
		eRetVal = eCMD_BRIGHTSET;
	}
	else if(cmd_comp(CODE_SETCLOCK))
	{
		eRetVal = eCMD_RTCUPDATE;
	}
	else if(cmd_comp(CODE_FCTRYRST))
	{
		eRetVal = eCMD_FACTORYRS;
	}
	
	return eRetVal;
}

void cmd_get_data(char *pcData)
{
	uint16_t i = 0;

	while(sCmdData[i] != '\0')
	{
		pcData[i] = sCmdData[i];
		i++;
	}

	/* Null end char */
	pcData[i] = '\0';
}