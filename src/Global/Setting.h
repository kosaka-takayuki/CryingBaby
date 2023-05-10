#define LGFX_AUTODETECT // 自動認識 (D-duino-32 XS, PyBadge はパネルID読取りが出来ないため自動認識の対象から外れています)
#define LGFX_USE_V1

#pragma once 
#ifndef SETTING_H
#define SETTING_H


#include <M5Core2.h>
#include "Global/Setting.h"             // 共通変数 
#include "Global/Enum.h"                // 共通変数
#include "Global/PCA9554.h"				// PCA9554
#include "Global/Setting.h"             // シリアル


#include <LovyanGFX.hpp>				// LovyanGFX
#include <LGFX_AUTODETECT.hpp>          // クラス"LGFX"を用意します

#include "BluetoothSerial.h"   		    // Bluetoothを使う設定
#include "AquesTalk/AquesTalkTTS.h"     // AquesTalkTTS
#include <Adafruit_NeoPixel.h>          // LEDテープ制御

#include "Device/Sensor/DataStock.h" 	//Sensor
#include "Device/Sensor/SensorData.h" 	//Sensor
#include "Device/MotorPump.h"			//モータ

#include "DFPlayer/Mp3Notify.h"		    //MP3

#include "TASK/GetSensorTASK.h"

#include "CryTASK/CryTASK.h"

