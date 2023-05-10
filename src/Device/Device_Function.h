#pragma once 
#ifndef DEVICE_FUNCTION_H
#define DEVICE_FUNCTION_H

#include <M5Core2.h>

//#include <WiFi.h>                    //Wifi関係
//#include <WiFiMulti.h>               //Wifi関係


#include "Global/Setting.h"          //共通変数 
#include "Global/Enum.h"            //共通変数
#include "Global/Function.h"       	//共通関数群


    /////////////////////////////////////////////////////
    //関数群
    /////////////////////////////////////////////////////
	extern void GetBattery();								//RTC接続
   	extern void SetTapeLEDs(int _Br, int _r, int _g,int _b); //LED設定
	extern void GetDFPlayer(void* arg);  					//DFPlayer接続 TASK実行

    extern void DrawTimeGauge(int _dx,int _dy, int _dw, int dh,  int _count , unsigned int BreakTime,int Type_No);

	extern int	GetSensorReadMux( int _channel);
	extern void GetM5Decice();								//IMU

	extern void MP3_KingLoopPlay( int King , float gain);	//MP3再生

	extern String GetStatus(int no);
	extern void SetTapeLEDsLoop( int no);

	extern void getHigh12SectionValue(void);
	extern void getLow8SectionValue(void);

	extern void GetWaterSensor();
	

#endif
