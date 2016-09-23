#include "Tools.h"
#include <Adafruit_NeoPixel.h>
#include <aJSON.h>
#include <Ethernet.h>
#include <SPI.h>
#include <SoftwareSerial.h>
using namespace Tools;

//------------------------------NET-----------------------------------src------------
#if defined(WIZ550io_WITH_MACADDRESS) // Use assigned MAC address of WIZ550io
;
#else
byte myMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
#endif 
IPAddress myIp A_IP;
IPAddress serverIp (192, 168, 1, 5);
int myPort = 4000;
EthernetClient client;  
String Arduino_ID = A_ID;
//--------------------LED---------------
Led m_led1(60,M_WALL_LED_1);//上1
Led m_led4(60,M_WALL_LED_4);//下1
Led m_led2(60,M_WALL_LED_2);//上2
Led m_led3(60,M_WALL_LED_3);//下2
Led m_led6(50,M_WALL_LED_6);//按键灯带左
Led m_led7(50,M_WALL_LED_7);//按键灯带右
Led m_led5(22,M_WALL_LED_5);//按键周边灯带

Led o1_led1(10,S_WALL_LED_1);
Led o1_led2(10,S_WALL_LED_2);
Led o1_led3(10,S_WALL_LED_3);
Led o1_led4(10,S_WALL_LED_4);
//---------------------CMD---------------
Cmd cmd;
CmdGameMode cmdGameMode;
CmdLedCtrl cmdLedCtrl;
CmdBtnCtrl cmdBtnCtrl;
CmdLaserCtrl cmdLaserCtrl;
CmdMp3Ctrl cmdMp3Ctrl;
CmdLightCtrl cmdLightCtrl;
CmdInitScore cmdInitScore;

aJsonObject* cmdRoot;
aJsonObject* root;

//data cmd处理完，放入data，释放cmd
uint8_t isUseful;
uint8_t btnMode;
uint8_t btnStage;

int ledMode_M[3];
int ledMode_O[3];


#if (S_REV_NUM > 0 || M_REV_NUM >0)
int laserRevStatus[S_REV_NUM + M_REV_NUM];
#else
int laserRevStatus[1];
#endif


uint8_t laserGun[LASER_NUM];
uint8_t mp3Mode[4];
uint8_t indicatorMode[2];
float score[4];//0为S，1为A，2为B，3为 暴走状态下读条
int currentMusic;//当前音乐

long uploadFrame = 0;//上传帧数
int uploadTime = 0;//上传间隔
int heartBeatTime = 0;//其他模式下的心跳间隔
int touchLaserFrame = 0;//触发激光后产生音效后的计算帧数
bool isConnected = false;//是否连接服务器
bool glodMusicDone =false;

//--------------------functions declare---------------
void initGame();
void parseCmd();
void gameMode();
void frameAdd();
void powerOffMode();
void powerOnMode();
void cleanMode();
void freeMode();

void btnDeal();
void Mp3Deal();
void scoreDeal();
void laserDeal();
void LaserRevDeal();
void M1LedDeal();
void M2LedDeal();
void M3LedDeal();
void lightDeal();
void uploadRevStatus();
//---------------------parse functions----------------
void ledParse();
void btnParse();
void laserParse();
void mp3Parse();
void lightParse();
void scoreParse();

//-------------tools fuctions-------------
char * clientConnect();
char * readPage();
void upload(char * msg);

int checkSize = 1024;
void checkFreeMem()
{
	for(int i = checkSize;i>0;i--)
	{
		char* c = (char*)malloc(i);
		if(c)
		{
			free(c);
			c=NULL;
			//Serial.print("Mem left:");
			//Serial.println(i);
			break;
		}
	}
}

void setup() {
#if defined(WIZ550io_WITH_MACADDRESS)
	Ethernet.begin(myIp);
#else
	Ethernet.begin(myMac, myIp);
#endif
	Serial.begin(9600);
	initGame();
	for (int i = 0; i < LASER_NUM; i++) // 激光发射器
	{
		pinMode(M_WALL_LASER_GUN_1 - i,OUTPUT); 
	}

	for (int i = 0; i < M_REV_NUM; i++) // 主墙激光接收器
	{
		pinMode(M_WALL_LASER_REV_1 - i,INPUT);
	}

	for (int i = 0; i < S_REV_NUM; i++) // 小墙激光接收器
	{
		pinMode(S_WALL_LASER_REV_1 - i,INPUT);
	}

	pinMode(M_WALL_TOUCH_MODE, INPUT);//触摸
	pinMode(M_WALL_INDICATOR_LIGHT_LEFT_PIN1, OUTPUT); //指示灯左Pin1
	pinMode(M_WALL_INDICATOR_LIGHT_LEFT_PIN2, OUTPUT); //指示灯左Pin2
	pinMode(M_WALL_INDICATOR_LIGHT_RIGHT_PIN1, OUTPUT); //指示灯右Pin1
	pinMode(M_WALL_INDICATOR_LIGHT_RIGHT_PIN2, OUTPUT); //指示灯右Pin2

	pinMode(M_WALL_MP3_PIN1, OUTPUT);//MP3控制Pin1~4
	pinMode(M_WALL_MP3_PIN2, OUTPUT); 
	pinMode(M_WALL_MP3_PIN3, OUTPUT); 
	pinMode(M_WALL_MP3_PIN4, OUTPUT); 
	delay(MILLISECOND);
}

//连接->判断连接->读取服务器信息->命令解析->switch 命令-> 实现命令
void loop() {
	//checkFreeMem();
	long startTime = millis();
	char *a = clientConnect();
	parseCmd();
	gameMode();
	frameAdd();
	heartBeats();
	long stop = millis();
	delay(MILLISECOND);
} 

char * readPage(){
	char inString[1024];
	int stringPos = 0;
	bool startRead = false;
	//read the page, and capture & return everything between '<' and '>'
	memset( &inString, 0, sizeof(inString) ); //clear inString memory
	if (client.available()) {
		while(true){
			char c = client.read();
			if (c == '<' ) { //'<' is our begining character
				startRead = true; //Ready to start reading the part 
			}else if(startRead){
				if(c != '>'){ //'>' is our ending character
					inString[stringPos] = c;
					stringPos ++;
				}else{
					//got what we need here! We can disconnect now
					//startRead = false;
					//stringPos = 0;
					client.flush();
					cmdRoot = parseServerCmd(inString,&cmd);
					return inString;
				}
			}
		}
	}
}
void upload(char * msg){
	if(client != NULL){
		client.print("<");
		client.print(msg);
		client.print(">");
	}
}

void(* resetFunc) (void) = 0; //制造重启命令
int falseConnectNum = 1;

char* clientConnect(){
	if(!client.connected()) {
		client.stop();
		if(client.connect(serverIp,myPort)){
			//client.print("<Hello,server,I'm comming!>");	
			llog("Connect Server","success!");
			client.print("<");
			client.print("[ID]");
			client.print(Arduino_ID);
			client.print(">");
			isConnected = true;
		} else {
			llog("Connect Server","failed!");
			isConnected = false;
			falseConnectNum++;
			if(falseConnectNum > 3){
				resetFunc();
			}
			//	Serial.println(falseConnectNum);
		}
	} else {
		char *c = readPage();
		return c;
	}
}

