#pragma once
#ifndef TOOLS_H
#include "Led.h"
#include "Color.h"

namespace Tools {
	//���ܵ�Ч���ø��Ӱ������ã�
	void ledEffect_buttonIsUseful(Led *led, Color color, int delayTime);
	//����������Ч
	void ledEffect_pressButton(Led *led, Color color, int delayTime);
	//��ˮЧ��
	void mode_6_waterFlow(Led *led, Color color, int startBrightness,int highLightNum,int delayTime);

	void mode_3_rainbowColor(Led *led, int delayTime);
};
#endif 