#pragma once 
#ifndef DRARFUNCTION_H
#define DRARFUNCTION_H

#include <M5Core2.h>

#include "Global/Setting.h"    	//共通変数
#include "Global/Function.h"    	//共通関数群
#include "Global/Enum.h"				//共通変数

#include "Device/Device_Function.h"


    /////////////////////////////////////////////////////
    //関数群
    /////////////////////////////////////////////////////

	extern void DrawTitle(		String msg, int _dy,unsigned int BreakTime, uint32_t _backcolor);
	extern void DrawTitle(		String msg, unsigned int BreakTime, int _Status);


	extern void DrawBox(		String msg, int _dy,unsigned int BreakTime);					//枠の表示
	extern void DrawBoxResult( 	String msg, int _dy,unsigned int BreakTime, boolean isTF);		//結果によって異なる
    extern void DrawString(     String msg, int _dx, int _dy, int _font, textdatum_t _position);

	extern void DrawBackGround( int no,int dy,uint32_t color);
	extern void DrawBackGround( int no,int dy,uint32_t colorA,uint32_t colorB,boolean isActive);

	extern void DrawDataGauge(int _dx,int _dy, int _data ,uint32_t color_gauge);
	extern void DrawDataGauge(int _dx,int _dy, int _data ,uint32_t color_gaugeA, uint32_t color_gaugeB, boolean isActice );

	extern boolean DrawFPS( uint32_t _backcolor);


#endif
