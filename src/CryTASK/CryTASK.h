#pragma once 
#ifndef CRYTASK_H
#define CRYTASK_H

#include <M5Core2.h>
#include "Global/Enum.h"

#include <Adafruit_NeoPixel.h>  //LEDテープ制御

#include "CryTASK/TimeLED.h"

/*
	String 	GuideMSG =  "";
					GuideMSG += "Name\t";
					GuideMSG += "IntervalTime\t";
					GuideMSG += "ElapsedTime\t";
					GuideMSG += "IntervalTime_Random\t";
					GuideMSG += "RunTime_Elapsed\t";
					GuideMSG += "ElapsedTime\t";
					GuideMSG += "RunTime_ElapsedOver\t";
					GuideMSG += "Status\t";
					GuideMSG += "Priority\n";
		OutPutLogs(LogCode_Info , 7,"+-- "+GuideMSG);
*/
	//********************************
	//CryTASK
	//********************************
	class CryTASK{
		public:
			int 	Name_No;						//TASKの識別番号
			String  Name;							//TASKの名前
			unsigned long	IntervalTime_Set;		//標準インターバル時間			規定値
			unsigned long 	IntervalTime_Random;	//インターバル時間の乱数　+- 　

			unsigned long   IntervalTime;   		//インターバル時間　IntervalTime_Set IntervalTime_Random	毎秒変化しない　
			unsigned long   ElapsedTime;    		//経過時間　秒   毎秒変化
			unsigned long   ElapsedTime_OLD;    	//経過時間　秒   毎秒変化
			unsigned long   RemainingTime;  		//残り時間　秒　 毎秒変化

		
			int		Status;			//状態
									//		TASK_Status_Count			=  0,		//0: カウント在り
									//		TASK_Status_Wait			=  1,		//1: 待ち状態
									//		TASK_Status_Run				=  2,		//2:実行中
									//		TASK_Status_Non				=  3,		//3:非実行
									//		TASK_Status_RunSuspend		=  4,		//4:実行中に割り込み処理があり停止している状態



			int     Priority;       //優先順位　　0：最優先     10-15:  通常運営
			int     Procedure[5];   //手順番号

			boolean isDraw;			//描写するかどうか

			int 	DrawY;			//Y軸
			int 	DrawY_OLD;
			
			int		DrawX;


			boolean Enable;	//有効

			///////////////////////////////////////////////////////////////////////
			//機嫌
			//機嫌がよくなる条件
			//　1.姿勢状態が良い					20  20秒　時間経過とともに0～20点　30秒
			//  2.振動がない						20  20秒　時間経過とともに0～20点
			//  3.音がうるさくない					20  20秒　時間経過とともに0～20点
			//  4.急激な明るさ変化がない			20  20秒　時間経過とともに0～20点
			//  5.トントンしてもらえる	　40～ 120 	20  20秒　時間経過とともに0～20点
			///////////////////////////////////////////////////////////////////////

			int 			MoodTotalCount;		//機嫌 0～100まで推移 100で抜ける
			unsigned long 	MoodTime_Set;		//開始時間	
			unsigned long 	MoodTime_TPMSet;	//開始時間	

			boolean			isAction =false;	//ある条件が満たされたかどうか？
			unsigned long 	ActionTime_Set;		//開始時間	
			
			

//			boolean			 	isMoodStart;	//機嫌開始
//			unsigned long     	MoodTime;		//機嫌
//			int 				MoodCount;		//機嫌

			////////////////////////////////////////////////////////////////////////////////////////
			// 実行中の処理
			////////////////////////////////////////////////////////////////////////////////////////
//			boolean isRun;					//実行の有無
			boolean isFirtstTime;			//初回のみ実行の有無

			unsigned long 	RunTime_Start;		//実行されてからの経過時間
			unsigned long 	RunTime_Elapsed;		//実行されてからの経過時間
			unsigned long 	RunTime_RemainingTime;		//実行されてからの残り時間  //残り時間　秒　 毎秒変化
			unsigned long 	RunTime_RemainingTime_OLD;		//実行されてからの残り時間  //残り時間　秒　 毎秒変化
			unsigned long	RunTime_ElapsedOver;	//実行されてから放置したときにリセットする時間　秒

			TimeLED LED_START;
			TimeLED LED_END;


			/////////////////////////////////////////////////////
			//関数群
			/////////////////////////////////////////////////////
		//	CryTASK();    //コンストラクタ
			void Initialize(int _Name_No,String _Name, unsigned long _IntervalTime_Set, unsigned long  _IntervalTime_Random , int _Status,  int _Priority, unsigned long _RunTime_ElapsedOver);
			void SetLED_Loop(TimeLED *start , TimeLED *end );

			void MoodReset();
			void MoodCount(int SafeTime, int TPMTime);
			void MoodTPMReset();



	}; 



#endif
