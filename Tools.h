#pragma once
#ifndef TOOLS_H
#define TOOLS_H

#include "Led.h"
#include "Color.h"
#include "CmdGameMode.h"
#include "CmdGameStatus.h"
#include "CmdLedCtrl.h"

#include <aJSON.h>

namespace Tools {
	//------------------------------------LED-------------------------------------
	//ģʽ3 (6�׵ƴ�Ч��)
	void mode_3_rainbowColor(Led *led, int delayTime);
	//ģʽ5 (����Ч��)
	void mode_5_starFlow(Led *led, int _highLightNum, int delayTime);
	//���ܵ�Ч���ø��Ӱ������ã�
	void mode_8_buttonIsUseful(Led *led, Color color, int delayTime);
	//��ˮЧ��
	void mode_6_waterFlow(Led *led, Color color, int startBrightness,int highLightNum,int delayTime);
	//����������Ч
	void mode_13_pressButton(Led *led, Color color, int delayTime);
	//������ת,darkNum Ϊ��������
	void mode_24_rotate(Led *led, Color color, int darkNum, int delayTime);
	//������Ч��
	void mode_34_breath(Led *led, Color color, int delayTime, int startBrightness);
	//�ʺ�����
	void mode_47_rainbowCycle(Led *led, int delayTime);
	//�ʺ簵����ת
	void mode_50_rainbowRotate(Led *led, Color color, int darkNum, int delayTime);
	//������
	void mode_56_lightAndoff(Led *led, Color color, int delayTime);
	//����
	void mode_71_slowLightOn(Led *led, Color color, int delayTime);
	//�������ķ�ɢ���������ջ�
	void mode_62_divergent(Led *led, Color color, int delayTime);

	//void mode_6_highLightFlow(Led *led, Color color, int _highLightNum, int delayTime);

	//------------------------------------Server Cmd parse-------------------------------------
	void parseServerCmd(char *msg, Cmd *cmd);

	void parseMode_ChangeCmd(char *msg, CmdGameMode *cmd);

	void parseStatus_ChangeCmd(char *msg, CmdGameStatus *cmd);

	void parseLed_CtrlCmd();

	void parseKey_CtrlCmd();

	void parseLaser_CtrlCmd();

	void parseLaser_Rev_CtrlCmd();

	void parseMp3_CtrlCmd();

	void parseLight_CtrlCmd();

	//------------------------------Arduino status update---------------------------
	bool arduinoStatusUpdate();
	//------------------------------about Server function---------------------------
	bool serverCmdDeal();
	bool modeChangeCmdDeal();
	//--------------------------------Info upload-----------------------------------
	bool buttonInfoUpload();
	bool laserRevInfoUpload();
	bool deviceInfoUpload();

};
#endif 