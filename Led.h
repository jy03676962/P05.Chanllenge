#pragma once
#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>
#include "config.h"

class Led
{
public:
	Adafruit_NeoPixel strip;
	int length;//灯带长度（灯珠数）
	int pin;//pin脚
	int loopNum;//循环次数
	int status;//灯条当前状态，全亮or全暗orXXX
	bool isRunning;//正在跑效果
	int curLightStatus[255];//每个灯的状态
	uint32_t curLightColor[255];//每个灯的颜色
	long ledTime;//led已经开启的时间
	long delayTime;//间隔时间
	int binaryValue;//遍历值（相当于for中的i）
	float brightnessAdd;//亮度增加数值
	int highLightNum;//高光灯珠数量
	int highLightLoc;//高光灯珠的位置

	String cell_num; // 所属格子编号
	char wall_num;// 所属墙面编号
	int led_type;//灯带类型，照明灯带、按键灯带...
	int led_num;//灯带编号
	int currentMode;//当前模式
	int newMode;//从PC读取出的即将变为的新模式

	/**
	@params
	_cellNum 格子编号
	_wallNum 墙体编号
	_ledType Led类型，按键Led or 墙体照明Led
	_ledNum Led编号
	*/
	void ledSetup(String _cellNum, char _wallNum, int _ledType, int _ledNum);
	//清除Led数据
	void ledReset();
	Led();
	Led(int Length,int pin);
	~Led(void);
};
#endif 
