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

	uint32_t getColor(Color color, Led *led){
		return led->strip.Color(color.red,color.green,color.blue);
	}

	void mode_3_rainbowColor(Led *led, int delayTime){
		if(led->currentMode != 3){
			led->ledReset();
			led->currentMode = 3;
			led->delayTime = delayTime;
			led->isRunning = true;
			led->status = 1;
		} 
		if(led->binaryValue < 256 && led->ledTime % led->delayTime == 0)
		{
			for(uint16_t i=0; i<led->strip.numPixels(); i++) {
				led->strip.setPixelColor(i, Wheel(led->binaryValue,led));
				led->curLightColor[i] = Wheel(led->binaryValue,led);
				led->curLightStatus[i] = 1;
			}
			led->binaryValue++;
			led->strip.show();
		} else if(led->binaryValue == 256){
			led->binaryValue = 0;
		}
	}

	void mode_5_starFlow(Led *led,int _highLightNum, int delayTime){
		if(led->currentMode != 5){
			led->ledReset();
			led->highLightNum = _highLightNum;
			led->highLightLoc = led->strip.numPixels() - 1;
			led->currentMode = 5;
			led->delayTime = delayTime;
			led->isRunning = true;
		} 
		int startColor = 0;
		int color = startColor;
		for(uint16_t i=0; i<led->strip.numPixels(); i++) {
			led->strip.setPixelColor(i, 0);
			led->curLightColor[i] = 0;
			led->curLightStatus[i] = 1;
		}
		if(led->highLightLoc - led->highLightNum  <= - 2 && led->ledTime % led->delayTime == 0){
			for (int i = 0; i < led->highLightLoc + 1; i++)
			{
				color =  color + (255-startColor)/(led->highLightNum);
				led->strip.setPixelColor(led->highLightLoc - i, led->strip.Color(0,color,0));
				led->curLightColor[i] = led->strip.Color(0,color,0);
				led->curLightStatus[i] = 1;
			}
			for (int i = 0; i < led->highLightNum - (led->highLightLoc + 1); i++)
			{
				color =  color + (255-startColor)/(led->highLightNum);
				led->strip.setPixelColor(led->strip.numPixels() - i, led->strip.Color(0,color,0));
				led->curLightColor[i] = led->strip.Color(0,color,0);
				led->curLightStatus[i] = 1;
			}
			led->strip.show();
		} else if(led->ledTime % led->delayTime == 0){
			for (int i = 0; i < led->highLightNum; i++)
			{
				color =  color + (255-startColor)/(led->highLightNum);
				led->strip.setPixelColor(led->highLightLoc - i, led->strip.Color(0,color,0));
				led->curLightColor[i] = led->strip.Color(0,color,0);
				led->curLightStatus[i] = 1;
			}
			led->strip.show();
		}

		if(led->highLightLoc == 0){
			led->highLightLoc = led->strip.numPixels() - 1;
		} else if(led->ledTime % led->delayTime == 0){
			led->highLightLoc--;
		}
	}

	void mode_6_waterFlow(Led *led, Color color, int startBrightness, int highLightNum, int delayTime){
		if(led->currentMode != 6){
			led->ledReset();
			led->currentMode = 6;
			led->delayTime = delayTime;
			led->isRunning = true;
			led->status = 1;
		}
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
				uint32_t colorNum = 0;
				if(color.red == 0 && color.green == 0 && color.blue == 0){
					colorNum = 0;
				} else if(color.red == 0 && color.green == 0 && color.blue != 0){
					colorNum = led->strip.Color(0,0,curBrightness);
				} else if(color.red == 0 && color.green != 0 && color.blue == 0){
					colorNum = led->strip.Color(0,curBrightness,0);
				} else if(color.red == 0 && color.green != 0 && color.blue != 0){
					colorNum = led->strip.Color(0,curBrightness,curBrightness);
				} else if(color.red != 0 && color.green == 0 && color.blue == 0){
					colorNum = led->strip.Color(curBrightness,0,0);
				} else if(color.red != 0 && color.green == 0 && color.blue != 0){
					colorNum = led->strip.Color(curBrightness,0,curBrightness);
				} else if(color.red != 0 && color.green != 0 && color.blue == 0){
					colorNum = led->strip.Color(curBrightness,curBrightness,0);
				} else if(color.red != 0 && color.green != 0 && color.blue != 0){
					colorNum = led->strip.Color(curBrightness,curBrightness,curBrightness);
				}
				led->strip.setPixelColor(i,colorNum);
				led->curLightColor[i] = colorNum;
				led->curLightStatus[i] = 1;
			}
			led->strip.show();
			led->binaryValue++;
		} else if(led->binaryValue == highLightNum){
			led->binaryValue = 0;
		}
	}

	void mode_6_highLightFlow(Led *led,Color color, int _highLightNum, int delayTime){
		if(led->currentMode != 6){
			led->ledReset();
			led->highLightNum = _highLightNum;
			led->highLightLoc = led->strip.numPixels() - 1;
			led->currentMode = 6;
			led->delayTime = delayTime;
			led->isRunning = true;
			led->status = 1;
		} 
		for(uint16_t i=0; i<led->strip.numPixels(); i++) {
			led->strip.setPixelColor(i, led->strip.Color(0,25,25));
			led->curLightColor[i] = led->strip.Color(0,25,25);
			led->curLightStatus[i] = 1;
		}
		if(led->highLightLoc - led->highLightNum  <= - 2 && led->ledTime % led->delayTime == 0){
			for (int i = 0; i < led->highLightLoc + 1; i++)
			{
				led->strip.setPixelColor(led->highLightLoc - i, getColor(color,led));
				led->curLightColor[i] = getColor(color,led);
				led->curLightStatus[i] = 1;
			}
			for (int i = 0; i < led->highLightNum - (led->highLightLoc + 1); i++)
			{
				led->strip.setPixelColor(led->strip.numPixels() - i, getColor(color,led));
				led->curLightColor[i] = getColor(color,led);
				led->curLightStatus[i] = 1;
			}
			led->strip.show();
		} else if(led->ledTime % led->delayTime == 0){
			for (int i = 0; i < led->highLightNum; i++)
			{
				led->strip.setPixelColor(led->highLightLoc - i, getColor(color,led));
				led->curLightColor[i] = getColor(color,led);
				led->curLightStatus[i] = 1;
			}
			led->strip.show();
		}
		if(led->highLightLoc == 0 ){
			led->highLightLoc = led->strip.numPixels() - 1;
		} else if(led->ledTime % led->delayTime == 0){
			led->highLightLoc--;
		}
	}

	void mode_8_buttonIsUseful(Led *led, Color color, int delayTime){
		if(led->currentMode != 8){
			led->ledReset();
			led->currentMode = 8;
			led->delayTime = delayTime;
			led->isRunning = true;
		} 
		if(led->loopNum < led->strip.numPixels()){
			if((led->binaryValue < led->strip.numPixels() - led->loopNum) && (led->ledTime % led->delayTime == 0)){
				for(uint16_t i=0; i<led->strip.numPixels(); i++) 
				{
					if(led->curLightStatus[i] == 1){
						led->strip.setPixelColor(i,getColor(color,led));
						led->curLightColor[i] = getColor(color,led);
					} else {
						led->strip.setPixelColor(i,0);
						led->curLightColor[i] = 0;
					}
				}
				led->strip.setPixelColor(led->binaryValue,getColor(color,led));
				led->curLightColor[led->binaryValue] = getColor(color,led);
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
			led->strip.setPixelColor(0,getColor(color,led));
			led->curLightColor[0] = getColor(color,led);
			led->strip.show();
			led->status = 1;
			led->loopNum++;
		} else {
			for(uint16_t i=0; i<led->strip.numPixels(); i++) 
			{
				if(led->curLightStatus[i] == 1){
					led->strip.setPixelColor(i,getColor(color,led));
					led->curLightColor[i] = getColor(color,led);
				} else {
					led->strip.setPixelColor(i,0);
					led->curLightColor[i] = 0;
				}
			}
		}
	}

	void mode_13_pressButton(Led *led, Color color, int delayTime){
		if(led->currentMode != 13 && led->currentMode != 8){
			led->currentMode = 13;
			led->delayTime = delayTime;
			led->isRunning = true;
			led->binaryValue = 0;
		} else if(led->currentMode == 8){
			led->currentMode = 13;
			led->delayTime = delayTime;
			led->isRunning = true;
			led->binaryValue = 0;
		}
		if(led->status == 1){
			if(led->binaryValue < led->strip.numPixels() && led->ledTime % led->delayTime == 0){
				for(uint16_t i=0; i<led->strip.numPixels(); i++) 
				{
					if(led->curLightStatus[i] == 1){
						led->strip.setPixelColor(i,led->curLightColor[i]);
					} else {
						led->strip.setPixelColor(i,0);
					}
				}
				led->strip.setPixelColor(led->binaryValue,0);
				led->curLightColor[led->binaryValue] = 0;
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

	void mode_24_rotate(Led *led, Color color, int darkNum, int delayTime){
		if(led->currentMode != 24){
			led->ledReset();
			led->currentMode = 24;
			led->isRunning = true;
			led->delayTime = delayTime;
			led->status = 1;
		}
		uint32_t colorNum = 0;
		colorNum = getColor(color,led);
		for (int i = 0; i < led->strip.numPixels(); i++)
		{
			led->strip.setPixelColor(i,colorNum);
			led->curLightColor[i] = colorNum;
			led->curLightStatus[i] = 1;
		}
		int space = led->strip.numPixels() / darkNum;
		if(led->binaryValue < space && led->ledTime % led->delayTime == 0){
			for (int i = 0; i < darkNum; i++)
			{
				led->strip.setPixelColor(led->binaryValue + space * i,0);
				led->curLightColor[led->binaryValue + space * i] = 0;
				led->curLightStatus[led->binaryValue + space * i] = 0;
			}	
			led->binaryValue++;
			led->strip.show();
		} else if(led->binaryValue == space){
			led->binaryValue = 0;
		}
	}

	void mode_34_breath(Led *led, Color color, int delayTime, int startBrightness){
		if(led->currentMode != 34){
			led->ledReset();
			led->currentMode = 34;
			led->status = 0;
			led->binaryValue = startBrightness;
			led->isRunning = true;
			led->brightnessAdd = (float)((255 - (float)startBrightness) / (float)delayTime * 2);
			led->delayTime = 1 / led->brightnessAdd;
		}
		//-----------------choose color
		uint32_t colorNum = 0;
		if(color.red == 0 && color.green == 0 && color.blue == 0){
			colorNum = 0;
		} else if(color.red == 0 && color.green == 0 && color.blue != 0){
			colorNum = led->strip.Color(0,0,led->binaryValue);
		} else if(color.red == 0 && color.green != 0 && color.blue == 0){
			colorNum = led->strip.Color(0,led->binaryValue,0);
		} else if(color.red == 0 && color.green != 0 && color.blue != 0){
			colorNum = led->strip.Color(0,led->binaryValue,led->binaryValue);
		} else if(color.red != 0 && color.green == 0 && color.blue == 0){
			colorNum = led->strip.Color(led->binaryValue,0,0);
		} else if(color.red != 0 && color.green == 0 && color.blue != 0){
			colorNum = led->strip.Color(led->binaryValue,0,led->binaryValue);
		} else if(color.red != 0 && color.green != 0 && color.blue == 0){
			colorNum = led->strip.Color(led->binaryValue,led->binaryValue,0);
		} else if(color.red != 0 && color.green != 0 && color.blue != 0){
			colorNum = led->strip.Color(led->binaryValue,led->binaryValue,led->binaryValue);
		}
		//----------------logic
		if(led->status == 0 && led->ledTime % led->delayTime == 0){
			for(uint16_t i=0; i<led->strip.numPixels(); i++) {
				led->strip.setPixelColor(i,colorNum);
				led->curLightColor[i] = colorNum;
				led->curLightStatus[i] = 1;
			}
			led->strip.show();
			led->binaryValue++;
			if(led->binaryValue >= 255){
				led->status = 1;
				led->binaryValue = 255;
			}
		} else if(led->status == 1 && led->ledTime % led->delayTime == 0){
			for(uint16_t i=0; i<led->strip.numPixels(); i++) {
				led->strip.setPixelColor(i,colorNum);
				led->curLightColor[i] = colorNum;
				led->curLightStatus[i] = 1;
			}
			led->strip.show();
			led->binaryValue--;
			if(led->binaryValue <= 0){
				led->status = 0;	
				led->binaryValue = 0;
			}
		}
	}

	void mode_47_rainbowCycle(Led *led, int delayTime) {
		if(led->currentMode != 47){
			led->ledReset();
			led->currentMode = 47;
			led->delayTime = delayTime;
			led->status = 1;
			led->isRunning = true;
		} 
		if((led->binaryValue < 256 * 5) && led->ledTime % led->delayTime == 0)
		{
			for(uint16_t i=0; i< led->strip.numPixels(); i++) {
				led->strip.setPixelColor(i, Wheel((i * 256 / led->strip.numPixels() + led->binaryValue) & 255, led));
				led->curLightStatus[i] = 1;
				led->curLightColor[i] = Wheel((i * 256 / led->strip.numPixels() + led->binaryValue) & 255, led);
			}
			led->strip.show();
			led->binaryValue++;
		} else if((led->binaryValue == 256 * 5) && led->ledTime % led->delayTime == 0){
			led->binaryValue = 0;
		}
	}

	void mode_50_rainbowRotate(Led *led, Color color, int darkNum, int delayTime) {
		if(led->currentMode != 50){
			led->ledReset();
			led->currentMode = 50;
			led->delayTime = delayTime;
			led->status = 1;
			led->isRunning = true;
		} 
		int space = led->strip.numPixels() / darkNum;
		if((led->loopNum < 256 * 5) && led->ledTime % led->delayTime == 0)
		{
			for(uint16_t i=0; i< led->strip.numPixels(); i++) {
				led->strip.setPixelColor(i, Wheel((i * 256 / led->strip.numPixels() + led->loopNum) & 255, led));
				led->curLightStatus[i] = 1;
				led->curLightColor[i] = Wheel((i * 256 / led->strip.numPixels() + led->loopNum) & 255, led);
			}
			if(led->binaryValue < space){
				for (int i = 0; i < darkNum; i++)
				{
					led->strip.setPixelColor(led->binaryValue + space * i,0);
					led->curLightColor[led->binaryValue + space * i] = 0;
					led->curLightStatus[led->binaryValue + space * i] = 0;
				}	
				led->binaryValue++;
			} else if(led->binaryValue == space){
				led->binaryValue = 0;
			}
			led->strip.show();
			led->loopNum++;
		} else if(led->loopNum == 256 * 5){
			led->loopNum = 0;
		}
	}

	void mode_56_lightAndoff(Led *led, Color color, int delayTime){
		if(led->currentMode != 56){
			led->ledReset();
			led->currentMode = 56;
			led->delayTime = delayTime;
			led->status = 1;
			led->isRunning = true;
		} 
		int red = color.red -led->binaryValue;
		if(red <= 0){
			red = 0;
		}
		int green = color.green -led->binaryValue;
		if(green <= 0){
			green = 0;
		}
		int blue = color.blue -led->binaryValue;
		if(blue <= 0){
			blue = 0;
		}
		uint32_t colorNum = led->strip.Color(red,green,blue);
		for (int i = 0; i < led->strip.numPixels(); i++)
		{
			led->strip.setPixelColor(i,colorNum);
			led->curLightColor[i] = colorNum;
			led->curLightStatus[i] = 1;
		}
		led->strip.show();
		if(0 == red && 0 == green && 0 == blue){
			return;
		}
		if(led->ledTime % led->delayTime == 0){
			led->binaryValue++;
		}
	}

	void mode_71_slowLightOn(Led *led, Color color, int delayTime){
		if(led->currentMode != 71){
			led->ledReset();
			led->currentMode = 71;
			led->brightnessAdd = 5;
			led->delayTime = delayTime;
			led->status = 1;
			led->isRunning = true;
		} 
		int red = led->binaryValue;
		if(color.red == 0){
			red = 0;
		}
		int green = led->binaryValue;
		if(color.green == 0){
			green = 0;
		}
		int blue = led->binaryValue;
		if(color.blue == 0){
			blue = 0;
		}
		uint32_t colorNum = led->strip.Color(red,green,blue);
		for (int i = 0; i < led->strip.numPixels(); i++)
		{
			led->strip.setPixelColor(i,colorNum);
			led->curLightColor[i] = colorNum;
			led->curLightStatus[i] = 1;
		}
		led->strip.show();
		if(led->binaryValue >= 255){
			led->binaryValue = 255;
			Serial.println("OK");
			return;
		}
		if(led->ledTime % led->delayTime == 0){
			led->binaryValue+=led->brightnessAdd;
		}
	}

	void mode_62_divergent(Led *led, Color color, int delayTime){
		if(led->currentMode != 62){
			led->ledReset();
			led->currentMode = 62;
			led->delayTime = delayTime;
			led->status = 0;
			led->isRunning = true;
			if(led->length % 2 == 0){
				led->loopNum = led->length / 2;
			} else {
				led->loopNum = (led->length + 1) / 2;
			}
		}
		uint32_t colorNum = getColor(color,led);
		int loc1 = led->length / 2 - 1 - led->binaryValue;
		if(loc1 < 0 ){
			loc1 = 0;
		}
		int loc2 = led->length / 2 + led->binaryValue;
		if(led->status == 0 && led->ledTime % led->delayTime == 0){
			led->curLightColor[loc1] = colorNum;
			led->curLightStatus[loc1] = 1;
			led->curLightColor[loc2] = colorNum;
			led->curLightStatus[loc2] = 1;
			for (int i = 0; i < led->length; i++)
			{
				led->strip.setPixelColor(i,led->curLightColor[i]);
			}
			led->strip.show();
			led->binaryValue++;
			if(led->binaryValue >= led->loopNum){
				led->status = 1;
				led->binaryValue--;
			}
		} else if(led->status == 1 && led->ledTime % led->delayTime == 0){
			led->curLightColor[loc1] = 0;
			led->curLightStatus[loc1] = 0;
			led->curLightColor[loc2] = 0;
			led->curLightStatus[loc2] = 0;
			for (int i = 0; i < led->length; i++)
			{
				led->strip.setPixelColor(i,led->curLightColor[i]);
			}
			led->strip.show();
			led->binaryValue--;
			if(led->binaryValue < 0){
				led->status = 0;	
				led->binaryValue++;
			}
		}
	}


	void parseServerCmd(char *msg, Cmd *cmd){
		aJsonObject *root = aJson.parse(msg);
		if(root != NULL){
			aJsonObject *cmdType = aJson.getObjectItem(root,"cmd");
			cmd->setCmd(cmdType->valuestring,msg);
			Serial.println(cmdType->valuestring);
			cmd->isDeal = false;
			cmd->isNew = true;
		}
	}

	void parseMode_ChangeCmd(char *msg, CmdGameMode *cmd){
		aJsonObject *root = aJson.parse(msg);
		if(root != NULL){
			aJsonObject *mode = aJson.getObjectItem(root,"mode");
			cmd->gameMode = mode->valuestring[0];
		}
	}
}
