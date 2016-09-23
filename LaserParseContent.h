#pragma once
#ifndef LASERPARSECONTENT_T
#define LASERPARSECONTENT_T

class LaserParseContent
{
public:

	char* laser_n;//¼¤¹â±àºÅ
	char laser_s;//¼¤¹â×´Ì¬

	LaserParseContent(void);
	~LaserParseContent(void);

	void setLaser_n(char* _laser_n);
	void setLaser_s(char _laser_s);
};
#endif 
