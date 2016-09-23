#pragma once
#ifndef TOOLS_H
#define TOOLS_H

#include "Led.h"
#include "Color.h"
#include "CmdGameMode.h"
#include "CmdLedCtrl.h"
#include "CmdBtnCtrl.h"
#include "CmdLaserCtrl.h"
#include "CmdMp3Ctrl.h"
#include "CmdLightCtrl.h"
#include "CmdInitScore.h"
#include "LaserParseContent.h"
#include "LedParseContent.h"
#include "ScoreParseContent.h"

#include <aJSON.h>

namespace Tools {
	void llog(char * title , char * content);
	void llog(char * title , float content);
	void llog(char * title , char content);
	void llog(char * title , int content);
	//------------------------------------LED-------------------------------------
	//ģʽ1 ����
	void mode_1_normallyOn(Led *led, Color color);
	//ģʽ2 ��ɫ������delayTime��λms��100msΪ��죩����ʼ����0~255
	void mode_2_breath(Led *led, Color color, int delayTime, int startBrightness, int mode);
	//ģʽ3 ����Ч��-----Ԥ��״̬1
	void mode_3_starFlow(Led *led, int _highLightNum, int delayTime);
	//ģʽ4 �ʺ絥ɫ�仯-----Ԥ��״̬2����ɫΪ85
	void mode_4_rainbowColor(Led *led, int startColor, int delayTime);
	//ģʽ19 ��ˮ���м����ͷС��-----����Ԥ��
	void mode_19_waterFlow(Led *led, Color color, int startBrightness,int highLightNum,int delayTime);
	//ģʽ21 �ʺ�A----����A��
	void mode_21_rainbowA(Led *led, int delayTime);
	//ģʽ22 �ʺ�B----����B��
	void mode_22_rainbowB(Led *led, int delayTime);
	//ģʽ24 ����
	void mode_24_divergent(Led *led, Color color, int delayTime);
	//ģʽ25 Ƶ��  Ŀǰû��
	void mode_25_flash(Led *led, Color color, int delayTime);
	//ģʽ26 ����
	void mode_26_buttonIsUseful(Led *led, Color color, int delayTime);
	//ģʽ27 ��ȡ
	void mode_27_pressButton(Led *led, int delayTime);
	//ģʽ28 ������ת
	void mode_28_darkRotate(Led *led, Color color, int darkNum, int delayTime);
	//ģʽ43 �ʺ�����
	void mode_42_rainbowFlow(Led *led, int delayTime);
	//ģʽ45 �ʺ簵����ת
	void mode_45_rainbowDarkRotate(Led *led, int darkNum, int delayTime);
	//ģʽ48 ���ǽ�壬�������ң����߳�����
	void mode_48_FlowFromLeft(Led *led, int _highLightNum, int delayTime);
	//ģʽ49 ���ǽ�壬��������
	void mode_49_FlowFromRight(Led *led, int _highLightNum, int delayTime);

	//------------------------------------Server Cmd parse-------------------------------------
	aJsonObject* parseServerCmd(char *msg, Cmd *cmd);

	aJsonObject* parseMode_ChangeCmd(char *msg, CmdGameMode *cmd);

	aJsonObject* parseLed_CtrlCmd(char *msg, CmdLedCtrl* cmd);

	aJsonObject* parseBtn_CtrlCmd(char *msg, CmdBtnCtrl* cmd);

	aJsonObject* parseLaser_CtrlCmd(char *msg, CmdLaserCtrl* cmd);

	//void parseLaser_Rev_CtrlCmd();

	aJsonObject* parseMp3_CtrlCmd(char *msg, CmdMp3Ctrl* cmd);

	aJsonObject* parseLight_CtrlCmd(char *msg, CmdLightCtrl* cmd);

	aJsonObject* parseInit_ScoreCmd(char *msg, CmdInitScore* cmd);

	//------------------------------Arduino status update---------------------------
	bool arduinoStatusUpdate();
	//------------------------------about Server function---------------------------
	bool serverCmdDeal();
	bool modeChangeCmdDeal();
	//--------------------------------Info upload-----------------------------------
	char* returnScoreS();
	char* returnScoreA();
	char* returnScoreB();
	char* returnScoreM();
	char* confirmInitScore2Json();
	void chooseMp3(char* music , uint8_t* mp3Mode);

};
#endif 