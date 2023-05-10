#pragma once 
#ifndef FUNCTION_H
#define FUNCTION_H

#include <M5Core2.h>


#include "Global/Setting.h" //共通変数

//#include "TASK/FileSaveTASK.h"


    /////////////////////////////////////////////////////
    //関数群
    /////////////////////////////////////////////////////
    extern long maps(long x, long in_min, long in_max, long out_min, long out_max);         ///map関数
    extern long maps_Between(long x, long Ain_min, long Ain_max, long Aout_min, long Aout_max, long Bin_min, long Bin_max, long Bout_min, long Bout_max);

  	extern void OutPutLogs(int _code ,int _tabLevel, String _msg);                           //OutputLogs関数
	extern int split(String data, char delimiter, String *dst);
	extern void SaveLogs();

    extern void FPS(int _no);

	extern void SwipeScreen();

	extern int 	TimeToSting(int no, int Stime);

	extern String TimeToStrings( unsigned long _time );

	extern String NoToTaskStrings( int _no );

	extern String NoToMP3FolderString( int _no );

	extern void ScreenChangeNo( int _no );

/*
	extern void OutPutLogs(int _code ,int _tabLevel, String _msg);
	extern void SaveLogs();
    */
#endif
