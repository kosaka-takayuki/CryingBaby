
#pragma once 
#ifndef Enum_H
#define Enum_H_H

#define BaseColor_Black		0x000000u
#define BaseColor_Cyan		0x92D1E0u
#define BaseColor_CyanDark	0x5291A0u
#define BaseColor_Gray		0x999999u


//987 6 5 4
//DCB A 9 8
//EDC B A 9

#define BaseColor_Orange 	0xF0AD57u
#define BaseColor_Tomato	0xEC7E5Au
#define BaseColor_Beige 	0xD8C5A4u
#define BaseColor_Green 	0x78BF58u
#define BaseColor_Remon 	0xF7E340u
#define BaseColor_Navy		0x03318Cu
#define BaseColor_Red		0xF80000u

#define BaseColor_White 	0xffffffu
 



    //////////////////////////////////////////////////////
    //センサー番号
    //////////////////////////////////////////////////////
	enum SensorName{
		Sensor_Eyes 		=  0,
		Sensor_Microhone 	=  1,
		Sensor_Mouth 		=  2,
		Sensor_Temperature 	=  3,
		Sensor_IMU 			=  4,
		Sensor_CROTCH 		=  5,
		Sensor_Level01 		=  6,
		Sensor_Level02 		=  7,
		Sensor_Level03 		=  8,
		Sensor_Level04 		=  9,
		Sensor_Level05 		= 10,
		Sensor_Level06 		= 11,
		Sensor_Level07 		= 12,
		Sensor_Level08		= 13,
		Sensor_LCD_Touch   	= 14,
		Sensor_NameMAX 		= 15	
	};

    //////////////////////////////////////////////////////
    //モータ制御
    //////////////////////////////////////////////////////
	enum MotorStatus{
		Motor_STOP		=     0,		//停止 
		Motor_Back		=  -255,		//反転
		Motor_Forward	=   255		//正転
	};
	enum MotorName{
		Motor_Main		=  0,		//メインタンク
		Motor_Ink_Red		=  1,		//インクタンク左
		Motor_Ink_Yellow		=  2,		//インクタンク右
		Motor_ValveA	=  3,		//バルブA
		Motor_ValveB	=  4,		//バルブA
	};


