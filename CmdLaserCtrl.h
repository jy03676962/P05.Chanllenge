#pragma once
#ifndef CMDLASERCTRL_H
#define CMDLASERCTRL_H
#include "cmd.h"
#include "LaserParseContent.h"

class CmdLaserCtrl : public Cmd
{
public:

	int size;
	LaserParseContent * laserParseContent;
	LaserParseContent * getLaserParseContent();
	void setLaserParseContent(LaserParseContent * _laserParseContent);
	void setSize(int _size);

	CmdLaserCtrl(void);
	~CmdLaserCtrl(void);
};
#endif 
