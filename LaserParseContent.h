#pragma once
#ifndef LASERPARSECONTENT_T
#define LASERPARSECONTENT_T

class LaserParseContent
{
public:

	char* laser_n;//������
	char laser_s;//����״̬

	LaserParseContent(void);
	~LaserParseContent(void);

	void setLaser_n(char* _laser_n);
	void setLaser_s(char _laser_s);
};
#endif 
