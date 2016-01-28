#pragma once
#ifndef CMDLEDCTRL_H
#define CMDLEDCTRL_H

#include "cmd.h"
#include "Led.h"

class CmdLedCtrl : public Cmd
{
public:

	Led ledList[20];

	CmdLedCtrl(void);
	~CmdLedCtrl(void);
};
#endif 
