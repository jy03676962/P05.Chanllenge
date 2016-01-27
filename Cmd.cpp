#include "Cmd.h"


Cmd::Cmd()
{
	cmdType = "";
	cmdContent = "";
	isDeal = false;
	isNew = false;
}

void Cmd::setCmd(char* _cmdType,char* _cmdContent)
{
	cmdType = _cmdType;
	cmdContent = _cmdContent;
}

Cmd::~Cmd(void)
{
}
