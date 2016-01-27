#pragma once
#include "cmd.h"
class CmdGameMode : public Cmd
{
public:
	char gameMode;
	CmdGameMode(void);
	~CmdGameMode(void);
};

