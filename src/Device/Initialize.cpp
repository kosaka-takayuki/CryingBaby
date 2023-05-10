#include "Device/Initialize.h"

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialize
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Initialize(){
  OutPutLogs(LogCode_Info,1,"--- Initialize Begin --");    //Log出力

        ////////////////////////////////////////////////
        //ピン設定
        ////////////////////////////////////////////////
		pinMode(Device.pinNo_DFPlayerBussy,	 INPUT);      
		pinMode(Device.pinNo_Sensor_S0, 	 OUTPUT); 
		pinMode(Device.pinNo_Sensor_S1, 	 OUTPUT); 
		pinMode(Device.pinNo_Sensor_S2,		 OUTPUT); 
		pinMode(Device.pinNo_Sensor_S3,		 OUTPUT); 
		pinMode(Device.pinNo_DFPlayerBussy,	 INPUT); 
		digitalWrite(Device.pinNo_Sensor_S0, LOW);
		digitalWrite(Device.pinNo_Sensor_S1, LOW);
		digitalWrite(Device.pinNo_Sensor_S2, LOW);
		digitalWrite(Device.pinNo_Sensor_S3, LOW);



        ////////////////////////////////////////////////
        //マックアドレス取得
        ////////////////////////////////////////////////
        OutPutLogs(LogCode_Info,3,"+- PhysicalAddress");    //Log出力
        uint8_t mac[6];
        esp_efuse_mac_get_default(mac);
        sprintf(Device.PhysicalAddress, "%02X:%02X:%02X:%02X:%02X:%02X",mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

        OutPutLogs(LogCode_Info,4,"+- "+ String(Device.PhysicalAddress) );    //Log出力


		////////////////////////////////////////////////
        //TASK処理
        ////////////////////////////////////////////////
        OutPutLogs(LogCode_Info,3,"+- TASK CLS begin");    //Log出力
		Device.TASK = 	new CryTASK[ TASK_Name_End ];


     	
//delay(3000);
        ////////////////////////////////////////////////
        //スピーカー設定
        ////////////////////////////////////////////////
        OutPutLogs(LogCode_Info,3,"+- Speaker Enable");    //Log出力
        M5.Axp.SetSpkEnable(true);    //スピーカー設定

        ////////////////////////////////////////////////
        //LED設定
        ////////////////////////////////////////////////
        OutPutLogs(LogCode_Info,3,"+- Neopixel LED ");    //Log出力
        Device.LEDs.updateLength(2);                              //LED 2個
        Device.LEDs.setPin(Device.pinNo_LED);                                   //LED 32ピン
        Device.LEDs.updateType(NEO_GRB + NEO_KHZ800);             //LED TYOE
        Device.LEDs.setBrightness(128);                           //LED 明るさ調整
        Device.LEDs.begin();
        Device.LEDs.clear(); // Set all pixel colors to 'off'
		SetTapeLEDs(64 , 0, 0, 0); //LEDセット


/*
		//A4:CF:12:44:6B:84
 		uint8_t new_mac[6] ={0xB8, 0xF0, 0x09, 0xC4, 0x70, 0xFA};
		esp_base_mac_addr_set(new_mac);
	
        esp_efuse_mac_get_default(mac);
        sprintf(Device.PhysicalAddress, "%02X:%02X:%02X:%02X:%02X:%02X",mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        OutPutLogs(LogCode_Info,4,"+- "+ String(Device.PhysicalAddress) );    //Log出力
*/

        ////////////////////////////////////////////////
        //AquesTalk ESP32
        ////////////////////////////////////////////////
        OutPutLogs(LogCode_Info,3,"+- AquesTalk");    //Log出力
        int iret = Device.AquesTalk.createK( Device.AquesTalk_LicenceKey); //ライセンスキー確認
        if (iret) {
            OutPutLogs(LogCode_Error,3,"+-- Error:" + String(iret));    //Log出力
        } else {
            OutPutLogs(LogCode_Info ,3,"+-- Clear");    //Log出力


        }


//delay(3000);


/*
        ////////////////////////////////////////////////
		//PCA9554初期化
        ////////////////////////////////////////////////
        OutPutLogs(LogCode_Info,3,"+- PCA9554");    //Log出力
		Device.EXP_IO = new PCA9554(0x24);
		Device.EXP_IO->twiWrite(21, 22);
		delay(20);
		uint8_t  res = 1;
  		Device.EXP_IO->twiRead(res);
		delay(20);
		OutPutLogs(LogCode_Info,4,"+-- "+String(res));    //Log出力
		Device.EXP_IO ->portMode0(ALLOUTPUT); //Set the port as all output 
		delay(20);

  		for(int i=0;i<8;i++){
    		OutPutLogs(LogCode_Info,5,"+-- "+String(i));    //Log出力
  			Device.EXP_IO ->digitalWrite0(i, LOW);	//全てLOWで出力
  		}
	  */

        ////////////////////////////////////////////////
        //配列群の初期化処理
        ////////////////////////////////////////////////
        OutPutLogs(LogCode_Info,3,"+- Matrix");    //Log出力
		Device.Sensor.Initialize();

		Device.LCD_Tocuh.x =-1;
		Device.LCD_Tocuh.y =-1;
		
//delay(3000);

        ////////////////////////////////////////////////
        //Motorの初期化処理
        ////////////////////////////////////////////////
		OutPutLogs(LogCode_Info,3,"+- Motor");    //Log出力

        OutPutLogs(LogCode_Info ,4,"+-- Initialize");    //Log出力
		Device.Motor = 	new MotorPump[5];
		Device.Motor[Motor_Main  ].Initialize("Main", 0x66); //メインタンク

		Device.Motor[Motor_Ink_Red  ].Initialize("InkA", 0x62); //インクタンク左
		Device.Motor[Motor_Ink_Yellow  ].Initialize("InkB", 0x60); //インクタンク右  生きてる


		Device.Motor[Motor_ValveA].Initialize("ValveA", 0x63 ); //バルブA
		Device.Motor[Motor_ValveB].Initialize("ValveB", 0x65 ); //バルブB


		Device.Motor[Motor_Ink_Red  ].Ratio =60.0f;
		Device.Motor[Motor_Ink_Yellow  ].Ratio =40.0f;

        OutPutLogs(LogCode_Info ,4,"+-- Set");    //Log出力
		Device.Motor[Motor_Main  ].SetSpeed( Motor_STOP );		Device.Motor[Motor_Main     ].Run( Device.Battery.isUSB );
		Device.Motor[Motor_Ink_Red  ].SetSpeed( Motor_STOP );	Device.Motor[Motor_Ink_Red  ].Run( Device.Battery.isUSB );
		Device.Motor[Motor_Ink_Yellow  ].SetSpeed( Motor_STOP );Device.Motor[Motor_Ink_Yellow  ].Run( Device.Battery.isUSB );
		Device.Motor[Motor_ValveA].SetSpeed( Motor_STOP );		Device.Motor[Motor_ValveA].Run( Device.Battery.isUSB );
		Device.Motor[Motor_ValveB].SetSpeed( Motor_STOP );		Device.Motor[Motor_ValveB].Run( Device.Battery.isUSB );

//delay(3000);

        ////////////////////////////////////////////////
        //Button初期化処理
        ////////////////////////////////////////////////
		OutPutLogs(LogCode_Info,3,"+- Button");    //Log出力
		Device.ScreenButton.Status =0;
		Device.Button = new ButtonInfo[ Button_END ];

		Device.Button[ Button_SystemCheck	    ].Initialize(260,	60, "STOP", 	"Ignore",	"Reboot",		"Shutdown", 	BaseColor_Gray, BaseColor_Tomato, BaseColor_Green,	BaseColor_Gray						);
		Device.Button[ Button_TASK_Emerg	    ].Initialize(260,	60, "STOP", 	"Run",		"Feelless", 					BaseColor_Gray, BaseColor_Tomato, BaseColor_Green						);
		Device.Button[ Button_TASK_Mood	    	].Initialize(260,	60, "STOP", 	"ReCount", 	"Wait", 		"Run", 			BaseColor_Gray, BaseColor_Green,  BaseColor_Orange, BaseColor_Tomato	);
		Device.Button[ Button_TASK_Hungry    	].Initialize(260,	60, "STOP", 	"ReCount", 	"Wait", 		"Run", 			BaseColor_Gray, BaseColor_Green,  BaseColor_Orange, BaseColor_Tomato	);
		Device.Button[ Button_TASK_Hungry_Motor ].Initialize(260,	60, "OFF", 		"Auto", 	"ON",							BaseColor_Gray, BaseColor_Orange, BaseColor_Tomato	);
		Device.Button[ Button_TASK_Burp 		].Initialize(260,	60, "OFF", 		"Wait", 	"Run",							BaseColor_Gray, BaseColor_Orange, BaseColor_Tomato	);
		Device.Button[ Button_TASK_Shit 	   	].Initialize(260,	60, "OFF", 		"Wait", 	"Run",							BaseColor_Gray, BaseColor_Orange, BaseColor_Tomato	);
		Device.Button[ Button_TASK_Shit_INK	   	].Initialize(260,	60, "Red", 		"Random", 	"Yellow",							BaseColor_Tomato, BaseColor_Gray, BaseColor_Orange	);
		Device.Button[ Button_TASK_Diapers 	   	].Initialize(260,	60, "OFF", 		"Wait", 	"Run",							BaseColor_Gray, BaseColor_Orange, BaseColor_Tomato	);

		Device.Button[ Button_TASK_Sleep	   	].Initialize(260,	60, "STOP", 	"ReCount", 	"Wait", 		"Run", 			BaseColor_Gray, BaseColor_Green,  BaseColor_Orange, BaseColor_Tomato	);

		Device.Button[ Button_TASK_Sleeping	   	].Initialize(260,	60, "STOP", 	"Wait", 	"Run", 								BaseColor_Gray,   BaseColor_Orange, BaseColor_Tomato	);


		Device.Button[ Button_MP3_Speaker 	   	].Initialize(260,	60, "OFF", 		"25", 	    "50",			"75", 	"100", 	BaseColor_Gray, BaseColor_Cyan, BaseColor_Green,	BaseColor_Orange,	BaseColor_Tomato			);

		Device.Button[ Button_M5_Speaker 	   	].Initialize(260,	60, "OFF", 		"25", 	    "50",			"75", 	"100", 	BaseColor_Gray, BaseColor_Cyan, BaseColor_Green,	BaseColor_Orange,	BaseColor_Tomato			);

		Device.Button[ Button_M5_Touch	 	   	].Initialize(260,	60, "OFF", 		"Non",		"ON",							BaseColor_Gray, BaseColor_Orange, BaseColor_Tomato );



        Device.Button_Square = new ButtonSquare[ ButtonSuare_END ];
		Device.Button_Square[ ButtonSuare_Touch_ON	 		].Initialize(128,30,6, "Touch ON", BaseColor_CyanDark, BaseColor_Cyan );
		Device.Button_Square[ ButtonSuare_Touch_OFF	 		].Initialize(128,30,6, "Touch OFF", BaseColor_CyanDark, BaseColor_Cyan );

//		Device.Button[Button_TASK_Mood	    ].Initialize(260,60, "STOP", 	"Run", 	"ReCount", 	BaseColor_Gray, BaseColor_Tomato, BaseColor_Green);
//		Device.Button[Button_TASK_Emerg	    ].SetSelectButton(1);

/*

		TASK_Status_Count			=  0,		//0: カウント在り
		TASK_Status_Wait			=  1,		//1: 待ち状態
		TASK_Status_Run				=  2,		//2:実行中
		TASK_Status_Non				=  3,		//3:非実行
		TASK_Status_RunSuspend		=  4,		//4:実行中に割り込み処理があり停止している状態

		Device.Button[Button_Motor_MAIN	].Initialize(Button_Type3,"Main","Reverse","Stop","Forward");
		Device.Button[Button_Motor_INKA	].Initialize(Button_Type3,"InkA","Reverse","Stop","Forward");
		Device.Button[Button_Motor_Ink_Yellow	].Initialize(Button_Type3,"InkB","Reverse","Stop","Forward");
		Device.Button[Button_Motor_ValveA	].Initialize(Button_Type2,"ValveA","OFF","ON","");
		Device.Button[Button_Motor_ValveB	].Initialize(Button_Type2,"ValveB","OFF","ON","");

		Device.Button[ Button_Motor_MAIN	].SetSelectButton(1);


		Device.Button[Button_Motor_Pump	].Initialize(Button_Type3,"Pump","Out","Stop","In");
*/



		////////////////////////////////////////////////
        //LovyanGFX初期化処理
        ////////////////////////////////////////////////
        OutPutLogs(LogCode_Info,3,"+-- LovyanGFX");    //Log出力


		Device.isLcdPowerOLD 	= true;
		Device.isLcdPower 		= false;


		Device.LCD.init();
		Device.LCD.setBrightness(128);
		Device.LCD.setColorDepth(8);  				// RGB66の18ビットに設定
		Device.LCD.fillScreen( BaseColor_Black );  	// 指定色で塗り潰し		

        OutPutLogs(LogCode_Info ,4,"+-- Sprite Begin"); 		//Log出力
		Device.LCD_Sprite.setPsram(true);			//メモリ確保 PSRAMを使う　低速になるので注意

        OutPutLogs(LogCode_Info ,5,"+-- 1"); 		//Log出力

		Device.LCD_Sprite.setColorDepth(8);     	//RGB66の18ビットに設定

        OutPutLogs(LogCode_Info ,5,"+-- 2"); 		//Log出力

		Device.LCD_Sprite.createSprite(300,220);	//生成

        OutPutLogs(LogCode_Info ,5,"+-- 3"); 		//Log出力

		Device.LCD_Message.setPsram(true);			//メモリ確保

        OutPutLogs(LogCode_Info ,5,"+-- 4"); 		//Log出力

		Device.LCD_Message.setColorDepth(8);     	// RGB66の18ビットに設定

        OutPutLogs(LogCode_Info ,5,"+-- 5"); 		//Log出力

		Device.LCD_Message.createSprite(260,40);	//生成

        OutPutLogs(LogCode_Info ,4,"+-- Sprite End"); 		//Log出力


		for(int i=0;i<4;i++){
			Device.TASK_Title[  i  ].Title 		= "";
			Device.TASK_Title[  i  ].DrawY 		=  0;
			Device.TASK_Title[  i  ].DrawY_OLD 	= -1;
			Device.TASK_Title[  i  ].isEnable	= false;
			Device.TASK_Title[  i  ].TASK_Count =0;
		}
		Device.TASK_Title[  TASK_Status_Wait  ].Title ="Wait";
		Device.TASK_Title[  TASK_Status_Run   ].Title ="Execution";
		Device.TASK_Title[  TASK_Status_Non   ].Title ="Non-execution";
		Device.TASK_Title[  TASK_Status_Count ].Title ="Count";

    OutPutLogs(LogCode_Info,1,"--- Initialize End --\n");    //Log出力} 

}