#include "Tools.h"

namespace Tools{
	//--------------------------------------------system---------------------------------------------
	void llog(char * title , char * content){
		if(strcmp(DEBUG,"true") == 0){
			Serial.print("[");
			Serial.print(title);
			Serial.print("]");
			Serial.print(":");
			Serial.print(content);
			Serial.print("\n");
		}
	}

	void llog(char * title , float content){
		if(strcmp(DEBUG,"true") == 0){
			Serial.print("[");
			Serial.print(title);
			Serial.print("]");
			Serial.print(":");
			Serial.print(content);
			Serial.print("\n");
		}
	}

	void llog(char * title , char content){
		if(strcmp(DEBUG,"true") == 0){
			Serial.print("[");
			Serial.print(title);
			Serial.print("]");
			Serial.print(":");
			Serial.print(content);
			Serial.print("\n");
		}
	}

	void llog(char * title , int content){
		if(strcmp(DEBUG,"true") == 0){
			Serial.print("[");
			Serial.print(title);
			Serial.print("]");
			Serial.print(":");
			Serial.print(content);
			Serial.print("\n");
		}
	}

	int chooseSmallerColor(Color color){
		int smallColor;
		if(color.red != 0){
			smallColor = color.red;
			if(smallColor > color.green && color.green != 0){
				smallColor = color.green;
				if(smallColor > color.blue && color.blue != 0){
					smallColor = color.blue;
				}
			} else if(smallColor > color.blue && color.blue != 0){
				smallColor = color.blue;
			}
		} else if(color.green != 0){
			smallColor = color.green;
			if(smallColor > color.blue && color.blue != 0){
				smallColor = color.blue;
			}
		} else if(color.blue != 0){
			smallColor = color.blue;
		}
		return smallColor;
	}

	//--------------------------------------------led---------------------------------------------
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

	void mode_1_normallyOn(Led *led, Color color){
		if(getColor(color,led) == 0){
			led->status = 0;
		} else {
			led->status = 1;
		}
		if(getColor(color,led) != led->curLightColor[0]){
			for (uint16_t i = 0; i < led->strip.numPixels(); i++)
			{
				led->strip.setPixelColor(i, getColor(color,led));
				led->curLightColor[i] = getColor(color,led);
				led->curLightStatus[i] = 1;
			}
			led->strip.show();
		}
	}

