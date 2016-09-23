#include "LaserParseContent.h"


LaserParseContent::LaserParseContent(void)
{
	laser_n = "";
	laser_s = '0';
}


LaserParseContent::~LaserParseContent(void)
{
}

void LaserParseContent::setLaser_n(char* _laser_n)
{
	laser_n = _laser_n;
}
void LaserParseContent::setLaser_s(char _laser_s)
{
	laser_s = _laser_s;
}