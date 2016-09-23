#pragma once
#ifndef CMDLEDCTRL_H
#define CMDLEDCTRL_H

#include "cmd.h"
#include "LedParseContent.h"

class CmdLedCtrl : public Cmd
{
public:

	int size;
	LedParseContent * ledParseContent;
	LedParseContent * getLedParseContent();
	void setLedParseContent(LedParseContent * _ledParseContent);
	void setSize(int _size);

	CmdLedCtrl(void);
	~CmdLedCtrl(void);
};
#endif 
