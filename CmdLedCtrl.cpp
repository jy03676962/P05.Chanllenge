#include "CmdLedCtrl.h"


CmdLedCtrl::CmdLedCtrl(void)
{
	for (int i = 0; i < 20; i++)
	{
		ledList[i].cell_num = "";
		ledList[i].wall_num = '0';
		ledList[i].led_type = 0;
		ledList[i].led_num = 0;
		ledList[i].newMode = 0;
	}
}


CmdLedCtrl::~CmdLedCtrl(void)
{
}
