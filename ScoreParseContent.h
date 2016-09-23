#pragma once
#ifndef SCOREPARSECONTENT_H
#define SCOREPARSECONTENT_H

class ScoreParseContent
{
public:

	char* status;
	char* time;

	ScoreParseContent(void);
	~ScoreParseContent(void);

	void setStatus(char* _status);
	void setTime(char* _time);

};
#endif

