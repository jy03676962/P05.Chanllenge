#pragma once
#ifndef CMDINITSCORE_H
#define CMDINITSCORE_H

#include "cmd.h"
#include "ScoreParseContent.h"
class CmdInitScore : public Cmd
{
public:

	int size;
	char* uploadTime;//Arduino ģʽ3��Ϣ�ϴ����
	char* heartBeatTime;//Arduino����ģʽ��Ϣ�ϴ����
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

