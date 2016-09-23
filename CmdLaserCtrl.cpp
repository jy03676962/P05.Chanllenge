#include "CmdLaserCtrl.h"


CmdLaserCtrl::CmdLaserCtrl(void)
{
	laserParseContent = nullptr;
}


CmdLaserCtrl::~CmdLaserCtrl(void)
{
}

LaserParseContent * CmdLaserCtrl::getLaserParseContent()
{
	return laserParseContent;
}
void CmdLaserCtrl::setLaserParseContent(LaserParseContent * _laserParseContent)
{
	laserParseContent = _laserParseContent;
}

void CmdLaserCtrl::setSize(int _size)
{
	size = _size;
}
