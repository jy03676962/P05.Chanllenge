#ifndef CONFIG_H
#define CONFIG_H

#define N32//当前Arduino编号，配置在最下面

//---------------------system--------------------------
#define DEBUG "true"
#define MILLISECOND 1

#define M_WALL "M" //墙体编号
#define S_WALL1 "O1"
#define S_WALL2 "O2"
#define S_WALL3 "O3"

#define T 20 // 第一档得分的miss友好间隔时间
#define RAMPAGE_T 5 // 第一档得分的miss友好间隔时间
#define UPLOAD_TIME 3 //每10ms上传一次
#define HEARTBEATS 300//在非模式3状态下，保持每300ms一次心跳，告诉服务器没有掉线
#define TOUCH_LASER_FRAME 100

//----------------------LED config---------------------
#define ALL_LED_BREATH_READY_MODE_TIME 100 // 所有led绿色呼吸时间
#define M1_LED_STARTFLOW_TIME 1 //流星 time
#define ALL_LED_RAINBOW_COLOR_TIME 1 //彩虹单色循环 time

#define S_WALL_BREATH_NUM 1.25//小墙呼吸的速度倍数（相比大墙，由于小墙灯带短，所以呼吸速度块，加如次参数调整）
#define TYPE1_LED_GAME_GOLD_MODE_TIME_P1 300 //赏金模式类型1灯带时间（呼吸）
#define TYPE1_LED_GAME_GOLD_MODE_TIME_P2 250
#define TYPE1_LED_GAME_GOLD_MODE_TIME_P3 200
#define TYPE1_LED_GAME_GOLD_MODE_TIME_P4 150
#define TYPE1_LED_GAME_GOLD_MODE_TIME_P5 100

#define TYPE1_LED_GAME_SURVIVE_MODE_TIME_P1 300 //生存模式类型1灯带时间（呼吸）
#define TYPE1_LED_GAME_SURVIVE_MODE_TIME_P2 250
#define TYPE1_LED_GAME_SURVIVE_MODE_TIME_P3 200
#define TYPE1_LED_GAME_SURVIVE_MODE_TIME_P4 150
#define TYPE1_LED_GAME_SURVIVE_MODE_TIME_P5 100

#define TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_NUM 20 //赏金暴走预热高亮灯珠数量
#define TYPE1_LED_GAME_GOLD_MODE_READY_RAMPAGE_TIME 1 //赏金暴走预热流动速率

#define TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_NUM 20 //生存暴走预热高亮灯珠数量
#define TYPE1_LED_GAME_SURVIVE_MODE_READY_RAMPAGE_TIME 1 //生存暴走预热流动速率

#define TYPE1_LED_RAMPAGE_TIME 1 //暴走类型1灯带
#define M1_LED_LASER_ALARM_TIME 1 //M1激光报警
#define TYPE1_LED_TOUCH_LASER_TIME 5//类型1，激光触碰
#define M1_LED_GAME_COUNT_DOWN_TIME 1

#define GAME_OVER_FLOW_TIME 1
#define M_WALL_GAME_OVER_HIGHLIGHT_NUM 20
#define S_WALL_GAME_OVER_HIGHLIGHT_NUM 5


#define M2_LED_BUTTON_IS_USEFUL_TIME 1 //按钮充能时间
#define M2_LED_RAINBOW_COLOR_TIME 1 // 按键周边彩虹流动

#define M3_LED_PRESS_BUTTON_TIME 3//按键灯带旋转速率
#define M3_LED_PRESS_BUTTON_RAMPAGE_TIME 1//按键灯带暴走模式下旋转速率



//-----------------主墙激光接收器1~5--------------------
#define M_WALL_LASER_REV_5 2
#define M_WALL_LASER_REV_4 3
#define M_WALL_LASER_REV_3 4
#define M_WALL_LASER_REV_2 5
#define M_WALL_LASER_REV_1 6

//--------------------主墙LED-----------------------
#define M_WALL_LED_7 7 //右边
#define M_WALL_LED_6 8//左边
#define M_WALL_LED_5 9//中间
#define M_WALL_LED_4 12
#define M_WALL_LED_3 13
#define M_WALL_LED_2 14
#define M_WALL_LED_1 15

//-----------------小墙LED-------------------------
#define S_WALL_LED_4 16
#define S_WALL_LED_3 17
#define S_WALL_LED_2 18
#define S_WALL_LED_1 19

//----------------小墙激光接收器1~10-----------------
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

//-----------------主墙激光发射器-------------------
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

