#pragma once
#ifndef LEDPARSECONTENT_H
#define LEDPARSECONTENT_H

class LedParseContent
{
public:

	char* wall;//ǽ����
	char led_t;//�ƴ�����
	int mode;//�ƴ�ģʽ

	LedParseContent(void);
	~LedParseContent(void);

	void setWall(char* _wall);
	void setLed_t(char _led_t);
	void setMode(int _mode);
};
#endif 
