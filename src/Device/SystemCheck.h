#pragma once 
#ifndef SYSTEMCHECK_H
#define SYSTEMCHECK_H

#include <M5Core2.h>
//#include <WiFi.h>               //Wifi関係

#include "Global/Setting.h"    	//共通変数
#include "Global/Function.h"    	//共通関数群
#include "DFPlayer/Mp3Notify.h"
#include "Device/Device_Function.h"

#include "File/File_Function.h"

#include "Draw/Draw_Function.h"

#include <EEPROM.h>
#include "CryTASK/CryTASK_Function.h"


    /////////////////////////////////////////////////////
    //関数群
    /////////////////////////////////////////////////////
	extern void SystemCheck();


#endif