void initGame(){
	cmd.isNew = false;
	cmd.isDeal = true;
	isUseful = 0;
	btnMode = 0;
	btnStage = 0;
	memset(ledMode_M,0,sizeof(int)*3);
	memset(ledMode_O,0,sizeof(int)*3);
	if((S_REV_NUM + M_REV_NUM)  > 0){
		memset(laserRevStatus,0,sizeof(int)*(S_REV_NUM + M_REV_NUM));
	}
	memset(laserGun,0,sizeof(int)*LASER_NUM);
	memset(mp3Mode,0,sizeof(uint8_t)*4);
	memset(indicatorMode,0,sizeof(uint8_t)*2);
	memset(score,0,sizeof(float)*4);

	//cmdGameMode.gameMode = '1';//小茹 激光全开

	m_led1.ledSetup();
	m_led2.ledSetup();
	m_led3.ledSetup();
	m_led4.ledSetup();
	m_led5.ledSetup();
	m_led6.ledSetup();
	m_led7.ledSetup();

	o1_led1.ledSetup();
	o1_led2.ledSetup();
	o1_led3.ledSetup();
	o1_led4.ledSetup();

	uploadFrame = 0;
	uploadTime = 0;
	heartBeatTime = 0;
	touchLaserFrame = 1;
	currentMusic = 0;
	isConnected = false;
	glodMusicDone = false;
}

void parseCmd(){
	if(!cmd.isDeal && cmd.isNew){
		cmd.isDeal = true;
		cmd.isNew = false;
		if(strcmp(cmd.cmdType,MODE_CHANGE) == 0){
			root = parseMode_ChangeCmd(cmd.cmdContent, &cmdGameMode);
			if(cmdGameMode.gameMode == '3'){ // 当Mode为3的时候自动进入待机模式
				for (int i = 0; i < 3; i++)
				{
					ledMode_M[i] = 2;
				}
				for (int i = 0; i < 3; i++)
				{
					ledMode_O[i] = 2;
				}
				isUseful  = 2;//将btn状态设置为2，即服务器可以调整M2,M3灯带的状态
			}
		} else if(strcmp(cmd.cmdType,LED_CTRL) == 0){
			root = parseLed_CtrlCmd(cmd.cmdContent, &cmdLedCtrl);
			ledParse();
		} else if(strcmp(cmd.cmdType,BTN_CTRL) == 0){
			root = parseBtn_CtrlCmd(cmd.cmdContent,&cmdBtnCtrl);
			memset(mp3Mode,0,sizeof(mp3Mode));
			Mp3Deal();
			btnParse();
		} else if(strcmp(cmd.cmdType,LASER_CTRL) == 0){
			root = parseLaser_CtrlCmd(cmd.cmdContent,&cmdLaserCtrl);
			laserParse();
		} else if(strcmp(cmd.cmdType,LASER_REV_CTRL) == 0){

		} else if(strcmp(cmd.cmdType,MP3_CTRL) == 0){
			root = parseMp3_CtrlCmd(cmd.cmdContent,&cmdMp3Ctrl);
			memset(mp3Mode,0,sizeof(mp3Mode));
			Mp3Deal();
			mp3Parse();
		} else if(strcmp(cmd.cmdType,LIGHT_CTRL) == 0){
			root = parseLight_CtrlCmd(cmd.cmdContent,&cmdLightCtrl);
			lightParse();
		} else if(strcmp(cmd.cmdType,INIT_SCORE) == 0){
			root = parseInit_ScoreCmd(cmd.cmdContent,&cmdInitScore);
			scoreParse();
			upload(confirmInitScore2Json());
		}
		if(root != NULL){
			aJson.deleteItem(root);
			root = NULL;
		}
		if(cmdRoot != NULL){
			aJson.deleteItem(cmdRoot);
			cmdRoot = NULL;
		}
	}
}

void heartBeats(){
	if(cmdGameMode.gameMode == '3'){//自由
		if(uploadTime == 0){
			if(uploadFrame % UPLOAD_TIME == 0 && ledMode_M[0] != 0){
				uploadRevStatus();
			} else if(ledMode_M[0] == 0 && uploadFrame % (UPLOAD_TIME * 10) == 0){
				uploadRevStatus();
			}
		} else {
			if(uploadFrame % uploadTime == 0){
				uploadRevStatus();
			} 
		}
	} else {
		if(heartBeatTime == 0){
			if(uploadFrame % HEARTBEATS == 0){
				uploadRevStatus();			
			}
		} else {
			if(uploadFrame % heartBeatTime == 0){
				uploadRevStatus();
			}
		}
	}
}

void gameMode(){
	if(isConnected){
		if(cmdGameMode.gameMode == '0'){// 全关
			powerOffMode();
			//llog("DealCmd","gamemode powerOffMode");
		} else if(cmdGameMode.gameMode == '1'){// 全开
			powerOnMode();
			//llog("DealCmd","gamemode powerOnMode");
		} else if(cmdGameMode.gameMode == '2'){// 清扫
			cleanMode();
			//llog("DealCmd","gamemode cleanMode");
		} else if(cmdGameMode.gameMode == '3'){//自由
			freeMode();
			//llog("DealCmd","gamemode freeMode");
		}
	} else {
		powerOffMode();
	}
}

void powerOffMode(){
	m_led1.ledReset();//led 清零
	m_led2.ledReset();
	m_led3.ledReset();
	m_led4.ledReset();
	m_led5.ledReset();
	m_led6.ledReset();
	m_led7.ledReset();
	o1_led1.ledReset();
	o1_led2.ledReset();
	o1_led3.ledReset();
	o1_led4.ledReset();

	memset(mp3Mode,0,sizeof(mp3Mode));
	Mp3Deal();

	memset(laserGun,0,sizeof(laserGun));
	laserDeal();

	memset(indicatorMode,1,sizeof(indicatorMode));
	lightDeal();

	isUseful = 0;
	btnMode = 0;
	btnStage = 0;
	btnDeal();

	memset(ledMode_M,0,sizeof(int)*3);
	M1LedDeal();
	M2LedDeal();
	M3LedDeal();
	memset(ledMode_O,0,sizeof(int)*3);
	O1LedDeal();
}

void powerOnMode(){
	mode_1_normallyOn(&m_led1,Color(255,255,255));
	mode_1_normallyOn(&m_led2,Color(255,255,255));
	mode_1_normallyOn(&m_led3,Color(255,255,255));
	mode_1_normallyOn(&m_led4,Color(255,255,255));
	mode_1_normallyOn(&m_led5,Color(255,255,255));
	mode_1_normallyOn(&m_led6,Color(255,255,255));
	mode_1_normallyOn(&m_led7,Color(255,255,255));

	mode_1_normallyOn(&o1_led1,Color(255,255,255));
	mode_1_normallyOn(&o1_led2,Color(255,255,255));
	mode_1_normallyOn(&o1_led3,Color(255,255,255));
	mode_1_normallyOn(&o1_led4,Color(255,255,255));

	for (int i = 0; i < LASER_NUM; i++)
	{
		digitalWrite(M_WALL_LASER_GUN_1 - i,1);
	}

	digitalWrite(M_WALL_INDICATOR_LIGHT_LEFT_PIN1,0);
	digitalWrite(M_WALL_INDICATOR_LIGHT_LEFT_PIN2,0);
	digitalWrite(M_WALL_INDICATOR_LIGHT_RIGHT_PIN1,0);
	digitalWrite(M_WALL_INDICATOR_LIGHT_RIGHT_PIN2,0);

	isUseful = 0;
	btnMode = 0;
	btnStage = 0;

	memset(ledMode_M,0,sizeof(int)*3);
	memset(ledMode_O,0,sizeof(int)*3);

	memset(laserGun,0,sizeof(laserGun));
}

