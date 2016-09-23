#include "CmdLedCtrl.h"


CmdLedCtrl::CmdLedCtrl(void)
{
	ledParseContent = nullptr;
}


CmdLedCtrl::~CmdLedCtrl(void)
{
}

LedParseContent * CmdLedCtrl::getLedParseContent()
{
	return ledParseContent;
}
void CmdLedCtrl::setLedParseContent(LedParseContent * _ledParseContent)
{
	ledParseContent = _ledParseContent;
}

void CmdLedCtrl::setSize(int _size)
{
	size = _size;
}
