#include "Led.h"

Led::Led(void)
{

}

Led::Led(uint16_t _length,uint8_t _pin)
{
	strip = Adafruit_NeoPixel(_length, _pin, NEO_GRB + NEO_KHZ800);
	length = _length;
	pin = _pin;
}

Led::~Led(void)
{

}

void Led::ledSetup(){
	memset(curLightStatus,0,60);
	memset(curLightColor,0,60);
	loopNum = 0;
	status = 0;
	ledTime = 0;
	delayTime = 0;
	binaryValue = 0;
	isRunning = false;
	brightnessAdd = 0.0f;
	highLightNum = 0;
	highLightLoc = 0;

	strip.begin();
	for (int i = 0; i < length; i++)
	{
		strip.setPixelColor(i,0);
	}
	strip.show();
	currentMode = -1;
	newMode = -1;
}

void Led::ledReset(){
	memset(curLightStatus,0,60);
	memset(curLightColor,0,60);
	loopNum = 0;
	status = 0;
	ledTime = 0;
	delayTime = 0;
	binaryValue = 0;
	brightnessAdd = 0.0f;
	highLightNum = 0;
	highLightLoc = 0;
	isRunning = false;

	for (int i = 0; i < length; i++)
	{
		strip.setPixelColor(i,0);
	}
	strip.show();
	currentMode = -1;
	newMode = -1;
}

