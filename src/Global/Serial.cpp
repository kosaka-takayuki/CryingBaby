#include "Global/Serial.h"

    ///////////////////////////////////////////////////////////////////////////
    // SerialRead 
    ///////////////////////////////////////////////////////////////////////////
	void SerialRead(){

		//データ受信
  		if (Device.BTSerial.available()>0) {  //受信データがある時
			String tmpString =  Device.BTSerial.readStringUntil('\n');


			///////////////////////////////////////////////////////
			//Sprite設定
			///////////////////////////////////////////////////////
			Device.LCD_Message.createSprite(260,40);	//生成
			Device.LCD_Message.fillRoundRect (0, 0,260,40,6,BaseColor_Black);	
			Device.LCD_Message.fillRoundRect (2, 2,256,36,3,BaseColor_Cyan);	
			Device.LCD_Message.setTextDatum( middle_center );		//文字位置設定
			Device.LCD_Message.setTextColor(BaseColor_Black);	//文字色設定(文字色、背景色)

			Device.LCD_Message.setFont(&fonts::efontJA_16_b);	//Font設定
			Device.LCD_Message.drawString( "Serial data reception"	, 130, 10); //タイトルの表示
			Device.LCD_Message.setFont(&fonts::efontJA_16);	//Font設定
			Device.LCD_Message.drawString( "["+tmpString+"]"		, 130, 25); //タイトルの表示
			Device.LCD_Message.pushSprite(&Device.LCD,30,100);	//描写
//			delay(1000);


			///////////////////////////////////////////////////////
			//データ解析
			///////////////////////////////////////////////////////
				OutPutLogs(LogCode_Command,0, "+--Send SerialMessage ["+tmpString  +"]");     //Log出力

				String SendData[80];
				split(tmpString,',', SendData);				//データスプリット タブ区切りで切る


				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//タッチ切り替え
				//Touch,0
				//Touch,1
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(SendData[0] == "Touch"){

						if(SendData[1] =="0"){		Device.M5Touch = false;			}
						if(SendData[1] =="1"){		Device.M5Touch  = true;			} 
						
					}


				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//ShowINFO
				//ShowINFO
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(SendData[0] == "ShowINFO"){
									ScreenChangeNo( Screen_TASKMonitor );	//スクリーン移動
	
					}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Helpモード切り替え
				//Help,0
				//Help,1
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(SendData[0] == "Help"){

						if(SendData[1] =="0"){		Device.isHelp  = false;			} //デモモード
						if(SendData[1] =="1"){		Device.isHelp  = true;			} //デモモード
						
					}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//デモモード切り替え
				//Demo,0
				//Demo,1
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(SendData[0] == "Demo"){

						 //デモモード
						if(SendData[1] =="0"){
							Device.isDemo  = true;
							for(int i=0;i<TASK_Name_End;i++){
									TASK_End( i );
							}
						}

						if(SendData[1] =="1"){		Device.isDemo  = false;			} //デモモード
						
					}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//電源OFF制御
				//PowerOFF
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(SendData[0] =="PowerOFF"){
						OutPutLogs(LogCode_Command,1, "+-- Command Execution:" + SendData[0]);     //Log出力
						Device.AquesTalk.playK("電源を切ります。", 50,Device.isAquesTalk);     //AquesTalkで会話　会話スピードは最低の50
						delay(3000);
						M5.Axp.PowerOff();                        //電源を落とす
					}    


				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//リセット
				//Reset
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(SendData[0] =="ReBoot"){
						OutPutLogs(LogCode_Command,1, "+-- Command Execution:" + SendData[0]);     //Log出力
						Device.AquesTalk.playK("再起動します。", 50,Device.isAquesTalk);       //AquesTalkで会話　会話スピードは最低の50
						delay(3000);
						esp_restart();                            //Reset
					}   

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//センサ値受信
				//SensorData,0;
				//SensorData,1;
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(SendData[0] =="SendSensorData"){
						OutPutLogs(LogCode_Command,1, "+-- Command Execution:" + SendData[0]);     //Log出力
						if(SendData[1] =="0"){		Device.isWriteData =false;			} //センサ値　非受信
						if(SendData[1] =="1"){		Device.isWriteData =true;			} //センサ値　受信
						
					}   


				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//RTC　保存
				//SaveNTP,2022,05,23,10,08,09
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(SendData[0] == "SaveNTP"){
						OutPutLogs(LogCode_Command,1, "+-- Command Execution:" + SendData[0]);     //Log出力
						Device.Sensor.isRTC =true;	//TASK　GetSensorのRTC読込をストップ
							//RTCは、データのセット順番によって書き込めないらしい
							//WeekDay, Month, Date,Yearの順番でセットする
							RTC_DateTypeDef DateStruct;
							DateStruct.WeekDay 	= RetunValue01(SendData[1] , 0);	//week day
							DateStruct.Month 	= RetunValue02(SendData[3] , 0); 	//MM
							DateStruct.Date 	= RetunValue02(SendData[4] , 0);	//dd
							DateStruct.Year 	= RetunValue04(SendData[2] , 0); 	//yyyy	
							M5.Rtc.SetDate(&DateStruct);
							delay(1000);

							RTC_TimeTypeDef TimeStruct;
							TimeStruct.Hours   = RetunValue02(SendData[5] , 0);	//HH
							TimeStruct.Minutes = RetunValue02(SendData[6] , 0);	//mm
							TimeStruct.Seconds = RetunValue02(SendData[7] , 0);	//ss
							M5.Rtc.SetTime(&TimeStruct);
							delay(1000);
						Device.Sensor.isRTC =false;//TASK　GetSensorのRTC読込を解放
					}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//LimitShow 閾値表示
				//LimitShow
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(SendData[0] == "ShowLimit"){
						OutPutLogs(LogCode_Command,1, "+-- Command Execution:" + SendData[0]);     //Log出力
						String msg ="ShowLimit";
						msg += ",";						msg += (int)Device.Sensor.Battery.Min;				msg += ",";						msg += (int)Device.Sensor.Battery.Max;
						msg += ",";						msg += (int)Device.Sensor.Microphone.Min;			msg += ",";						msg += (int)Device.Sensor.Microphone.Max;
						msg += ",";						msg += (int)Device.Sensor.Eye.Min;					msg += ",";						msg += (int)Device.Sensor.Eye.Max;
						msg += ",";						msg += (int)Device.Sensor.Diapers.Min;				msg += ",";						msg += (int)Device.Sensor.Diapers.Max;
						msg += ",";						msg +=  (int)Device.Sensor.Mouth.Min;				msg += ",";						msg +=  (int)Device.Sensor.Mouth.Max;
						msg += ",";						msg +=  (int)Device.Sensor.Temperature.Min;			msg += ",";						msg +=  (int)Device.Sensor.Temperature.Max;
						msg += ",";						msg +=  (int)Device.Sensor.Level.Min;				msg += ",";						msg +=  (int)Device.Sensor.Level.Max;
						msg += ",";						msg +=  (int)Device.Sensor.TPM.Min;					msg += ",";						msg +=  (int)Device.Sensor.TPM.Max;
						msg += ",";						msg +=  (int)Device.Sensor.IMU.Min;					msg += ",";						msg +=  (int)Device.Sensor.IMU.Max;
						msg += ",";						msg +=  (int)Device.Sensor.Position.Min;			msg += ",";						msg +=  (int)Device.Sensor.Position.Max;
						msg +="\n";
						Serial.println(msg);
						Device.BTSerial.println(msg);	//BTにデータを送信する
					}


				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//SendLimit 閾値設定
				//SendLimit //Send:SendLimit,Battery,0,50
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(SendData[0] == "SendLimit"){
						OutPutLogs(LogCode_Command,1, "+-- Command Execution:" + SendData[0]);     //Log出力
						if(SendData[1] =="Battery"){ 	Device.Sensor.Battery.Min 		= RetunValue04(SendData[2],0);		Device.Sensor.Battery.Max 		= RetunValue04(SendData[3],0); }
						if(SendData[1] =="Micophone"){ 	Device.Sensor.Microphone.Min 	= RetunValue04(SendData[2],0);		Device.Sensor.Microphone.Max 	= RetunValue04(SendData[3],0); }
						if(SendData[1] =="Eye"){ 		Device.Sensor.Eye.Min 			= RetunValue04(SendData[2],0);		Device.Sensor.Eye.Max 			= RetunValue04(SendData[3],0); }
						if(SendData[1] =="Diapers"){ 	Device.Sensor.Diapers.Min 		= RetunValue04(SendData[2],0);		Device.Sensor.Diapers.Max 		= RetunValue04(SendData[3],0); }
						if(SendData[1] =="Mouth"){ 		Device.Sensor.Mouth.Min 		= RetunValue04(SendData[2],0);		Device.Sensor.Mouth.Max 		= RetunValue04(SendData[3],0); }
						if(SendData[1] =="Temprature"){	Device.Sensor.Temperature.Min 	= RetunValue04(SendData[2],0);		Device.Sensor.Temperature.Max 	= RetunValue04(SendData[3],0); }
						if(SendData[1] =="Level"){ 		Device.Sensor.Level.Min 		= RetunValue04(SendData[2],0);		Device.Sensor.Level.Max 		= RetunValue04(SendData[3],0); }
						if(SendData[1] =="TPM"){ 		Device.Sensor.TPM.Min 			= RetunValue04(SendData[2],0);		Device.Sensor.TPM.Max 			= RetunValue04(SendData[3],0); }
						if(SendData[1] =="IMU"){ 		Device.Sensor.IMU.Min 			= RetunValue04(SendData[2],0);		Device.Sensor.IMU.Max 			= RetunValue04(SendData[3],0); }
						if(SendData[1] =="Position"){ 	Device.Sensor.Position.Min 		= RetunValue04(SendData[2],0);		Device.Sensor.Position.Max 		= RetunValue04(SendData[3],0); }
						Save_Threshold_File();
					}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//SendHack センサ値改ざん　ハックする
				//SendHack //Send:SendHack,Battery,1,50
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(SendData[0] == "SendHack"){
						OutPutLogs(LogCode_Command,1, "+-- Command Execution:" + SendData[0]);     //Log出力
						boolean _isHack =false;
						if(SendData[2]=="0"){	_isHack = false;}
						if(SendData[2]=="1"){	_isHack = true;}
						int		_hackData =	RetunValue04(SendData[3],0);

						if(SendData[1] =="Battery"){ 	Device.Sensor.Battery.isHack 	 = _isHack;		Device.Sensor.Battery.HackData 		= _hackData; }
						if(SendData[1] =="Micophone"){ 	Device.Sensor.Microphone.isHack  = _isHack;		Device.Sensor.Microphone.HackData 	= _hackData; }
						if(SendData[1] =="Eye"){ 		Device.Sensor.Eye.isHack 		 = _isHack;		Device.Sensor.Eye.HackData 			= _hackData; }
						if(SendData[1] =="Diapers"){ 	Device.Sensor.Diapers.isHack 	 = _isHack;		Device.Sensor.Diapers.HackData 		= _hackData; }
						if(SendData[1] =="Mouth"){ 		Device.Sensor.Mouth.isHack 		 = _isHack;		Device.Sensor.Mouth.HackData 		= _hackData; }
						if(SendData[1] =="Temprature"){	Device.Sensor.Temperature.isHack = _isHack;		Device.Sensor.Temperature.HackData 	= _hackData; }
						if(SendData[1] =="Level"){ 		Device.Sensor.Level.isHack 		 = _isHack;		Device.Sensor.Level.HackData 		= _hackData; }
						if(SendData[1] =="TPM"){ 		Device.Sensor.TPM.isHack 		 = _isHack;		Device.Sensor.TPM.HackData 			= _hackData; }
						if(SendData[1] =="IMU"){ 		Device.Sensor.IMU.isHack		 = _isHack;		Device.Sensor.IMU.HackData 			= _hackData; }
						if(SendData[1] =="Position"){ 	Device.Sensor.Position.isHack	 = _isHack;		Device.Sensor.Position.HackData 	= _hackData; }


						//機嫌のHack
						if(SendData[1] == "Mood"){
							if(SendData[2] == "1"){	 Device.isMoodHack = true;	Serial.println("HACK ON");	}	//Hack
							if(SendData[2] == "0"){	 Device.isMoodHack = false;						}	//Hackしない
						}
						//SendHack,Mood,1

						SendTASK();	//TASK送信

					}


				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Motor,Main,0 	モータ制御
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(SendData[0] == "Motor"){
						OutPutLogs(LogCode_Command,1, "+-- Command Execution:" + SendData[0]);     //Log出力


						int _Speed = RetunValue04(SendData[2] , 0);


						int _MotorNo =-1;
						if(SendData[1] == "Main"  ){ _MotorNo = Motor_Main;   }
						if(SendData[1] == "InkA"  ){ _MotorNo = Motor_Ink_Red;   }
						if(SendData[1] == "InkB"  ){ _MotorNo = Motor_Ink_Yellow;   }
						if(SendData[1] == "ValveA"){ _MotorNo = Motor_ValveA; }
						if(SendData[1] == "ValveB"){ _MotorNo = Motor_ValveB; }

						if(_MotorNo !=-1){
							Device.Motor[_MotorNo].SetSpeed( _Speed);	//モータセット
						}
					}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//PlaySound,0,100;
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(SendData[0] == "PlaySound"){
						OutPutLogs(LogCode_Command,1, "+-- Command Execution:" + SendData[0]);     //Log出力

						int  no   = RetunValue01(SendData[1] , 0);
						int  gain = RetunValue03(SendData[2] , 0);

						MP3_KingLoopPlay( no, gain);

					}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//TASK,Hungry,0  TASK制御
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(SendData[0] == "TASK"){
						OutPutLogs(LogCode_Command,1, "+-- Command Execution:" + SendData[0]);     //Log出力

						int TaskName =-1;
						int ScreenNo =-1;

						
						if(SendData[1] == "Hungry"	){	TaskName = TASK_Name_Hungry;	ScreenNo = Screen_Hungry; 		}
						if(SendData[1] == "Sleep"	){	TaskName = TASK_Name_Sleep;		ScreenNo = Screen_Sleep;	 	}
						if(SendData[1] == "Mood"	){	TaskName = TASK_Name_Mood;		ScreenNo = Screen_Mood; 		}
						if(SendData[1] == "Wait"	){	TaskName = TASK_Name_Wait;		ScreenNo = 0; 					}
						if(SendData[1] == "Emerg"	){	TaskName = TASK_Name_Emerg;		ScreenNo = Screen_Emergency; 	}
						if(SendData[1] == "Shit"	){	TaskName = TASK_Name_Shit;		ScreenNo = Screen_Shit;			}
						if(SendData[1] == "Power"	){	TaskName = TASK_Name_Power;		ScreenNo = 0; 					}
						if(SendData[1] == "Diapers"	){	TaskName = TASK_Name_Diapers;	ScreenNo = Screen_Diapers;		}

						if(SendData[1] == "Burp"	){	TaskName = TASK_Name_Burp;		ScreenNo = Screen_Burp;			}
						if(SendData[1] == "Sleeping"){	TaskName = TASK_Name_Sleeping;	ScreenNo = Screen_Sleeping;		}



						//強制実行
						if(SendData[2] == "Execution"	){	
																TASK_ForcedExecution( TaskName );
																TASK_Sort( );		//データソートおよび正規化

//																Device.TASK[ GetNo_TASK_Mood(TASK_Name_Emerg) ].isFirtstTime = true;
																ScreenChangeNo( ScreenNo );	//画面推移

						}
						//強制終了
						if(SendData[2] == "End"			){

																TASK_End( TaskName );
																//Waitの終了以外
																if(TaskName != TASK_Name_Wait ){
																	TASK_ForcedExecution( TASK_Name_Wait );		//タスク終了後にWaitを入れる
																	TASK_Sort();		//ソート
																}
//																Device.TASK[ GetNo_TASK_Mood(TASK_Name_Emerg) ].isFirtstTime = true;
																ScreenChangeNo( Screen_TASKMonitor );	//スクリーン移動

						}
						//ReStart
						if(SendData[2] == "ReStart"		){	
																TASK_ReStart( TaskName );
						}

						//Feelless //Emergのときのみ有効
						if(TaskName == TASK_Name_Emerg){	
							if(SendData[2] == "Feelless"){	
								Device.TASK[ GetNo_TASK_Mood(TASK_Name_Emerg) ].Enable =false;	//自動センシング　無効可
							}
							if(SendData[2] == "Feel"){	
								Device.TASK[ GetNo_TASK_Mood(TASK_Name_Emerg) ].Enable =true;	//自動センシング　有効可
							}

						}
	


						SendTASK();	//TASK送信



					}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//InKRatio,0
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(SendData[0] == "InKRatio"){
						OutPutLogs(LogCode_Command,1, "+-- Command Execution:" + SendData[0]);     //Log出力

						int  r   = RetunValue03(SendData[1] , 0);

						Device.Motor[Motor_Ink_Red  ].Ratio = (float)r;
						Device.Motor[Motor_Ink_Yellow  ].Ratio = 100.0f - (float)r;



					}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//ShowIntervalFile 	インターバルファイル送信
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if(SendData[0] == "ShowIntervalFile"){
					OutPutLogs(LogCode_Command,1, "+-- Command Execution:" + SendData[0]);     //Log出力

					String msg ="";
						msg =  "ShowIntervalFile,";
					for(int i=0;i<TASK_Name_End;i++){
						msg += (String(Device.TASK[ i ].Name) +",");
						msg += (String(Device.TASK[ i ].IntervalTime) +",");
						msg += (String(Device.TASK[ i ].ElapsedTime) +",");

						msg += (String(Device.TASK[ i ].IntervalTime_Set) +",");
						msg += (String(Device.TASK[ i ].IntervalTime_Random) +",");

						msg += (String(Device.TASK[ i ].RunTime_Elapsed) +",");
						msg += (String(Device.TASK[ i ].RunTime_ElapsedOver) +",");

						msg += (String(Device.TASK[ i ].Status) +",");
//						msg += (String(Device.TASK[ i ].Priority) +"\n");
					}

					Device.BTSerial.println(msg);	//BTにデータを送信する
//					Serial.println(msg);	//BTにデータを送信する
//					delay(1000);


				}


				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//AskTASK 	タスク情報を要求　送信
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if(SendData[0] == "AskTASK"){
					OutPutLogs(LogCode_Command,1, "+-- Command Execution:" + SendData[0]);     //Log出力

					SendTASK();	//TASK送信
				}


				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Ink 	インク状態
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if(SendData[0] == "Ink"){
					OutPutLogs(LogCode_Command,1, "+-- Command Execution:" + SendData[0]);     //Log出力
					if(SendData[1] =="0"){
						Device.Motor[ Motor_Ink_Yellow ].Ratio =  100;	Device.Motor[ Motor_Ink_Red ].Ratio =  0;
					}

					if(SendData[1] =="1"){
							int inkY = (int)random(0,100);
							int inkR = 100 - inkY;						
							Device.Motor[ Motor_Ink_Yellow ].Ratio =    (int)inkY;	Device.Motor[ Motor_Ink_Red ].Ratio = (int)inkR;
					}	

					if(SendData[1] =="2"){
							Device.Motor[ Motor_Ink_Yellow ].Ratio =    0;			Device.Motor[ Motor_Ink_Red ].Ratio =100;
					}
					Device.Motor[	Motor_Ink_Red		].SetSpeed( maps( Device.Motor[ Motor_Ink_Red    ].Ratio , 0,100,0,255 ));	//モータセット
					Device.Motor[	Motor_Ink_Yellow	].SetSpeed( maps( Device.Motor[ Motor_Ink_Yellow ].Ratio , 0,100,0,255 ));	//モータセット

					SendTASK();	//TASK送信

				}


				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//LED 	LED情報受信
				//Color,0 Auto
				//Color,1
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if(SendData[0] == "Color"){
					OutPutLogs(LogCode_Command,1, "+-- Command Execution:" + SendData[0]);     //Log出力



					switch(	SendData[1].toInt() ){
						case 0: Serial.println("L0"); Device.isLEDHack = false;	break;
						case 1: Serial.println("L1"); Device.isLEDHack = true;	Device.HackLED =  Device.LEDs.Color(255,   0,   0);		break;
						case 2: Serial.println("L2"); Device.isLEDHack = true;	Device.HackLED =  Device.LEDs.Color(255, 170,   0);		break;
						case 3: Serial.println("L3"); Device.isLEDHack = true;	Device.HackLED =  Device.LEDs.Color(170, 255,   0);		break;
						case 4: Serial.println("L4"); Device.isLEDHack = true;	Device.HackLED =  Device.LEDs.Color(  0, 255,   0);		break;
						case 5: Serial.println("L5"); Device.isLEDHack = true;	Device.HackLED =  Device.LEDs.Color(  0, 255, 170);		break;
						case 6: Serial.println("L6"); Device.isLEDHack = true;	Device.HackLED =  Device.LEDs.Color(  0, 170, 255);		break;
						case 7: Serial.println("L7"); Device.isLEDHack = true;	Device.HackLED =  Device.LEDs.Color(  0,   0, 255);		break;
						case 8: Serial.println("L8"); Device.isLEDHack = true;	Device.HackLED =  Device.LEDs.Color(170,   0, 255);		break;
						case 9: Serial.println("L9"); Device.isLEDHack = true;	Device.HackLED =  Device.LEDs.Color(255,   0, 170);		break;
					}

				}


			Device.TimeCountTouch = millis();	//最後にタッチした時間を計測
			Device.BTSerial.flush();
		} 
    

    
  }


  	//////////////////////////////////////////////////////////////////////
	//  	void SendDATA(){
	//////////////////////////////////////////////////////////////////////
	void SendDATA(){
		String msg = "SendDATA,";
		msg += "Mouth," + String(Device.Sensor.Mouth.SData) +",";
		msg += "Level," + String(Device.Sensor.Level.SData) +",";

		if(Device.mag_SendDATA != msg){
			Device.BTSerial.println(msg);	//BTにデータを送信する
		}
		//Serial.print("Send DATA ***************************** \t");
		//Serial.println(msg);
		Device.mag_SendDATA = msg;

	}

  	//////////////////////////////////////////////////////////////////////
	//  	void SendTASK(){
	//////////////////////////////////////////////////////////////////////
	void SendTASK(){
		String msg = "SendTASK,";
		
		//タスク情報の送信
		for(int i=0;i<TASK_Name_End;i++){
			msg += (String(Device.TASK[ i ].Name) +",");
			msg += (String(Device.TASK[ i ].Status) +",");
			msg += (String(Device.TASK[ i ].Priority) +",");
		}

		//制御状態の送信

		msg += "Feeing,"      + String( Device.TASK[ GetNo_TASK_Mood(TASK_Name_Emerg) ].Enable) +",";		//Emerg制御の有無

		int infoData =1;
		if(Device.Sensor.Level.isHack  == true){	if(Device.Sensor.Level.HackData == 5000){		infoData =2;	}else{	infoData =0; }	}else{		infoData =1;	 }
		msg += "LevelHack,"   + String( infoData   ) +",";		//Level制御の有無

		if(Device.Sensor.Mouth.isHack  == true){	if(Device.Sensor.Mouth.HackData == 5000){		infoData =2;	}else{	infoData =0; }	}else{		infoData =1;	 }
		msg += "MouthHack,"   + String( infoData   ) +",";	//Mouth制御の有無

		if(Device.Sensor.Diapers.isHack  == true){	if(Device.Sensor.Diapers.HackData ==5000){		infoData =2;	}else{	infoData =0; }	}else{		infoData =1;	 }
		msg += "DiapersHack," + String( infoData ) +",";		//Mouth制御の有無

		
		if(Device.Motor[ Motor_Ink_Red ].Ratio ==100){
			msg += "Ink,0,";
		}else if(Device.Motor[ Motor_Ink_Yellow ].Ratio ==100){
			msg += "Ink,2,";
		}else{
			msg += "Ink,1,";
		} 
		
		msg+= "Mood," + String( Device.isMoodHack );
	
		Device.BTSerial.println(msg);	//BTにデータを送信する

//		Serial.println("Send TASK *************************************************:" + msg);
	}


  	//////////////////////////////////////////////////////////////////////
	//  RetunValue04
	//////////////////////////////////////////////////////////////////////
	int RetunValue04( String  data , int n ){

		char Buf[10];
		data.toCharArray(Buf, 10);

		char   tmp[5];
			tmp[0] = Buf[ n + 0 ];
			tmp[1] = Buf[ n + 1 ];
			tmp[2] = Buf[ n + 2 ];
			tmp[3] = Buf[ n + 3 ];
			tmp[4] = '\0'; 
		return atoi(tmp);  
	}

	//////////////////////////////////////////////////////////////////////
	//  RetunValue03
	//////////////////////////////////////////////////////////////////////
	int RetunValue03( String  data , int n ){

		char Buf[10];
		data.toCharArray(Buf, 10);

		char   tmp[4];
			tmp[0] = Buf[ n + 0 ];
			tmp[1] = Buf[ n + 1 ];
			tmp[2] = Buf[ n + 2 ];
			tmp[3] = '\0'; 
		return atoi(tmp);  
	}

	//////////////////////////////////////////////////////////////////////
	//  RetunValue02
	//////////////////////////////////////////////////////////////////////
	int RetunValue02( String  data , int n ){

		char Buf[10];
		data.toCharArray(Buf, 10);

		char   tmp[3];
			tmp[0] = Buf[ n + 0 ];
			tmp[1] = Buf[ n + 1 ];
			tmp[2] = '\0'; 
		return atoi(tmp);  
	}	


	//////////////////////////////////////////////////////////////////////
	//  RetunValue01
	//////////////////////////////////////////////////////////////////////
	int RetunValue01( String  data , int n ){

		char Buf[10];
		data.toCharArray(Buf, 10);

		char   tmp[3];
			tmp[0] = Buf[ n + 0 ];
			tmp[1] = '\0'; 
		return atoi(tmp);  
	}	