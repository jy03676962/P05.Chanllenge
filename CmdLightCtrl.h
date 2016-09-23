#pragma once
#ifndef CMDLIGHTCTRL_H
#define CMDLIGHTCTRL_H

#include "cmd.h"
class CmdLightCtrl : public Cmd
{
public:
	char light_mode;
	CmdLightCtrl(void);
	~CmdLightCtrl(void);
};
#endif