#include "Button/ButtonInfo.h"
#include "Button/Button_Square.h"


    /////////////////////////////////////////////////////
    //共通変数
    /////////////////////////////////////////////////////

            //********************************
            //構造体
            //********************************

                ///////////////////////////////////////////////
                //バッテリー関係
                ///////////////////////////////////////////////
                struct BatteryInfo{
                    boolean isUSB; //USB充電の有無 
                    int     Level; //バッテリーレベル(0-100%)
                    float   Volt;
					unsigned long	GetTime;  			//１秒増加を計測

                };

                ///////////////////////////////////////////////
                //MP3　デバイス
                ///////////////////////////////////////////////
                typedef enum {
                    kPOWER_EXTERNALB = 0,
                    kPOWER_INTERNALB,
                    kPOWER_MAXB
                }system_power_tB;

                ///////////////////////////////////////////////
                //RGBInfo 構造体
                ///////////////////////////////////////////////
                struct RGBInfo{
                    int R;
                    int G;
                    int B;
                };


				//********************************
				//DeviceCheck
				//********************************
				struct DeviceCheck{
					boolean isSDCard;          	//SDカードの有無
					boolean isFile_Interval;   	//ファイル読み込みの有無
					boolean isFile_Threshold;	//ファイル読み込みの有無
					boolean isDFPlayer;			//DFPlayer接続の有無
					boolean isIMU;				//IMU接続の有無
					boolean isDeviceClear;		//クリアできるか？
				};		




	//********************************
    //Device class
    //********************************
    class DeviceInfo{
            public:

				boolean 	isHelp =false;	//ヘルプモード　しゃべるか、しゃべらないか

				String BabyName ="";
				boolean isMainBatteryConnect =true;			//メインバッテリーに接続されていないとき　つまりデバック時のこと

				boolean 	isLEDHack = false;
				uint32_t 	HackLED;

				boolean 	isDemo = false;

                //ピン設定
                int pinNo_Sensor_S0		= 32;   //センサ S0
                int pinNo_Sensor_S1		= 26;   //センサ S1
                int pinNo_Sensor_S2		= 27;   //センサ S2
                int pinNo_Sensor_S3		= 19;   //センサ S3
                int pinNo_LED			= 25;   //LED
                int pinNo_DFPlayerBussy	= 33;   //MP3 Bussy
                int pinNo_Sensor_SIG	= 35;	//入力ピン

                // ---macアドレス
                char PhysicalAddress[40];

				//  --- AquesTalk関係 ---
				const char* AquesTalk_LicenceKey = "86BB-BF76-F6AD-03D2";  // AquesTalk-ESP32 licencekey

				boolean 	isAquesTalk = true;		//喋る
                AquesTalkTTS AquesTalk;         	// AquesTalkTTS関係

                //Bluetoothシリアル
                BluetoothSerial BTSerial;       // Bluetoothシリアル
				String 			mag_SendDATA;

                //--- 日時 ---
				String 			DateString ="";
				String 			TimeString ="";
				unsigned long	TimeRTC;  			//１秒増加を計測

			  	unsigned long  TimeCountTASKBack ;       //時間経過計算　タスクの時間軸
			  	unsigned long  TimeCountRunBack ;        //時間経過計算　実行中の時間軸
			  	unsigned long  TimeFileSaveBack ;        //時間経過計算　ファイル保存
				int			   CryIntervalFileSaveTime = 10000;	//ファイルを保存する時間
																// 10秒間隔 10000
																// 20秒間隔 20000
																// 30秒間隔 30000
																// 60秒間隔 60000

				//省エネ設定
				unsigned long  	TimeCountTouch;			//最後にタッチしてからの経過時間
				int			isLcdPower;
				int			isLcdPowerOLD;


				boolean			isMoodHack = false;			//ハックの有無　Trueの場合、強制100になる
	

                //--- バッテリー情報 ---
                BatteryInfo Battery;            				// バッテリー情報
                String      BatteryString_P="";					// バッテリー %
                String      BatteryString_V="";					// バッテリー Volt

                //--- 各種データ ---
                Adafruit_NeoPixel	LEDs; 						// LED
				uint32_t 			LED_OLD;					// LED
//				PCA9554 			*EXP_IO;  					// Create an object at this address
				SensorData			Sensor;						//センサデータ
				MotorPump			*Motor;						//モータ
				DeviceCheck isCheck;							//デバイスチェック構造体
				portMUX_TYPE mutex = portMUX_INITIALIZER_UNLOCKED;	//他の処理で使わないように排他制御する仕組 宣言をしたときに、他の処理が使っていた場合には使えるようになるまで待機します。

				
                //  --- LCD画面関係 ---
				LGFX LCD;              							// LGFXのインスタンスを作成。
				LGFX_Sprite 	LCD_Sprite; 					// スプライトを使う場合はLGFX_Spriteのインスタンスを作成。
				LGFX_Sprite 	LCD_Message; 					// スプライトを使う場合はLGFX_Spriteのインスタンスを作成。
				Point 			LCD_Tocuh;						//タッチ座標
				Point 			LCD_Tocuh_Sprite;				//スポライト	左右にタッチ時に出現するバーの座標

                //  --- メッセージ ---
   				String OutPutMSG="";							//出力メッセージ
				String OutPutFileName ="/logs/2022_12_19.txt";  //出力ファイル名　日付付き


                //--- 画面推移  ---
                unsigned  long 		TimeModeChangeElapsed;      //モードが変更してからの経過時間
                boolean        		isModeChangeFirstTime;      //モードが変更してからの一度だけ実行
//				int			   		AnimationdelayTime =100;			//アニメーション用
				int 		   		ScreenNo =0;						//現在のスクリーン情報
				ScreenChangeButton	ScreenButton;

				//Touch
				int M5Touch = false;


                //MP3
                int isMp3DeviceCheckStatus  = -1;				//チェック用　これを最初のチェック以外使わない
				boolean isMp3SoundPlay = false;					//再生中の有無
  				unsigned long TimeMp3Play2Bussy;         		//PLAYしてからの時間
				int 	Mp3Volume =10;							//再生ボリューム　5
				int 	M5Volume =100;

				//MP3 SDフォルダの番号03-10に格納されている、MP3の数を格納
				int MP3_FoolderNo[20];							//フォルダーの数
				int MP3_PlayBackNo[3];							//過去3回の再生番号を記録


	            boolean isWriteData  = false;        			//データ出力の有無

				struct  InfoData InfoData[13];      			//Info用 表示有無

				// FPS設定
				struct FPS FPS[2];


				//ボタン
				ButtonInfo 		*Button;
                ButtonSquare    *Button_Square;


/*
				uint32_t 		FPS_pSec=0;
				uint32_t 		FPS_Sec=0;
				int				FPS_Count =0; 
				int				FPS; 							//FPS
				int 			FPS_B;
*/
				//CryTASK
				CryTASK *TASK;
				TASK_Info_Title TASK_Title[TASK_Name_End];
				String TaskSendMSG="Task,Power,2,1,Hungry,1,2,Shit,1,3,Sleep,1,4,Mood,1,5,Wait,3,-1,Emerg,3,-1,Diapers,3,-1";


				
				int Water_Threshold =100;
				unsigned char Water_low_data[8] = {0};
				unsigned char Water_high_data[12] = {0};	




	};
		extern DeviceInfo Device;



#endif
