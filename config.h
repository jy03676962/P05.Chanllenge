#ifndef CONFIG_H
#define CONFIG_H

#define N32//��ǰArduino��ţ�������������

//---------------------system--------------------------
#define DEBUG "true"
#define MILLISECOND 1

#define M_WALL "M" //ǽ����
#define S_WALL1 "O1"
#define S_WALL2 "O2"
#define S_WALL3 "O3"

#define T 20 // ��һ���÷ֵ�miss�Ѻü��ʱ��
#define RAMPAGE_T 5 // ��һ���÷ֵ�miss�Ѻü��ʱ��
#define UPLOAD_TIME 3 //ÿ10ms�ϴ�һ��
#define HEARTBEATS 300//�ڷ�ģʽ3״̬�£�����ÿ300msһ�����������߷�����û�е���
#define TOUCH_LASER_FRAME 100

//----------------------LED config---------------------
#define ALL_LED_BREATH_READY_MODE_TIME 100 // ����led��ɫ����ʱ��
#define M1_LED_STARTFLOW_TIME 1 //���� time
#define ALL_LED_RAINBOW_COLOR_TIME 1 //�ʺ絥ɫѭ�� time

#define S_WALL_BREATH_NUM 1.25//Сǽ�������ٶȱ�������ȴ�ǽ������Сǽ�ƴ��̣����Ժ����ٶȿ飬����β���������
#define TYPE1_LED_GAME_GOLD_MODE_TIME_P1 300 //�ͽ�ģʽ����1�ƴ�ʱ�䣨������
#define TYPE1_LED_GAME_GOLD_MODE_TIME_P2 250
#define TYPE1_LED_GAME_GOLD_MODE_TIME_P3 200
#define TYPE1_LED_GAME_GOLD_MODE_TIME_P4 150
#define TYPE1_LED_GAME_GOLD_MODE_TIME_P5 100

#define TYPE1_LED_GAME_SURVIVE_MODE_TIME_P1 300 //����ģʽ����1�ƴ�ʱ�䣨������
#define TYPE1_LED_GAME_SURVIVE_MODE_TIME_P2 250
#define TYPE1_LED_GAME_SURVIVE_MODE_TIME_P3 200
#define TYPE1_LED_GAME_SURVIVE_MODE_TIME_P4 150
#define TYPE1_LED_GAME_SURVIVE_MODE_TIME_P5 100

#define TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_NUM 20 //�ͽ���Ԥ�ȸ�����������
#define TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_TIME 1 //�ͽ���Ԥ����������

#define TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_NUM 20 //���汩��Ԥ�ȸ�����������
#define TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_TIME 1 //���汩��Ԥ����������

#define TYPE1_LED_RAMPAGE_TIME 1 //��������1�ƴ�
#define M1_LED_LASER_ALARM_TIME 1 //M1���ⱨ��
#define TYPE1_LED_TOUCH_LASER_TIME 5//����1�����ⴥ��
#define M1_LED_GAME_COUNT_DOWN_TIME 1

#define GAME_OVER_FLOW_TIME 1
#define M_WALL_GAME_OVER_HIGHLIGHT_NUM 20
#define S_WALL_GAME_OVER_HIGHLIGHT_NUM 5


#define M2_LED_BUTTON_IS_USEFUL_TIME 1 //��ť����ʱ��
#define M2_LED_RAINBOW_COLOR_TIME 1 // �����ܱ߲ʺ�����

#define M3_LED_PRESS_BUTTON_TIME 3//�����ƴ���ת����
#define M3_LED_PRESS_BUTTON_RAMPAGE_TIME 1//�����ƴ�����ģʽ����ת����



//-----------------��ǽ���������1~5--------------------
#define M_WALL_LASER_REV_5 2
#define M_WALL_LASER_REV_4 3
#define M_WALL_LASER_REV_3 4
#define M_WALL_LASER_REV_2 5
#define M_WALL_LASER_REV_1 6

//--------------------��ǽLED-----------------------
#define M_WALL_LED_7 7 //�ұ�
#define M_WALL_LED_6 8//���
#define M_WALL_LED_5 9//�м�
#define M_WALL_LED_4 12
#define M_WALL_LED_3 13
#define M_WALL_LED_2 14
#define M_WALL_LED_1 15