	void mode_2_breath(Led *led, Color color, int delayTime, int startBrightness, int mode){
		float d;
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		int smallColor = chooseSmallerColor(color);
		uint32_t colorNum = 0;
		if(led->currentMode != mode){
			led->ledReset();
			led->currentMode = mode;
			led->status = 0;
			float flag = (float)((smallColor - (float)startBrightness) / (float)delayTime * 2);//每单位时间需要增加的亮度
			if(flag < 1){
				flag = 1 / flag;
				//Serial.println(flag);
				led->delayTime = (int)(flag + 0.5) > (int)flag?(int)flag + 1:(int)flag;
				led->brightnessAdd = 1;
			} else {
				led->delayTime = 1;
				led->brightnessAdd = (int)(flag + 0.5) > (int)flag?(int)flag + 1:(int)flag;
			}
			led->binaryValue = startBrightness;
			led->isRunning = true;
		}
		//-----------------choose color
		if(color.red == 0 && color.green == 0 && color.blue == 0){
			colorNum = 0;
		} else if(color.red == 0 && color.green == 0 && color.blue != 0){
			colorNum = led->strip.Color(0,0,led->binaryValue);
		} else if(color.red == 0 && color.green != 0 && color.blue == 0){
			colorNum = led->strip.Color(0,led->binaryValue,0);
		} else if(color.red == 0 && color.green != 0 && color.blue != 0){
			if(color.blue > color.green){
				d = (float)color.blue / (float)color.green;
				blue = led->binaryValue * d;
				green = led->binaryValue;
				if(green <= 0){
					blue = 0;
					green = 0;
					led->status = 0;
				} else if(green >= color.green && d != 1){
					blue = color.blue;
					led->status = 1;
				}
			} else {
				d = (float)color.green / (float)color.blue;
				green = led->binaryValue * d;
				blue = led->binaryValue;
				if(blue <= 0){
					green = 0;
					blue = 0;
					led->status = 0;
				} else if(blue >= color.blue && d != 1){
					green = color.green;
					led->status = 1;
				}
			}
			colorNum = led->strip.Color(0,green,blue);
		} else if(color.red != 0 && color.green == 0 && color.blue == 0){
			colorNum = led->strip.Color(led->binaryValue,0,0);
		} else if(color.red != 0 && color.green == 0 && color.blue != 0){
			if(color.red > color.blue){
				d = (float)color.red / (float)color.blue;
				red = led->binaryValue * d;
				blue = led->binaryValue;
				if(blue <= 0){
					red = 0;
					blue = 0;
					led->status = 0;
				} else if(blue >= color.blue){
					red = color.red;
					led->status = 1;
				}
			} else {
				d = (float)color.blue / (float)color.red;
				blue = led->binaryValue * d;
				red = led->binaryValue;
				if(red <= 0){
					blue = 0;
					red = 0;
					led->status = 0;
				} else if(red >= color.red){
					blue = color.blue;
					led->status = 1;
				}
			}
			colorNum = led->strip.Color(led->binaryValue,0,led->binaryValue);
		} else if(color.red != 0 && color.green != 0 && color.blue == 0){
			if(color.red > color.green){
				d = (float)color.red / (float)color.green;
				red = led->binaryValue * d;
				green = led->binaryValue;
				if(green <= 0){
					red = 0;
					green = 0;
					led->status = 0;
				} else if(green >= color.green){
					red = color.red;
					led->status = 1;
				}
			} else {
				d = (float)color.green / (float)color.red;
				green = led->binaryValue * d;
				red = led->binaryValue;
				if(red <= 0){
					green = 0;
					red = 0;
					led->status = 0;
				} else if(red >= color.red){
					green = color.green;
					led->status = 1;
				}
			}
			colorNum = led->strip.Color(red,green,0);
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
			led->binaryValue += led->brightnessAdd;
			if(led->binaryValue >= 255){
				led->status = 1;
				led->binaryValue = 255;
				return;
			}
		} else if(led->status == 1 && led->ledTime % led->delayTime == 0){
			for(uint16_t i=0; i<led->strip.numPixels(); i++) {
				led->strip.setPixelColor(i,colorNum);
				led->curLightColor[i] = colorNum;
				led->curLightStatus[i] = 1;
			}
			led->strip.show();
			led->binaryValue -= led->brightnessAdd;
			if(led->binaryValue <= 0){
				led->status = 0;	
				led->binaryValue = 0;
				return;
			}
		}
	}