void cleanMode(){
	mode_1_normallyOn(&m_led1,Color(255,255,255));
	mode_1_normallyOn(&m_led2,Color(255,255,255));
	mode_1_normallyOn(&m_led3,Color(255,255,255));
	mode_1_normallyOn(&m_led4,Color(255,255,255));

	mode_1_normallyOn(&m_led5,Color(0,0,0));
	mode_1_normallyOn(&m_led6,Color(0,0,0));
	mode_1_normallyOn(&m_led7,Color(0,0,0));

	mode_1_normallyOn(&o1_led1,Color(255,255,255));
	mode_1_normallyOn(&o1_led2,Color(255,255,255));
	mode_1_normallyOn(&o1_led3,Color(255,255,255));
	mode_1_normallyOn(&o1_led4,Color(255,255,255));

	memset(laserGun,0,sizeof(laserGun));
	laserDeal();

	isUseful = 0;
	btnMode = 0;
	btnStage = 0;
	btnDeal();

	memset(ledMode_M,0,sizeof(int)*3);
	memset(ledMode_O,0,sizeof(int)*3);
}

void freeMode(){
	btnDeal();
	scoreDeal();
	M1LedDeal();
	O1LedDeal();
	Mp3Deal();
	laserDeal();
	//LaserRevDeal();	
	lightDeal();
}

