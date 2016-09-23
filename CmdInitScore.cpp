#include "CmdInitScore.h"


CmdInitScore::CmdInitScore(void)
{
	scoreParseContent = nullptr;
	uploadTime = "0";
}


CmdInitScore::~CmdInitScore(void)
{
}
ScoreParseContent * CmdInitScore::getScoreParseContent()
{
	return scoreParseContent;
}
void CmdInitScore::setScoreParseContent(ScoreParseContent * _scoreParseContent)
{
	scoreParseContent = _scoreParseContent;
}

void CmdInitScore::setSize(int _size)
{
	size = _size;
}

void CmdInitScore::setUploadTime(char* _uploadTime)
{
	uploadTime = _uploadTime;
}
void CmdInitScore::setHeartBeatTime(char* _heartBeatTime)
{
	heartBeatTime = _heartBeatTime;
}