//-------------------主墙体----------------------------
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
#define MODE_CHANGE "mode_change" //游戏模式切换
#define STATUS_CHANGE "status_change" //游戏状态，待机or游戏中
#define LED_CTRL "led_ctrl" //灯带控制
#define BTN_CTRL "btn_ctrl" //按键控制
#define LASER_CTRL "laser_ctrl" //激光发射器控制
#define LASER_REV_CTRL "laser_rev_ctrl" //激光接收器控制
#define MP3_CTRL "mp3_ctrl" //MP3控制（预留）
#define LIGHT_CTRL "light_ctrl" //指示灯控制（预留)
#define INIT_SCORE "init_score" //初始化分数配置

//--------------------------upload cmd----------------
#define UPLOAD_SCORE "upload_score" //按键信息上传
#define UPLOAD_REV "[UR]" //激光接收器信息上传
#define CONFIRM_BTN "confirm_btn" //按键接收反馈
#define CONFIRM_INIT_SCORE "confirm_init_score" //初始化信息反馈

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
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N2)
#define A_IP (192, 168, 1, 102)
#define A_ID "M-2-6-1-B-5-L"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N3)
#define A_IP (192, 168, 1, 103)
#define A_ID "M-3-6-1-A-10-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N4)
#define A_IP (192, 168, 1, 104)
#define A_ID "M-4-6-1-B-10-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N5)
#define A_IP (192, 168, 1, 105)
#define A_ID "M-5-6-1-A-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N6)
#define A_IP (192, 168, 1, 106)
#define A_ID "M-6-6-1-B-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 5 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N7)
#define A_IP (192, 168, 1, 107)
#define A_ID "M-5-6-2-B-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N8)
#define A_IP (192, 168, 1, 108)
#define A_ID "M-6-6-4-A-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N11)
#define A_IP (192, 168, 1, 111)
#define A_ID "M-8-6-1-B-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 5 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N12)
#define A_IP (192, 168, 1, 112)
#define A_ID "M-8-6-2-A-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N13)
#define A_IP (192, 168, 1, 113)
#define A_ID "M-8-5-2-B-5-L"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N14)
#define A_IP (192, 168, 1, 114)
#define A_ID "M-8-4-2-A-10-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N15)
#define A_IP (192, 168, 1, 115)
#define A_ID "M-8-3-2-B-5-R"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N16)
#define A_IP (192, 168, 1, 116)
#define A_ID "M-8-2-2-A-5-R"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N17)
#define A_IP (192, 168, 1, 117)
#define A_ID "M-8-1-2-B-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N18)
#define A_IP (192, 168, 1, 118)
#define A_ID "M-8-1-3-A-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N19)
#define A_IP (192, 168, 1, 119)
#define A_ID "M-7-1-3-B-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N20)
#define A_IP (192, 168, 1, 120)
#define A_ID "M-6-1-3-A-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N21)
#define A_IP (192, 168, 1, 121)
#define A_ID "M-5-1-3-B-5-R"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N22)
#define A_IP (192, 168, 1, 122)
#define A_ID "M-4-1-3-A-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N23)
#define A_IP (192, 168, 1, 123)
#define A_ID "M-3-1-2-A-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N24)
#define A_IP (192, 168, 1, 124)
#define A_ID "M-4-1-4-B-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N25)
#define A_IP (192, 168, 1, 125)
#define A_ID "M-3-1-3-B-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N26)
#define A_IP (192, 168, 1, 126)
#define A_ID "M-2-1-3-A-10-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N27)
#define A_IP (192, 168, 1, 127)
#define A_ID "M-1-1-3-A-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N28)
#define A_IP (192, 168, 1, 128)
#define A_ID "M-1-1-4-B-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 5 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N30)
#define A_IP (192, 168, 1, 130)
#define A_ID "M-1-3-4-A-5-L"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 5 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N31)
#define A_IP (192, 168, 1, 131)
#define A_ID "M-1-4-4-B-10-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N32)
#define A_IP (192, 168, 1, 132)
#define A_ID "M-1-5-4-A-5-L"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N33)
#define A_IP (192, 168, 1, 133)
#define A_ID "M-1-6-4-B-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N35)
#define A_IP (192, 168, 1, 135)
#define A_ID "M-2-5-4-B-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N37)
#define A_IP (192, 168, 1, 137)
#define A_ID "M-2-5-1-A-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N38)
#define A_IP (192, 168, 1, 138)
#define A_ID "M-2-6-3-B-5-R"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N41)
#define A_IP (192, 168, 1, 141)
#define A_ID "M-3-5-2-A-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N42)
#define A_IP (192, 168, 1, 142)
#define A_ID "M-4-5-4-B-5-R"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N43)
#define A_IP (192, 168, 1, 143)
#define A_ID "M-3-5-3-B-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N44)
#define A_IP (192, 168, 1, 144)
#define A_ID "M-3-4-1-A-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N47)
#define A_IP (192, 168, 1, 147)
#define A_ID "M-7-5-1-B-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N48)
#define A_IP (192, 168, 1, 148)
#define A_ID "M-7-6-3-A-10-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N49)
#define A_IP (192, 168, 1, 149)
#define A_ID "M-7-5-2-A-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N53)
#define A_IP (192, 168, 1, 153)
#define A_ID "M-5-5-4-A-10-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N54)
#define A_IP (192, 168, 1, 154)
#define A_ID "M-4-5-2-B-5-L"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N55)
#define A_IP (192, 168, 1, 155)
#define A_ID "M-5-4-4-B-5-L"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N56)
#define A_IP (192, 168, 1, 156)
#define A_ID "M-4-4-2-A-5-R"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N59)
#define A_IP (192, 168, 1, 159)
#define A_ID "M-7-2-2-B-5-L"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N60)
#define A_IP (192, 168, 1, 160)
#define A_ID "M-8-2-4-A-5-L"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N61)
#define A_IP (192, 168, 1, 161)
#define A_ID "M-7-3-2-A-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N62)
#define A_IP (192, 168, 1, 162)
#define A_ID "M-8-3-4-B-5-L"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N63)
#define A_IP (192, 168, 1, 163)
#define A_ID "M-7-4-3-A-10-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 5 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N64)
#define A_IP (192, 168, 1, 164)
#define A_ID "M-7-3-1-B-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N66)
#define A_IP (192, 168, 1, 166)
#define A_ID "M-6-1-2-B-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N67)
#define A_IP (192, 168, 1, 167)
#define A_ID "M-7-1-4-A-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N68)
#define A_IP (192, 168, 1, 168)
#define A_ID "M-7-2-4-B-5-R"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N69)
#define A_IP (192, 168, 1, 169)
#define A_ID "M-6-2-2-A-5-R"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N72)
#define A_IP (192, 168, 1, 172)
#define A_ID "M-5-2-3-A-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N74)
#define A_IP (192, 168, 1, 174)
#define A_ID "M-5-2-2-B-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N75)
#define A_IP (192, 168, 1, 175)
#define A_ID "M-6-2-4-A-5-L"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N76)
#define A_IP (192, 168, 1, 176)
#define A_ID "M-6-3-4-B-10-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N77)
#define A_IP (192, 168, 1, 177)
#define A_ID "M-5-3-2-A-10-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N78)
#define A_IP (192, 168, 1, 178)
#define A_ID "M-5-4-2-B-5-R"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N79)
#define A_IP (192, 168, 1, 179)
#define A_ID "M-6-4-4-A-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N80)
#define A_IP (192, 168, 1, 180)
#define A_ID "M-6-4-1-B-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 5 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N81)
#define A_IP (192, 168, 1, 181)
#define A_ID "M-6-5-3-A-10-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N83)
#define A_IP (192, 168, 1, 183)
#define A_ID "M-3-2-4-B-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N85)
#define A_IP (192, 168, 1, 185)
#define A_ID "M-3-2-1-A-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N86)
#define A_IP (192, 168, 1, 186)
#define A_ID "M-3-3-3-B-5-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N87)
#define A_IP (192, 168, 1, 187)
#define A_ID "M-4-2-1-B-10-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N88)
#define A_IP (192, 168, 1, 188)
#define A_ID "M-4-3-3-A-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N90)
#define A_IP (192, 168, 1, 190)
#define A_ID "M-4-3-4-B-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N91)
#define A_IP (192, 168, 1, 191)
#define A_ID "M-3-3-2-A-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N92)
#define A_IP (192, 168, 1, 192)
#define A_ID "M-4-4-4-A-5-L"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N93)
#define A_IP (192, 168, 1, 193)
#define A_ID "M-3-4-2-B-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N94)
#define A_IP (192, 168, 1, 194)
#define A_ID "M-2-2-4-A-5-L"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N95)
#define A_IP (192, 168, 1, 195)
#define A_ID "M-1-2-2-A-10-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N96)
#define A_IP (192, 168, 1, 196)
#define A_ID "M-2-3-4-B-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N97)
#define A_IP (192, 168, 1, 197)
#define A_ID "M-1-3-2-A-5-R"
#define M_REV_NUM 5 //主墙接收器数量
#define S_REV_NUM 5 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N98)
#define A_IP (192, 168, 1, 198)
#define A_ID "M-2-3-1-A-5-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N99)
#define A_IP (192, 168, 1, 199)
#define A_ID "M-2-4-3-B-10-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif
//-----------------------------not this code-------------------------
//-----------------------A3_B3-------------------------------
//#if defined (N34)
//#define A_IP (192, 168, 1, 134)
//#define A_ID "M-1-5-2-A-5-R"
//#define M_REV_NUM 5 //主墙接收器数量
//#define S_REV_NUM 10 //小墙接收器数量
//#define LASER_NUM 10 //激光发射器数量
//#endif
//
//#if defined (N50)
//#define A_IP (192, 168, 1, 150)
//#define A_ID "M-8-5-4-B-5-L"
//#define M_REV_NUM 5 //主墙接收器数量
//#define S_REV_NUM 10 //小墙接收器数量
//#define LASER_NUM 10 //激光发射器数量
//#endif
//
//#if defined (N73)
//#define A_IP (192, 168, 1, 173)
//#define A_ID "M-5-1-1-B-5-L"
//#define M_REV_NUM 5 //主墙接收器数量
//#define S_REV_NUM 10 //小墙接收器数量
//#define LASER_NUM 10 //激光发射器数量
//#endif
//
//#if defined (N84)
//#define A_IP (192, 168, 1, 184)
//#define A_ID "M-2-2-2-A-5-R"
//#define M_REV_NUM 5 //主墙接收器数量
//#define S_REV_NUM 10 //小墙接收器数量
//#define LASER_NUM 10 //激光发射器数量
//#endif

