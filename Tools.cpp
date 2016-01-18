#include "Tools.h"


namespace Tools{

	uint32_t Wheel(byte WheelPos, Led *led) {
		WheelPos = 255 - WheelPos;
		if(WheelPos < 85) {
			return led->strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
		}
		if(WheelPos < 170) {
			WheelPos -= 85;
			return led->strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
		}
		WheelPos -= 170;
		return led->strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	}

	void ledEffect_buttonIsUseful(Led *led, Color color, int delayTime){
		led->delayTime = delayTime;
		if(led->loopNum < led->strip.numPixels()){
			if((led->binaryValue < led->strip.numPixels() - led->loopNum) && (led->ledTime % led->delayTime == 0)){
				for(uint16_t i=0; i<led->strip.numPixels(); i++) 
				{
					if(led->curLightStatus[i] == 1){
						led->strip.setPixelColor(i,color.red,color.green,color.blue);
					} else {
						led->strip.setPixelColor(i,0,0,0);
					}
				}
				led->strip.setPixelColor(led->binaryValue,color.red,color.green,color.blue);
				led->strip.show();
				led->binaryValue++;
			}
			if(led->binaryValue == (led->strip.numPixels() - led->loopNum))
			{
				led->curLightStatus[led->strip.numPixels() - led->loopNum - 1] = 1;
				led->loopNum++;
				led->binaryValue = 0;
			}
		} else if(led->loopNum == led->strip.numPixels()){
			led->strip.setPixelColor(0,color.red,color.green,color.blue);
			led->strip.show();
			led->status = 1;
			led->loopNum++;
		} else {
			for(uint16_t i=0; i<led->strip.numPixels(); i++) 
			{
				if(led->curLightStatus[i] == 1){
					led->strip.setPixelColor(i,color.red,color.green,color.blue);
				} else {
					led->strip.setPixelColor(i,0,0,0);
				}
			}
		}
	}

	void ledEffect_pressButton(Led *led, Color color, int delayTime){
		led->delayTime = delayTime;
		if(led->status == 1){
			if(led->binaryValue < led->strip.numPixels() && led->ledTime % led->delayTime == 0){
				for(uint16_t i=0; i<led->strip.numPixels(); i++) 
				{
					if(led->curLightStatus[i] == 1){
						led->strip.setPixelColor(i,color.red,color.green,color.blue);
					} else {
						led->strip.setPixelColor(i,0,0,0);
					}
				}
				led->strip.setPixelColor(led->binaryValue,0);
				led->curLightStatus[led->binaryValue] = 0;
				led->strip.show();
				led->binaryValue++;
			} else if(led->binaryValue == led->strip.numPixels()){
				led->status = 0;
				led->loopNum = 0;
				led->binaryValue = 0;
			}
		}
	}

	/**
	* 流水效果
	*/
	void mode_6_waterFlow(Led *led, Color color, int startBrightness, int highLightNum, int delayTime){
		led->delayTime = delayTime;
		//int startBrightness = 10;
		//int highLightNum = 20;// 必备参数
		int curBrightness = 0;// 必备参数
		int addBrightness = (255 - startBrightness) / (highLightNum /2);
		if(led->binaryValue < highLightNum && led->ledTime % led->delayTime == 0){
			for (int i = 0; i < led->strip.numPixels(); i++)
			{
				int loc = abs(i - led->binaryValue);
				int halfHighLightNum = loc / (highLightNum /2);
				if(halfHighLightNum % 2 == 0){
					curBrightness= 255 - (loc - halfHighLightNum * highLightNum / 2) * addBrightness;
				} else {
					curBrightness = (loc - halfHighLightNum * highLightNum / 2)* addBrightness + startBrightness;
				}
				if(color.red == 0 && color.green == 0 && color.blue == 0){
					led->strip.setPixelColor(i,0,0,0);
				} else if(color.red == 0 && color.green == 0 && color.blue != 0){
					led->strip.setPixelColor(i,0,0,curBrightness);
				} else if(color.red == 0 && color.green != 0 && color.blue == 0){
					led->strip.setPixelColor(i,0,curBrightness,0);
				} else if(color.red == 0 && color.green != 0 && color.blue != 0){
					led->strip.setPixelColor(i,0,curBrightness,curBrightness);
				} else if(color.red != 0 && color.green == 0 && color.blue == 0){
					led->strip.setPixelColor(i,curBrightness,0,0);
				} else if(color.red != 0 && color.green == 0 && color.blue != 0){
					led->strip.setPixelColor(i,curBrightness,0,curBrightness);
				} else if(color.red != 0 && color.green != 0 && color.blue == 0){
					led->strip.setPixelColor(i,curBrightness,curBrightness,0);
				} else if(color.red != 0 && color.green != 0 && color.blue != 0){
					led->strip.setPixelColor(i,curBrightness,curBrightness,curBrightness);
				}

			}
			led->strip.show();
			led->binaryValue++;
		} else if(led->binaryValue == highLightNum){
			led->binaryValue = 0;
		}
	}

	void mode_3_rainbowColor(Led *led, int delayTime){
		led->delayTime = delayTime;
		if(led->binaryValue < 256 && led->ledTime % led->delayTime == 0)
		{
			for(uint16_t i=0; i<led->strip.numPixels(); i++) {
				led->strip.setPixelColor(i, Wheel(led->binaryValue,led));
			}	
			led->binaryValue++;
			led->strip.show();
		} else if(led->binaryValue == 256){
			led->binaryValue = 0;
		}
	}

}
