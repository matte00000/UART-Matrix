/*****************
MdLep32X32.cpp

******************/

#include"MdLep32X32.h"
#include"Arduino.h"

#define  LEP_CMD_NO_OPERATION 	0  //  0-无操作
#define  LEP_CMD_SCREEN_HIDE		1  //  1-隐藏屏幕
#define  LEP_CMD_SCREEN_INVERT	2  //  2-反显屏幕
#define  LEP_CMD_SCREEN_MIRROR 	3  //  3-镜像屏幕
#define  LEP_CMD_SCREEN_TURN		4  //  4-翻转屏幕
#define  LEP_CMD_SCREEN_PIXEL		5  //  5-像素操作
#define  LEP_CMD_SCREEN_FILL		6  //  6-屏幕填充
#define  LEP_CMD_SCREEN_LOAD		7  //  7-全屏载入
#define  LEP_CMD_SCREEN_ICON		8  //  8-图标显示
#define  LEP_CMD_PRINT_ASCII		9  //  9-显示字符
//保留
//保留
#define  LEP_CMD_BMP_OPTION		 12  // 12-开启bmp

MdLep32X32::MdLep32X32(byte sn0,byte sn1,byte sn2,byte sn3)
{
	 cmdStr[1] = 0;//长度由后续操作填入
   cmdStr[1] = sn0;//设备号第一字节
   cmdStr[2] = sn1;//设备号第二字节
   cmdStr[3] = sn2;//设备号第三字节
   cmdStr[4] = sn3;//设备号第四字节
}

MdLep32X32::~MdLep32X32()
{
   cmdStr[1] = 0x00;//未知设备号
   cmdStr[2] = 0x00;//未知设备号
   cmdStr[3] = 0x00;//未知设备号
   cmdStr[4] = 0x00;//未知设备号
} 



void MdLep32X32::setHidden(byte flag)
{
  cmdStr[5] = LEP_CMD_SCREEN_HIDE;//设置隐藏标志位
	cmdStr[6] = flag;
	cmdStr[0] = DEVSN_OCTS + 1 + 1; //4字节设备号，1字节命令号，1字节参数，下同
	Serial.write(cmdStr,1 + cmdStr[0]);
}   

void MdLep32X32::setInvert(byte flag)
{
  cmdStr[5] = LEP_CMD_SCREEN_INVERT;//设置反显标志位
	cmdStr[6] = flag;
	cmdStr[0] = DEVSN_OCTS + 1 + 1;
	Serial.write(cmdStr,1 + cmdStr[0]);
}   

void MdLep32X32::setMirror(byte flag)
{
  cmdStr[5] = LEP_CMD_SCREEN_MIRROR;//设置镜像标志位
	cmdStr[6] = flag;
	cmdStr[0] = DEVSN_OCTS + 1 + 1;
	Serial.write(cmdStr,1 + cmdStr[0]);
}   

void MdLep32X32::setTurn(byte flag)
{
  cmdStr[5] = LEP_CMD_SCREEN_TURN;//设置翻转标志位
	cmdStr[6] = flag;
	cmdStr[0] = DEVSN_OCTS + 1 + 1;
	Serial.write(cmdStr,1 + cmdStr[0]);
}
   
void MdLep32X32::displayOn()
{
  setHidden(OPTION_ON);
}

void MdLep32X32::displayOff()
{
  setHidden(OPTION_OFF);
}

void MdLep32X32::invertOn()
{
  setInvert(OPTION_ON);
}

void MdLep32X32::invertOff()
{
  setInvert(OPTION_OFF);
}

void MdLep32X32::mirrorOn()
{
  setMirror(OPTION_ON);
}

void MdLep32X32::mirrorOff()
{
  setMirror(OPTION_OFF);
}

void MdLep32X32::turnOn()
{
  setTurn(OPTION_ON);
}

void MdLep32X32::turnOff()
{
  setTurn(OPTION_OFF);
}

void MdLep32X32::fillGram(byte val)
{
  cmdStr[5] = LEP_CMD_SCREEN_FILL;//填充屏幕
	cmdStr[6] = val;
	cmdStr[0] = DEVSN_OCTS + 1 + 1;
	Serial.write(cmdStr,1 + cmdStr[0]);	
} 

void MdLep32X32::setPixel(byte x, byte y,byte flag)
{
  cmdStr[5] = LEP_CMD_SCREEN_PIXEL;//像素操作
	cmdStr[6] = x;
	cmdStr[7] = y;
	cmdStr[8] = flag;
	cmdStr[0] = DEVSN_OCTS + 1 + 3;//4字节设备号，1字节命令号，3字节参数
	Serial.write(cmdStr,1 + cmdStr[0]);		
}

void MdLep32X32::drawPixel(byte x, byte y)
{
	setPixel(x, y, OPTION_ON);
}

void MdLep32X32::clearPixel(byte x, byte y)
{
	setPixel(x, y, OPTION_OFF);
}

void MdLep32X32::showASCII(byte x, byte y,byte ascii)
{
  cmdStr[5] = LEP_CMD_PRINT_ASCII;//显示字符
	cmdStr[6] = x;
	cmdStr[7] = y;
	cmdStr[8] = ascii;
	cmdStr[0] = DEVSN_OCTS + 1 + 3;//4字节设备号，1字节命令号，3字节参数;
	Serial.write(cmdStr,1 + cmdStr[0]);		
}

void MdLep32X32::loadScreen(byte logo[])
{
	cmdStr[5] = LEP_CMD_SCREEN_LOAD;//全屏载入
	for(byte i=0; i<MAX_PARAM_LEN;i++)
	{
		cmdStr[6+i] = logo[i];
	}
	cmdStr[0] = DEVSN_OCTS + 1 + MAX_PARAM_LEN;//4字节设备号，1字节命令号，后跟全屏数据区;
	Serial.write(cmdStr,1 + cmdStr[0]);	
}

void MdLep32X32::showIcon(byte x, byte y, byte w, byte h, byte len, byte icon[])
{
  cmdStr[5] = LEP_CMD_SCREEN_ICON;//显示字符
	cmdStr[6] = x;
	cmdStr[7] = y;
	cmdStr[8] = w;
	cmdStr[9] = h;
  for(byte i=0; i<len;i++)
	{
		cmdStr[9+i] = icon[i];
	}
	cmdStr[0] = DEVSN_OCTS + 1 + 4 + len;//4字节设备号，1字节命令号，4字节参数，后跟数据区;
	Serial.write(cmdStr,1 + cmdStr[0]);		
}