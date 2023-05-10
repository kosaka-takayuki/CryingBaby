#include "CryTASK/CryTASK.h"
#include "Global/Function.h"


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Initialize
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void CryTASK::Initialize(int _Name_No, String _Name, unsigned long _IntervalTime_Set, unsigned long  _IntervalTime_Random , int _Status,  int _Priority, unsigned long _RunTime_ElapsedOver){

			this->Name_No				= _Name_No;
			this->Name 					= _Name;
			this->IntervalTime_Set		= _IntervalTime_Set;		//標準インターバル時間
			this->IntervalTime_Random	= _IntervalTime_Random;		//インターバル時間の乱数　+- 

			this->Status 				= _Status;

			this->MoodTotalCount 		= 0;

			this->ElapsedTime 			= 0;
			this->RemainingTime 		= 0;

			this->Priority				= _Priority;       //優先順位　　0：最優先     10-15:  通常運営

			for(int i=0;i<5;i++){
				this->Procedure[i] 			=-1; 		   //手順番号
			}

			this->isFirtstTime 			= false;			//初回実行の有無

//			this->RunTime_Start		=0;//実行されてからの時間計測
			this->RunTime_Elapsed 	=0;//実行されてからの経過時間

			this->RunTime_ElapsedOver = _RunTime_ElapsedOver;	//実行中のTimeOUT時間
			
			this->Enable 			= true;


		}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SetLED_Loop
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void CryTASK::SetLED_Loop(TimeLED *start , TimeLED *end ){
			this->LED_START = *start;
			this->LED_END	= *end;
		}





	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MoodReset
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void CryTASK::MoodReset(){
			
//			Serial.println( "Mood CLS --------------------- \t "+ this->Name);
		
			this->MoodTime_Set = millis();	//時間を記録
			this->MoodTime_TPMSet = millis();	//時間を記録
		}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MoodTPMReset
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void CryTASK::MoodTPMReset(){

//			Serial.println( "Mood TPM RESET \t "+ this->Name);

//			Serial.println( "MoodTPMReset\t "+ this->Name);
			this->MoodTime_TPMSet = millis();	//時間を記録
		}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MoodCount
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void CryTASK::MoodCount(int SafeTime, int TPMTime){

//			Serial.println( "Mood Count \t "+ this->Name);
			
			this->MoodTotalCount  =0;
			this->MoodTotalCount  = maps( millis() - this->MoodTime_Set,	 0, 1000*SafeTime, 0, 80);
			this->MoodTotalCount += maps( millis() - this->MoodTime_TPMSet,	 0, 1000*TPMTime,  0, 20);

			//ハックモード
			if(Device.isMoodHack == true){
				this->MoodTotalCount =100;
			}

//			Serial.println( "MoodCount\t "+ this->Name +"\t" + maps( millis() - this->MoodTime_Set,	 0,1000*20,0,80) +"\t" + maps( millis() - this->MoodTime_TPMSet,	 0,1000*20,0,20));
	
		}
