#pragma once
#ifndef CMDINITSCORE_H
#define CMDINITSCORE_H

#include "cmd.h"
#include "ScoreParseContent.h"
class CmdInitScore : public Cmd
{
public:

	int size;
	char* uploadTime;//Arduino 模式3信息上传间隔
	char* heartBeatTime;//Arduino其他模式信息上传间隔
	ScoreParseContent * scoreParseContent;
	ScoreParseContent * getScoreParseContent();
	void setScoreParseContent(ScoreParseContent * _scoreParseContent);
	void setSize(int _size);
	void setUploadTime(char* _uploadTime);
	void setHeartBeatTime(char* _heartBeatTime);

	CmdInitScore(void);
	~CmdInitScore(void);
};
#endif

