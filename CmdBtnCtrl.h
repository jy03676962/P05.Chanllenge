#pragma once
#ifndef CMDBTNCTRL_H
#define CMDBTNCTRL_H

#include "cmd.h"
class CmdBtnCtrl : public Cmd
{
public:
	char useful;
	char mode;
	char stage;

	CmdBtnCtrl(void);
	~CmdBtnCtrl(void);
};
#endif 

