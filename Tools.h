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
	//模式1 常亮
	void mode_1_normallyOn(Led *led, Color color);
	//模式2 绿色呼吸，delayTime单位ms（100ms为最快），起始亮度0~255
	void mode_2_breath(Led *led, Color color, int delayTime, int startBrightness, int mode);
	//模式3 流星效果-----预热状态1
	void mode_3_starFlow(Led *led, int _highLightNum, int delayTime);
	//模式4 彩虹单色变化-----预热状态2，绿色为85
	void mode_4_rainbowColor(Led *led, int startColor, int delayTime);
	//模式19 流水（中间大，两头小）-----暴走预热
	void mode_19_waterFlow(Led *led, Color color, int startBrightness,int highLightNum,int delayTime);
	//模式21 彩虹A----暴走A段
	void mode_21_rainbowA(Led *led, int delayTime);
	//模式22 彩虹B----暴走B段
	void mode_22_rainbowB(Led *led, int delayTime);
	//模式24 收缩
	void mode_24_divergent(Led *led, Color color, int delayTime);
	//模式25 频闪  目前没有
	void mode_25_flash(Led *led, Color color, int delayTime);
	//模式26 充能
	void mode_26_buttonIsUseful(Led *led, Color color, int delayTime);
	//模式27 读取
	void mode_27_pressButton(Led *led, int delayTime);
	//模式28 暗点旋转
	void mode_28_darkRotate(Led *led, Color color, int darkNum, int delayTime);
	//模式43 彩虹流动
	void mode_42_rainbowFlow(Led *led, int delayTime);
	//模式45 彩虹暗点旋转
	void mode_45_rainbowDarkRotate(Led *led, int darkNum, int delayTime);
	//模式48 面对墙体，从左向右（从线出发）
	void mode_48_FlowFromLeft(Led *led, int _highLightNum, int delayTime);
	//模式49 面对墙体，从右向左
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