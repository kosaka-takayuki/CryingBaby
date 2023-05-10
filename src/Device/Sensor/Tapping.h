#pragma once 
#ifndef TAPPING_H
#define TAPPING_H

#include <M5Core2.h>
	//********************************
	//Device class
	//********************************
	class TappingInfo{
		public:
		    bool 			isFlag;         	//閾値を超えているかのフラグ
			float 			ThresholdMax;		//閾値 最大
			float 			ThresholdMin;		//閾値 最小
			unsigned long 	Time_Elapsed_S;		//STRT時間
			unsigned long 	Time_Elapsed_B;		//Back時間
			float         	Datas[5];   		//データ格納用
			int           	Counter; 			//カウント用
		    int  	        TPM;                //TPM
		    int     	    TPM_Tmp;            //TPM テンプ

			/////////////////////////////////////////////////////
			//関数群
			/////////////////////////////////////////////////////
			TappingInfo();    //コンストラクタ
			void Initialize(float min , float max);
			int AddData( float val );
	};  

#endif
