#include "Screen/CryTASK/Shit.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shit
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shit(){	//

//Serial.print("#D");
	int _DrawY =0;
	boolean isDraw = false;	//更新する必要があるかどうか

	int _DrawX_MSG_C = 233-10;

	int ShowNo;

	String DrawMSG ="";


	bool isFirstDraw =false;	//画面更新時に表示されない問題を防ぐ
	
	int RunNo=-1;

	boolean isRun = false;

	/////////////////////////////////////////////////////////////////////////////////////
    //画面設定
	/////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////
    // 時間経過アニメーション　徐々にフェードイン
	/////////////////////////////////////////////////////////////////////////////////////
  	RunNo  = GetNo_TASK_Mood(TASK_Name_Shit);	//指定されたTASKのNo


	DrawTitle("Shit", 600, Device.TASK[RunNo].Status );

	if(Device.TASK[RunNo].Status  == TASK_Status_Run ){	isRun =true;	}else{	isRun =false;	}	//ステータスが実行中かそうじゃないか


	//最初の一度だけ実行
	if( Device.isModeChangeFirstTime == false ){
		isFirstDraw = true;	//画面更新時に表示されない問題を防ぐ

		if(Device.isHelp == true){
			Device.AquesTalk.playK("おしっこ", 50, Device.isAquesTalk);                          //AquesTalkで会話　会話スピードは最低の50
		}
		
		Device.InfoData[ 0].Name = "State";
		Device.InfoData[ 1].Name = "Remaining";
		Device.InfoData[ 2].Name = "Satiety Level";
		Device.InfoData[ 3].Name = "Motor";
		
		Device.InfoData[ 4].Name = "Drink Level";			

		
		_DrawY = 40;
		for(int i=0;i<5;i++){
			//Y軸座標計算
			Device.InfoData[ i ].Gauge_OLD =-1;
			Device.InfoData[ i ].MSG_A_OLD ="-1";
			Device.InfoData[ i ].MSG_B_OLD ="-1";
			Device.InfoData[ i ].MSG_C_OLD ="-1";

			
			uint32_t DColor= BaseColor_Orange;

			if(i<=3){
				Device.InfoData[ i ].Draw_Y =  _DrawY +(i*15);	//座標を格納
				if(isRun == true ){	DColor = BaseColor_Tomato;	}else{		DColor = BaseColor_Gray;		}
				Device.LCD_Sprite.fillRoundRect (0, Device.InfoData[ i ].Draw_Y,130,13,2,DColor);		//左側の枠描写
				Device.LCD_Sprite.fillRoundRect (233, Device.InfoData[ i ].Draw_Y, 67,13,2,DColor);		//背景塗
				DrawString( Device.InfoData[ i ].Name   , 125,Device.InfoData[ i ].Draw_Y+6, 14, middle_right);	//文字描写
			}else{
				Device.InfoData[ i ].Draw_Y =  _DrawY +(i*15);	//座標を格納
				DColor = BaseColor_Orange;
				Device.LCD_Sprite.fillRoundRect (0, Device.InfoData[ i ].Draw_Y,130,13,2,DColor);		//左側の枠描写
				Device.LCD_Sprite.fillRoundRect (233, Device.InfoData[ i ].Draw_Y, 67,13,2,DColor);		//背景塗
				DrawString( Device.InfoData[ i ].Name   , 125,Device.InfoData[ i ].Draw_Y+6, 14, middle_right);	//文字描写
			}
			isDraw = true;
		}
	
		for(int i=0;i<12;i++){
			Device.InfoData[ i ].MSG_A_OLD ="-1";
			Device.InfoData[ i ].MSG_B_OLD ="-1";
			Device.InfoData[ i ].MSG_C_OLD ="-1";
		}
		Device.isModeChangeFirstTime = true;


		///////////////////////////////////////
		//ボタン設定
		///////////////////////////////////////
		switch (Device.TASK[RunNo].Status){
			case TASK_Status_Non:			Device.Button[ Button_TASK_Shit	].SetSelectButton(0);	Device.Button[ Button_TASK_Shit ].SelectButton_OLD =0;		isRun = false;	break;
			case TASK_Status_Run:			Device.Button[ Button_TASK_Shit	].SetSelectButton(2);	Device.Button[ Button_TASK_Shit ].SelectButton_OLD =2;		isRun = true;	break;
			default:						Device.Button[ Button_TASK_Shit	].SetSelectButton(1);	Device.Button[ Button_TASK_Shit ].SelectButton_OLD =1;		isRun = false;	break;

		}


		if(	Device.Motor[ Motor_Ink_Red ].Ratio > 50){
			Device.Button[ Button_TASK_Shit_INK	].SetSelectButton(0);	Device.Button[ Button_TASK_Shit_INK ].SelectButton_OLD =0;	
		}else{
			Device.Button[ Button_TASK_Shit_INK	].SetSelectButton(2);	Device.Button[ Button_TASK_Shit_INK ].SelectButton_OLD =2;	
		}

		Device.Button[Button_TASK_Shit	    ].isClick = false;
		Device.Button[Button_TASK_Shit	    ].ClickPoint_B.x =-1;
		Device.Button[Button_TASK_Shit	    ].ClickPoint_B.y =-1;





	}


	/////////////////////////////////////////////////////////////////////
	//FPS表示
	/////////////////////////////////////////////////////////////////////
	isDraw =DrawFPS(BaseColor_Tomato);


	
	/////////////////////////////////////////////////////////////////////
	//State
	/////////////////////////////////////////////////////////////////////
					ShowNo =0;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						Device.InfoData[ ShowNo ].MSG_A = GetStatus_Name(Device.TASK[RunNo].Status);
						
						if(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD){
								DrawBackGround(2, Device.InfoData[ ShowNo ].Draw_Y,BaseColor_Tomato, BaseColor_Gray, !isRun );	//背景塗
								DrawString(Device.InfoData[ ShowNo ].MSG_A, 182, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_center);	//文字描写
								isDraw = true;	//更新する
								DrawMSG +="State \t";
						}
						Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納
	/////////////////////////////////////////////////////////////////////
	//Remaining Time
	/////////////////////////////////////////////////////////////////////
					ShowNo =1;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						Device.InfoData[ ShowNo ].MSG_A = TimeToStrings(Device.TASK[RunNo].RunTime_RemainingTime);					//残り時間の表示
						if(isRun == false){	Device.InfoData[ ShowNo ].MSG_A ="";       }


						if(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD){

								DrawBackGround(2, Device.InfoData[ ShowNo ].Draw_Y, BaseColor_Tomato,BaseColor_Gray, !isRun );	//背景塗
								DrawString(Device.InfoData[ ShowNo ].MSG_A, 182, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_center);	//文字描写
								isDraw = true;	//更新する
								DrawMSG +="Remaining \t";

							////////////////////////////////////////////////////////////////////////////
							//ゲージの描写	
							////////////////////////////////////////////////////////////////////////////
								Device.InfoData[ ShowNo ].Gauge = maps(( Device.TASK[RunNo].RunTime_RemainingTime),0,Device.TASK[RunNo].RunTime_ElapsedOver,15,0);
								if(Device.InfoData[ ShowNo ].Gauge != Device.InfoData[ ShowNo ].Gauge_OLD && isRun == true){
									DrawDataGauge(233+4,Device.InfoData[ ShowNo ].Draw_Y+1,Device.InfoData[ ShowNo ].Gauge,BaseColor_White, BaseColor_Tomato,false);	//データゲージの描写
										DrawMSG +="Remaining  G\t";
								}
								Device.InfoData[ ShowNo ].Gauge_OLD =Device.InfoData[ ShowNo ].Gauge;	//データ格納
						}
						Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納

	/////////////////////////////////////////////////////////////////////
	//Satiety Level
	/////////////////////////////////////////////////////////////////////
					ShowNo =2;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						Device.InfoData[ ShowNo ].MSG_A  =Device.Sensor.Level.SData+" %";
						if(isRun == false){	Device.InfoData[ ShowNo ].MSG_A ="";}

						if(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD){

							//FPSを稼ぐために前のデータを比べて5以上であるときのみ描写
							if((abs(Device.Sensor.Level.Data_Old - Device.Sensor.Level.Data)  >= 0.5)|| (Device.Sensor.Level.Data==0)||(isFirstDraw == true)){
								DrawBackGround(2, Device.InfoData[ ShowNo ].Draw_Y,BaseColor_Tomato, BaseColor_Gray,  !isRun );	//背景塗
								DrawString(Device.InfoData[ ShowNo ].MSG_A, _DrawX_MSG_C, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_right);	//文字描写
								isDraw = true;	//更新する
								DrawMSG +="Level \t";
							}
							Device.Sensor.Level.Data_Old =   Device.Sensor.Level.Data ;		//描写用

							////////////////////////////////////////////////////////////////////////////
							//ゲージの描写	
							////////////////////////////////////////////////////////////////////////////
								Device.InfoData[ ShowNo ].Gauge = maps((int)Device.Sensor.Level.Data,Device.Sensor.Level.Min,Device.Sensor.Level.Max,0,15);
								if(Device.InfoData[ ShowNo ].Gauge != Device.InfoData[ ShowNo ].Gauge_OLD  && isRun == true ){
									DrawDataGauge(233+4,Device.InfoData[ ShowNo ].Draw_Y+1,Device.InfoData[ ShowNo ].Gauge,BaseColor_White, BaseColor_Red,Device.Sensor.Level.isActive );	//データゲージの描写
										DrawMSG +="Remaining  G\t";
								}
								Device.InfoData[ ShowNo ].Gauge_OLD =Device.InfoData[ ShowNo ].Gauge;	//データ格納
						}
						Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納



	/////////////////////////////////////////////////////////////////////
	//Motor
	/////////////////////////////////////////////////////////////////////
					ShowNo =3;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						if(Device.Sensor.Mouth.isActive == true){		Device.InfoData[ ShowNo ].MSG_A  = "ON";	}else{		Device.InfoData[ ShowNo ].MSG_A  = "OFF";			}
						if(isRun == false){								Device.InfoData[ ShowNo ].MSG_A  = "";		}

						if(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD){
							//FPSを稼ぐために前のデータを比べて5以上であるときのみ描写
								DrawBackGround(2, Device.InfoData[ ShowNo ].Draw_Y,BaseColor_Tomato, BaseColor_Gray, !isRun );	//背景塗
								DrawString(Device.InfoData[ ShowNo ].MSG_A, 185, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_center);	//文字描写

								isDraw = true;	//更新する
								DrawMSG +="Level \t";
							Device.Sensor.Level.Data_Old =   Device.Sensor.Level.Data ;		//描写用


						}
						Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納



	



	/////////////////////////////////////////////////////////////////////
	//Level　Sensor
	/////////////////////////////////////////////////////////////////////
					ShowNo =4;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						Device.InfoData[ ShowNo ].MSG_A  =Device.Sensor.Level.SData+" %";
						if(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD){
							//FPSを稼ぐために前のデータを比べて5以上であるときのみ描写
							if((abs(Device.Sensor.Level.Data_Old - Device.Sensor.Level.Data)  >= 1)||(isFirstDraw == true)){
								DrawBackGround(2, Device.InfoData[ ShowNo ].Draw_Y,BaseColor_Orange, BaseColor_Tomato, Device.Sensor.Level.isActive );	//背景塗
								DrawString(Device.InfoData[ ShowNo ].MSG_A, _DrawX_MSG_C, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_right);	//文字描写
								isDraw = true;	//更新する
								DrawMSG +="Level \t";
							}
							Device.Sensor.Level.Data_Old =   Device.Sensor.Level.Data ;		//描写用

							////////////////////////////////////////////////////////////////////////////
							//ゲージの描写	
							////////////////////////////////////////////////////////////////////////////
								Device.InfoData[ ShowNo ].Gauge = maps((int)Device.Sensor.Level.Data,Device.Sensor.Level.Min,Device.Sensor.Level.Max,0,15);
								if(Device.InfoData[ ShowNo ].Gauge != Device.InfoData[ ShowNo ].Gauge_OLD){
									DrawDataGauge(233+4,Device.InfoData[ ShowNo ].Draw_Y+1,Device.InfoData[ ShowNo ].Gauge,BaseColor_White, BaseColor_Tomato,Device.Sensor.Level.isActive );	//データゲージの描写

										DrawMSG +="Level  G\t";
								}
								Device.InfoData[ ShowNo ].Gauge_OLD =Device.InfoData[ ShowNo ].Gauge;	//データ格納

						}
						Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納



	////////////////////////////////////////////////
	//フリックボタンの描写
	////////////////////////////////////////////////
	if( Device.Button[ Button_TASK_Shit_INK   ].DrawButton( Button_TASK_Shit_INK, 155 )  == true){	isDraw =true;	DrawMSG +="Button \t";}

	if( Device.Button[ Button_TASK_Shit       ].DrawButton( Button_TASK_Shit, 190 )  == true){	isDraw =true;	DrawMSG +="Button \t";}

	////////////////////////////////////////////////////
	// 更新する
	////////////////////////////////////////////////////
	if(isDraw == true){
		if(DrawMSG !=""){
//			Serial.println(DrawMSG);
		}
		Device.LCD.startWrite();
			Device.LCD_Sprite.pushSprite(&Device.LCD,10,10);
		Device.LCD.endWrite();	

	}


}