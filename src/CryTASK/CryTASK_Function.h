#pragma once 
#ifndef CRYTASK_FUNCTON_H
#define CRYTASK_FUNCTON_H

#include <M5Core2.h>
#include "Global/Setting.h"

	extern void TASK_Sort( );				//ソート
//	extern void TASK_DrawYFunction( );
	
	extern void SetTASK_Status_Priority( int no, int _status, int _priority, boolean _isrun);
	extern void TASK_ForcedExecution( int _no);
	extern void TASK_MoodReset( int _no );
	extern void TASK_ReStart( int _no);
	extern void TASK_Wait( int _no );



	extern void SetTASK_SET(int _no , int _IntervalTime,	int _ElapsedTime,	int _IntervalTime_Set, int _IntervalTime_Random, int _RunTime_Elapsed, int _RunTime_ElapsedOver, int _Status, int _Priority);

	extern void TASK_Run( );
	extern void TASK_End( int _no );

	void SetTASK_Status_Procedure(int _no , int _procedure_no, int _procedure);



	int GetTASK_Status(int _no);
	int GetNo_TASK_Mood(int _no );
	int GetTASK_RunTASK_No();

	String GetStatus_Name(int _no);

	extern void SendTASK_Sort( );			//送信用





#endif
