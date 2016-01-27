#pragma once
#ifndef TOOLS_H
#include "Led.h"
#include "Color.h"
#include "Cmd.h"
#include "CmdGameMode.h"
#include <aJSON.h>

namespace Tools {
	//------------------------------------LED-------------------------------------
	//模式3 (6米灯带效果)
	void mode_3_rainbowColor(Led *led, int delayTime);
	//模式5 (流星效果)
	void mode_5_starFlow(Led *led, int _highLightNum, int delayTime);
	//充能灯效（该格子按键可用）
	void mode_8_buttonIsUseful(Led *led, Color color, int delayTime);
	//流水效果
	void mode_6_waterFlow(Led *led, Color color, int startBrightness,int highLightNum,int delayTime);
	//触摸按键灯效
	void mode_13_pressButton(Led *led, Color color, int delayTime);
	//暗点旋转,darkNum 为暗点数量
	void mode_24_rotate(Led *led, Color color, int darkNum, int delayTime);
	//呼吸灯效果
	void mode_34_breath(Led *led, Color color, int delayTime, int startBrightness);
	//彩虹流动
	void mode_47_rainbowCycle(Led *led, int delayTime);
	//彩虹暗点旋转
	void mode_50_rainbowRotate(Led *led, Color color, int darkNum, int delayTime);
	//亮起渐灭
	void mode_56_lightAndoff(Led *led, Color color, int delayTime);
	//渐亮
	void mode_71_slowLightOn(Led *led, Color color, int delayTime);
	//光点从中心发散至两边再收回
	void mode_62_divergent(Led *led, Color color, int delayTime);

	//void mode_6_highLightFlow(Led *led, Color color, int _highLightNum, int delayTime);

	//------------------------------------cmd parse-------------------------------------
	void parseServerCmd(char *msg, Cmd *cmd);

	void parseMode_ChangeCmd(char *msg, CmdGameMode *cmd);
};
#endif 