//-----------------------specile-------------------------------

#if defined (N29)//特殊门：入口
#define A_IP (192, 168, 1, 129)
#define A_ID "M-1-2-4-A-0-R"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

#if defined (N10) //消防门
#define A_IP (192, 168, 1, 110)
#define A_ID "M-7-6-1-A-0-L"
#define M_REV_NUM 0 //主墙接收器数量
#define S_REV_NUM 0 //小墙接收器数量
#define LASER_NUM 10 //激光发射器数量
#endif

//-----------------------------s wall--------------------------
//#if defined (N9)
//#define A_IP (192, 168, 1, 109)
//#define A_ID "S-5-5"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 10 //小墙接收器数量
//#endif
//
//#if defined (N36)
//#define A_IP (192, 168, 1, 136)
//#define A_ID "S-1-4"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 10 //小墙接收器数量
//#endif
//
//#if defined (N39)
//#define A_IP (192, 168, 1, 139)
//#define A_ID "S-2-5"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 15 //小墙接收器数量
//#endif
//
//#if defined (N40)
//#define A_IP (192, 168, 1, 140)
//#define A_ID "S-3-5"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 10 //小墙接收器数量
//#endif
//
//#if defined (N45)
//#define A_IP (192, 168, 1, 145)
//#define A_ID "S-2-4"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 15 //小墙接收器数量
//#endif
//
//#if defined (N46)
//#define A_IP (192, 168, 1, 146)
//#define A_ID "S-6-5"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 15 //小墙接收器数量
//#endif
//
//#if defined (N51)
//#define A_IP (192, 168, 1, 151)
//#define A_ID "S-7-4"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 10 //小墙接收器数量
//#endif
//
//#if defined (N52)
//#define A_IP (192, 168, 1, 152)
//#define A_ID "S-4-5L"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 15 //小墙接收器数量
//#endif
//
//#if defined (N57)
//#define A_IP (192, 168, 1, 157)
//#define A_ID "S-4-3"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 15 //小墙接收器数量
//#endif
//
//#if defined (N58)
//#define A_IP (192, 168, 1, 158)
//#define A_ID "S-7-1"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 20 //小墙接收器数量
//#endif
//
//#if defined (N65)
//#define A_IP (192, 168, 1, 165)
//#define A_ID "S-6-3"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 15 //小墙接收器数量
//#endif
//
//#if defined (N70)
//#define A_IP (192, 168, 1, 170)
//#define A_ID "S-6-2"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 15 //小墙接收器数量
//#endif
//
//
//#if defined (N71)
//#define A_IP (192, 168, 1, 171)
//#define A_ID "S-4-1"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 15 //小墙接收器数量
//#endif
//
//#if defined (N82)
//#define A_IP (192, 168, 1, 182)
//#define A_ID "S-6-4"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 15 //小墙接收器数量
//#endif
//
//#if defined (N89)
//#define A_IP (192, 168, 1, 189)
//#define A_ID "S-4-2"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 15 //小墙接收器数量
//#endif
//
//#if defined (N100)
//#define A_IP (192, 168, 1, 200)
//#define A_ID "S-2-3"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 20 //小墙接收器数量
//#endif
//
//#if defined (N109)
//#define A_IP (192, 168, 1, 209)
//#define A_ID "S-3-1"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 15 //小墙接收器数量
//#endif
//
//#if defined (N110)
//#define A_IP (192, 168, 1, 210)
//#define A_ID "S-2-1"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 15 //小墙接收器数量
//#endif
//
//#if defined (N111)
//#define A_IP (192, 168, 1, 211)
//#define A_ID "S-1-1"
//#define M_REV_NUM 0 //主墙接收器数量
//#define S_REV_NUM 15 //小墙接收器数量
//#endif

#endif 

