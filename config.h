#ifndef CONFIG_H
#define CONFIG_H

#define LED_LENG6 20
#define LED_LENG7 60
#define PIN6 6
#define PIN7 7
#define MILLISECOND 1

//--------------------------rev cmd-----------------
#define MODE_CHANGE "mode_change" //游戏模式切换
#define STATUS_CHANGE "status_change" //阶段切换
#define LED_CTRL "led_ctrl" //灯带控制
#define KEY_CTRL "key_ctrl" //按键控制
#define LASER_CTRL "laser_ctrl" //激光发射器控制
#define LASER_REV_CTRL "laser_rev_ctrl" //激光接收器控制
#define MP3_CTRL "mp3_ctrl" //MP3控制（预留）
#define LIGHT_CTRL "light_ctrl" //指示灯控制（预留)

//--------------------------upload cmd----------------
#define BUTTON_INFO_UPLOAD "button_info_upload" //按键信息上传
#define REV_INFO_UPLOAD "rev_info_upload" //激光接收器信息上传
#define DEVICE_INFO_UPLOAD "device_info_upload" //设备信息上传





#endif 