//-----------------СǽLED-------------------------
#define S_WALL_LED_4 16
#define S_WALL_LED_3 17
#define S_WALL_LED_2 18
#define S_WALL_LED_1 19

//----------------Сǽ���������1~10-----------------
#define S_WALL_LASER_REV_10 20
#define S_WALL_LASER_REV_9 21
#define S_WALL_LASER_REV_8 22
#define S_WALL_LASER_REV_7 23
#define S_WALL_LASER_REV_6 24
#define S_WALL_LASER_REV_5 25
#define S_WALL_LASER_REV_4 26
#define S_WALL_LASER_REV_3 27
#define S_WALL_LASER_REV_2 28
#define S_WALL_LASER_REV_1 29

//-----------------��ǽ���ⷢ����-------------------
#define M_WALL_LASER_GUN_10 30
#define M_WALL_LASER_GUN_9 31
#define M_WALL_LASER_GUN_8 32
#define M_WALL_LASER_GUN_7 33
#define M_WALL_LASER_GUN_6 34
#define M_WALL_LASER_GUN_5 35
#define M_WALL_LASER_GUN_4 36
#define M_WALL_LASER_GUN_3 37
#define M_WALL_LASER_GUN_2 38
#define M_WALL_LASER_GUN_1 39

//-------------------��ǽ��----------------------------
#define M_WALL_TOUCH_MODE 40
#define M_WALL_INDICATOR_LIGHT_LEFT_PIN1 41
#define M_WALL_INDICATOR_LIGHT_LEFT_PIN2 42
#define M_WALL_INDICATOR_LIGHT_RIGHT_PIN1 43
#define M_WALL_INDICATOR_LIGHT_RIGHT_PIN2 44

#define M_WALL_MP3_PIN1 45
#define M_WALL_MP3_PIN2 46
#define M_WALL_MP3_PIN3 47
#define M_WALL_MP3_PIN4 48

//--------------------------rev cmd-----------------
#define MODE_CHANGE "mode_change" //��Ϸģʽ�л�
#define STATUS_CHANGE "status_change" //��Ϸ״̬������or��Ϸ��
#define LED_CTRL "led_ctrl" //�ƴ�����
#define BTN_CTRL "btn_ctrl" //��������
#define LASER_CTRL "laser_ctrl" //���ⷢ��������
#define LASER_REV_CTRL "laser_rev_ctrl" //�������������
#define MP3_CTRL "mp3_ctrl" //MP3���ƣ�Ԥ����
#define LIGHT_CTRL "light_ctrl" //ָʾ�ƿ��ƣ�Ԥ��)
#define INIT_SCORE "init_score" //��ʼ����������

//--------------------------upload cmd----------------
#define UPLOAD_SCORE "upload_score" //������Ϣ�ϴ�
#define UPLOAD_REV "[UR]" //�����������Ϣ�ϴ�
#define CONFIRM_BTN "confirm_btn" //�������շ���
#define CONFIRM_INIT_SCORE "confirm_init_score" //��ʼ����Ϣ����

//------------------------------Music-----------------------------
#define MP3_NULL 0
#define MP3_GAME_START 1;
#define MP3_WARM_UP 2
#define MP3_RAMPAGE 3
#define MP3_LASER_BORNING 4
#define MP3_LASER_LOC 5
#define MP3_LASER_TOUCHED 6
#define MP3_GOLD_BORNING 9
#define MP3_GETING_GOLD 10
#define MP3_GET_MISS 11
#define MP3_GET_B 12
#define MP3_GET_A 13
#define MP3_GET_S 14
#define MP3_GOLD_BORNED 15