	void mode_3_starFlow(Led *led, int _highLightNum, int delayTime){
		if(led->currentMode != 3){
			led->ledReset();
			led->highLightNum = _highLightNum;
			led->highLightLoc = led->strip.numPixels() - 1;
			led->currentMode = 3;
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

	void mode_4_rainbowColor(Led *led, int startColor, int delayTime){
		if(led->currentMode != 4){
			led->ledReset();
			led->currentMode = 4;
			led->delayTime = delayTime;
			led->isRunning = true;
			led->status = 1;
			led->binaryValue = startColor;
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

	void mode_19_waterFlow(Led *led, Color color, int startBrightness,int highLightNum,int delayTime){
		float d;
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		int smallColor = chooseSmallerColor(color);
		uint32_t colorNum = 0;
		if(led->currentMode != 19){
			led->ledReset();
			led->currentMode = 19;
			led->delayTime = delayTime;
			led->isRunning = true;
			led->status = 1;
		}
		int curBrightness = 0;// 必备参数
		//int addBrightness = (255 - startBrightness) / (highLightNum /2);
		int addBrightness = (smallColor - startBrightness) / (highLightNum /2);
		if(led->binaryValue < highLightNum && led->ledTime % led->delayTime == 0){
			for (int i = 0; i < led->strip.numPixels(); i++)
			{
				int loc = abs(i - led->binaryValue);
				int halfHighLightNum = loc / (highLightNum /2);
				if(halfHighLightNum % 2 == 0){
					//curBrightness= 255 - (loc - halfHighLightNum * highLightNum / 2) * addBrightness;
					curBrightness= smallColor - (loc - halfHighLightNum * highLightNum / 2) * addBrightness;
				} else {
					curBrightness = (loc - halfHighLightNum * highLightNum / 2)* addBrightness + startBrightness;
				}
				if(color.red == 0 && color.green == 0 && color.blue == 0){
					colorNum = 0;
				} else if(color.red == 0 && color.green == 0 && color.blue != 0){
					colorNum = led->strip.Color(0,0,curBrightness);
				} else if(color.red == 0 && color.green != 0 && color.blue == 0){
					colorNum = led->strip.Color(0,curBrightness,0);
				} else if(color.red == 0 && color.green != 0 && color.blue != 0){
					if(color.blue > color.green){
						d = (float)color.blue / (float)color.green;
						blue = curBrightness * d;
						green = curBrightness;
						if(blue > 255){
							blue = 255;
						}
					} else {
						d = (float)color.green / (float)color.blue;
						green = curBrightness * d;
						blue = curBrightness;
						if(green > 255){
							green = 255;
						}
					}
					colorNum = led->strip.Color(0,green,blue);
				} else if(color.red != 0 && color.green == 0 && color.blue == 0){
					colorNum = led->strip.Color(curBrightness,0,0);
				} else if(color.red != 0 && color.green == 0 && color.blue != 0){
					if(color.red > color.blue){
						d = (float)color.red / (float)color.blue;
						red = curBrightness * d;
						blue = curBrightness;
						if(red > 255){
							red = 255;
						}
					} else {
						d = (float)color.blue / (float)color.red;
						blue = curBrightness * d;
						red = curBrightness;
						if(blue > 255){
							blue = 255;
						}
					}
					colorNum = led->strip.Color(red,0,blue);
				} else if(color.red != 0 && color.green != 0 && color.blue == 0){
					if(color.red > color.green){
						d = (float)color.red / (float)color.green;
						red = curBrightness * d;
						green = curBrightness;
						if(red > 255){
							red = 255;
						}
					} else {
						d = (float)color.green / (float)color.red;
						green = curBrightness * d;
						red = curBrightness;
						if(green > 255){
							green = 255;
						}
					}
					colorNum = led->strip.Color(red,green,0);
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

	void mode_21_rainbowA(Led *led, int delayTime){
		if(led->currentMode != 21){
			led->ledReset();
			led->currentMode = 21;
			led->delayTime = delayTime;
			led->status = 1;
			led->isRunning = true;
		} 
		if((led->binaryValue < 256 * 5) && led->ledTime % led->delayTime == 0)
		{
			for(uint16_t i=0; i< led->strip.numPixels(); i++) {
				led->strip.setPixelColor(i, Wheel((i * 256 / led->strip.numPixels() / 2 + led->binaryValue) & 255, led));
				led->curLightStatus[i] = 1;
				led->curLightColor[i] = Wheel((i * 256 / led->strip.numPixels() / 2 + led->binaryValue) & 255, led);
			}
			led->strip.show();
			led->binaryValue++;
		} else if((led->binaryValue == 256 * 5) && led->ledTime % led->delayTime == 0){
			led->binaryValue = 0;
		}
	}

	void mode_22_rainbowB(Led *led, int delayTime){
		if(led->currentMode != 22){
			led->ledReset();
			led->currentMode = 22;
			led->delayTime = delayTime;
			led->status = 1;
			led->isRunning = true;
		} 
		if((led->binaryValue < 256 * 5) && led->ledTime % led->delayTime == 0)
		{
			for(uint16_t i=0; i< led->strip.numPixels(); i++) {
				led->strip.setPixelColor(i, Wheel(((i + led->strip.numPixels()) * 256 / led->strip.numPixels() / 2 + led->binaryValue) & 255, led));
				led->curLightStatus[i] = 1;
				led->curLightColor[i] = Wheel(((i + led->strip.numPixels()) * 256 / led->strip.numPixels() / 2 + led->binaryValue) & 255, led);
			}
			led->strip.show();
			led->binaryValue++;
		} else if((led->binaryValue == 256 * 5) && led->ledTime % led->delayTime == 0){
			led->binaryValue = 0;
		}
	}

	void mode_24_divergent(Led *led, Color color, int delayTime){
		if(led->currentMode != 24){
			led->ledReset();
			led->currentMode = 24;
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
			led->curLightColor[loc1-1] = colorNum;
			led->curLightStatus[loc1-1] = 1;
			led->curLightColor[loc2] = colorNum;
			led->curLightStatus[loc2] = 1;
			led->curLightColor[loc2+1] = colorNum;
			led->curLightStatus[loc2+1] = 1;
			for (int i = 0; i < led->length; i++)
			{
				led->strip.setPixelColor(i,led->curLightColor[i]);
			}
			led->strip.show();
			led->binaryValue+=2;
			if(led->binaryValue >= led->loopNum){
				led->status = 1;
				led->binaryValue--;
			}
		} else if(led->status == 1 && led->ledTime % led->delayTime == 0){
			led->curLightColor[loc1] = 0;
			led->curLightStatus[loc1] = 0;
			led->curLightColor[loc1-1] = 0;
			led->curLightStatus[loc1-1] = 0;
			led->curLightColor[loc2] = 0;
			led->curLightStatus[loc2] = 0;
			led->curLightColor[loc2+1] = 0;
			led->curLightStatus[loc2+1] = 0;
			for (int i = 0; i < led->length; i++)
			{
				led->strip.setPixelColor(i,led->curLightColor[i]);
			}
			led->strip.show();
			led->binaryValue-=2;
			if(led->binaryValue < 0){
				led->status = 0;	
				led->binaryValue++;
			}
		}
	}

	void mode_25_flash(Led *led, Color color, int delayTime){
		if(led->currentMode != 25){
			led->ledReset();
			led->currentMode = 25;
			led->delayTime = delayTime;
			led->isRunning = true;
			led->status = 0;
		}
		if(led->status == 0 && (led->ledTime % led->delayTime == 0)){
			for (uint16_t i = 0; i < led->strip.numPixels(); i++)
			{
				led->strip.setPixelColor(i,getColor(color,led));
				led->curLightColor[i] = getColor(color,led);
				led->curLightStatus[i] = 1;
			}
			led->strip.show();
			led->status = 1;
		} else if(led->status == 1 && (led->ledTime % led->delayTime == 0)){
			for (uint16_t i = 0; i < led->strip.numPixels(); i++)
			{
				led->strip.setPixelColor(i,0);
				led->curLightColor[i] = 0;
				led->curLightStatus[i] = 0;
			}
			led->strip.show();
			led->status = 0;
		}
	}

	void mode_26_buttonIsUseful(Led *led, Color color, int delayTime){
		if(led->currentMode != 26){
			led->ledReset();
			led->currentMode = 26;
			led->delayTime = delayTime;
			led->isRunning = true;
			led->binaryValue = led->strip.numPixels() - 1;
		} 
		if(led->loopNum < led->strip.numPixels() && (led->ledTime % led->delayTime == 0)){
			for(uint16_t i=0; i < led->strip.numPixels(); i++) 
			{
				if(led->curLightStatus[i] == 1){
					led->strip.setPixelColor(i,led->curLightColor[i]);
				} else {
					led->strip.setPixelColor(i,0);
				}
			}
			led->strip.show();
			if((led->binaryValue == led->loopNum)){
				led->curLightStatus[led->loopNum] = 1;
				led->curLightColor[led->loopNum] = getColor(color,led);
				led->binaryValue = led->strip.numPixels() - 1;
				led->loopNum++;
			} else {
				led->strip.setPixelColor(led->binaryValue,getColor(color,led));
				led->curLightColor[led->binaryValue] = getColor(color,led);
				led->strip.show();
				led->binaryValue--;
			}
		} else if(led->loopNum == led->strip.numPixels()){
			led->status = 1;
			led->isRunning = false;
			for(uint16_t i=0; i < led->strip.numPixels(); i++) 
			{
				if(led->curLightStatus[i] == 1){
					led->strip.setPixelColor(i,led->curLightColor[i]);
				} else {
					led->strip.setPixelColor(i,0);
				}
			}
			led->strip.show();
		}
	}

	void mode_27_pressButton(Led *led, int delayTime){
		if(led->currentMode != 27){
			led->currentMode = 27;
			led->delayTime = delayTime;
			if(led->delayTime <= 0){
				led->delayTime = 1;
			}
			led->isRunning = true;
			led->binaryValue = led->strip.numPixels() - 1;
			//Serial.println(led->delayTime);
		}
		if(led->status == 1){
			if(led->binaryValue >= 0 && led->ledTime % led->delayTime == 0){
				for(uint16_t i = 0; i < led->strip.numPixels(); i++) 
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
				led->binaryValue--;
			} else if(led->binaryValue < 0){
				led->status = 0;
				led->loopNum = 0;
				led->binaryValue = 0;
			}
		}
	}

	void mode_28_darkRotate(Led *led, Color color, int darkNum, int delayTime){
		if(led->currentMode != 28){
			led->ledReset();
			led->currentMode = 28;
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
				led->strip.setPixelColor(led->binaryValue + space * i + 1,0);
				led->curLightColor[led->binaryValue + space * i + 1] = 0;
				led->curLightStatus[led->binaryValue + space * i + 1] = 0;
			}	
			led->binaryValue++;
			led->strip.show();
		} else if(led->binaryValue == space){
			led->binaryValue = 0;
		}
	}

	void mode_42_rainbowFlow(Led *led, int delayTime){
		if(led->currentMode != 42){
			led->ledReset();
			led->currentMode = 42;
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

	void mode_45_rainbowDarkRotate(Led *led, int darkNum, int delayTime){
		if(led->currentMode != 45){
			led->ledReset();
			led->currentMode = 45;
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
					led->strip.setPixelColor(led->binaryValue + space * i + 1,0);
					led->curLightColor[led->binaryValue + space * i + 1] = 0;
					led->curLightStatus[led->binaryValue + space * i + 1] = 0;
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

	void mode_48_FlowFromLeft(Led *led, int _highLightNum, int delayTime){
		if(led->currentMode != 48){
			led->ledReset();
			led->highLightNum = _highLightNum;
			led->highLightLoc = _highLightNum - 1;
			led->currentMode = 48;
			led->delayTime = delayTime;
			led->isRunning = true;
			led->status = 1;
		} 
		int startColor = 0;
		int color = startColor;
		for(uint16_t i=0; i<led->strip.numPixels(); i++) {
			led->strip.setPixelColor(i, led->strip.Color(25,25,25));
			led->curLightColor[i] = led->strip.Color(25,25,25);
			led->curLightStatus[i] = 1;
		}
		if((led->highLightLoc < led->strip.numPixels()) && (led->ledTime % led->delayTime == 0) && (led->highLightLoc > led->highLightNum - 2)){
			for (int i = 0; i < led->highLightNum; i++)
			{
				color =  255 - (255-startColor)/(led->highLightNum) * i;
				led->strip.setPixelColor(led->highLightLoc - i, led->strip.Color(color,color,color));
				led->curLightColor[i] = led->strip.Color(color,color,color);
				led->curLightStatus[i] = 1;
			}
			led->strip.show();
		} else if(led->ledTime % led->delayTime == 0){
			for (int i = 0; i < led->highLightLoc + 1; i++)
			{
				color =  255 - (255-startColor)/(led->highLightNum) * i;
				led->strip.setPixelColor(led->highLightLoc - i, led->strip.Color(color,color,color));
				led->curLightColor[i] = led->strip.Color(color,color,color);
				led->curLightStatus[i] = 1;
			}
			for (int i = 0; i < led->highLightNum - (led->highLightLoc + 1); i++)
			{
				color =  255 - (255-startColor)/(led->highLightNum) * (i + 1);
				led->strip.setPixelColor(led->strip.numPixels() - i, led->strip.Color(color,color,color));
				led->curLightColor[i] = led->strip.Color(color,color,color);
				led->curLightStatus[i] = 1;
			}
			led->strip.show();
		}
		if(led->highLightLoc == led->strip.numPixels() - 1){
			led->highLightLoc = 0;
		} else if(led->ledTime % led->delayTime == 0){
			led->highLightLoc++;
		}

	}

	void mode_49_FlowFromRight(Led *led, int _highLightNum, int delayTime){
		if(led->currentMode != 49){
			led->ledReset();
			led->highLightNum = _highLightNum;
			led->highLightLoc = led->strip.numPixels() - 1;
			led->currentMode = 49;
			led->delayTime = delayTime;
			led->isRunning = true;
		} 
		int startColor = 0;
		int color = startColor;
		for(uint16_t i=0; i<led->strip.numPixels(); i++) {
			led->strip.setPixelColor(i, led->strip.Color(25,25,25));
			led->curLightColor[i] = led->strip.Color(25,25,25);
			led->curLightStatus[i] = 1;
		}
		if(led->highLightLoc - led->highLightNum  <= - 2 && led->ledTime % led->delayTime == 0){
			for (int i = 0; i < led->highLightLoc + 1; i++)
			{
				color =  color + (255-startColor)/(led->highLightNum);
				led->strip.setPixelColor(led->highLightLoc - i, led->strip.Color(color,color,color));
				led->curLightColor[i] = led->strip.Color(color,color,color);
				led->curLightStatus[i] = 1;
			}
			for (int i = 0; i < led->highLightNum - (led->highLightLoc + 1); i++)
			{
				color =  color + (255-startColor)/(led->highLightNum);
				led->strip.setPixelColor(led->strip.numPixels() - i, led->strip.Color(color,color,color));
				led->curLightColor[i] = led->strip.Color(color,color,color);
				led->curLightStatus[i] = 1;
			}
			led->strip.show();
		} else if(led->ledTime % led->delayTime == 0){
			for (int i = 0; i < led->highLightNum; i++)
			{
				color =  color + (255-startColor)/(led->highLightNum);
				led->strip.setPixelColor(led->highLightLoc - i, led->strip.Color(color,color,color));
				led->curLightColor[i] = led->strip.Color(color,color,color);
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

	//--------------------------------------------parse---------------------------------------------
	aJsonObject* parseServerCmd(char *msg, Cmd* cmd){
		//Serial.println(msg);
		aJsonObject* root = aJson.parse(msg);
		if(root != NULL){
			aJsonObject* cmdType = aJson.getObjectItem(root,"cmd");
			cmd->setCmd(cmdType->valuestring,msg);
			cmd->isDeal = false;
			cmd->isNew = true;
		} else {
			aJson.deleteItem(root);
			root = NULL;
		}
		return root;
	}

	aJsonObject* parseMode_ChangeCmd(char *msg, CmdGameMode* cmd){
		aJsonObject* root = aJson.parse(msg);
		if(root != NULL){
			aJsonObject *mode = aJson.getObjectItem(root,"mode");
			cmd->gameMode = mode->valuestring[0];
		} else {
			aJson.deleteItem(root);
			root = NULL;
		}
		return root;
	}

	aJsonObject* parseLed_CtrlCmd(char *msg, CmdLedCtrl* cmd){
		aJsonObject* root = aJson.parse(msg);
		if(root != NULL){
			aJsonObject *ledArray = aJson.getObjectItem(root,"led");
			int size = aJson.getArraySize(ledArray);
			LedParseContent* content = (LedParseContent *)malloc(sizeof(LedParseContent)*size);
			aJsonObject *led = ledArray->child;
			for (int i = 0; i < size; i++)
			{
				content[i].setWall(aJson.getObjectItem(led,"wall")->valuestring);
				content[i].setLed_t(aJson.getObjectItem(led,"led_t")->valuestring[0]);
				content[i].setMode(atoi(aJson.getObjectItem(led,"mode")->valuestring));
				led = led->next;
			}
			//	aJson.deleteItem(root);
			cmd->setLedParseContent(content);
			cmd->setSize(size);
		} else {
			aJson.deleteItem(root);
			root = NULL;
			cmd->setLedParseContent(NULL);
			cmd->setSize(0);
			return NULL;	
		}
		return root;
	}

	aJsonObject* parseBtn_CtrlCmd(char *msg, CmdBtnCtrl* cmd){
		aJsonObject* root = aJson.parse(msg);
		if(root != NULL){
			aJsonObject *useful = aJson.getObjectItem(root,"useful");
			aJsonObject *mode = aJson.getObjectItem(root,"mode");
			aJsonObject *stage = aJson.getObjectItem(root,"stage");
			cmd->useful = useful->valuestring[0];
			cmd->mode = mode->valuestring[0];
			cmd->stage = stage->valuestring[0];
		} else {
			aJson.deleteItem(root);
			root = NULL;
		}
		return root;
	}

	aJsonObject* parseLaser_CtrlCmd(char *msg, CmdLaserCtrl* cmd){
		aJsonObject* root = aJson.parse(msg);
		if(root != NULL){
			aJsonObject *laserArray = aJson.getObjectItem(root,"laser");
			int size = aJson.getArraySize(laserArray);
			LaserParseContent* content = (LaserParseContent *)malloc(sizeof(LaserParseContent)*size);
			aJsonObject *laser = laserArray->child;
			for (int i = 0; i < size; i++)
			{
				content[i].setLaser_n(aJson.getObjectItem(laser,"laser_n")->valuestring);
				content[i].setLaser_s(aJson.getObjectItem(laser,"laser_s")->valuestring[0]);
				laser = laser->next;
			}
			//aJson.deleteItem(root);
			cmd->setLaserParseContent(content);
			cmd->setSize(size);
		} else {
			aJson.deleteItem(root);
			root = NULL;
			cmd->setLaserParseContent(NULL);
			cmd->setSize(0);
		}
		return root;
	}

	aJsonObject* parseMp3_CtrlCmd(char *msg, CmdMp3Ctrl* cmd){
		aJsonObject* root = aJson.parse(msg);
		if(root != NULL){
			aJsonObject *mp3 = aJson.getObjectItem(root,"music");
			cmd->music = mp3->valuestring;
		} else {
			aJson.deleteItem(root);
			root = NULL;
		}
		return root;
	}

	aJsonObject* parseLight_CtrlCmd(char *msg, CmdLightCtrl* cmd){
		aJsonObject* root = aJson.parse(msg);
		if(root != NULL){
			aJsonObject *lightMode = aJson.getObjectItem(root,"light_mode");
			cmd->light_mode = lightMode->valuestring[0];
		} else {
			aJson.deleteItem(root);
			root = NULL;
		}
		return root;
	}

	aJsonObject* parseInit_ScoreCmd(char *msg, CmdInitScore* cmd){
		aJsonObject* root = aJson.parse(msg);
		if(root != NULL){
			aJsonObject *scoreArray = aJson.getObjectItem(root,"score");
			aJsonObject *uploadTime = aJson.getObjectItem(root,"upload_time");
			aJsonObject *heartBeatTime = aJson.getObjectItem(root,"heartbeat_time");
			int size = aJson.getArraySize(scoreArray);
			ScoreParseContent* content = (ScoreParseContent *)malloc(sizeof(ScoreParseContent)*size);
			aJsonObject *score = scoreArray->child;
			for (int i = 0; i < size; i++)
			{
				content[i].setStatus(aJson.getObjectItem(score,"status")->valuestring);
				content[i].setTime(aJson.getObjectItem(score,"time")->valuestring);
				score = score->next;
			}
			//aJson.deleteItem(root);
			cmd->setScoreParseContent(content);
			cmd->setSize(size);
			cmd->setUploadTime(uploadTime->valuestring);
			cmd->setHeartBeatTime(heartBeatTime->valuestring);
		} else {
			aJson.deleteItem(root);
			root = NULL;	
			cmd->setScoreParseContent(NULL);
			cmd->setSize(0);
		}
		return root;
	}

	//--------------------------------------------upload---------------------------------------------
	char* returnScoreS(){
		char *msg = "{\"cmd\":\"upload_score\",\"score\":\"S\"}";
		return msg;
	}

	char* returnScoreA(){
		char *msg = "{\"cmd\":\"upload_score\",\"score\":\"A\"}";
		return msg;
	}

	char* returnScoreB(){
		char *msg = "{\"cmd\":\"upload_score\",\"score\":\"B\"}";
		return msg;
	}

	char* returnScoreM(){
		char *msg = "{\"cmd\":\"upload_score\",\"score\":\"M\"}";
		return msg;
	}

	/*char* revInfo2Json(char laserRevStatus[]){   已废除，频繁分配内存，不科学
	char *msg;
	aJsonObject* root = aJson.createObject();
	if(root != NULL){
	aJson.addStringToObject(root,"cmd",UPLOAD_REV);
	aJsonObject* rev_array = aJson.createArray();
	if(rev_array != NULL){
	for (int i = 1; i < REV_NUM + 1; i++)
	{
	aJsonObject* rev = aJson.createObject();
	aJson.addNumberToObject(rev,"rev_n",i);
	aJson.addNumberToObject(rev,"rev_s",laserRevStatus[i]);
	aJson.addItemToArray(rev_array, rev);
	}
	}
	aJson.addItemToObject(root,"rev",rev_array);
	}
	msg = aJson.print(root);
	aJson.deleteItem(root);
	root = NULL;
	return msg;
	}*/



	char* confirmInitScore2Json(){
		char *msg = "{\"cmd\":\"confirm_init_score\"}";
		return msg;
	}

	void chooseMp3(char* music , uint8_t* mp3Mode){
		if(strcmp(music,"0") == 0){
			mp3Mode[0] = 0;
			mp3Mode[1] = 0;
			mp3Mode[2] = 0;
			mp3Mode[3] = 0;
		} else if(strcmp(music,"1") == 0){
			mp3Mode[0] = 0;
			mp3Mode[1] = 0;
			mp3Mode[2] = 0;
			mp3Mode[3] = 1;
		} else if(strcmp(music,"2") == 0){
			mp3Mode[0] = 0;
			mp3Mode[1] = 0;
			mp3Mode[2] = 1;
			mp3Mode[3] = 0;
		} else if(strcmp(music,"3") == 0){
			mp3Mode[0] = 0;
			mp3Mode[1] = 0;
			mp3Mode[2] = 1;
			mp3Mode[3] = 1;
		} else if(strcmp(music,"4") == 0){
			mp3Mode[0] = 0;
			mp3Mode[1] = 1;
			mp3Mode[2] = 0;
			mp3Mode[3] = 0;
		} else if(strcmp(music,"5") == 0){
			mp3Mode[0] = 0;
			mp3Mode[1] = 1;
			mp3Mode[2] = 0;
			mp3Mode[3] = 1;
		} else if(strcmp(music,"6") == 0){
			mp3Mode[0] = 0;
			mp3Mode[1] = 1;
			mp3Mode[2] = 1;
			mp3Mode[3] = 0;
		} else if(strcmp(music,"7") == 0){
			mp3Mode[0] = 0;
			mp3Mode[1] = 1;
			mp3Mode[2] = 1;
			mp3Mode[3] = 1;
		} else if(strcmp(music,"8") == 0){
			mp3Mode[0] = 1;
			mp3Mode[1] = 0;
			mp3Mode[2] = 0;
			mp3Mode[3] = 0;
		} else if(strcmp(music,"9") == 0){
			mp3Mode[0] = 1;
			mp3Mode[1] = 0;
			mp3Mode[2] = 0;
			mp3Mode[3] = 1;
		} else if(strcmp(music,"10") == 0){
			mp3Mode[0] = 1;
			mp3Mode[1] = 0;
			mp3Mode[2] = 1;
			mp3Mode[3] = 0;
		} else if(strcmp(music,"11") == 0){
			mp3Mode[0] = 1;
			mp3Mode[1] = 0;
			mp3Mode[2] = 1;
			mp3Mode[3] = 1;
		} else if(strcmp(music,"12") == 0){
			mp3Mode[0] = 1;
			mp3Mode[1] = 1;
			mp3Mode[2] = 0;
			mp3Mode[3] = 0;
		} else if(strcmp(music,"13") == 0){
			mp3Mode[0] = 1;
			mp3Mode[1] = 1;
			mp3Mode[2] = 0;
			mp3Mode[3] = 1;
		} else if(strcmp(music,"14") == 0){
			mp3Mode[0] = 1;
			mp3Mode[1] = 1;
			mp3Mode[2] = 1;
			mp3Mode[3] = 0;
		} else if(strcmp(music,"15") == 0){
			mp3Mode[0] = 1;
			mp3Mode[1] = 1;
			mp3Mode[2] = 1;
			mp3Mode[3] = 1;
		}
	}

}
