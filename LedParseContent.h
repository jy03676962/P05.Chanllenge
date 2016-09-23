#pragma once
#ifndef LEDPARSECONTENT_H
#define LEDPARSECONTENT_H

class LedParseContent
{
public:

	char* wall;//墙体编号
	char led_t;//灯带类型
	int mode;//灯带模式

	LedParseContent(void);
	~LedParseContent(void);

	void setWall(char* _wall);
	void setLed_t(char _led_t);
	void setMode(int _mode);
};
#endif 
