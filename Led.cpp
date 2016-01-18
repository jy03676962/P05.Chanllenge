#include "Led.h"

Led::Led(int _length,int _pin)
{
	strip = Adafruit_NeoPixel(_length, _pin, NEO_GRB + NEO_KHZ800);
	length = _length;
	pin = _pin;
}


Led::~Led(void)
{
	String cell_num; // 所属格子编号
	char wall_num;// 所属墙面编号
	int led_type;//灯带类型，照明灯带、按键灯带...
	int led_num;//灯带编号
	int currentMode;//当前模式
	int newMode;//从PC读取出的即将变为的新模式
}

void Led::ledSetup(String _cellNum,char _wallNum,int _ledType,int _ledNum){
	memset(curLightStatus,0,255);
	loopNum = 0;
	status = 0;
	ledTime = 0;
	delayTime = 50;
	binaryValue = 0;
	isRunning = false;
	strip.begin();
	for (int i = 0; i < length; i++)
	{
		strip.setPixelColor(i,0);
	}
	strip.show();
	cell_num = _cellNum;
	wall_num = _wallNum;
	led_type = _ledType;
	led_num = _ledNum;
	currentMode = -1;
	newMode = -1;


}

