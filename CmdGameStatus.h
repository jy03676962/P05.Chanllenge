#pragma once
#ifndef CMDGAMESTATUS_H
#define CMDGAMESTATUS_H

#include "cmd.h"
class CmdGameStatus : public Cmd
{
public:

	char* gameStatus;

	CmdGameStatus(void);
	~CmdGameStatus(void);
};
#endif 
