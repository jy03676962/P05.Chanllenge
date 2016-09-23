#include "ScoreParseContent.h"


ScoreParseContent::ScoreParseContent(void)
{
	status = "";
	time = "0";
}


ScoreParseContent::~ScoreParseContent(void)
{
}
void ScoreParseContent::setStatus(char* _status)
{
	status = _status;
}
void ScoreParseContent::setTime(char* _time)
{
	time = _time;
}