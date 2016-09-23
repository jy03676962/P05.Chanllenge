#pragma once
#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>
#include "config.h"

class Led
{
public:
	Adafruit_NeoPixel strip;
	uint16_t length;//�ƴ����ȣ���������
	uint8_t pin;//pin��
	uint8_t loopNum;//ѭ������
	uint8_t status;//������ǰ״̬��ȫ��orȫ��orXXX
	bool isRunning;//������Ч��
	uint8_t curLightStatus[60];//ÿ���Ƶ�״̬
	uint32_t curLightColor[60];//ÿ���Ƶ���ɫ
	long ledTime;//led�Ѿ�������ʱ��
	int delayTime;//���ʱ��
	int binaryValue;//����ֵ���൱��for�е�i��
	float brightnessAdd;//����������ֵ
	uint8_t highLightNum;//�߹��������
	int highLightLoc;//�߹�����λ��

	uint8_t currentMode;//��ǰģʽ
	uint8_t newMode;//��PC��ȡ���ļ�����Ϊ����ģʽ

	//���Led����
	void ledReset();
	void ledSetup();
	Led();
	Led(uint16_t Length,uint8_t pin);
	~Led(void);
};
#endif 