//---------------------------------------------arduino config----------------------------------------
#if defined (N1)
#define A_IP (192, 168, 1, 101)
#define A_ID "M-1-6-1-A-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N2)
#define A_IP (192, 168, 1, 102)
#define A_ID "M-2-6-1-B-5-L"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N3)
#define A_IP (192, 168, 1, 103)
#define A_ID "M-3-6-1-A-10-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N4)
#define A_IP (192, 168, 1, 104)
#define A_ID "M-4-6-1-B-10-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N5)
#define A_IP (192, 168, 1, 105)
#define A_ID "M-5-6-1-A-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N6)
#define A_IP (192, 168, 1, 106)
#define A_ID "M-6-6-1-B-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 5 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N7)
#define A_IP (192, 168, 1, 107)
#define A_ID "M-5-6-2-B-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N8)
#define A_IP (192, 168, 1, 108)
#define A_ID "M-6-6-4-A-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N11)
#define A_IP (192, 168, 1, 111)
#define A_ID "M-8-6-1-B-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 5 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N12)
#define A_IP (192, 168, 1, 112)
#define A_ID "M-8-6-2-A-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N13)
#define A_IP (192, 168, 1, 113)
#define A_ID "M-8-5-2-B-5-L"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N14)
#define A_IP (192, 168, 1, 114)
#define A_ID "M-8-4-2-A-10-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N15)
#define A_IP (192, 168, 1, 115)
#define A_ID "M-8-3-2-B-5-R"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N16)
#define A_IP (192, 168, 1, 116)
#define A_ID "M-8-2-2-A-5-R"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N17)
#define A_IP (192, 168, 1, 117)
#define A_ID "M-8-1-2-B-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N18)
#define A_IP (192, 168, 1, 118)
#define A_ID "M-8-1-3-A-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N19)
#define A_IP (192, 168, 1, 119)
#define A_ID "M-7-1-3-B-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N20)
#define A_IP (192, 168, 1, 120)
#define A_ID "M-6-1-3-A-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N21)
#define A_IP (192, 168, 1, 121)
#define A_ID "M-5-1-3-B-5-R"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N22)
#define A_IP (192, 168, 1, 122)
#define A_ID "M-4-1-3-A-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N23)
#define A_IP (192, 168, 1, 123)
#define A_ID "M-3-1-2-A-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N24)
#define A_IP (192, 168, 1, 124)
#define A_ID "M-4-1-4-B-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N25)
#define A_IP (192, 168, 1, 125)
#define A_ID "M-3-1-3-B-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N26)
#define A_IP (192, 168, 1, 126)
#define A_ID "M-2-1-3-A-10-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N27)
#define A_IP (192, 168, 1, 127)
#define A_ID "M-1-1-3-A-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N28)
#define A_IP (192, 168, 1, 128)
#define A_ID "M-1-1-4-B-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 5 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N30)
#define A_IP (192, 168, 1, 130)
#define A_ID "M-1-3-4-A-5-L"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 5 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N31)
#define A_IP (192, 168, 1, 131)
#define A_ID "M-1-4-4-B-10-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N32)
#define A_IP (192, 168, 1, 132)
#define A_ID "M-1-5-4-A-5-L"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N33)
#define A_IP (192, 168, 1, 133)
#define A_ID "M-1-6-4-B-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N35)
#define A_IP (192, 168, 1, 135)
#define A_ID "M-2-5-4-B-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N37)
#define A_IP (192, 168, 1, 137)
#define A_ID "M-2-5-1-A-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N38)
#define A_IP (192, 168, 1, 138)
#define A_ID "M-2-6-3-B-5-R"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N41)
#define A_IP (192, 168, 1, 141)
#define A_ID "M-3-5-2-A-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N42)
#define A_IP (192, 168, 1, 142)
#define A_ID "M-4-5-4-B-5-R"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N43)
#define A_IP (192, 168, 1, 143)
#define A_ID "M-3-5-3-B-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N44)
#define A_IP (192, 168, 1, 144)
#define A_ID "M-3-4-1-A-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N47)
#define A_IP (192, 168, 1, 147)
#define A_ID "M-7-5-1-B-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N48)
#define A_IP (192, 168, 1, 148)
#define A_ID "M-7-6-3-A-10-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N49)
#define A_IP (192, 168, 1, 149)
#define A_ID "M-7-5-2-A-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N53)
#define A_IP (192, 168, 1, 153)
#define A_ID "M-5-5-4-A-10-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N54)
#define A_IP (192, 168, 1, 154)
#define A_ID "M-4-5-2-B-5-L"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N55)
#define A_IP (192, 168, 1, 155)
#define A_ID "M-5-4-4-B-5-L"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N56)
#define A_IP (192, 168, 1, 156)
#define A_ID "M-4-4-2-A-5-R"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N59)
#define A_IP (192, 168, 1, 159)
#define A_ID "M-7-2-2-B-5-L"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N60)
#define A_IP (192, 168, 1, 160)
#define A_ID "M-8-2-4-A-5-L"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N61)
#define A_IP (192, 168, 1, 161)
#define A_ID "M-7-3-2-A-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N62)
#define A_IP (192, 168, 1, 162)
#define A_ID "M-8-3-4-B-5-L"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N63)
#define A_IP (192, 168, 1, 163)
#define A_ID "M-7-4-3-A-10-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 5 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N64)
#define A_IP (192, 168, 1, 164)
#define A_ID "M-7-3-1-B-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N66)
#define A_IP (192, 168, 1, 166)
#define A_ID "M-6-1-2-B-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N67)
#define A_IP (192, 168, 1, 167)
#define A_ID "M-7-1-4-A-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N68)
#define A_IP (192, 168, 1, 168)
#define A_ID "M-7-2-4-B-5-R"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N69)
#define A_IP (192, 168, 1, 169)
#define A_ID "M-6-2-2-A-5-R"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N72)
#define A_IP (192, 168, 1, 172)
#define A_ID "M-5-2-3-A-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N74)
#define A_IP (192, 168, 1, 174)
#define A_ID "M-5-2-2-B-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N75)
#define A_IP (192, 168, 1, 175)
#define A_ID "M-6-2-4-A-5-L"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N76)
#define A_IP (192, 168, 1, 176)
#define A_ID "M-6-3-4-B-10-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N77)
#define A_IP (192, 168, 1, 177)
#define A_ID "M-5-3-2-A-10-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N78)
#define A_IP (192, 168, 1, 178)
#define A_ID "M-5-4-2-B-5-R"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N79)
#define A_IP (192, 168, 1, 179)
#define A_ID "M-6-4-4-A-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N80)
#define A_IP (192, 168, 1, 180)
#define A_ID "M-6-4-1-B-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 5 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N81)
#define A_IP (192, 168, 1, 181)
#define A_ID "M-6-5-3-A-10-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N83)
#define A_IP (192, 168, 1, 183)
#define A_ID "M-3-2-4-B-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N85)
#define A_IP (192, 168, 1, 185)
#define A_ID "M-3-2-1-A-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N86)
#define A_IP (192, 168, 1, 186)
#define A_ID "M-3-3-3-B-5-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N87)
#define A_IP (192, 168, 1, 187)
#define A_ID "M-4-2-1-B-10-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N88)
#define A_IP (192, 168, 1, 188)
#define A_ID "M-4-3-3-A-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N90)
#define A_IP (192, 168, 1, 190)
#define A_ID "M-4-3-4-B-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N91)
#define A_IP (192, 168, 1, 191)
#define A_ID "M-3-3-2-A-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N92)
#define A_IP (192, 168, 1, 192)
#define A_ID "M-4-4-4-A-5-L"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N93)
#define A_IP (192, 168, 1, 193)
#define A_ID "M-3-4-2-B-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N94)
#define A_IP (192, 168, 1, 194)
#define A_ID "M-2-2-4-A-5-L"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N95)
#define A_IP (192, 168, 1, 195)
#define A_ID "M-1-2-2-A-10-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N96)
#define A_IP (192, 168, 1, 196)
#define A_ID "M-2-3-4-B-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N97)
#define A_IP (192, 168, 1, 197)
#define A_ID "M-1-3-2-A-5-R"
#define M_REV_NUM 5 //��ǽ����������
#define S_REV_NUM 5 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N98)
#define A_IP (192, 168, 1, 198)
#define A_ID "M-2-3-1-A-5-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N99)
#define A_IP (192, 168, 1, 199)
#define A_ID "M-2-4-3-B-10-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif
//-----------------------------not this code-------------------------
//-----------------------A3_B3-------------------------------
//#if defined (N34)
//#define A_IP (192, 168, 1, 134)
//#define A_ID "M-1-5-2-A-5-R"
//#define M_REV_NUM 5 //��ǽ����������
//#define S_REV_NUM 10 //Сǽ����������
//#define LASER_NUM 10 //���ⷢ��������
//#endif
//
//#if defined (N50)
//#define A_IP (192, 168, 1, 150)
//#define A_ID "M-8-5-4-B-5-L"
//#define M_REV_NUM 5 //��ǽ����������
//#define S_REV_NUM 10 //Сǽ����������
//#define LASER_NUM 10 //���ⷢ��������
//#endif
//
//#if defined (N73)
//#define A_IP (192, 168, 1, 173)
//#define A_ID "M-5-1-1-B-5-L"
//#define M_REV_NUM 5 //��ǽ����������
//#define S_REV_NUM 10 //Сǽ����������
//#define LASER_NUM 10 //���ⷢ��������
//#endif
//
//#if defined (N84)
//#define A_IP (192, 168, 1, 184)
//#define A_ID "M-2-2-2-A-5-R"
//#define M_REV_NUM 5 //��ǽ����������
//#define S_REV_NUM 10 //Сǽ����������
//#define LASER_NUM 10 //���ⷢ��������
//#endif

