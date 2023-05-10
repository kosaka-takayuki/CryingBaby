
#pragma once 
#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <M5Core2.h>
#include "Global/Enum.h"    	//共通変数
//#include "Gloabal/Function.h"    	//共通関数群
#include "Device/Sensor/DataStock.h"

	//********************************
    //DataInfo
    //********************************
	struct SensorDataInfo{
				float 	 Data;				//データ
				float	 Data_Old =-100;	//過去のデータ

				float	 Min;				//最小値
				float	 Max;				//最大値


				String  SData="";				//データの文字列
				String  SData_Old="";			//データの文字列 過去の値

				boolean isActive =false;	//閾値を超えたかどうか
				boolean	isRun =false;		//実行したかどうか？

				unsigned long GetTime;		//時間の取得　インターバル時間




//			String  MSG="";



				boolean  isHack =false;		//Hackされているかどうかの有無
				float 	 HackData =0;		//Hackデータ


				boolean  		 isTime =false;	//閾値を超えたかどうか
				unsigned long    TimeSet;	//開始時間を記録   	




	};


	//********************************
	//SensorData class
	//********************************
	class SensorData{
		public:

			DataStock 	*SensorTMP;	//センサーデータ
			
			SensorDataInfo Battery;
			SensorDataInfo Microphone;
			SensorDataInfo Eye;
			SensorDataInfo Diapers;
			SensorDataInfo Mouth;
			SensorDataInfo Temperature;
			SensorDataInfo Level;
			SensorDataInfo IMU;
			SensorDataInfo TPM;
			SensorDataInfo Position;

			SensorDataInfo Level_Min;


			boolean isRTC =false;


			/////////////////////////////////////////////////////
			//関数群
			/////////////////////////////////////////////////////
			SensorData();    //コンストラクタ
			void Initialize();  //Initialize
			boolean JudgeThreshold(SensorDataInfo data, int TC);
			


	};  
#endif
	
