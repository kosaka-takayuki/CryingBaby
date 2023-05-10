#pragma once 
#ifndef FILE_FUNCTION_H
#define FILE_FUNCTION_H

#include <M5Core2.h>
//#include <WiFi.h>               //Wifi関係

#include "Global/Setting.h"    	//共通変数
#include "Global/Function.h"  	//共通関数群
#include "Global/Enum.h"    	//共通関数群
//#include "Device/File_Function.h"


#include "File/File_Function.h"	//ファイル読込

    /////////////////////////////////////////////////////
    //関数群
    /////////////////////////////////////////////////////

	extern boolean Load_Threshold_File();
	extern boolean Save_Threshold_File();
	
	extern unsigned long Get_FileSize(String filename);		//ファイルサイズの取得
	extern boolean Load_Interval_Check_Files();  				    //設定ファイルの読み込み
	extern boolean Load_Interval_File(String filename);		//単体のファイル読み込み

	extern void Save_Interval_File(String filename);


	extern boolean 	Load_Preferences_File(String filename);		//単体のファイル読み込み
	extern void		Save_Preferences_File(String filename);		//単体のファイル読み込み

/*
	extern boolean Load_CryIntervalFile();  				    //設定ファイルの読み込み
	extern void Save_AccessPoint(String data);
	extern void Save_CryIntervalFile(String filename);			//ファイル保存
	extern void Save_Threshold(String data);
	extern boolean CryInterval_FileOpen(String filename);
	extern unsigned long CryInterval_FileSize(String filename);
*/



#endif
