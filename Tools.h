#pragma once
#ifndef TOOLS_H
#include "Led.h"
#include "Color.h"
#include "Cmd.h"
#include "CmdGameMode.h"
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

	//------------------------------------cmd parse-------------------------------------
	void parseServerCmd(char *msg, Cmd *cmd);

	void parseMode_ChangeCmd(char *msg, CmdGameMode *cmd);
};
#endif 