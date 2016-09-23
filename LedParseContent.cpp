#include "LedParseContent.h"


LedParseContent::LedParseContent(void)
{
	wall = "";
	led_t = '0';
	mode = 0;
}


LedParseContent::~LedParseContent(void)
{
}
void LedParseContent::setWall(char* _wall)
{
	wall = _wall;
}
void LedParseContent::setLed_t(char _led_t)
{
	led_t = _led_t;
}
void LedParseContent::setMode(int _mode)
{
	mode = _mode;
}
