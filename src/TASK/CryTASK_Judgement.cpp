#include "TASK/CryTASK_Judgement.h"

	//////////////////////////////////////////////////////////////
	//CryTASK_Judgement
	//////////////////////////////////////////////////////////////
	void CryTASK_Judgement(){
		////////////////////////////////////////////////////////////////////////////////////////
		//バッテリーが閾値を超えたら
		////////////////////////////////////////////////////////////////////////////////////////
		if( Device.Sensor.Battery.isActive == true && Device.Sensor.Battery.isRun ==false){
			Device.Sensor.Battery.isRun = true;
			OutPutLogs(LogCode_Action,0, "+-- Judgement,Battery,:\t Now:"+ String(Device.Sensor.Battery.Min,2)+"%  <= Limit min:" + String(Device.Sensor.Battery.Data,1)+ "%");     //Log出力
		}

		////////////////////////////////////////////////////////////////////////////////////////
		//Diapersが閾値を超えたら
		////////////////////////////////////////////////////////////////////////////////////////
		if( Device.Sensor.Diapers.isActive == true && Device.Sensor.Diapers.isRun ==false ){
			Device.Sensor.Diapers.isRun = true;
			OutPutLogs(LogCode_Action,0, "+-- Judgement,Diapers,\t Now:"+ String(Device.Sensor.Diapers.Data)+"  >= Limit max:" + String(Device.Sensor.Diapers.Max));     //Log出力
		}

		////////////////////////////////////////////////////////////////////////////////////////
		//Mouthが閾値を超えたら
		////////////////////////////////////////////////////////////////////////////////////////
		if( Device.Sensor.Mouth.isActive == true  && Device.Sensor.Mouth.isRun ==false ){
			Device.Sensor.Mouth.isRun = true;
			OutPutLogs(LogCode_Action,0, "+-- Judgement,Mouth,\t Now:"+ String(Device.Sensor.Mouth.Data)+"  >= Limit max:" + String(Device.Sensor.Mouth.Max));     //Log出力
		}

		////////////////////////////////////////////////////////////////////////////////////////
		//TPMが閾値を超えたら
		////////////////////////////////////////////////////////////////////////////////////////
/*
		if( Device.Sensor.TPM.isActive == true && Device.Sensor.TPM.isRun ==false ){
			Device.Sensor.TPM.isRun = true;
			OutPutLogs(LogCode_Action,0, "+-- Judgement,TPM,\t Now:"+ String(Device.Sensor.TPM.Data)+"  >= Limit max:" + String(Device.Sensor.TPM.Max));     //Log出力
		}

*/
		////////////////////////////////////////////////////////////////////////////////////////
		//IMU or Position  or Temperature or  Eye or Microphone
		////////////////////////////////////////////////////////////////////////////////////////
 		if( Device.TASK[ GetNo_TASK_Mood(TASK_Name_Emerg) ].Enable == true ){	//有効のときのだけ反応する
				if( Device.Sensor.IMU.isActive == true || Device.Sensor.Position.isActive == true || Device.Sensor.Temperature.isActive == true || Device.Sensor.Eye.isActive == true ||  Device.Sensor.Microphone.isActive == true ){
					if(GetTASK_Status( TASK_Name_Emerg ) != TASK_Status_Run){


						OutPutLogs(LogCode_Action,0, "+-- Judgement,IMU,\t Now:"+ String(Device.Sensor.IMU.Data)+"  >= Limit max:" + String(Device.Sensor.IMU.Max));     //Log出力
						TASK_ForcedExecution( TASK_Name_Emerg );	//緊急起動
						TASK_Sort( );	
//						Device.TASK[ GetNo_TASK_Mood(TASK_Name_Emerg) ].isFirtstTime = true; 	//初回実行
						ScreenChangeNo( Screen_Emergency );	//画面推移

						if(Device.Sensor.IMU.isActive 			== true ){ Device.Sensor.IMU.isRun 			=true;}
						if(Device.Sensor.Position.isActive 		== true ){ Device.Sensor.Position.isRun 	=true;}
						if(Device.Sensor.Temperature.isActive 	== true ){ Device.Sensor.Temperature.isRun	=true;}
						if(Device.Sensor.Eye.isActive 			== true ){ Device.Sensor.Eye.isRun 			=true;}
						if(Device.Sensor.Microphone.isActive 	== true ){ Device.Sensor.Microphone.isRun 	=true;}
					}else{
						//既に実行中にも関わらず呼び出された場合、機嫌をリセット
						TASK_MoodReset(TASK_Name_Emerg);

					}

				}
		}

	}



