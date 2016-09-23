#pragma once
#ifndef CMD_H
#define CMD_H
#define nullptr 0

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
