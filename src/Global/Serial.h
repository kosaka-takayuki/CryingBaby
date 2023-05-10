#pragma once 
#ifndef SERIAL_H
#define SERIAL_H

#include <M5Core2.h>
#include "Global/Setting.h"   //共通変数
#include "Global/Enum.h"      //共通変数
#include "Global/Function.h"      //共通変数
#include "Draw/Draw_Function.h"

#include "File/File_Function.h"
#include "CryTASK/CryTASK_Function.h"

    /////////////////////////////////////////////////////
    //関数群
    /////////////////////////////////////////////////////
    extern void SerialRead();

    extern void SendTASK();
    extern void SendDATA();


	extern int RetunValue01( String  data , int n );
	extern int RetunValue02( String  data , int n );
	extern int RetunValue03( String  data , int n );
	extern int RetunValue04( String  data , int n );

#endif
