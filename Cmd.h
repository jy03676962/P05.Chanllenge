#pragma once
#ifndef CMD_H
#define CMD_H

class Cmd
{
public:

	char* cmdType;
	char* cmdContent;
	bool isDeal;
	bool isNew;

	void setCmd(char* _cmdType,char* _cmdContent);
	Cmd();
	~Cmd(void);
};
#endif 
