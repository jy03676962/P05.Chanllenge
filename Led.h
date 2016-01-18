#pragma once
#include <Adafruit_NeoPixel.h>
#include "config.h"

class Led
{
public:
	Adafruit_NeoPixel strip;
	int length;//�ƴ����ȣ���������
	int pin;//pin��
	int loopNum;//ѭ������
	int status;//������ǰ״̬��ȫ��orȫ��orXXX
	bool isRunning;//������Ч��
	int curLightStatus[255];//ÿ���Ƶ�״̬
	long ledTime;//led�Ѿ�������ʱ��
	long delayTime;//���ʱ��
	int binaryValue;//����ֵ���൱��for�е�i��

	String cell_num; // �������ӱ��
	char wall_num;// ����ǽ����
	int led_type;//�ƴ����ͣ������ƴ��������ƴ�...
	int led_num;//�ƴ����
	int currentMode;//��ǰģʽ
	int newMode;//��PC��ȡ���ļ�����Ϊ����ģʽ

	/**
		@params
			_cellNum ���ӱ��
			_wallNum ǽ����
			_ledType Led���ͣ�����Led or ǽ������Led
			_ledNum Led���
	*/
	void ledSetup(String _cellNum, char _wallNum, int _ledType, int _ledNum);
	Led(int Length,int pin);
	~Led(void);
};
