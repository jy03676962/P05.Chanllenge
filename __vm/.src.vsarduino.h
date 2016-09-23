/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Mega 2560 or Mega ADK, Platform=avr, Package=arduino
*/

#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
#define __AVR_ATmega2560__
#define ARDUINO 106
#define ARDUINO_MAIN
#define __AVR__
#define __avr__
#define F_CPU 16000000L
#define __cplusplus 201103L
#define GCC_VERSION 40302
#define ARDUINO_ARCH_AVR
#define ARDUINO_AVR_MEGA2560
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__
#define __AVR__
typedef void *__builtin_va_list;
#define __builtin_va_start
#define __builtin_va_end
//#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int

#define NEW_H
            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}
#include <arduino.h>
#include <pins_arduino.h> 
#undef F
#define F(string_literal) ((const PROGMEM char *)(string_literal))
#undef PSTR
#define PSTR(string_literal) ((const PROGMEM char *)(string_literal))
#undef cli
#define cli()
#define pgm_read_byte(address_short)
#define pgm_read_word(address_short)
#define pgm_read_word2(address_short)
#define digitalPinToPort(P)
#define digitalPinToBitMask(P) 
#define digitalPinToTimer(P)
#define analogInPinToBit(P)
#define portOutputRegister(P)
#define portInputRegister(P)
#define portModeRegister(P)
#include <..\src\P05.Chanllenge.ino>
#include <..\src\Cmd.cpp>
#include <..\src\Cmd.h>
#include <..\src\CmdBtnCtrl.cpp>
#include <..\src\CmdBtnCtrl.h>
#include <..\src\CmdGameMode.cpp>
#include <..\src\CmdGameMode.h>
#include <..\src\CmdInitScore.cpp>
#include <..\src\CmdInitScore.h>
#include <..\src\CmdLaserCtrl.cpp>
#include <..\src\CmdLaserCtrl.h>
#include <..\src\CmdLedCtrl.cpp>
#include <..\src\CmdLedCtrl.h>
#include <..\src\CmdLightCtrl.cpp>
#include <..\src\CmdLightCtrl.h>
#include <..\src\CmdMp3Ctrl.cpp>
#include <..\src\CmdMp3Ctrl.h>
#include <..\src\Color.cpp>
#include <..\src\Color.h>
#include <..\src\LaserParseContent.cpp>
#include <..\src\LaserParseContent.h>
#include <..\src\Led.cpp>
#include <..\src\Led.h>
#include <..\src\LedParseContent.cpp>
#include <..\src\LedParseContent.h>
#include <..\src\ScoreParseContent.cpp>
#include <..\src\ScoreParseContent.h>
#include <..\src\Tools.cpp>
#include <..\src\Tools.h>
#include <..\src\config.h>
#endif