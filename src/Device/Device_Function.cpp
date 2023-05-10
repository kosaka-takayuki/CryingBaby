#include "Device/Device_Function.h"
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//バッテリー情報の取得
// バッテリー　M5関数なのでTASK化できない
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void GetBattery(){
		BatteryInfo tmp;

		//USB電源供給中であるかチェックする
		system_power_tB PowerNow = ( M5.Axp.isACIN()) ? kPOWER_EXTERNALB : kPOWER_INTERNALB;
		if (  PowerNow == kPOWER_EXTERNALB ){
			tmp.isUSB = true;
		}else{
			tmp.isUSB = false;
		}
		M5.Axp.SetCHGCurrent(AXP192::kCHG_1320mA);
		//バッテリー残量チェック
		float         batVoltage = M5.Axp.GetBatVoltage();                        //バッテリー Vの取得

		tmp.Volt = batVoltage;
		//バッテリー残量
			// M5は3.2Vあれば起動できる
			// 3.2V以下であれば0%
			// BatteryはMAX3.8Vと過程
		if( batVoltage < 3.3 ){
			tmp.Level  = 0;
		}else{
			//残量は3.8V -3.3V = 0.6V がMAXと過程
			tmp.Level= maps(batVoltage*100 , 330 ,370, 0.0f, 100.0f);
		}

		//ハック
		if( Device.Sensor.Battery.isHack 	 == true){	
			tmp.isUSB = false;
			tmp.Level = Device.Sensor.Battery.HackData; 		
		} 


		//////////////////////////////

/*
		//画面更新
		if(tmp.V != Device.Battery.V){				Device.InfoData[ 2 ].MSG_OLD ="-1";		}
		if(tmp.isUSB != Device.Battery.isUSB){		Device.InfoData[ 2 ].MSG_OLD ="-1";		}
*/

		Device.Battery = tmp;

	} 


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//SetLEDs
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void SetTapeLEDs(int _Br, int _r, int _g,int _b){

		//非制御時　TASK実行時
		Device.LEDs.setBrightness(_Br);                           //LED 明るさ調整
		Device.LEDs.setPixelColor(0, Device.LEDs.Color(_r, _g, _b)); //0番目　のLEDをセット
		Device.LEDs.setPixelColor(1, Device.LEDs.Color(_r, _g, _b)); //1番目　のLEDをセット
		Device.LEDs.show(); 

	}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DrawTimeGauge
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawTimeGauge(int _dx,int _dy, int _dw, int dh,  int _count , unsigned int BreakTime,int Type_No){

	int w = _dw / (_count+1);
	int s = (_dw - (w*_count))/ (_count-1);

	Device.TimeModeChangeElapsed = millis();	//時間記録
	
	int Back_c =-1;


	while(1){
		int c = maps( millis()- Device.TimeModeChangeElapsed ,0,BreakTime,0,_count);
		if(c!=Back_c){
			for(int i=0;i<_count;i++){
				if(i <= c){
					Device.LCD_Sprite.fillRoundRect (_dx+((w+s)*i),_dy,w,dh,2,BaseColor_Orange);	
				}else{
					Device.LCD_Sprite.fillRoundRect (_dx+((w+s)*i),_dy,w,dh,2,BaseColor_Black);	
				}
			}
			Device.LCD_Sprite.pushSprite(&Device.LCD,10,10);
		}
		Back_c = c;


		if ( millis() - Device.TimeModeChangeElapsed > BreakTime) {   break;    }
		if (Type_No ==2 && Device.isMp3DeviceCheckStatus != -1) {  break;    }							///DFPLAYER

	}

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GetDFPlayer
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetDFPlayer(void* arg){  					//DFPlayer接続 TASK実行

	OutPutLogs(LogCode_Info,4,"--- START TASK DFPlayer ---");    //Log出力
	Device.isMp3DeviceCheckStatus  = -1;

	MP3.stop();
	MP3.reset();
	MP3.begin();            //mp3初期化
	delay(2000);
	MP3.setVolume(10);  //DFPlayerの出力音量 From 0 to 30

	Device.isMp3DeviceCheckStatus  = MP3.getStatus();

	OutPutLogs(LogCode_Info,4,"--- END TASK DFPlayer ---");    //Log出力
	vTaskDelete(NULL);		//タスク終了

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GetSensorReadMux
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int	GetSensorReadMux( int _channel){
		int controlPin[] = { Device.pinNo_Sensor_S0, Device.pinNo_Sensor_S1, Device.pinNo_Sensor_S2, Device.pinNo_Sensor_S3};
		int muxChannel[16][4]={
			{0,0,0,0}, //channel 0
			{1,0,0,0}, //channel 1
			{0,1,0,0}, //channel 2
			{1,1,0,0}, //channel 3
			{0,0,1,0}, //channel 4
			{1,0,1,0}, //channel 5
			{0,1,1,0}, //channel 6
			{1,1,1,0}, //channel 7
			{0,0,0,1}, //channel 8
			{1,0,0,1}, //channel 9
			{0,1,0,1}, //channel 10
			{1,1,0,1}, //channel 11
			{0,0,1,1}, //channel 12
			{1,0,1,1}, //channel 13
			{0,1,1,1}, //channel 14
			{1,1,1,1}  //channel 15
		};
		//loop through the 4 sig
		for(int i = 0; i < 4; i ++){
			digitalWrite(controlPin[i], muxChannel[_channel][i]);
		}

		//read the value at the SIG pin
		int val = analogRead(Device.pinNo_Sensor_SIG);


	//	delay(10);
		return val;						//return the value

	}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//IMU情報の取得
// GetIMU　M5関数なのでTASK化できない
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void GetM5Decice(){

		/////////////////////////
		//バッテリー取得
		/////////////////////////
		if( (millis() - Device.Battery.GetTime) >=30000  ){ //30秒に１回計測 
			GetBattery();  //バッテリー接続状況チェック 常にバッテリーを監視するとCPUパワーを取られるので10秒に１回
			Device.Battery.GetTime = millis();
		}


		////////////////////////////////////////////////////////
		// IMU
		////////////////////////////////////////////////////////
			float accX = 0;
			float accY = 0;
			float accZ = 0;
			float pitch = 0;
			float roll = 0;
			float yaw = 0;

			//加速度の検出
			M5.IMU.getAccelData(&accX, &accY, &accZ);
			float 	mg = abs(sqrt( (accX *accX) +(accY*accY) +(accZ*accZ)  )  -1.0f) ;		//XYZ軸のMGを求める。下軸方向の重力加速度(1.0)を引く。単位はG
//			Device.Sensor.SensorTMP[ Sensor_IMU ].Data = mg;
			Device.Sensor.SensorTMP[ Sensor_IMU  	].AddData(  mg  );		//Sensor_IMU
			Device.Sensor.SensorTMP[ Sensor_IMU  	].Data2   = mg;			//Sensor_IMU TPMの検出に取得
			// 通常			： 0.0 - 0.02
			// トントン		： 0.3 -0.5
			//　衝撃		： 0.5 -


			/////////////////////////////////////////////////
			//向きの検出
			/////////////////////////////////////////////////
			M5.IMU.getAhrsData(&pitch,&roll,&yaw);
			float angle = maps(roll,-180,180 , 0, 360);

			int Position =0;

			if((angle >=0 && angle <=45) || (angle >=315 && angle <=360)){
				Position   = (float)Position_Supine;			//仰臥位
			}else if(angle >=45 && angle <=135){
				Position   = (float)Position_Inversus;		//逆さ
			}else if(angle >=135 && angle <=202.5){
				Position   = (float)Position_Depression;		//うつむせ
			}else if(angle >=202.5 && angle <=315){
				Position  = (float)Position_Standing;		//起きる
			}
			if(Device.Sensor.Position.isHack == false){	Device.Sensor.Position.Data	=	Position;}








			//////////////////////////////////////////////////////
			// Mp3　
			///////////////////////////////////////////////////////
			if( (millis()-Device.TimeMp3Play2Bussy) >= 500){
				if (Device.isMp3SoundPlay == true && digitalRead( Device.pinNo_DFPlayerBussy )== HIGH) {
					//もし、いま再生中フラグが立ち上がったままで、また、BUSSYピンがHIGHの時（再生終了の時）
					Device.isMp3SoundPlay = false;

				}
			}

	} 


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//MP3_KingLoopPlay
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void MP3_KingLoopPlay( int Kind , float gain ){

		if( Device.isCheck.isDFPlayer == true){
			if(Device.isMp3SoundPlay == false){

				MP3.setVolume( (int)maps(gain,0,100,0,30) );
				int SoundNo =1;
//				Serial.println("MP3 PLAY LOOP");
//				Serial.println(NoToMP3FolderString(Kind));

//				Serial.print("\t" 	+(String)Device.MP3_PlayBackNo[0] );
//				Serial.print("\t" 	+(String)Device.MP3_PlayBackNo[1] );
//				Serial.println("\t" +(String)Device.MP3_PlayBackNo[2] );
//					Serial.print("\t Kind:" +(String)Kind );
//					Serial.println( "\t" + (String)Device.MP3_FoolderNo[ Kind ]   );

				do{
					if(Device.isHelp == true){
						SoundNo = random(0,  Device.MP3_FoolderNo[ Kind ] ) +1 ;
					}else{
						SoundNo = random(1,  Device.MP3_FoolderNo[ Kind ] ) +1 ;
					}
				}while (SoundNo == Device.MP3_PlayBackNo[0] || SoundNo == Device.MP3_PlayBackNo[1] ||
						SoundNo == Device.MP3_PlayBackNo[2] );    //前回と重複しない

//				Serial.print("*********** Kind:" +(String)Kind );
//				Serial.println("\t No:" +(String)SoundNo );
				MP3.stop();
				MP3.playFolderTrack( Kind , SoundNo );
				MP3.start();

//				Device.MP3_PlayBackNo[3] = Device.MP3_PlayBackNo[2];
				Device.MP3_PlayBackNo[2] = Device.MP3_PlayBackNo[1];
				Device.MP3_PlayBackNo[1] = Device.MP3_PlayBackNo[0];
				Device.MP3_PlayBackNo[0] = SoundNo;	//再生番号を記録
				Device.isMp3SoundPlay = true;	//再生中
				Device.TimeMp3Play2Bussy= millis();     //再生時の時間を計測

			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//GetStatus
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	String GetStatus(int no){
		String  MSG ="";

		switch (no){
			case TASK_Status_Count:			MSG= "Count";			break;
			case TASK_Status_Wait:			MSG= "Wait";			break;
			case TASK_Status_Run:			MSG= "Run";				break;
			case TASK_Status_Non:			MSG= "Non";				break;
			case TASK_Status_RunSuspend:	MSG= "Suspend";			break;
			default:						MSG= "Error";			break;
		}

		return  MSG;
	}



	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//SetTapeLEDsLoop
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void SetTapeLEDsLoop( int no){
		int r,g,b;

		if(no == -1){
		
			//なにもしていない時
			//			Device.TASK[ RunNo ].SetLED_Loop(new TimeLED(0,1000, Device.LEDs.Color( 64, 0, 0)), new TimeLED(1000,2000, Device.LEDs.Color( 32,  0,  0)) ); 
			TimeLED LED_START 	= TimeLED(   0,1000, Device.LEDs.Color( 64,  0,  0) );
			TimeLED LED_END		= TimeLED(1000,2000, Device.LEDs.Color( 32,  0,  0) );

			int  len  = LED_END.TimeEnd;
			uint32_t sc = LED_START.Color;
			uint8_t start_R = (uint8_t)(sc >> 16),
					start_G = (uint8_t)(sc >>  8),
					start_B = (uint8_t)sc;

			uint32_t ec = LED_END.Color;
			uint8_t end_R = (uint8_t)(ec >> 16),
					end_G = (uint8_t)(ec >>  8),
					end_B = (uint8_t)ec;

			 r =  maps_Between( (millis()%len),
									LED_START.TimeStart , LED_START.TimeEnd , (long)start_R ,(long)end_R,
									LED_END.TimeStart   , LED_END.TimeEnd   , (long)end_R, (long)start_R);
			 g =  maps_Between( (millis()%len),
									LED_START.TimeStart , LED_START.TimeEnd , (long)start_G ,(long)end_G,
									LED_END.TimeStart   , LED_END.TimeEnd   , (long)end_G,(long)start_G);
			 b=  maps_Between( (millis()%len),
									LED_START.TimeStart , LED_START.TimeEnd , (long)start_B ,(long)end_B,
									LED_END.TimeStart   , LED_END.TimeEnd   , (long)end_B,(long)start_B);

		}else{
			//通常タスクk時
			int  len  = Device.TASK[ no ].LED_END.TimeEnd;
			uint32_t sc = Device.TASK[ no ].LED_START.Color;
			uint8_t start_R = (uint8_t)(sc >> 16),
					start_G = (uint8_t)(sc >>  8),
					start_B = (uint8_t)sc;

			uint32_t ec = Device.TASK[ no ].LED_END.Color;
			uint8_t end_R = (uint8_t)(ec >> 16),
					end_G = (uint8_t)(ec >>  8),
					end_B = (uint8_t)ec;

			 r =  maps_Between( (millis()%len),
									Device.TASK[ no ].LED_START.TimeStart ,Device.TASK[ no ].LED_START.TimeEnd , (long)start_R ,(long)end_R,
									Device.TASK[ no ].LED_END.TimeStart   ,Device.TASK[ no ].LED_END.TimeEnd   , (long)end_R, (long)start_R);
			 g =  maps_Between( (millis()%len),
									Device.TASK[ no ].LED_START.TimeStart ,Device.TASK[ no ].LED_START.TimeEnd , (long)start_G ,(long)end_G,
									Device.TASK[ no ].LED_END.TimeStart   ,Device.TASK[ no ].LED_END.TimeEnd   , (long)end_G,(long)start_G);
			 b=  maps_Between( (millis()%len),
									Device.TASK[ no ].LED_START.TimeStart ,Device.TASK[ no ].LED_START.TimeEnd , (long)start_B ,(long)end_B,
									Device.TASK[ no ].LED_END.TimeStart   ,Device.TASK[ no ].LED_END.TimeEnd   , (long)end_B,(long)start_B);
		}

	    Device.LEDs.setBrightness(32);                           //LED 明るさ調整

		uint32_t _ledColor = Device.LEDs.Color(r, g, b);

		//ハックモード
		if(Device.isLEDHack == true){
			_ledColor = Device.HackLED;
		}


		if(_ledColor != Device.LED_OLD){				//過去のデータと異なるときのみ実行
			Device.LEDs.setPixelColor(0, _ledColor); //0番目　のLEDをセット
			Device.LEDs.setPixelColor(1, _ledColor); //1番目　のLEDをセット
			Device.LEDs.show(); 


//			Serial.print(String(start_R) +"\t" +String(start_G) +"\t" +String(start_B) +"\t\t" );
//			Serial.print(String(end_R) +"\t" +String(end_G) +"\t" +String(end_B) +"\t\t" );


//			Serial.println(String(r) +"\t" +String(g) +"\t" +String(b) +"\t" );
		}
		Device.LED_OLD = _ledColor;	//過去データ

	}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//getHigh12SectionValue
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getLow8SectionValue(void){
	byte _adress =0x77;
	memset(Device.Water_low_data, 0, sizeof(Device.Water_low_data));
	Wire1.requestFrom(_adress, 8);
	while (8 != Wire1.available());
	for (int i = 0; i < 8 ; i++) {
		Device.Water_low_data[i] = Wire1.read(); // receive a byte as character
	}
	delay(10);
}

void GetWaterSensor(){
	int sensorvalue_min = 250;
	int sensorvalue_max = 255;
	int low_count = 0;
	int high_count = 0;

		uint32_t touch_val = 0;
		uint8_t trig_section = 0;
		low_count = 0;
		high_count = 0;
		getLow8SectionValue();

		Serial.println("low 8 sections value = ");
		
		for (int i = 0; i < 8; i++){
			Serial.print(Device.Water_low_data[i]);
			Serial.print(".");
			if (Device.Water_low_data[i] >= sensorvalue_min && Device.Water_low_data[i] <= sensorvalue_max){
				low_count++;
			}
			if (low_count == 8){
				Serial.print("      ");
				Serial.print("PASS");
			}
		}
		Serial.println("  ");
		Serial.println("  ");

		for (int i = 0 ; i < 8; i++) {
			if (Device.Water_low_data[i] > Device.Water_Threshold) {		touch_val |= 1 << i						;	}
		}
		for (int i = 0 ; i < 12; i++) {
			if (Device.Water_high_data[i] > Device.Water_Threshold) {		touch_val |= (uint32_t)1 << (8 + i);		}
		}

		while (touch_val & 0x01){
			trig_section++;
			touch_val >>= 1;
		}

		Serial.print("water level = ");
		Serial.print(trig_section * 5);
		Serial.println("% ");

}