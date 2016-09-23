#pragma once
#ifndef CMDMP3CTRL_H
#define CMDMP3CTRL_H

#include "cmd.h"
class CmdMp3Ctrl : public Cmd
{
public:

	char* music;

	CmdMp3Ctrl(void);
	~CmdMp3Ctrl(void);
};
#endif

