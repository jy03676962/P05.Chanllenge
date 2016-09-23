#pragma once
#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>
#include "config.h"

class Led
{
public:
	Adafruit_NeoPixel strip;
	uint16_t length;//灯带长度（灯珠数）
	uint8_t pin;//pin脚
	uint8_t loopNum;//循环次数
	uint8_t status;//灯条当前状态，全亮or全暗orXXX
	bool isRunning;//正在跑效果
	uint8_t curLightStatus[60];//每个灯的状态
	uint32_t curLightColor[60];//每个灯的颜色
	long ledTime;//led已经开启的时间
	int delayTime;//间隔时间
	int binaryValue;//遍历值（相当于for中的i）
	float brightnessAdd;//亮度增加数值
	uint8_t highLightNum;//高光灯珠数量
	int highLightLoc;//高光灯珠的位置

	uint8_t currentMode;//当前模式
	uint8_t newMode;//从PC读取出的即将变为的新模式

	//清除Led数据
	void ledReset();
	void ledSetup();
	Led();
	Led(uint16_t Length,uint8_t pin);
	~Led(void);
};
#endif 
