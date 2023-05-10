#pragma once 
#ifndef DATASTOCK_H
#define DATASTOCK_H

#include <M5Core2.h>
#include "Device/Sensor/Tapping.h"

	//********************************
	//DataStock class
	//********************************
	class DataStock{
		public:

			int   AVG_MAX;		//平均数

			int   Count;		//カウント用
			float *Datas;		//データ格納用
			float Data;			//出力データ
			float Data_B;		//過去のデータ
			float Sum;			//合計

			float Data_R;		//生データ


			float DataMAX;		//データ取得時の最大値を記録　加速度センサのみ利用

			int  Threshold_min;	//最小値
			int  Threshold_max;	//最大値

			unsigned long 	ActiveTime;

			float 	Data2;		//IMUの生値　TPMを検出用




			/////////////////////////////////////
			//Tapping用
			/////////////////////////////////////
			TappingInfo Tapping;		//TPM
			int 	TPM =0;

			/////////////////////////////////////
			// 温度
			/////////////////////////////////////
			float Tempture =0;


			/////////////////////////////////////////////////////
			//関数群
			/////////////////////////////////////////////////////
			DataStock();    //コンストラクタ
			void Initialize(int _avg_max , int min, int max, float TPM_min, float TPM_max);
			void AddData(float val);		//値の追加
			void Average();				//平均
			float GetTempture();			//温度出力

	}; 

#endif
