
#define LGFX_M5STACKCORE2
#define LGFX_USE_V1

#include <M5Core2.h>
#include <LovyanGFX.hpp>

#include <Global/Setting.h>		//共通変数
#include <Global/Function.h>	//共通関数
#include <Global/Serial.h>

#include <Device/Device_Function.h>	//共通関数

#include "Device/Initialize.h"		//Initialize
#include "Device/SystemCheck.h"		//SystemCheck

#include "TASK/GetSensorTASK.h"
#include "TASK/FileSaveTASK.h"
#include "TASK/CryTASK_Execution.h"

#include "Time/TimeCount.h"
#include "Screen/SystemInfo.h"
#include "Screen/TASKMonitor.h"
#include "Screen/CryTASK/Emergency.h"
#include "Screen/CryTASK/Mood.h"
#include "Screen/CryTASK/Hungry.h"
#include "Screen/CryTASK/Burp.h"
#include "Screen/CryTASK/Shit.h"
#include "Screen/CryTASK/Diapers.h"
#include "Screen/CryTASK/Sleep.h"
#include "Screen/Error.h"
#include "Screen/DeviceSet.h"
#include "Screen/CryTASK/Sleeping.h"

int scani2caddr() {
    for (int i = 0; i < 120; i++) {
        Wire1.beginTransmission(i);
        if (Wire1.endTransmission() == 0) {
            Serial.printf("0x%02X (%d) \t|FIND", i, i );

			switch(i){
				case  52:	Serial.printf(" AXP192\tPOWER");	break;		//0x34
				case  56:	Serial.printf(" FT6336V\tTouch");	break;	//0x38
				case  81:	Serial.printf(" BM8563\tRTC");	break;		//0x51

				case  96:	Serial.printf(" Pomp A");	break;		//0x60
				case  98:	Serial.printf(" Pomp B");	break;		//0x62

				case 104:	Serial.printf(" MPU6886\tIMU");	break;		//0x68

			}



            Serial.println(".");
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////
// setup
//////////////////////////////////////////////////////////////////////
void setup() {

	M5.begin(true, true, true, false); //LCD , SD, Serial, I2C
//	M5.begin(true, true, true, true); //LCD , SD, Serial, I2C

    Wire1.begin(21, 22, 100000UL);
scani2caddr();

 uint8_t macBT[6];
  esp_read_mac(macBT, ESP_MAC_BT);
  Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\r\n", macBT[0], macBT[1], macBT[2], macBT[3], macBT[4], macBT[5]);



	OutPutLogs(LogCode_Info,0,"-----------------------------------------------------------");     //Log出力
	OutPutLogs(LogCode_Info,0,"--- M5 setup Begin ---");     //Log出力

	OutPutLogs(LogCode_Info,1,"--- Battery Check");    //Log出力
	////////////////////////////////////////////////
	//Battery　Check
	////////////////////////////////////////////////
	GetBattery();	//バッテリー情報取得
	if(Device.Battery.isUSB == true){
		OutPutLogs(LogCode_Info,3,"+- USB Connect");    //Log出力
	}else{
		OutPutLogs(LogCode_Info,3,"+- USB Disconnect");    //Log出力
	}
	OutPutLogs(LogCode_Info,4,"+- "+String(Device.Battery.Level) +"% \t" +String(Device.Battery.Volt)+"V ---");    //Log出力
	
	Initialize();	//Initialize関数	
	

  	SystemCheck();	//システムチェック	//第1引数:wifiチェックの有無、第2引数:isDFPlayのチェックの有無

	////////////////////////////////////////////////
	//Bluetooth開始
	////////////////////////////////////////////////
	Device.BTSerial.begin("CryingBaby(" + Device.BabyName +")");            //PC側で確認する時の名前
			

	///////////////////////////////////////////////////////////////
  	//マルチスレッド起動
	///////////////////////////////////////////////////////////////
		OutPutLogs(LogCode_Info,1,"--- Thread begin ---");     //Log出力
		
		xTaskCreatePinnedToCore( GetSensorTASK 	, "GetSensorDviceTASK"	,   4096, NULL, 1, NULL, 1);
		//xTaskCreatePinnedToCore( FileSaveTASK 	, "FileSaveTASK"		,   4096, NULL, 2, NULL, 0);

		
		//xTaskCreatePinnedToCore( GetSensorTASK 	, "GetSensorDviceTASK"	,   4096, NULL, 1, NULL, 1);
		//xTaskCreatePinnedToCore( FileSaveTASK 	, "FileSaveTASK"		,   4096, NULL, 2, NULL, 0);


		OutPutLogs(LogCode_Info,1,"--- Thread end ---");     //Log出力
		delay(10);

	OutPutLogs(LogCode_Info,0,"--- M5 setup End ---\n\n");     //Log出力


	//////////////////////////////////////////////////////////
	//起動直後だと、センサ値が0なのでしばらく待つ
	//////////////////////////////////////////////////////////
	for(int i=0;i<64;i++){
		SetTapeLEDs(64, i, 0, 0); //LEDセット 
		delay(10);
	}

		Device.TimeModeChangeElapsed = millis();
	Device.isModeChangeFirstTime =false;


}
//////////////////////////////////////////////////////////////////////
// loop
//////////////////////////////////////////////////////////////////////
void loop() {

	FPS( 0 ); 				//FPS計算
	SerialRead();				//シリアル通信
	TimeCount(1.0f);			//時間計算 (x速度)
	CryTASK_Execution(1.0f);	//タスク処理 (x速度)
	SwipeScreen();

	switch(Device.ScreenNo){
		case -1:
			Error();
			break;
		case Screen_Info:
			Info();				//インフォメーション表示
			break;
		case Screen_TASKMonitor:					//TASK表示
			TASKMonitor();
			break;

		case Screen_Emergency:					//TASK表示
			Emergency();		//Emergency
			break;
		case Screen_Mood:					//TASK表示
			Mood();				//Emergency
			break;
		case Screen_Hungry:					//TASK表示
			Hungry();			//Hungry
			break;
		case Screen_Burp:
			Burp();				//げっぷ
			break;
		case Screen_Shit:
			Shit();				//おしっこ
			break;
		case Screen_Diapers:
			Diapers();			//おむつ
			break;

		case Screen_Sleep:					//デバイスセット
			Sleep();	
			break;

		case Screen_Sleeping:				//デバイスセット
			Sleeping();	
			break;


		case Screen_Device:					//デバイスセット
			DeviceSet();	
			break;

	}

	vTaskDelay(1);


}


  