void M1LedDeal(){
	switch (ledMode_M[0])
	{
	case 2:
		mode_2_breath(&m_led1,Color(0,255,0),ALL_LED_BREATH_READY_MODE_TIME,10,ledMode_M[0]);
		mode_2_breath(&m_led4,Color(0,255,0),ALL_LED_BREATH_READY_MODE_TIME,10,ledMode_M[0]);
		mode_2_breath(&m_led2,Color(0,255,0),ALL_LED_BREATH_READY_MODE_TIME,10,ledMode_M[0]);
		mode_2_breath(&m_led3,Color(0,255,0),ALL_LED_BREATH_READY_MODE_TIME,10,ledMode_M[0]);
		break;
	case 3:
		mode_3_starFlow(&m_led1,20,M1_LED_STARTFLOW_TIME);
		mode_3_starFlow(&m_led4,20,M1_LED_STARTFLOW_TIME);
		mode_3_starFlow(&m_led2,20,M1_LED_STARTFLOW_TIME);
		mode_3_starFlow(&m_led3,20,M1_LED_STARTFLOW_TIME);
		break;
	case 4:
		mode_4_rainbowColor(&m_led1,75,ALL_LED_RAINBOW_COLOR_TIME);
		mode_4_rainbowColor(&m_led4,75,ALL_LED_RAINBOW_COLOR_TIME);
		mode_4_rainbowColor(&m_led2,75,ALL_LED_RAINBOW_COLOR_TIME);
		mode_4_rainbowColor(&m_led3,75,ALL_LED_RAINBOW_COLOR_TIME);
		break;
	case 5:
		mode_2_breath(&m_led1,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P1,10,ledMode_M[0]);
		mode_2_breath(&m_led4,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P1,10,ledMode_M[0]);
		mode_2_breath(&m_led2,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P1,10,ledMode_M[0]);
		mode_2_breath(&m_led3,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P1,10,ledMode_M[0]);
		break;
	case 6:
		mode_2_breath(&m_led1,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P2,10,ledMode_M[0]);
		mode_2_breath(&m_led4,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P2,10,ledMode_M[0]);
		mode_2_breath(&m_led2,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P2,10,ledMode_M[0]);
		mode_2_breath(&m_led3,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P2,10,ledMode_M[0]);
		break;
	case 7:
		mode_2_breath(&m_led1,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P3,10,ledMode_M[0]);
		mode_2_breath(&m_led4,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P3,10,ledMode_M[0]);
		mode_2_breath(&m_led2,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P3,10,ledMode_M[0]);
		mode_2_breath(&m_led3,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P3,10,ledMode_M[0]);
		break;
	case 8:
		mode_2_breath(&m_led1,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P4,10,ledMode_M[0]);
		mode_2_breath(&m_led4,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P4,10,ledMode_M[0]);
		mode_2_breath(&m_led2,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P4,10,ledMode_M[0]);
		mode_2_breath(&m_led3,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P4,10,ledMode_M[0]);
		break;
	case 9:
		mode_2_breath(&m_led1,Color(255,30,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P5,10,ledMode_M[0]);
		mode_2_breath(&m_led4,Color(255,30,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P5,10,ledMode_M[0]);
		mode_2_breath(&m_led2,Color(255,30,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P5,10,ledMode_M[0]);
		mode_2_breath(&m_led3,Color(255,30,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P5,10,ledMode_M[0]);
		break;
	case 12:
		mode_2_breath(&m_led1,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P1,10,ledMode_M[0]);
		mode_2_breath(&m_led4,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P1,10,ledMode_M[0]);
		mode_2_breath(&m_led2,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P1,10,ledMode_M[0]);
		mode_2_breath(&m_led3,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P1,10,ledMode_M[0]);
		break;
	case 13:
		mode_2_breath(&m_led1,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P2,10,ledMode_M[0]);
		mode_2_breath(&m_led4,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P2,10,ledMode_M[0]);
		mode_2_breath(&m_led2,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P2,10,ledMode_M[0]);
		mode_2_breath(&m_led3,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P2,10,ledMode_M[0]);
		break;
	case 14:
		mode_2_breath(&m_led1,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P3,10,ledMode_M[0]);
		mode_2_breath(&m_led4,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P3,10,ledMode_M[0]);
		mode_2_breath(&m_led2,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P3,10,ledMode_M[0]);
		mode_2_breath(&m_led3,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P3,10,ledMode_M[0]);
		break;
	case 15:
		mode_2_breath(&m_led1,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P4,10,ledMode_M[0]);
		mode_2_breath(&m_led4,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P4,10,ledMode_M[0]);
		mode_2_breath(&m_led2,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P4,10,ledMode_M[0]);
		mode_2_breath(&m_led3,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P4,10,ledMode_M[0]);
		break;
	case 16:
		mode_2_breath(&m_led1,Color(0,100,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P5,10,ledMode_M[0]);
		mode_2_breath(&m_led4,Color(0,100,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P5,10,ledMode_M[0]);
		mode_2_breath(&m_led2,Color(0,100,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P5,10,ledMode_M[0]);
		mode_2_breath(&m_led3,Color(0,100,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P5,10,ledMode_M[0]);
		break;
	case 19:
		mode_19_waterFlow(&m_led1,Color(255,30,0),5,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_TIME);
		mode_19_waterFlow(&m_led4,Color(255,30,0),5,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_TIME);
		mode_19_waterFlow(&m_led2,Color(255,30,0),5,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_TIME);
		mode_19_waterFlow(&m_led3,Color(255,30,0),5,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_TIME);
		break;
	case 21:
		mode_21_rainbowA(&m_led1,TYPE1_LED_RAMPAGE_TIME);
		mode_21_rainbowA(&m_led4,TYPE1_LED_RAMPAGE_TIME);
		mode_21_rainbowA(&m_led2,TYPE1_LED_RAMPAGE_TIME);
		mode_21_rainbowA(&m_led3,TYPE1_LED_RAMPAGE_TIME);
		break;
	case 22:
		mode_22_rainbowB(&m_led1,TYPE1_LED_RAMPAGE_TIME);
		mode_22_rainbowB(&m_led4,TYPE1_LED_RAMPAGE_TIME);
		mode_22_rainbowB(&m_led2,TYPE1_LED_RAMPAGE_TIME);
		mode_22_rainbowB(&m_led3,TYPE1_LED_RAMPAGE_TIME);
		break;
	case 20:
		mode_19_waterFlow(&m_led1,Color(0,100,255),5,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_TIME);
		mode_19_waterFlow(&m_led4,Color(0,100,255),5,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_TIME);
		mode_19_waterFlow(&m_led2,Color(0,100,255),5,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_TIME);
		mode_19_waterFlow(&m_led3,Color(0,100,255),5,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_TIME);
		break;
	case 24:
		mode_24_divergent(&m_led1,Color(0,255,0),M1_LED_LASER_ALARM_TIME);
		mode_24_divergent(&m_led4,Color(0,255,0),M1_LED_LASER_ALARM_TIME);
		mode_24_divergent(&m_led2,Color(0,255,0),M1_LED_LASER_ALARM_TIME);
		mode_24_divergent(&m_led3,Color(0,255,0),M1_LED_LASER_ALARM_TIME);
		break;
	case 25:
		mode_25_flash(&m_led1,Color(0,255,0),TYPE1_LED_TOUCH_LASER_TIME);
		mode_25_flash(&m_led4,Color(0,255,0),TYPE1_LED_TOUCH_LASER_TIME);
		mode_25_flash(&m_led2,Color(0,255,0),TYPE1_LED_TOUCH_LASER_TIME);
		mode_25_flash(&m_led3,Color(0,255,0),TYPE1_LED_TOUCH_LASER_TIME);
		break;
	case 42:
		mode_42_rainbowFlow(&m_led1,TYPE1_LED_RAMPAGE_TIME);
		mode_42_rainbowFlow(&m_led4,TYPE1_LED_RAMPAGE_TIME);
		mode_42_rainbowFlow(&m_led2,TYPE1_LED_RAMPAGE_TIME);
		mode_42_rainbowFlow(&m_led3,TYPE1_LED_RAMPAGE_TIME);
		break;
	case 47:
		mode_24_divergent(&m_led1,Color(255,0,0),M1_LED_GAME_COUNT_DOWN_TIME);
		mode_24_divergent(&m_led4,Color(255,0,0),M1_LED_GAME_COUNT_DOWN_TIME);
		mode_24_divergent(&m_led2,Color(255,0,0),M1_LED_GAME_COUNT_DOWN_TIME);
		mode_24_divergent(&m_led3,Color(255,0,0),M1_LED_GAME_COUNT_DOWN_TIME);
		break;
	case 48:
		mode_48_FlowFromLeft(&m_led1,M_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		mode_48_FlowFromLeft(&m_led4,M_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		mode_48_FlowFromLeft(&m_led2,M_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		mode_48_FlowFromLeft(&m_led3,M_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		break;
	case 49:
		mode_49_FlowFromRight(&m_led1,M_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		mode_49_FlowFromRight(&m_led4,M_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		mode_49_FlowFromRight(&m_led2,M_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		mode_49_FlowFromRight(&m_led3,M_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		break;
	default:
		mode_1_normallyOn(&m_led1,Color(0,0,0));
		mode_1_normallyOn(&m_led4,Color(0,0,0));
		mode_1_normallyOn(&m_led2,Color(0,0,0));
		mode_1_normallyOn(&m_led3,Color(0,0,0));
		break;
	}
}

void M2LedDeal(){
	switch (ledMode_M[1])
	{
	case 1:
		mode_1_normallyOn(&m_led6,Color(255,255,255));
		mode_1_normallyOn(&m_led7,Color(255,255,255));
		break;
	case 2:
		mode_2_breath(&m_led6,Color(0,255,0),ALL_LED_BREATH_READY_MODE_TIME,10,ledMode_M[2]);
		mode_2_breath(&m_led7,Color(0,255,0),ALL_LED_BREATH_READY_MODE_TIME,10,ledMode_M[2]);
		break;
	case 4:
		mode_4_rainbowColor(&m_led6,75,ALL_LED_RAINBOW_COLOR_TIME);
		mode_4_rainbowColor(&m_led7,75,ALL_LED_RAINBOW_COLOR_TIME);
		break;
	case 48:
		mode_48_FlowFromLeft(&m_led6,M_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		mode_48_FlowFromLeft(&m_led7,M_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		break;
	case 49:
		mode_49_FlowFromRight(&m_led6,M_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		mode_49_FlowFromRight(&m_led7,M_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		break;
	default:
		mode_1_normallyOn(&m_led6,Color(0,0,0));
		mode_1_normallyOn(&m_led7,Color(0,0,0));
		break;
	}
}

void M3LedDeal(){
	switch (ledMode_M[2])
	{
	case 1:
		mode_1_normallyOn(&m_led5,Color(255,255,255));
		break;
	case 2:
		mode_2_breath(&m_led5,Color(0,255,0),ALL_LED_BREATH_READY_MODE_TIME,10,ledMode_M[2]);
		break;
	case 4:
		mode_4_rainbowColor(&m_led5,75,ALL_LED_RAINBOW_COLOR_TIME);
		break;
	default:
		mode_1_normallyOn(&m_led5,Color(0,0,0));
		break;
	}
}

void O1LedDeal(){
	switch (ledMode_O[0])
	{
	case 1:
		mode_1_normallyOn(&o1_led1,Color(255,255,255));
		mode_1_normallyOn(&o1_led4,Color(255,255,255));
		mode_1_normallyOn(&o1_led3,Color(255,255,255));
		mode_1_normallyOn(&o1_led2,Color(255,255,255));
		break;
	case 2:
		mode_2_breath(&o1_led1,Color(0,255,0),ALL_LED_BREATH_READY_MODE_TIME,10,ledMode_O[0]);
		mode_2_breath(&o1_led4,Color(0,255,0),ALL_LED_BREATH_READY_MODE_TIME,10,ledMode_O[0]);
		mode_2_breath(&o1_led3,Color(0,255,0),ALL_LED_BREATH_READY_MODE_TIME,10,ledMode_O[0]);
		mode_2_breath(&o1_led2,Color(0,255,0),ALL_LED_BREATH_READY_MODE_TIME,10,ledMode_O[0]);
		break;
	case 4:
		mode_4_rainbowColor(&o1_led1,75,ALL_LED_RAINBOW_COLOR_TIME);
		mode_4_rainbowColor(&o1_led4,75,ALL_LED_RAINBOW_COLOR_TIME);
		mode_4_rainbowColor(&o1_led3,75,ALL_LED_RAINBOW_COLOR_TIME);
		mode_4_rainbowColor(&o1_led2,75,ALL_LED_RAINBOW_COLOR_TIME);
		break;
	case 5:
		mode_2_breath(&o1_led1,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P1,10,ledMode_O[0]);
		mode_2_breath(&o1_led4,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P1,10,ledMode_O[0]);
		mode_2_breath(&o1_led3,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P1,10,ledMode_O[0]);
		mode_2_breath(&o1_led2,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P1,10,ledMode_O[0]);
		break;
	case 6:
		mode_2_breath(&o1_led1,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P2,10,ledMode_O[0]);
		mode_2_breath(&o1_led4,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P2,10,ledMode_O[0]);
		mode_2_breath(&o1_led3,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P2,10,ledMode_O[0]);
		mode_2_breath(&o1_led2,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P2,10,ledMode_O[0]);
		break;
	case 7:
		mode_2_breath(&o1_led1,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P3,10,ledMode_O[0]);
		mode_2_breath(&o1_led4,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P3,10,ledMode_O[0]);
		mode_2_breath(&o1_led3,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P3,10,ledMode_O[0]);
		mode_2_breath(&o1_led2,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P3,10,ledMode_O[0]);
		break;
	case 8:
		mode_2_breath(&o1_led1,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P4,10,ledMode_O[0]);
		mode_2_breath(&o1_led4,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P4,10,ledMode_O[0]);
		mode_2_breath(&o1_led3,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P4,10,ledMode_O[0]);
		mode_2_breath(&o1_led2,Color(255,80,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P4,10,ledMode_O[0]);
		break;
	case 9:
		mode_2_breath(&o1_led1,Color(255,30,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P5,10,ledMode_O[0]);
		mode_2_breath(&o1_led4,Color(255,30,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P5,10,ledMode_O[0]);
		mode_2_breath(&o1_led3,Color(255,30,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P5,10,ledMode_O[0]);
		mode_2_breath(&o1_led2,Color(255,30,0),TYPE1_LED_GAME_GOLD_MODE_TIME_P5,10,ledMode_O[0]);
		break;
	case 12:
		mode_2_breath(&o1_led1,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P1,10,ledMode_O[0]);
		mode_2_breath(&o1_led4,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P1,10,ledMode_O[0]);
		mode_2_breath(&o1_led3,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P1,10,ledMode_O[0]);
		mode_2_breath(&o1_led2,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P1,10,ledMode_O[0]);
		break;
	case 13:
		mode_2_breath(&o1_led1,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P2,10,ledMode_O[0]);
		mode_2_breath(&o1_led4,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P2,10,ledMode_O[0]);
		mode_2_breath(&o1_led3,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P2,10,ledMode_O[0]);
		mode_2_breath(&o1_led2,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P2,10,ledMode_O[0]);
		break;
	case 14:
		mode_2_breath(&o1_led1,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P3,10,ledMode_O[0]);
		mode_2_breath(&o1_led4,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P3,10,ledMode_O[0]);
		mode_2_breath(&o1_led3,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P3,10,ledMode_O[0]);
		mode_2_breath(&o1_led2,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P3,10,ledMode_O[0]);
		break;
	case 15:
		mode_2_breath(&o1_led1,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P4,10,ledMode_O[0]);
		mode_2_breath(&o1_led4,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P4,10,ledMode_O[0]);
		mode_2_breath(&o1_led3,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P4,10,ledMode_O[0]);
		mode_2_breath(&o1_led2,Color(0,255,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P4,10,ledMode_O[0]);
		break;
	case 16:
		mode_2_breath(&o1_led1,Color(0,100,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P5,10,ledMode_O[0]);
		mode_2_breath(&o1_led4,Color(0,100,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P5,10,ledMode_O[0]);
		mode_2_breath(&o1_led3,Color(0,100,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P5,10,ledMode_O[0]);
		mode_2_breath(&o1_led2,Color(0,100,255),TYPE1_LED_GAME_SURVIVE_MODE_TIME_P5,10,ledMode_O[0]);
		break;
	case 19:
		mode_19_waterFlow(&o1_led1,Color(255,30,0),5,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_TIME);
		mode_19_waterFlow(&o1_led4,Color(255,30,0),5,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_TIME);
		mode_19_waterFlow(&o1_led3,Color(255,30,0),5,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_TIME);
		mode_19_waterFlow(&o1_led2,Color(255,30,0),5,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_TIME);
		break;
	case 20:
		mode_19_waterFlow(&o1_led1,Color(0,100,255),5,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_TIME);
		mode_19_waterFlow(&o1_led4,Color(0,100,255),5,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_TIME);
		mode_19_waterFlow(&o1_led3,Color(0,100,255),5,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_TIME);
		mode_19_waterFlow(&o1_led2,Color(0,100,255),5,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_NUM,TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_TIME);
		break;
	case 21:
		mode_21_rainbowA(&o1_led1,TYPE1_LED_RAMPAGE_TIME);
		mode_21_rainbowA(&o1_led4,TYPE1_LED_RAMPAGE_TIME);
		mode_21_rainbowA(&o1_led3,TYPE1_LED_RAMPAGE_TIME);
		mode_21_rainbowA(&o1_led2,TYPE1_LED_RAMPAGE_TIME);
		break;
	case 22:
		mode_22_rainbowB(&o1_led1,TYPE1_LED_RAMPAGE_TIME);
		mode_22_rainbowB(&o1_led4,TYPE1_LED_RAMPAGE_TIME);
		mode_22_rainbowB(&o1_led3,TYPE1_LED_RAMPAGE_TIME);
		mode_22_rainbowB(&o1_led2,TYPE1_LED_RAMPAGE_TIME);
		break;
	case 23:
		mode_1_normallyOn(&o1_led1,Color(0,255,0));
		mode_1_normallyOn(&o1_led4,Color(0,255,0));
		mode_1_normallyOn(&o1_led3,Color(0,255,0));
		mode_1_normallyOn(&o1_led2,Color(0,255,0));
		break;
	case 25:
		mode_25_flash(&o1_led1,Color(0,255,0),TYPE1_LED_TOUCH_LASER_TIME);
		mode_25_flash(&o1_led4,Color(0,255,0),TYPE1_LED_TOUCH_LASER_TIME);
		mode_25_flash(&o1_led3,Color(0,255,0),TYPE1_LED_TOUCH_LASER_TIME);
		mode_25_flash(&o1_led2,Color(0,255,0),TYPE1_LED_TOUCH_LASER_TIME);
		break;
	case 42:
		mode_42_rainbowFlow(&o1_led1,TYPE1_LED_RAMPAGE_TIME);
		mode_42_rainbowFlow(&o1_led4,TYPE1_LED_RAMPAGE_TIME);
		mode_42_rainbowFlow(&o1_led3,TYPE1_LED_RAMPAGE_TIME);
		mode_42_rainbowFlow(&o1_led2,TYPE1_LED_RAMPAGE_TIME);
		break;
	case 46:
		mode_1_normallyOn(&o1_led1,Color(255,0,0));
		mode_1_normallyOn(&o1_led4,Color(255,0,0));
		mode_1_normallyOn(&o1_led3,Color(255,0,0));
		mode_1_normallyOn(&o1_led2,Color(255,0,0));
		break;
	case 48:
		mode_48_FlowFromLeft(&o1_led1,S_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		mode_48_FlowFromLeft(&o1_led4,S_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		mode_48_FlowFromLeft(&o1_led3,S_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		mode_48_FlowFromLeft(&o1_led2,S_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		break;
	case 49:
		mode_49_FlowFromRight(&o1_led1,S_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		mode_49_FlowFromRight(&o1_led4,S_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		mode_49_FlowFromRight(&o1_led3,S_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		mode_49_FlowFromRight(&o1_led2,S_WALL_GAME_OVER_HIGHLIGHT_NUM,GAME_OVER_FLOW_TIME);
		break;
	default:
		mode_1_normallyOn(&o1_led1,Color(0,0,0));
		mode_1_normallyOn(&o1_led4,Color(0,0,0));
		mode_1_normallyOn(&o1_led3,Color(0,0,0));
		mode_1_normallyOn(&o1_led2,Color(0,0,0));
		break;
	}
}

int userScore = 0;//用户得分
int isTouched = 0;//按键是否被触摸过
int isNoTouch = 0;//按键是否触摸
int touchFrame = 0;//按键时长

void btnDeal(){
	if(isUseful == 1){
		if(m_led6.status == 0 && m_led7.status == 0 && !touchFrame){
			//灯带增长特效 TODO
			if(btnMode == 1){//赏金
				switch (btnStage)
				{
				case 0://低能
					mode_26_buttonIsUseful(&m_led6,Color(255,80,0),M2_LED_BUTTON_IS_USEFUL_TIME);
					mode_26_buttonIsUseful(&m_led7,Color(255,80,0),M2_LED_BUTTON_IS_USEFUL_TIME);
					break;
				case 1://高能
					mode_26_buttonIsUseful(&m_led6,Color(255,30,0),M2_LED_BUTTON_IS_USEFUL_TIME);
					mode_26_buttonIsUseful(&m_led7,Color(255,30,0),M2_LED_BUTTON_IS_USEFUL_TIME);
					break;
				case 2://暴走
					mode_42_rainbowFlow(&m_led6,M2_LED_RAINBOW_COLOR_TIME);
					mode_42_rainbowFlow(&m_led7,M2_LED_RAINBOW_COLOR_TIME);
					break;
				default:
					break;
				}
			} else if(btnMode == 2){//生存
				switch (btnStage)
				{
				case 0:
					mode_26_buttonIsUseful(&m_led6,Color(0,255,255),M2_LED_BUTTON_IS_USEFUL_TIME);
					mode_26_buttonIsUseful(&m_led7,Color(0,255,255),M2_LED_BUTTON_IS_USEFUL_TIME);
					break;
				case 1:
					mode_26_buttonIsUseful(&m_led6,Color(0,100,255),M2_LED_BUTTON_IS_USEFUL_TIME);
					mode_26_buttonIsUseful(&m_led7,Color(0,100,255),M2_LED_BUTTON_IS_USEFUL_TIME);
					break;
				case 2:
					mode_42_rainbowFlow(&m_led6,M2_LED_RAINBOW_COLOR_TIME);
					mode_42_rainbowFlow(&m_led7,M2_LED_RAINBOW_COLOR_TIME);
					break;
				default:
					break;
				}
			}
			if(btnStage != 2 &&  currentMusic == MP3_NULL){
				chooseMp3("9",mp3Mode);
				currentMusic = MP3_GOLD_BORNING;
				touchLaserFrame = 1;
			}
		} else {
			isNoTouch = digitalRead(M_WALL_TOUCH_MODE);
			if(!isNoTouch){//当前是否触摸
				isTouched = 1;//该按键被触发
				//灯带减少特效 TODO
				if(btnStage == 2){//暴走模式
					mode_27_pressButton(&m_led6,(int)(score[3]*1000)/50);
					mode_27_pressButton(&m_led7,(int)(score[3]*1000)/50);
					mode_45_rainbowDarkRotate(&m_led5,2,M3_LED_PRESS_BUTTON_TIME);
				} else{//非暴走
					mode_27_pressButton(&m_led6,(int)(score[0]*1000)/50);
					mode_27_pressButton(&m_led7,(int)(score[0]*1000)/50);
					if(btnMode == 1){//赏金
						switch (btnStage)
						{
						case 0://低能
							mode_28_darkRotate(&m_led5,Color(255,80,0),2,M3_LED_PRESS_BUTTON_TIME);
							break;
						case 1://高能
							mode_28_darkRotate(&m_led5,Color(255,30,0),2,M3_LED_PRESS_BUTTON_TIME);
							break;
						default:
							break;
						}
					} else if(btnMode == 2){//生存
						switch (btnStage)
						{
						case 0:
							mode_28_darkRotate(&m_led5,Color(0,255,255),2,M3_LED_PRESS_BUTTON_TIME);
							break;
						case 1:
							mode_28_darkRotate(&m_led5,Color(0,100,255),2,M3_LED_PRESS_BUTTON_TIME);
							break;
						default:
							break;
						}
					}
				}
				if(currentMusic != MP3_LASER_TOUCHED || currentMusic == MP3_NULL){
					chooseMp3("10",mp3Mode);
					currentMusic = MP3_GETING_GOLD;
				}
				touchFrame++;
				userScore = touchFrame;
			} else {//没有被触摸的满能量情况
				touchFrame = 0;
				m_led6.ledTime = 0;
				m_led7.ledTime = 0;
				if(btnStage == 2 && !isTouched){ // 暴走，无触摸
					mode_42_rainbowFlow(&m_led6,M2_LED_RAINBOW_COLOR_TIME);
					mode_42_rainbowFlow(&m_led7,M2_LED_RAINBOW_COLOR_TIME);
					mode_42_rainbowFlow(&m_led5,M3_LED_PRESS_BUTTON_TIME);
				} else {
					if(btnMode == 1 && !isTouched){//赏金
						switch (btnStage)
						{
						case 0:
							mode_1_normallyOn(&m_led5,Color(255,80,0));
							break;
						case 1:
							mode_1_normallyOn(&m_led5,Color(255,30,0));
							break;
						default:
							break;
						}
						//Serial.println("Mucis 15 already --------- 1");
					} else if(btnMode == 2 && btnStage != 2){//生存
						switch (btnStage)
						{
						case 0:
							mode_1_normallyOn(&m_led5,Color(0,255,255));
							break;
						case 1:
							mode_1_normallyOn(&m_led5,Color(0,100,255));
							break;
						default:
							break;
						}
						//Serial.println("Mucis 15 already ---------- 2");
					}
					if(currentMusic != MP3_LASER_TOUCHED && currentMusic != MP3_LASER_BORNING && currentMusic != MP3_LASER_LOC){
						if(!glodMusicDone){
							chooseMp3("15",mp3Mode);
							currentMusic = MP3_GOLD_BORNED;
							glodMusicDone = true;
						}
					}
				}
			}
		}
	} else if(isUseful == 0){
		//按键不可用，灯效恢复初始设置
		m_led5.ledReset();
		m_led6.ledReset();
		m_led7.ledReset();
	} else if(isUseful == 2){
		M2LedDeal();
		M3LedDeal();
	} else if(isUseful == 3){
		if(m_led6.status == 0 && m_led7.status == 0 && !touchFrame){
			//灯带增长特效 TODO
			if(btnMode == 1){//赏金
				switch (btnStage)
				{
				case 0://低能
					mode_1_normallyOn(&m_led6,Color(255,80,0));
					mode_1_normallyOn(&m_led7,Color(255,80,0));
					break;
				case 1://高能
					mode_1_normallyOn(&m_led6,Color(255,30,0));
					mode_1_normallyOn(&m_led7,Color(255,30,0));
					break;
				default:
					break;
				}
			} else if(btnMode == 2){//生存
				switch (btnStage)
				{
				case 0:
					mode_1_normallyOn(&m_led6,Color(0,255,255));
					mode_1_normallyOn(&m_led7,Color(0,255,255));
					break;
				case 1:
					mode_1_normallyOn(&m_led6,Color(0,100,255));
					mode_1_normallyOn(&m_led7,Color(0,100,255));
					break;
				default:
					break;
				}
			}
		} else {
			isNoTouch = digitalRead(M_WALL_TOUCH_MODE);
			if(!isNoTouch){//当前是否触摸
				isTouched = 1;//该按键被触发
				//灯带减少特效 TODO
				if(btnStage == 2){//暴走模式
					mode_27_pressButton(&m_led6,(int)(score[3]*1000)/50);
					mode_27_pressButton(&m_led7,(int)(score[3]*1000)/50);
					mode_45_rainbowDarkRotate(&m_led5,2,M3_LED_PRESS_BUTTON_TIME);
				} else{//非暴走
					mode_27_pressButton(&m_led6,(int)(score[0]*1000)/50);
					mode_27_pressButton(&m_led7,(int)(score[0]*1000)/50);
					if(btnMode == 1){//赏金
						switch (btnStage)
						{
						case 0://低能
							mode_28_darkRotate(&m_led5,Color(255,80,0),2,M3_LED_PRESS_BUTTON_TIME);
							break;
						case 1://高能
							mode_28_darkRotate(&m_led5,Color(255,30,0),2,M3_LED_PRESS_BUTTON_TIME);
							break;
						default:
							break;
						}
					} else if(btnMode == 2){//生存
						switch (btnStage)
						{
						case 0:
							mode_28_darkRotate(&m_led5,Color(0,255,255),2,M3_LED_PRESS_BUTTON_TIME);
							break;
						case 1:
							mode_28_darkRotate(&m_led5,Color(0,100,255),2,M3_LED_PRESS_BUTTON_TIME);
							break;
						default:
							break;
						}
					}
				}
				if(currentMusic != MP3_LASER_TOUCHED){
					chooseMp3("10",mp3Mode);
					currentMusic = MP3_GETING_GOLD;
				}
				touchFrame++;
				userScore = touchFrame;
			} else {//没有被触摸的满能量情况
				touchFrame = 0;
				m_led6.ledTime = 0;
				m_led7.ledTime = 0;
				if(btnMode == 1 && !isTouched){//赏金
					switch (btnStage)
					{
					case 0:
						mode_1_normallyOn(&m_led5,Color(255,80,0));
						break;
					case 1:
						mode_1_normallyOn(&m_led5,Color(255,30,0));
						break;
					default:
						break;
					}
					//Serial.println("Mucis 15 already --------- 1");
				} else if(btnMode == 2 && btnStage != 2){//生存
					switch (btnStage)
					{
					case 0:
						mode_1_normallyOn(&m_led5,Color(0,255,255));
						break;
					case 1:
						mode_1_normallyOn(&m_led5,Color(0,100,255));
						break;
					default:
						break;
					}
					//Serial.println("Mucis 15 already ---------- 2");
				}
			}
		}
	}
}

void Mp3Deal(){
	digitalWrite(M_WALL_MP3_PIN4,mp3Mode[0]);
	digitalWrite(M_WALL_MP3_PIN3,mp3Mode[1]);
	digitalWrite(M_WALL_MP3_PIN2,mp3Mode[2]);
	digitalWrite(M_WALL_MP3_PIN1,mp3Mode[3]);
}

void scoreDeal(){
	if(isTouched && isNoTouch && userScore){//按键被触摸过，并且当前没有被触摸
		//Serial.println(userScore);
		if(btnStage != 2){ //非暴走
			if(userScore < (int)(score[0]*1000) - T){
				//MISS TODO
				upload(returnScoreM());
				chooseMp3("11",mp3Mode);
				currentMusic = MP3_GET_MISS;
				//Serial.println("Mucis 11 MISS");
			} else if(userScore < (int)(score[0]*1000) && userScore >= ((int)(score[0]*1000) - T)){
				//A TODO
				upload(returnScoreA());
				chooseMp3("13",mp3Mode);
				currentMusic = MP3_GET_A;
				//Serial.println("Mucis 13 A");
			} else if(userScore < (int)(score[1]*1000) && userScore >= (int)(score[0]*1000)){
				//S TODO
				upload(returnScoreS());
				chooseMp3("14",mp3Mode);
				currentMusic = MP3_GET_S;
				//Serial.println("Mucis 14 S");
			} else if(userScore < (int)(score[2]*1000) && userScore >= (int)(score[1]*1000)){
				//A TODO
				upload(returnScoreA());
				chooseMp3("13",mp3Mode);

				currentMusic = MP3_GET_A;
				//Serial.println("Mucis 13 A");
			} else if(userScore >= (int)(score[2]*1000)){
				//B TODO
				upload(returnScoreB());
				chooseMp3("12",mp3Mode);
				currentMusic = MP3_GET_B;
				//Serial.println("Mucis 12 B");
			}
		} else {//暴走
			if(userScore < (int)(score[3]*1000) - RAMPAGE_T){
				upload(returnScoreM());
				chooseMp3("11",mp3Mode);
				currentMusic = MP3_GET_MISS;
				//Serial.println("Mucis 11 M---RAMPAGE");
			} else {
				upload(returnScoreS());
				chooseMp3("14",mp3Mode);
				currentMusic = MP3_GET_S;
				//Serial.println("Mucis 11 S---RAMPAGE");
			}
		}
		//Serial.println(userScore);
		m_led6.ledReset();
		m_led7.ledReset();
		isTouched = 0;
		isUseful = 0;
		userScore = 0;
		glodMusicDone = false;
	}
}

void laserDeal(){
	for (int i = 0; i < LASER_NUM; i++)
	{
		digitalWrite(M_WALL_LASER_GUN_1 - i,laserGun[i]);
	}
}

void lightDeal(){
	digitalWrite(M_WALL_INDICATOR_LIGHT_LEFT_PIN1,indicatorMode[1]);
	digitalWrite(M_WALL_INDICATOR_LIGHT_LEFT_PIN2,indicatorMode[0]);
	digitalWrite(M_WALL_INDICATOR_LIGHT_RIGHT_PIN1,indicatorMode[1]);
	digitalWrite(M_WALL_INDICATOR_LIGHT_RIGHT_PIN2,indicatorMode[0]);
}

void uploadRevStatus(){
	for (int i = 0; i < M_REV_NUM; i++)
	{
		laserRevStatus[i] = digitalRead(M_WALL_LASER_REV_1 - i);
	}
	for (int i = 0; i < S_REV_NUM; i++)
	{
		laserRevStatus[i + M_REV_NUM] = digitalRead(S_WALL_LASER_REV_1 - i);
	}
	client.print("<[UR]");
	for (int i = 0; i < M_REV_NUM + S_REV_NUM; i++)
	{
		client.print(laserRevStatus[i]);
	}
	client.print("[ID]");
	client.print(Arduino_ID);
	client.print("[MD]");
	client.print(cmdGameMode.gameMode);
	client.print("[ST]");
	client.print(isUseful);
	client.print(">");
}

void ledParse(){
	LedParseContent* content = cmdLedCtrl.getLedParseContent();
	char* wall;
	if(content){
		for (int i = 0; i < cmdLedCtrl.size; i++)
		{
			wall = content[i].wall;
			if(strcmp(wall,M_WALL) == 0){
				if(content[i].led_t == '1'){
					ledMode_M[0] = content[i].mode;
				} else if(content[i].led_t == '2'){
					ledMode_M[1] = content[i].mode;
				} else if(content[i].led_t == '3'){
					ledMode_M[2] = content[i].mode;
				}
			} else if(strcmp(wall,S_WALL1) == 0){
				if(content[i].led_t == '1'){
					ledMode_O[0] = content[i].mode;
				}
			} else if(strcmp(wall,S_WALL2) == 0){
				if(content[i].led_t == '1'){
					ledMode_O[1] = content[i].mode;
				}
			} else if(strcmp(wall,S_WALL3) == 0){
				if(content[i].led_t == '1'){
					ledMode_O[2] = content[i].mode;
				}
			}
		}
		free(content);
		cmdLedCtrl.setLedParseContent(NULL);
		content = NULL;
	}
}

void btnParse(){
	char btn = cmdBtnCtrl.useful;
	isUseful = btn - '0';
	cmdBtnCtrl.useful = '0';
	btnMode = cmdBtnCtrl.mode - '0';
	btnStage = cmdBtnCtrl.stage - '0';
	if(isUseful == 1){
		if(btnStage == 2){
			chooseMp3("15",mp3Mode);
			currentMusic = MP3_GOLD_BORNED;
		} else {
			chooseMp3("9",mp3Mode);
			currentMusic = MP3_GOLD_BORNING;
		}
	} else if(isUseful ==3){
		chooseMp3("15",mp3Mode);
		currentMusic = MP3_GOLD_BORNED;
	}
}

void laserParse(){
	LaserParseContent* content = cmdLaserCtrl.getLaserParseContent();
	char* laser_n;
	if(content){
		for (int i = 0; i < cmdLaserCtrl.size; i++)
		{
			laser_n = content[i].laser_n;
			if(strcmp(laser_n,"1") == 0){
				laserGun[0] = content[i].laser_s - '0';
			} else if(strcmp(laser_n,"2") == 0){
				laserGun[1] = content[i].laser_s - '0';
			} else if(strcmp(laser_n,"3") == 0){
				laserGun[2] = content[i].laser_s - '0';
			} else if(strcmp(laser_n,"4") == 0){
				laserGun[3] = content[i].laser_s - '0';
			} else if(strcmp(laser_n,"5") == 0){
				laserGun[4] = content[i].laser_s - '0';
			} else if(strcmp(laser_n,"6") == 0){
				laserGun[5] = content[i].laser_s - '0';
			} else if(strcmp(laser_n,"7") == 0){
				laserGun[6] = content[i].laser_s - '0';
			} else if(strcmp(laser_n,"8") == 0){
				laserGun[7] = content[i].laser_s - '0';
			} else if(strcmp(laser_n,"9") == 0){
				laserGun[8] = content[i].laser_s - '0';
			} else if(strcmp(laser_n,"10") == 0){
				laserGun[9] = content[i].laser_s - '0';
			}
		}
		//for (int i = 0; i < 10; i++)
		//{
		//	Serial.print("LaserGun");
		//	Serial.print(i + 1);
		//	Serial.print(":");
		//	Serial.println(laserGun[i]);
		//}
		free(content);
		cmdLaserCtrl.setLaserParseContent(NULL);
		content = NULL;
	}
}

void mp3Parse(){
	char* music = cmdMp3Ctrl.music;
	if(strcmp(music,"0") == 0){
		mp3Mode[0] = 0;
		mp3Mode[1] = 0;
		mp3Mode[2] = 0;
		mp3Mode[3] = 0;

		currentMusic = 0;
	} else if(strcmp(music,"1") == 0){
		mp3Mode[0] = 0;
		mp3Mode[1] = 0;
		mp3Mode[2] = 0;
		mp3Mode[3] = 1;

		currentMusic = 1;
	} else if(strcmp(music,"2") == 0){
		mp3Mode[0] = 0;
		mp3Mode[1] = 0;
		mp3Mode[2] = 1;
		mp3Mode[3] = 0;

		currentMusic = 2;
	} else if(strcmp(music,"3") == 0){
		mp3Mode[0] = 0;
		mp3Mode[1] = 0;
		mp3Mode[2] = 1;
		mp3Mode[3] = 1;

		currentMusic = 3;
	} else if(strcmp(music,"4") == 0){
		mp3Mode[0] = 0;
		mp3Mode[1] = 1;
		mp3Mode[2] = 0;
		mp3Mode[3] = 0;

		currentMusic = 4;
	} else if(strcmp(music,"5") == 0){
		mp3Mode[0] = 0;
		mp3Mode[1] = 1;
		mp3Mode[2] = 0;
		mp3Mode[3] = 1;

		currentMusic = 5;
	} else if(strcmp(music,"6") == 0){
		mp3Mode[0] = 0;
		mp3Mode[1] = 1;
		mp3Mode[2] = 1;
		mp3Mode[3] = 0;

		currentMusic = 6;
	} else if(strcmp(music,"7") == 0){
		mp3Mode[0] = 0;
		mp3Mode[1] = 1;
		mp3Mode[2] = 1;
		mp3Mode[3] = 1;

		currentMusic = 7;
	} else if(strcmp(music,"8") == 0){
		mp3Mode[0] = 1;
		mp3Mode[1] = 0;
		mp3Mode[2] = 0;
		mp3Mode[3] = 0;

		currentMusic = 8;
	} else if(strcmp(music,"9") == 0){
		mp3Mode[0] = 1;
		mp3Mode[1] = 0;
		mp3Mode[2] = 0;
		mp3Mode[3] = 1;

		currentMusic = 9;
	} else if(strcmp(music,"10") == 0){
		mp3Mode[0] = 1;
		mp3Mode[1] = 0;
		mp3Mode[2] = 1;
		mp3Mode[3] = 0;

		currentMusic = 10;
	} else if(strcmp(music,"11") == 0){
		mp3Mode[0] = 1;
		mp3Mode[1] = 0;
		mp3Mode[2] = 1;
		mp3Mode[3] = 1;

		currentMusic = 11;
	} else if(strcmp(music,"12") == 0){
		mp3Mode[0] = 1;
		mp3Mode[1] = 1;
		mp3Mode[2] = 0;
		mp3Mode[3] = 0;

		currentMusic = 12;
	} else if(strcmp(music,"13") == 0){
		mp3Mode[0] = 1;
		mp3Mode[1] = 1;
		mp3Mode[2] = 0;
		mp3Mode[3] = 1;

		currentMusic = 13;
	} else if(strcmp(music,"14") == 0){
		mp3Mode[0] = 1;
		mp3Mode[1] = 1;
		mp3Mode[2] = 1;
		mp3Mode[3] = 0;

		currentMusic = 14;
	} else if(strcmp(music,"15") == 0){
		mp3Mode[0] = 1;
		mp3Mode[1] = 1;
		mp3Mode[2] = 1;
		mp3Mode[3] = 1;

		currentMusic = 15;
	}
}

void lightParse(){
	char lightMode = cmdLightCtrl.light_mode;
	if(lightMode == '0'){
		indicatorMode[0] = 0;
		indicatorMode[1] = 0;
	} else if(lightMode == '1'){
		indicatorMode[0] = 0;
		indicatorMode[1] = 1;
	} else if(lightMode == '2'){
		indicatorMode[0] = 1;
		indicatorMode[1] = 0;
	} else if(lightMode == '3'){
		indicatorMode[0] = 1;
		indicatorMode[1] = 1;
	}
	cmdLightCtrl.light_mode = '0';
}

void scoreParse(){
	ScoreParseContent* content = cmdInitScore.getScoreParseContent();
	char * status;
	if(content){
		for (int i = 0; i < cmdInitScore.size; i++)
		{
			status = content[i].status;
			if(strcmp(status,"T1") == 0){
				score[0] = atof(content[i].time);
			} else if(strcmp(status,"T2") == 0){
				score[1] = atof(content[i].time);
			} else if(strcmp(status,"T3") == 0){
				score[2] = atof(content[i].time);
			} else if(strcmp(status,"TR") == 0){
				score[3] = atof(content[i].time);
			}
		}
		free(content);
		cmdInitScore.setScoreParseContent(NULL);
		content = NULL;
	}
	uploadTime = atoi(cmdInitScore.uploadTime);
	heartBeatTime = atoi(cmdInitScore.heartBeatTime);
}

void frameAdd(){
	m_led1.ledTime += MILLISECOND;
	m_led2.ledTime += MILLISECOND;
	m_led3.ledTime += MILLISECOND;
	m_led4.ledTime += MILLISECOND;
	m_led5.ledTime += MILLISECOND;
	m_led6.ledTime += MILLISECOND;
	m_led7.ledTime += MILLISECOND;
	o1_led1.ledTime += MILLISECOND;
	o1_led2.ledTime += MILLISECOND;
	o1_led3.ledTime += MILLISECOND;
	o1_led4.ledTime += MILLISECOND;
	uploadFrame += MILLISECOND;
	if(currentMusic == 6){
		touchLaserFrame+= MILLISECOND;
		if(touchLaserFrame % TOUCH_LASER_FRAME == 0){
			currentMusic = 0;
			touchLaserFrame = 1;
		}
	}
}