#pragma once
#ifndef TOOLS_H
#include "Led.h"
#include "Color.h"

namespace Tools {
	//充能灯效（该格子按键可用）
	void ledEffect_buttonIsUseful(Led *led, Color color, int delayTime);
	//触摸按键灯效
	void ledEffect_pressButton(Led *led, Color color, int delayTime);
	//流水效果
	void mode_6_waterFlow(Led *led, Color color, int startBrightness,int highLightNum,int delayTime);

	void mode_3_rainbowColor(Led *led, int delayTime);
};
#endif 