//-----------------------specile-------------------------------

#if defined (N29)//�����ţ����
#define A_IP (192, 168, 1, 129)
#define A_ID "M-1-2-4-A-0-R"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

#if defined (N10) //������
#define A_IP (192, 168, 1, 110)
#define A_ID "M-7-6-1-A-0-L"
#define M_REV_NUM 0 //��ǽ����������
#define S_REV_NUM 0 //Сǽ����������
#define LASER_NUM 10 //���ⷢ��������
#endif

//-----------------------------s wall--------------------------
//#if defined (N9)
//#define A_IP (192, 168, 1, 109)
//#define A_ID "S-5-5"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 10 //Сǽ����������
//#endif
//
//#if defined (N36)
//#define A_IP (192, 168, 1, 136)
//#define A_ID "S-1-4"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 10 //Сǽ����������
//#endif
//
//#if defined (N39)
//#define A_IP (192, 168, 1, 139)
//#define A_ID "S-2-5"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 15 //Сǽ����������
//#endif
//
//#if defined (N40)
//#define A_IP (192, 168, 1, 140)
//#define A_ID "S-3-5"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 10 //Сǽ����������
//#endif
//
//#if defined (N45)
//#define A_IP (192, 168, 1, 145)
//#define A_ID "S-2-4"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 15 //Сǽ����������
//#endif
//
//#if defined (N46)
//#define A_IP (192, 168, 1, 146)
//#define A_ID "S-6-5"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 15 //Сǽ����������
//#endif
//
//#if defined (N51)
//#define A_IP (192, 168, 1, 151)
//#define A_ID "S-7-4"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 10 //Сǽ����������
//#endif
//
//#if defined (N52)
//#define A_IP (192, 168, 1, 152)
//#define A_ID "S-4-5L"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 15 //Сǽ����������
//#endif
//
//#if defined (N57)
//#define A_IP (192, 168, 1, 157)
//#define A_ID "S-4-3"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 15 //Сǽ����������
//#endif
//
//#if defined (N58)
//#define A_IP (192, 168, 1, 158)
//#define A_ID "S-7-1"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 20 //Сǽ����������
//#endif
//
//#if defined (N65)
//#define A_IP (192, 168, 1, 165)
//#define A_ID "S-6-3"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 15 //Сǽ����������
//#endif
//
//#if defined (N70)
//#define A_IP (192, 168, 1, 170)
//#define A_ID "S-6-2"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 15 //Сǽ����������
//#endif
//
//
//#if defined (N71)
//#define A_IP (192, 168, 1, 171)
//#define A_ID "S-4-1"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 15 //Сǽ����������
//#endif
//
//#if defined (N82)
//#define A_IP (192, 168, 1, 182)
//#define A_ID "S-6-4"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 15 //Сǽ����������
//#endif
//
//#if defined (N89)
//#define A_IP (192, 168, 1, 189)
//#define A_ID "S-4-2"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 15 //Сǽ����������
//#endif
//
//#if defined (N100)
//#define A_IP (192, 168, 1, 200)
//#define A_ID "S-2-3"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 20 //Сǽ����������
//#endif
//
//#if defined (N109)
//#define A_IP (192, 168, 1, 209)
//#define A_ID "S-3-1"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 15 //Сǽ����������
//#endif
//
//#if defined (N110)
//#define A_IP (192, 168, 1, 210)
//#define A_ID "S-2-1"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 15 //Сǽ����������
//#endif
//
//#if defined (N111)
//#define A_IP (192, 168, 1, 211)
//#define A_ID "S-1-1"
//#define M_REV_NUM 0 //��ǽ����������
//#define S_REV_NUM 15 //Сǽ����������
//#endif

#endif 

