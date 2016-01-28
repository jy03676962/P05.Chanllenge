#pragma once
#ifndef CMDGAMEMODE_H
#define CMDGAMEMODE_H

#include "cmd.h"
class CmdGameMode : public Cmd
{
public:
	char gameMode;
	CmdGameMode(void);
	~CmdGameMode(void);
};
#endif 
