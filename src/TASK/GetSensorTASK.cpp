#include "TASK/GetSensorTASK.h"
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GetSensorTASK
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetSensorTASK(void* arg){

//	OutPutLogs(LogCode_Info,2,"--- START TASK GetSensorTASK ---");    //Log出力

	
	while (1) {

		//メインバッテリーに接続されていないときは実行しない
		if(Device.isMainBatteryConnect == true){
			/////////////////////////////////////////////////
			//Tocuh検出
			/////////////////////////////////////////////////
			Device.LCD_Tocuh = M5.Touch.getPressPoint();
			Device.LCD_Tocuh_Sprite.x = Device.LCD_Tocuh.x -10;
			Device.LCD_Tocuh_Sprite.y = Device.LCD_Tocuh.y -10;
			if(Device.LCD_Tocuh_Sprite.x <0){	Device.LCD_Tocuh_Sprite.x =-1;}
			if(Device.LCD_Tocuh_Sprite.y <0){	Device.LCD_Tocuh_Sprite.y =-1;}


		if(Device.ScreenNo != -1){
			FPS( 1 ); 				//FPS計算	

			Device.Sensor.SensorTMP[ Sensor_CROTCH  	].AddData(  GetSensorReadMux( 0 )  );		//CROTCH
			Device.Sensor.SensorTMP[ Sensor_Microhone  	].AddData(  GetSensorReadMux( 4 )  );		//Microhone
			Device.Sensor.SensorTMP[ Sensor_Mouth		].AddData(  GetSensorReadMux( 1 )  );		//Mouth
			Device.Sensor.SensorTMP[ Sensor_Temperature ].AddData(  GetSensorReadMux( 2 )  );		//Temperature
			Device.Sensor.SensorTMP[ Sensor_Eyes  		].AddData(  GetSensorReadMux( 3 )  );		//Eyes
			Device.Sensor.SensorTMP[ Sensor_Level01  	].AddData(  GetSensorReadMux( 8 )  );		//Level01
			Device.Sensor.SensorTMP[ Sensor_Level02  	].AddData(  GetSensorReadMux( 9 )  );		//Level02
			Device.Sensor.SensorTMP[ Sensor_Level03  	].AddData(  GetSensorReadMux( 10 )  );		//Level03
			Device.Sensor.SensorTMP[ Sensor_Level04  	].AddData(  GetSensorReadMux( 11 )  );		//Level04
			Device.Sensor.SensorTMP[ Sensor_Level05  	].AddData(  GetSensorReadMux( 12 )  );		//Level05
			Device.Sensor.SensorTMP[ Sensor_Level06  	].AddData(  GetSensorReadMux( 13 )  );		//Level06
			Device.Sensor.SensorTMP[ Sensor_Level07  	].AddData(  GetSensorReadMux( 14 )  );		//Level07
			Device.Sensor.SensorTMP[ Sensor_Level08  	].AddData(  GetSensorReadMux( 15 )  );		//Level08


			GetM5Decice();
		



			// 時間取得
			if( (millis() - Device.TimeRTC) >=1000  ){
				if(Device.Sensor.isRTC !=true){	//RTCデータ受信中は、無視する。これをはずすとハングアップする

					RTC_DateTypeDef DateStruct;
					RTC_TimeTypeDef TimeStruct;

					M5.Rtc.GetDate(&DateStruct);  //時間取得
					M5.Rtc.GetTime(&TimeStruct);  //時間取得
					char tmpA[40];
					char tmpB[40];
					sprintf(tmpA, "%04d/%02d/%02d",	DateStruct.Year,		DateStruct.Month,	DateStruct.Date	);
					sprintf(tmpB, "%02d:%02d:%02d",	TimeStruct.Hours,	TimeStruct.Minutes,	TimeStruct.Seconds	);
					Device.DateString = tmpA;
					Device.TimeString = tmpB;
					Device.TimeRTC = millis();
	//				Serial.print(Device.DateString+"");
	//				Serial.println(Device.TimeString);
				}else{
					Serial.println("RTC STOP");
				}
			}




			////////////////////////////////////////////////////////
			// LCD Touch
			////////////////////////////////////////////////////////
			if(Device.LCD_Tocuh.x  ==-1){
				Device.Sensor.SensorTMP[ Sensor_LCD_Touch ].AddData(  0  );		//Sensor_LCD_Touch
			}else{
				Device.Sensor.SensorTMP[ Sensor_LCD_Touch ].AddData(  1  );		//Sensor_LCD_Touch

				Device.TimeCountTouch = millis();	//最後にタッチした時間を計測
			}

/*
			//最後にタッチしてから30秒が経過したら
			if( millis() - Device.TimeCountTouch > 30*1000 ){

					Device.isLcdPower =0;
					if(Device.isLcdPowerOLD != Device.isLcdPower){
						M5.Axp.SetDCDC3(false);
					}
					Device.isLcdPowerOLD = Device.isLcdPower;
			}else{
					//27秒～30秒にかけて、徐々に暗くしていく
					Device.isLcdPower = maps( (millis() - Device.TimeCountTouch), 27*1000, 30*1000, 3000,2500  );
					if(Device.isLcdPowerOLD != Device.isLcdPower){
						M5.Axp.SetDCDC3(true);
						M5.Axp.SetLcdVoltage(Device.isLcdPower);
					}
					Device.isLcdPowerOLD = Device.isLcdPower;
			}
*/


			//////////////////////////////////
			//平均処理
			//////////////////////////////////
			int max_count=0;
			//初期化
			for(int i=0;i<Sensor_NameMAX;i++){
	//			if(i !=Sensor_IMU){
					Device.Sensor.SensorTMP[i].Sum  =0;
					if(max_count <= Device.Sensor.SensorTMP[i].AVG_MAX ){	max_count =Device.Sensor.SensorTMP[i].AVG_MAX; 	}	
	//			}
			}



			//合計処理
			for(int j=0;j< max_count;j++){
				for(int i=0;i<Sensor_NameMAX;i++){
						if(j <  Device.Sensor.SensorTMP[i].AVG_MAX ){
							if(i !=Sensor_IMU){
								//加算
								Device.Sensor.SensorTMP[i].Sum +=  Device.Sensor.SensorTMP[i].Datas[j];
							}else{
								//IMUの時は最大値を記録
								if(Device.Sensor.SensorTMP[i].Sum <= Device.Sensor.SensorTMP[i].Datas[j]){
									Device.Sensor.SensorTMP[i].Sum = Device.Sensor.SensorTMP[i].Datas[j];
								}
							}
						}
				}
			}


			//平均処理
			for(int i=0;i<Sensor_NameMAX;i++){
				if(i !=Sensor_IMU){
					//平均を求める
					Device.Sensor.SensorTMP[i].Data =  (float)Device.Sensor.SensorTMP[i].Sum / (float)Device.Sensor.SensorTMP[i].AVG_MAX;
				}else{
					////IMUの時は最大値を記録
					Device.Sensor.SensorTMP[i].Data = Device.Sensor.SensorTMP[i].Sum;
				}
			}

	//			Serial.print(Device.Sensor.SensorTMP[ Sensor_IMU ].Data);
	//			Serial.print("\n");



			//Tapping計算
			Device.Sensor.SensorTMP[ Sensor_LCD_Touch 	].TPM = Device.Sensor.SensorTMP[ Sensor_LCD_Touch 	].Tapping.AddData( Device.Sensor.SensorTMP[ Sensor_LCD_Touch ].Data );
			Device.Sensor.SensorTMP[ Sensor_IMU 		].TPM = Device.Sensor.SensorTMP[ Sensor_IMU 		].Tapping.AddData( Device.Sensor.SensorTMP[ Sensor_IMU  	 ].Data2  );



			/////////////////////////////////////////////////////////// 
			//モータ処理
			//個別に記載すると、マルチタスク上で、Wire1関数が分割される可能性がある
			///////////////////////////////////////////////////////////

					Device.Motor[Motor_Main  ].Run( Device.Battery.isUSB );
					Device.Motor[Motor_Ink_Red  ].Run( Device.Battery.isUSB );
					Device.Motor[Motor_Ink_Yellow  ].Run( Device.Battery.isUSB);
					Device.Motor[Motor_ValveA].Run( Device.Battery.isUSB );
					Device.Motor[Motor_ValveB].Run( Device.Battery.isUSB );




			/////////////////////////////////////////////////////////// 
			//水位センサ
			///////////////////////////////////////////////////////////
			GetWaterSensor();




			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//データ処理
			//データを処理する
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			Device.Sensor.Battery.Data		= 	Device.Battery.Level;				//バッテリーレベル
			Device.Sensor.Microphone.Data 	=	abs(Device.Sensor.SensorTMP[ Sensor_Microhone ].Data -1915);	
			Device.Sensor.Eye.Data 			=	Device.Sensor.SensorTMP[ Sensor_Eyes ].Data;					
			Device.Sensor.Diapers.Data 		=	Device.Sensor.SensorTMP[ Sensor_CROTCH ].Data;					
			Device.Sensor.Mouth.Data 		=	Device.Sensor.SensorTMP[ Sensor_Mouth ].Data;					
			Device.Sensor.Temperature.Data 	=	Device.Sensor.SensorTMP[ Sensor_Temperature ].GetTempture();	
			Device.Sensor.IMU.Data 			=	Device.Sensor.SensorTMP[ Sensor_IMU ].Data;						



				/////////////////////////////////////////////////////////////////////////////////
				//MilkLevel計算
				// 浸かっていない  4095
				// 漬かっているいる ちょっと4000
				// 漬かっているいる かなり3700
				/////////////////////////////////////////////////////////////////////////////////
				float sum =0;
				float Data[8];

				for(int i=Sensor_Level01; i<=Sensor_Level08; i++){
					Data[ (i - Sensor_Level01)] = maps( Device.Sensor.SensorTMP[ i ].Data , 3800,4095,100,0 );
//					Serial.print( String((int)Device.Sensor.SensorTMP[ i ].Data) +"(");
//					Serial.print( String((int)Data[ (i-Sensor_Level01) ]) + ")\t");
					sum+= Data[i - Sensor_Level01];
				}

				Device.Sensor.Level.Data =0;

				if( Data[ 7 ] == 100){	Device.Sensor.Level.Data	= 100.0;	 }else 
				if( Data[ 6 ] == 100){	Device.Sensor.Level.Data	=  87.5;	 }else 
				if( Data[ 5 ] == 100){	Device.Sensor.Level.Data	=  75.0;	 }else 
				if( Data[ 4 ] == 100){	Device.Sensor.Level.Data	=  62.5;	 }else 
				if( Data[ 3 ] == 100){	Device.Sensor.Level.Data	=  50.0;	 }else 
				if( Data[ 2 ] == 100){	Device.Sensor.Level.Data	=  37.5;	 }else 
				if( Data[ 1 ] == 100){	Device.Sensor.Level.Data	=  25.0;	 }else 
				if( Data[ 0 ] == 100){	Device.Sensor.Level.Data	=  12.5;	 }else {	Device.Sensor.Level.Data =0;  }
//				Serial.print( "\t" + String(Device.Sensor.Level.Data));


//				int L = maps( Device.Sensor.SensorTMP[ Sensor_Level01 ].Data , 2800,3300,100,0 );
//				Serial.print( "\t\t" +String(Device.Sensor.SensorTMP[ Sensor_Level01 ].Data) +"\t"+String(L));

//				Serial.print("\n");
//				Device.Sensor.Level.Data	=  L;




				///////////////////////
				////////////////////
				//TPM計算 TochとIMUの大きいほうを採用
				///////////////////////////////////////////
				int tmpTPM =0;
				if( 	(int)Device.Sensor.SensorTMP[ Sensor_IMU ].TPM > (int)Device.Sensor.SensorTMP[ Sensor_LCD_Touch ].TPM){
					tmpTPM = (int)Device.Sensor.SensorTMP[ Sensor_IMU ].TPM;
				}else{
					tmpTPM = (int)Device.Sensor.SensorTMP[ Sensor_LCD_Touch ].TPM;
				}
				Device.Sensor.TPM.Data = tmpTPM;

			//////////////////////////////////////////////
			//Hack処理
			//////////////////////////////////////////////
			//バッテリーハックに関してはここでは行わない
			if( Device.Sensor.Microphone.isHack  == true){		Device.Sensor.Microphone.Data 	= Device.Sensor.Microphone.HackData; 	} 
			if( Device.Sensor.Eye.isHack 		 == true){		Device.Sensor.Eye.Data 			= Device.Sensor.Eye.HackData; 			} 
			if( Device.Sensor.Diapers.isHack 	 == true){		Device.Sensor.Diapers.Data 		= Device.Sensor.Diapers.HackData; 		} 
			if( Device.Sensor.Mouth.isHack 		 == true){		Device.Sensor.Mouth.Data 		= Device.Sensor.Mouth.HackData; 		} 
			if( Device.Sensor.Temperature.isHack == true){		Device.Sensor.Temperature.Data 	= Device.Sensor.Temperature.HackData; 	} 
			if( Device.Sensor.Level.isHack 		 == true){		Device.Sensor.Level.Data 		= Device.Sensor.Level.HackData; 		} 
			if( Device.Sensor.TPM.isHack 		 == true){		Device.Sensor.TPM.Data 			= Device.Sensor.TPM.HackData; 			} 
			if( Device.Sensor.IMU.isHack 		 == true){		Device.Sensor.IMU.Data 			= Device.Sensor.IMU.HackData; 			} 
			if( Device.Sensor.Position.isHack 	 == true){		Device.Sensor.Position.Data 	= Device.Sensor.Position.HackData;		} 


			//////////////////////////////////////////////
			//MSG文字列化
			//////////////////////////////////////////////
			Device.Sensor.Microphone.SData	 =	(String)(int)Device.Sensor.Microphone.Data;
			Device.Sensor.Eye.SData	 		 =	(String)(int)Device.Sensor.Eye.Data;
			Device.Sensor.Diapers.SData	 	 =	(String)(int)Device.Sensor.Diapers.Data;
			Device.Sensor.Mouth.SData	 	 =	(String)(int)Device.Sensor.Mouth.Data;
			Device.Sensor.Temperature.SData	 =	String(Device.Sensor.Temperature.Data,1);
			Device.Sensor.Level.SData	 	 =	String(Device.Sensor.Level.Data,1);
			Device.Sensor.TPM.SData	 		 =	String(Device.Sensor.TPM.Data,1);
			Device.Sensor.IMU.SData			 =  String(Device.Sensor.IMU.Data,1);

			switch( (int)Device.Sensor.Position.Data ){
				case Position_Supine:	 	Device.Sensor.Position.SData	 = "Supine";	  break;   	//1:仰臥位 
				case Position_Inversus: 	Device.Sensor.Position.SData	 = "Inversus";    break;    //3:逆さ    
				case Position_Depression: 	Device.Sensor.Position.SData	 = "Depression";  break;    //2:うつ伏せ   
				case Position_Standing: 	Device.Sensor.Position.SData	 = "Standing";    break;    //0: 立っている 
			}



			///////////////////////////////////////////////////////////////////////////////////////////////////////
			//閾値判定
			///////////////////////////////////////////////////////////////////////////////////////////////////////
			if(Device.Battery.isUSB ==false){
				Device.Sensor.Battery.isActive 	= Device.Sensor.JudgeThreshold(	Device.Sensor.Battery,	 	ThresholdConditions_Min );		//バッテリー判定
			}
			Device.Sensor.Microphone.isActive 	= Device.Sensor.JudgeThreshold(	Device.Sensor.Microphone,	ThresholdConditions_Max );		//マイクロフォン判定
			Device.Sensor.Eye.isActive 			= Device.Sensor.JudgeThreshold(	Device.Sensor.Eye,			ThresholdConditions_Max );		//目
			Device.Sensor.Diapers.isActive 		= Device.Sensor.JudgeThreshold(	Device.Sensor.Diapers, 		ThresholdConditions_Max );		//おむつ
			Device.Sensor.Temperature.isActive 	= Device.Sensor.JudgeThreshold(	Device.Sensor.Temperature,	ThresholdConditions_MinMAX );	//温度
//			Device.Sensor.Level.isActive		= Device.Sensor.JudgeThreshold(	Device.Sensor.Level,		ThresholdConditions_Max );		//レベル
//			Device.Sensor.Level_Min.isActive	= Device.Sensor.JudgeThreshold(	Device.Sensor.Level,		ThresholdConditions_Min );		//レベル

			Device.Sensor.IMU.isActive 			= Device.Sensor.JudgeThreshold(	Device.Sensor.IMU,			ThresholdConditions_Max);		//IMU
			Device.Sensor.TPM.isActive 			= Device.Sensor.JudgeThreshold(	Device.Sensor.TPM,			ThresholdConditions_MinMAX);	//TPM


	//Serial.println("*********" + (String)Device.Sensor.TPM.isActive);



			/////////////////////////////////////////////////////////////////////////////////////////////////////
			// 口のセンサ　時間推移による設定
			//口センサの場合、瞬時にisActiveをFalseに変更するのではなく
			//5秒程度してから、isActiveをFalseに変更する
			/////////////////////////////////////////////////////////////////////////////////////////////////////
			boolean isTempFlag = Device.Sensor.JudgeThreshold(Device.Sensor.Mouth,		ThresholdConditions_Max);
			if(isTempFlag == true){
				Device.Sensor.Mouth.isActive = true;		
				Device.Sensor.Mouth.isTime =false;
			}

			if(isTempFlag == false && Device.Sensor.Mouth.isTime ==false){
					//既にisActiveがTrue(有効中)で、今回、初めてisTempFlagがtrue(無効になったら)
					Device.Sensor.Mouth.TimeSet = millis();	//時間を記録
					Device.Sensor.Mouth.isTime =true;
			}
			if(Device.Sensor.Mouth.isTime ==true &&  (millis() - Device.Sensor.Mouth.TimeSet)>10*1000){
				Device.Sensor.Mouth.isActive  = false;		
				Device.Sensor.Mouth.isTime =false;
			}
//			Serial.println( String(Device.Sensor.Mouth.Data)  +"\t" +  String( Device.Sensor.Mouth.isActive ) +"\t" + String( Device.Sensor.JudgeThreshold(	Device.Sensor.Mouth,		ThresholdConditions_Max )));



//			Device.Sensor.Level.isActive		= Device.Sensor.JudgeThreshold(	Device.Sensor.Level,		ThresholdConditions_Max );		//レベル
//			Device.Sensor.Level_Min.isActive	= Device.Sensor.JudgeThreshold(	Device.Sensor.Level,		ThresholdConditions_Min );		//レベル

			/////////////////////////////////////////////////////////////////////////////////////////////////////
			//Levelセンサ　時間推移による設定  MIN 
			//Levelセンサの場合、瞬時にisActiveをFalseに変更するのではなく
			//5秒程度してから、isActiveをFalseに変更する
			/////////////////////////////////////////////////////////////////////////////////////////////////////
			isTempFlag = Device.Sensor.JudgeThreshold(Device.Sensor.Level,		ThresholdConditions_Min);

			if(isTempFlag == false){
				Device.Sensor.Level_Min.isActive = false;		
				Device.Sensor.Level_Min.isTime   = false;
			}

			if(isTempFlag == false && Device.Sensor.Level_Min.isTime ==false){
					//既にisActiveがTrue(有効中)で、今回、初めてisTempFlagがtrue(無効になったら)
					Device.Sensor.Level_Min.TimeSet = millis();	//時間を記録
					Device.Sensor.Level_Min.isTime  = true;
			}
	
			if(Device.Sensor.Level_Min.isTime ==true &&  (millis() - Device.Sensor.Level_Min.TimeSet)>10* 1000){
				Device.Sensor.Level_Min.isActive  = true;		
				Device.Sensor.Level_Min.isTime =false;
			}


//			Device.Sensor.Level_Min.isActive	= Device.Sensor.JudgeThreshold(	Device.Sensor.Level,		ThresholdConditions_Min );		//レベル

			/////////////////////////////////////////////////////////////////////////////////////////////////////
			//Levelセンサ　時間推移による設定  MAX 
			//Levelセンサの場合、瞬時にisActiveをFalseに変更するのではなく
			//5秒程度してから、isActiveをFalseに変更する
			/////////////////////////////////////////////////////////////////////////////////////////////////////

			isTempFlag = Device.Sensor.JudgeThreshold( Device.Sensor.Level,		ThresholdConditions_Max);
			if(isTempFlag == false){		//予備チェックで、trueのとき
	//			Device.Sensor.Position.isActive = false;		
				Device.Sensor.Level.isTime =false;
			}
			if(isTempFlag == true && Device.Sensor.Level.isTime ==false){
					//既にisActiveがTrue(有効中)で、今回、初めてisTempFlagがtrue(無効になったら)
					Device.Sensor.Level.TimeSet = millis();	//時間を記録
					Device.Sensor.Level.isTime =true;
			}
			if(Device.Sensor.Level.isTime ==true &&  (millis() - Device.Sensor.Level.TimeSet)>10*1000){
				Device.Sensor.Level.isActive  = true;		
			//	Device.Sensor.Position.isTime =false;
			}else{
				Device.Sensor.Level.isActive  = false;		
			}



			/////////////////////////////////////////////////////////////////////////////////////////////////////
			// 姿勢　時間推移による設定
			//姿勢の場合、瞬時にisActiveに変更するのではなく
			//3秒経過してから、isActiveに変更する
			/////////////////////////////////////////////////////////////////////////////////////////////////////

			isTempFlag = Device.Sensor.JudgeThreshold( Device.Sensor.Position,		ThresholdConditions_Max);
			if(isTempFlag == false){		//予備チェックで、trueのとき
	//			Device.Sensor.Position.isActive = false;		
				Device.Sensor.Position.isTime =false;
			}
			if(isTempFlag == true && Device.Sensor.Position.isTime ==false){
					//既にisActiveがTrue(有効中)で、今回、初めてisTempFlagがtrue(無効になったら)
					Device.Sensor.Position.TimeSet = millis();	//時間を記録
					Device.Sensor.Position.isTime =true;
			}
			if(Device.Sensor.Position.isTime ==true &&  (millis() - Device.Sensor.Position.TimeSet)>3000){
				Device.Sensor.Position.isActive  = true;		
			//	Device.Sensor.Position.isTime =false;
			}else{
				Device.Sensor.Position.isActive  = false;		
			}




			///////////////////////////////////////////////////////////////////////////////////////
			//データ送信
			///////////////////////////////////////////////////////////////////////////////////////
			if(Device.isWriteData == true){
				if(Device.BTSerial.connected()  == true){
					String MSG ="D,";								//0
					MSG += (float)Device.Sensor.Battery.Data;			//1
					MSG += ",";
					MSG += (int)Device.Sensor.Microphone.Data;
					MSG += ",";
					MSG += (int)Device.Sensor.Eye.Data;
					MSG += ",";
					MSG += (int)Device.Sensor.Diapers.Data;
					MSG += ",";
					MSG += (int)Device.Sensor.Mouth.Data;
					MSG += ",";
					MSG += (int)Device.Sensor.Temperature.Data;
					MSG += ",";
					MSG += (int)Device.Sensor.Level.Data;
					MSG += ",";
					MSG += (int)Device.Sensor.IMU.Data;
					MSG += ",";
					MSG += (int)Device.Sensor.TPM.Data;
					MSG += ",";
					MSG += (int)Device.Sensor.Position.Data;
					MSG += ",";
					////////////////////
					//Active
					////////////////////
					MSG += (int)Device.Sensor.Battery.isActive;
					MSG += ",";
					MSG += (int)Device.Sensor.Microphone.isActive;
					MSG += ",";
					MSG += (int)Device.Sensor.Eye.isActive;
					MSG += ",";
					MSG += (int)Device.Sensor.Diapers.isActive;
					MSG += ",";
					MSG += (int)Device.Sensor.Mouth.isActive;
					MSG += ",";
					MSG += (int)Device.Sensor.Temperature.isActive;
					MSG += ",";
					MSG += (int)Device.Sensor.Level.isActive;
					MSG += ",";
					MSG += (int)Device.Sensor.IMU.isActive;
					MSG += ",";
					MSG += (int)Device.Sensor.TPM.isActive;
					MSG += ",";
					MSG += (int)Device.Sensor.Position.isActive;
					MSG += ",";

					Device.BTSerial.println(MSG);	//BTにデータを送信する
				}
			}
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// TASK　起動処理
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
			CryTASK_Judgement();
		}
		vTaskDelay(1);


	}

}