/*
		Device.Motor[0].Initialize(0x66); //メインタンク
		Device.Motor[1].Initialize(0x62); //インクタンク左
		Device.Motor[2].Initialize(0x60); //インクタンク右
		Device.Motor[3].Initialize(0x63); //バルブA
		Device.Motor[4].Initialize(0x65); //バルブB

						if(SendData[1] == "Main"  ){ Serial.print("Main: ");	Serial.println(_Status); }
						if(SendData[1] == "InkA"  ){ Serial.print("InkA: ");	Serial.println(_Status); }
						if(SendData[1] == "InkB"  ){ Serial.print("InkB: ");	Serial.println(_Status); }
						if(SendData[1] == "ValveA"){ Serial.print("ValveA: ");	Serial.println(_Status); }
						if(SendData[1] == "ValveB"){ Serial.print("ValveB: ");	Serial.println(_Status); }
						*/



    //////////////////////////////////////////////////////
    //姿勢制御
    //////////////////////////////////////////////////////
	enum Position{
		Position_Standing		=  0,		//通常
		Position_Supine			=  1,		//仰臥位
		Position_Depression		=  2,		//うつむせ
		Position_Inversus		=  3		//逆さ
	};


    //////////////////////////////////////////////////////
    //エラーコード
    //////////////////////////////////////////////////////
	enum LogCode{
		LogCode_Info			=  0,		// 0: Info
		LogCode_Error			=  1,		// 1: エラー
		LogCode_Command			=  2,		// 2:シリアルコマンド
		LogCode_Action			=  3,		// 3:判定
		LogCode_TASK			=  4,		// 4:タスク
		LogCode_FILESAVE		=  5,		// 5:ファイルセーブ

	};



	enum ThresholdConditions{
		ThresholdConditions_Min 		= 0,
		ThresholdConditions_Max 		= 1,
		ThresholdConditions_MinMAX 		= 2
	};


    //////////////////////////////////////////////////////
    //InfoData
    //////////////////////////////////////////////////////
	struct InfoData{
		String Name;		//文字列
		int    Draw_Y;		//描写位置
		boolean isDraw;		//描写の有無

		String MSG_A;		//出力文字A
		String MSG_A_OLD;	//過去の文字

		String MSG_B;		//出力文字A
		String MSG_B_OLD;	//過去の文字

		String MSG_C;		//出力文字A
		String MSG_C_OLD;	//過去の文字

		int Gauge;			//ゲージ値
		int Gauge_OLD;		//過去のゲージ値

		int isActice;		//
	};

	
	enum MP3FolderNo{
		MP3_Mood			=  3,		// 3: Mood
		MP3_Emerg			=  4,		// 4: Emerg
		MP3_Burp			=  5,		// 5: Burp
		MP3_Shit			=  6,		// 6: Shit
		MP3_Happy			=  7,		// 7: Happy
		MP3_Gokugoku		=  8,		// 8: Gokugoku
		MP3_Hungry			=  9,		// 9: Hungry
		MP3_Sleep			= 10,		//10: Sleep
	};


	struct ScreenChangeButton{
		int 	Status;			// ステータス
		Point 	ClickPoint;		// クリックしたポイント
		int 	Length;			// 長さ
		int		LR;				// 0: 左　1:右
		int		Status_OLD;
	};


	enum TASKNames{
		TASK_Name_Hungry			=  0,		//0: Hungry
		TASK_Name_Sleep				=  1,		//1: Sleep	
		TASK_Name_Mood				=  2,		//2: Mood
		TASK_Name_Wait				=  3,		//3: Wait
		TASK_Name_Emerg				=  4,		//4: Emerg	
		TASK_Name_Shit				=  5,		//5: Wait
		TASK_Name_Power				=  6,		//6: Power	
		TASK_Name_Diapers			=  7,		//7: おむつ
		TASK_Name_Burp				=  8,		//8: げっぷ
		TASK_Name_Sleeping			=  9,		//9: 眠っている
		TASK_Name_End				=  10		//10: 終了を表す
		
	};

	enum ButtonType{
		Button_Type5				=  5,		// 0: ノーマルボタン
		Button_Type4				=  4,		// 0: ノーマルボタン
		Button_Type3				=  3,		// 0: ノーマルボタン
		Button_Type2				=  2,		// 1: ノーマルボタン
	};

	struct ButtonArea{
		int x;
		int y;
		int w;
		int h;
	};


	enum ButtonNo{
		Button_TASK_Emerg		=0,
		Button_SystemCheck		=1,
		Button_TASK_Hungry		=2,
		Button_TASK_Hungry_Motor=3,
		Button_TASK_Mood		=4,
		Button_TASK_Burp		=5,
		Button_TASK_Shit		=6,
		Button_TASK_Shit_INK	=7,
		Button_TASK_Diapers		=8,

		Button_TASK_Sleep		=9,
		Button_TASK_Sleeping	=10,

		Button_MP3_Speaker		=11,
		Button_M5_Speaker		=12,

		Button_M5_Touch			=13,

		Button_END				=14,
		
	

	};

enum Button__Square{
		ButtonSuare_Touch_ON	=0,
		ButtonSuare_Touch_OFF	=1,
		ButtonSuare_END			=2,
};


	struct TASK_Info_Title{
		String Title;
		int TASK_Count;
		int TASK_Count_OLD;
		boolean isEnable;
		
		int DrawY;
		int DrawY_OLD;
	};	

	enum TASKStatus{
		TASK_Status_Count			=  0,		//0: カウント在り
		TASK_Status_Wait			=  1,		//1: 待ち状態
		TASK_Status_Run				=  2,		//2:実行中
		TASK_Status_Non				=  3,		//3:非実行
		TASK_Status_RunSuspend		=  4,		//4:実行中に割り込み処理があり停止している状態

	};

	enum TASK_Height{
		TASK_H_Exe		= 16,
		TASK_H_Wait		= 16,
		TASK_H_Count	= 16,
		TASK_H_Non 		= 12,
		TASK_H_MSG		= 12

	};
	
	enum TimeNo{
		Time_S	=  0,		//S
		Time_M	=  1,		//M
		Time_H	=  2		//H
	};


    //////////////////////////////////////////////////////
    //FPS
    //////////////////////////////////////////////////////
	struct FPS{
		uint32_t 		pSec=0;
		uint32_t 		Sec=0;
		int				Count =0; 
		int				FPS; 							//FPS
		int 			FPS_B;		
	};

    //////////////////////////////////////////////////////
    //ScreenNo
    //////////////////////////////////////////////////////
	enum ScreenNo{
		Screen_Info			= 	0,
		Screen_TASKMonitor	= 	1,
		Screen_Emergency	= 	2,
		Screen_Mood			= 	3,
		Screen_Hungry		=   4,
		Screen_Burp			=   5,
		Screen_Shit			=   6,
		Screen_Diapers		=   7,
		Screen_Sleep		=   8,
		Screen_Sleeping		=   9,
		Screen_Device		=  10,

		
	};


#endif
