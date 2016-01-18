#include "Tools.h"
#include <Adafruit_NeoPixel.h>
#include <aJSON.h>
#include <SPI.h>
#include <Ethernet.h>
#include <SPI.h>
#include <SoftwareSerial.h>

//------------------------------------------NET-----------------------------------
byte myMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress myIp (172, 16, 10, 180);
IPAddress serverIp (172, 16, 10, 62);
int myPort = 8989;
String Arduino_ID = "AT01";
EthernetClient client;  
using namespace Tools;

//----------------------------------LED-----------------------------------------
Led l1(LED_LENG6,PIN6);
Led l2(LED_LENG7,PIN7);
void setup() {
	Serial.begin(9600);
	Ethernet.begin(myMac, myIp);
	l1.ledSetup("1-1",'n',1,1);
	l2.ledSetup("1-1",'n',1,2);
}
int stringPos = 0;
bool startRead = false;
char inString[255];
char * readPage(){
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
					startRead = false;
					stringPos = 0;
					client.stop();
					client.flush();
					return inString;
				}
			}
		}
	}
}

void jsonParseLaser_Control(char *msg){
	aJsonObject *root = aJson.parse(msg);
	if(root != NULL){
		aJsonObject *cmd = aJson.getObjectItem(root,"cmd");
		Serial.println(cmd->valuestring);
		aJsonObject *next_cell_num = aJson.getObjectItem(root,"next_cell_num");
		Serial.println(next_cell_num->valuestring);
		aJsonObject *cur_cell_num = aJson.getObjectItem(root,"cur_cell_num");
		Serial.println(cur_cell_num->valuestring);
		aJsonObject *wall = aJson.getObjectItem(root,"wall");
		int size = aJson.getArraySize(wall);
		Serial.println(size);
		aJsonObject *wallChild = wall->child;
		for(int i = 0;i < size; i++){
			aJsonObject *wall_num = aJson.getObjectItem(wallChild,"wall_num");
			aJsonObject *laser_num = aJson.getObjectItem(wallChild,"laser_num");
			aJsonObject *laser_status = aJson.getObjectItem(wallChild,"laser_status");
			Serial.print("wall_num:");
			Serial.println(wall_num->valuestring);
			Serial.print("laser_num:");
			Serial.println(laser_num->valuestring);
			Serial.print("laser_status:");
			Serial.println(laser_status->valuestring);
			wallChild = wallChild->next;
		}
	}
}

bool isUse = false;

void loop() {
	mode_3_rainbowColor(&l1,20);
	//mode_6_waterFlow(&l1,Color(0,255,255),10,20,20);
	char *a = clientConnect();
	if(*a == '1'){
		isUse = true;
	} else if(*a == '0') {
		isUse = false;
	}
	if(isUse){
		mode_34_breath(&l2,Color(1,0,0),800,0);
		//mode_6_waterFlow(&l2,Color(255,255,255),10,20,20);
		//ledEffect_buttonIsUseful(&l2,Color(0,255,255),50);
	} else {
		mode_6_waterFlow(&l2,Color(0,255,255),10,20,20);
		//ledEffect_pressButton(&l2,Color(0,255,255),50);
	}
	l1.ledTime += MILLISECOND;
	l2.ledTime += MILLISECOND;
	delay(MILLISECOND);
} 

char* clientConnect(){
	if(!client.connected()) {
		if(client.connect(serverIp,myPort)){
			client.print("Hello,server,I'm comming!");	
			client.print("{\
						 \"cmd\": \"alarm_info_upload\",\
						 \"cell_num\": \"1-1\",\
						 \"wall_num\": \"n\",\
						 \"alarm_status\": \"off\"\
						 }");	
			Serial.println("Connected success!");
		} else {
			Serial.println("Oh,fuck!connected failed!");
		}
	} else {
		char *c = readPage();
		//jsonParseLaser_Control(c);
		return c;
	}
}
