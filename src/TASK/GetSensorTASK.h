#pragma once 
#ifndef GETSENSOR_H
#define GETSENSOR_H

#include <M5Core2.h>

#include "Global/Setting.h"    		//共通変数
#include "Global/Function.h"    		//共通関数群
#include "Device/Device_Function.h"    	//共通関数群
#include "Global/Enum.h"				//共通変数

#include "TASK/CryTASK_Judgement.h"

//#include "CryTASK/CryTASK_Function.h"
    /////////////////////////////////////////////////////
    //関数群
    /////////////////////////////////////////////////////
	extern void GetSensorTASK(void* arg);



#endif
