#include "Led.h"

Led::Led(int _length,int _pin)
{
	strip = Adafruit_NeoPixel(_length, _pin, NEO_GRB + NEO_KHZ800);
	length = _length;
	pin = _pin;
}


Led::~Led(void)
{
	String cell_num; // �������ӱ��
	char wall_num;// ����ǽ����
	int led_type;//�ƴ����ͣ������ƴ��������ƴ�...
	int led_num;//�ƴ����
	int currentMode;//��ǰģʽ
	int newMode;//��PC��ȡ���ļ�����Ϊ����ģʽ
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

