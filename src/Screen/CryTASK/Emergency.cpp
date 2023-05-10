#include "Screen/CryTASK/Emergency.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Emergency
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Emergency(){	//

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
  	RunNo  = GetNo_TASK_Mood(TASK_Name_Emerg);	//指定されたTASKのNo


	DrawTitle("Emergency", 600, Device.TASK[RunNo].Status );

	if(Device.TASK[RunNo].Status  == TASK_Status_Run ){	isRun =true;	}else{	isRun =false;	}	//ステータスが実行中かそうじゃないか


	//最初の一度だけ実行
	if( Device.isModeChangeFirstTime == false ){
		isFirstDraw = true;	//画面更新時に表示されない問題を防ぐ
		if(Device.isHelp == true){
			Device.AquesTalk.playK("緊急", 50, Device.isAquesTalk);                          //AquesTalkで会話　会話スピードは最低の50
		}
		Device.InfoData[ 0].Name = "State";
		Device.InfoData[ 1].Name = "Remaining";
		Device.InfoData[ 2].Name = "Mood";

		Device.InfoData[ 3].Name = "Microphone";		
		Device.InfoData[ 4].Name = "Eye Sensor";		
		Device.InfoData[ 5].Name = "Milk Temperature";	
		Device.InfoData[ 6].Name = "Ton Per Minutes";	
		Device.InfoData[ 7].Name = "IMU";				
		Device.InfoData[ 8].Name = "Position";			

		
		_DrawY = 40;
		for(int i=0;i<9;i++){
			//Y軸座標計算
			Device.InfoData[ i ].Gauge_OLD =-1;
			Device.InfoData[ i ].MSG_A_OLD ="-1";
			Device.InfoData[ i ].MSG_B_OLD ="-1";
			Device.InfoData[ i ].MSG_C_OLD ="-1";

			
			uint32_t DColor= BaseColor_Orange;

			if(i<=2){
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



		switch (Device.TASK[RunNo].Status){
			case TASK_Status_Count:			Device.Button[ Button_TASK_Emerg	].SetSelectButton(2); 	Device.Button[ Button_TASK_Emerg ].SelectButton_OLD =2;		break;
			case TASK_Status_Run:			Device.Button[ Button_TASK_Emerg	].SetSelectButton(1);	Device.Button[ Button_TASK_Emerg ].SelectButton_OLD =1;		break;
			case TASK_Status_Non:			Device.Button[ Button_TASK_Emerg	].SetSelectButton(0);	Device.Button[ Button_TASK_Emerg ].SelectButton_OLD =0;		break;
		}

		Device.Button[Button_TASK_Emerg	    ].isClick = false;
		Device.Button[Button_TASK_Emerg	    ].ClickPoint_B.x =-1;
		Device.Button[Button_TASK_Emerg	    ].ClickPoint_B.y =-1;





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
	//Mood
	/////////////////////////////////////////////////////////////////////
					ShowNo =2;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						Device.InfoData[ ShowNo ].MSG_A = (String)(Device.TASK[RunNo].MoodTotalCount)+" %";					//機嫌％の描写
						if(isRun == false){	Device.InfoData[ ShowNo ].MSG_A ="";}

						if(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD){

								DrawBackGround(2, Device.InfoData[ ShowNo ].Draw_Y,BaseColor_Tomato,BaseColor_Gray, !isRun );	//背景塗
								DrawString(Device.InfoData[ ShowNo ].MSG_A, _DrawX_MSG_C, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_right);	//文字描写
								isDraw = true;	//更新する
								DrawMSG +="Mood \t";


							////////////////////////////////////////////////////////////////////////////
							//ゲージの描写	
							////////////////////////////////////////////////////////////////////////////
								Device.InfoData[ ShowNo ].Gauge = maps(Device.TASK[RunNo].MoodTotalCount ,0,100,0,15);
								if(Device.InfoData[ ShowNo ].Gauge != Device.InfoData[ ShowNo ].Gauge_OLD  && isRun == true ){
									DrawDataGauge(233+4,Device.InfoData[ ShowNo ].Draw_Y+1,Device.InfoData[ ShowNo ].Gauge,BaseColor_White, BaseColor_Tomato,false);	//データゲージの描写
										DrawMSG +="Remaining  G\t";
								}
								Device.InfoData[ ShowNo ].Gauge_OLD =Device.InfoData[ ShowNo ].Gauge;	//データ格納
						}
						Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納



	/////////////////////////////////////////////////////////////////////
	//Microhone Sensor
	/////////////////////////////////////////////////////////////////////
					ShowNo =3;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						Device.InfoData[ ShowNo ].MSG_A  =Device.Sensor.Microphone.SData;
						if(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD){
							//FPSを稼ぐために前のデータを比べて5以上であるときのみ描写
							if((abs(Device.Sensor.Microphone.Data_Old - Device.Sensor.Microphone.Data)  >= 5)|| (Device.Sensor.Microphone.Data==0)||(isFirstDraw == true)){
								DrawBackGround(2, Device.InfoData[ ShowNo ].Draw_Y,BaseColor_Orange, BaseColor_Tomato, Device.Sensor.Microphone.isActive );	//背景塗
								DrawString(Device.InfoData[ ShowNo ].MSG_A, _DrawX_MSG_C, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_right);	//文字描写
								isDraw = true;	//更新する
								DrawMSG +="Mic \t";
							}
							Device.Sensor.Microphone.Data_Old =   Device.Sensor.Microphone.Data ;		//描写用
							////////////////////////////////////////////////////////////////////////////
							//ゲージの描写	
							////////////////////////////////////////////////////////////////////////////
								Device.InfoData[ ShowNo ].Gauge = maps((int)Device.Sensor.Microphone.Data,Device.Sensor.Microphone.Min,Device.Sensor.Microphone.Max,0,15);
								if(Device.InfoData[ ShowNo ].Gauge != Device.InfoData[ ShowNo ].Gauge_OLD){
									DrawDataGauge(233+4,Device.InfoData[ ShowNo ].Draw_Y+1,Device.InfoData[ ShowNo ].Gauge,BaseColor_White, BaseColor_Tomato,Device.Sensor.Microphone.isActive );	//データゲージの描写
										DrawMSG +="Mic  G\t";
								}
								Device.InfoData[ ShowNo ].Gauge_OLD =Device.InfoData[ ShowNo ].Gauge;	//データ格納
						}
						Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納



	/////////////////////////////////////////////////////////////////////
	//Cds EYE Sensor
	/////////////////////////////////////////////////////////////////////
					ShowNo =4;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						Device.InfoData[ ShowNo ].MSG_A  =Device.Sensor.Eye.SData;
						if(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD){
							//FPSを稼ぐために前のデータを比べて5以上であるときのみ描写
							if((abs(Device.Sensor.Eye.Data_Old - Device.Sensor.Eye.Data)  >= 5)|| (Device.Sensor.Eye.Data==0)||(isFirstDraw == true)){
								DrawBackGround(2, Device.InfoData[ ShowNo ].Draw_Y,BaseColor_Orange, BaseColor_Tomato, Device.Sensor.Eye.isActive );	//背景塗
								DrawString(Device.InfoData[ ShowNo ].MSG_A, _DrawX_MSG_C, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_right);	//文字描写
								isDraw = true;	//更新する
								DrawMSG +="Eye \t";
							}
							Device.Sensor.Eye.Data_Old =   Device.Sensor.Eye.Data ;		//描写用
							////////////////////////////////////////////////////////////////////////////
							//ゲージの描写	
							////////////////////////////////////////////////////////////////////////////
								Device.InfoData[ ShowNo ].Gauge = maps((int)Device.Sensor.Eye.Data,Device.Sensor.Eye.Min,Device.Sensor.Eye.Max,0,15);
								if(Device.InfoData[ ShowNo ].Gauge != Device.InfoData[ ShowNo ].Gauge_OLD){
									DrawDataGauge(233+4,Device.InfoData[ ShowNo ].Draw_Y+1,Device.InfoData[ ShowNo ].Gauge,BaseColor_White, BaseColor_Tomato,Device.Sensor.Eye.isActive );	//データゲージの描写
										DrawMSG +="Eye  G\t";
								}
								Device.InfoData[ ShowNo ].Gauge_OLD =Device.InfoData[ ShowNo ].Gauge;	//データ格納
						}
						Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納



				
	

	/////////////////////////////////////////////////////////////////////
	//Milk Temperature
	/////////////////////////////////////////////////////////////////////
				ShowNo =5;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						Device.InfoData[ ShowNo ].MSG_A  =Device.Sensor.Temperature.SData+" C";
						if(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD){
							//FPSを稼ぐために前のデータを比べて5以上であるときのみ描写
							if((abs(Device.Sensor.Temperature.Data_Old - Device.Sensor.Temperature.Data)  >= 0.1f)|| (Device.Sensor.Temperature.Data==0)||(isFirstDraw == true)){
								DrawBackGround(2, Device.InfoData[ ShowNo ].Draw_Y,BaseColor_Orange, BaseColor_Tomato, Device.Sensor.Temperature.isActive );	//背景塗
								DrawString(Device.InfoData[ ShowNo ].MSG_A, _DrawX_MSG_C, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_right);	//文字描写
								DrawString( "o",_DrawX_MSG_C-6, Device.InfoData[ ShowNo ].Draw_Y+3, 10, middle_right);	//文字描写
								//℃

								isDraw = true;	//更新する
								DrawMSG +="Temperature \t";
							}
							Device.Sensor.Temperature.Data_Old =   Device.Sensor.Temperature.Data ;		//描写用

							////////////////////////////////////////////////////////////////////////////
							//ゲージの描写	
							////////////////////////////////////////////////////////////////////////////
								Device.InfoData[ ShowNo ].Gauge = maps((int)Device.Sensor.Temperature.Data,Device.Sensor.Temperature.Min,Device.Sensor.Temperature.Max,0,15);
								if(Device.InfoData[ ShowNo ].Gauge != Device.InfoData[ ShowNo ].Gauge_OLD){
									DrawDataGauge(233+4,Device.InfoData[ ShowNo ].Draw_Y+1,Device.InfoData[ ShowNo ].Gauge,BaseColor_White, BaseColor_Tomato,Device.Sensor.Temperature.isActive );	//データゲージの描写

										DrawMSG +="Temperature  G\t";
								}
								Device.InfoData[ ShowNo ].Gauge_OLD =Device.InfoData[ ShowNo ].Gauge;	//データ格納
						}
						Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納


	
	/////////////////////////////////////////////////////////////////////
	//TPM
	/////////////////////////////////////////////////////////////////////
					ShowNo =6;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						Device.InfoData[ ShowNo ].MSG_A  =Device.Sensor.TPM.SData+"  ";
						if(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD){
							//FPSを稼ぐために前のデータを比べて5以上であるときのみ描写
							if((abs(Device.Sensor.Level.Data_Old - Device.Sensor.TPM.Data)  >= 1)|| (Device.Sensor.TPM.Data==0)||(isFirstDraw == true)){
								DrawBackGround(2, Device.InfoData[ ShowNo ].Draw_Y,BaseColor_Orange, BaseColor_Tomato, Device.Sensor.TPM.isActive );	//背景塗
								DrawString(Device.InfoData[ ShowNo ].MSG_A, _DrawX_MSG_C, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_right);	//文字描写
								DrawString( "TPM",_DrawX_MSG_C+4, Device.InfoData[ ShowNo ].Draw_Y+9, 10, middle_right);	//文字描写

								isDraw = true;	//更新する
								DrawMSG +="TPM \t";
							}
							Device.Sensor.Level.Data_Old =   Device.Sensor.Level.Data ;		//描写用

							////////////////////////////////////////////////////////////////////////////
							//ゲージの描写	
							////////////////////////////////////////////////////////////////////////////
								Device.InfoData[ ShowNo ].Gauge = maps((int)Device.Sensor.TPM.Data,Device.Sensor.TPM.Min,Device.Sensor.TPM.Max,0,15);
								if(Device.InfoData[ ShowNo ].Gauge != Device.InfoData[ ShowNo ].Gauge_OLD){
									DrawDataGauge(233+4,Device.InfoData[ ShowNo ].Draw_Y+1,Device.InfoData[ ShowNo ].Gauge,BaseColor_White, BaseColor_Tomato,Device.Sensor.TPM.isActive );	//データゲージの描写

										DrawMSG +="TPM  G\t";
								}
								Device.InfoData[ ShowNo ].Gauge_OLD =Device.InfoData[ ShowNo ].Gauge;	//データ格納

						}
						Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納


	/////////////////////////////////////////////////////////////////////
	//IMU
	/////////////////////////////////////////////////////////////////////
					ShowNo =7;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						Device.InfoData[ ShowNo ].MSG_A  =Device.Sensor.IMU.SData +" G";
						if(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD){
							//FPSを稼ぐために前のデータを比べて5以上であるときのみ描写
							if((abs(Device.Sensor.IMU.Data_Old - Device.Sensor.IMU.Data)  >= 0.05f)|| (Device.Sensor.IMU.Data==0)||(isFirstDraw == true)){
								DrawBackGround(2, Device.InfoData[ ShowNo ].Draw_Y,BaseColor_Orange, BaseColor_Tomato, Device.Sensor.IMU.isActive );	//背景塗
								DrawString(Device.InfoData[ ShowNo ].MSG_A, _DrawX_MSG_C, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_right);	//文字描写
								isDraw = true;	//更新する
								DrawMSG +="IMU \t";
							}
							Device.Sensor.IMU.Data_Old =   Device.Sensor.IMU.Data ;		//描写用
							////////////////////////////////////////////////////////////////////////////
							//ゲージの描写	
							////////////////////////////////////////////////////////////////////////////
								Device.InfoData[ ShowNo ].Gauge = maps((int)Device.Sensor.IMU.Data,Device.Sensor.IMU.Min,Device.Sensor.IMU.Max,0,15);
								if(Device.InfoData[ ShowNo ].Gauge != Device.InfoData[ ShowNo ].Gauge_OLD){
									DrawDataGauge(233+4,Device.InfoData[ ShowNo ].Draw_Y+1,Device.InfoData[ ShowNo ].Gauge,BaseColor_White, BaseColor_Tomato,Device.Sensor.IMU.isActive );	//データゲージの描写

										DrawMSG +="IMU G\t";
								}
								Device.InfoData[ ShowNo ].Gauge_OLD =Device.InfoData[ ShowNo ].Gauge;	//データ格納

						}
						Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納

	/////////////////////////////////////////////////////////////////////
	//Position
	/////////////////////////////////////////////////////////////////////
					ShowNo =8;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						Device.InfoData[ ShowNo ].MSG_A  = Device.Sensor.Position.SData;
						Device.InfoData[ ShowNo ].MSG_B  = (String)Device.Sensor.Position.isActive;
						
 						if( (Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD) || 
						    (Device.InfoData[ ShowNo ].MSG_B != Device.InfoData[ ShowNo ].MSG_B_OLD)){
							                                                                                     
							DrawBackGround(2, Device.InfoData[ ShowNo ].Draw_Y,BaseColor_Orange, BaseColor_Tomato, Device.Sensor.Position.isActive );	//背景塗
							DrawString(Device.InfoData[ ShowNo ].MSG_A, 182, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_center);	//文字描写

							isDraw = true;	//更新する
							DrawMSG +="Position \t";
							Device.Sensor.Level.Data_Old =   Device.Sensor.Level.Data ;		//描写用

							////////////////////////////////////////////////////////////////////////////
							//ゲージの描写	
							////////////////////////////////////////////////////////////////////////////
								Device.InfoData[ ShowNo ].Gauge = maps((int)Device.Sensor.Position.Data,Device.Sensor.Position.Min,Device.Sensor.Position.Max,0,15);
	
								if(Device.InfoData[ ShowNo ].Gauge != Device.InfoData[ ShowNo ].Gauge_OLD){
									DrawDataGauge(233+4,Device.InfoData[ ShowNo ].Draw_Y+1,Device.InfoData[ ShowNo ].Gauge,BaseColor_White, BaseColor_Tomato,Device.Sensor.Position.isActive );	//データゲージの描写

										DrawMSG +="Position G\t";
								}
								Device.InfoData[ ShowNo ].Gauge_OLD =Device.InfoData[ ShowNo ].Gauge;	//データ格納

						}
						Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納
						Device.InfoData[ ShowNo ].MSG_B_OLD =Device.InfoData[ ShowNo ].MSG_B;	//データ格納


	////////////////////////////////////////////////
	//フリックボタンの描写
	////////////////////////////////////////////////
	if( Device.Button[ Button_TASK_Emerg ].DrawButton( Button_TASK_Emerg, 190 )  == true){	isDraw =true;	DrawMSG +="Button \t";}

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