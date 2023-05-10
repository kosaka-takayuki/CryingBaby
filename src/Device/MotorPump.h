
#pragma once 
#ifndef MOTORPUMP_H
#define MOTORPUMP_H

#include <M5Core2.h>

#include "Global/Enum.h"    	//共通関数群
#include "Global/PCA9554.h"



	//********************************
	//SensorData class
	//********************************
	class MotorPump{
		public:

			String Name;

			byte Adress;		//アドレス
			int  Speed;			//速度
			int  Speed_Old=-1;	//箱の速度
			

			int  isBatteryStop = false;

			float Ratio;			//比率　0-100

			/////////////////////////////////////////////////////
			//関数群
			/////////////////////////////////////////////////////
			MotorPump();    //コンストラクタ
			void Initialize(String _name, byte _adress);  //Initialize
			void SetSpeed(int _speed);

			void Run(bool _isUSB);
//			void Run(PCA9554 &exp );
			void MotorWrite(byte pwm, byte ctrl);
			int MotoroRead();

	};  
#endif
