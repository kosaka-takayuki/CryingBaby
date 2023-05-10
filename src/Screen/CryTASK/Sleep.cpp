#include "Screen/CryTASK/Sleep.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sleep
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sleep(){	//

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
  	RunNo  = GetNo_TASK_Mood(TASK_Name_Sleep);	//指定されたTASKのNo


	DrawTitle("Sleep", 600, Device.TASK[RunNo].Status );

	if(Device.TASK[RunNo].Status  == TASK_Status_Run ){	isRun =true;	}else{	isRun =false;	}	//ステータスが実行中かそうじゃないか


	//最初の一度だけ実行
	if( Device.isModeChangeFirstTime == false ){
		isFirstDraw = true;	//画面更新時に表示されない問題を防ぐ

		if(Device.isHelp == true){
			Device.AquesTalk.playK("眠たい", 50, Device.isAquesTalk);                          //AquesTalkで会話　会話スピードは最低の50
		}
		Device.InfoData[ 0].Name = "State";
		Device.InfoData[ 1].Name = "Remaining";
		Device.InfoData[ 2].Name = "Mood";

			_DrawY = 40;
		for(int i=0;i<=2;i++){
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
			case TASK_Status_Non:			Device.Button[ Button_TASK_Sleep	].SetSelectButton(0);	Device.Button[ Button_TASK_Sleep ].SelectButton_OLD =0;		isRun = false;	break;
			case TASK_Status_Count:			Device.Button[ Button_TASK_Sleep	].SetSelectButton(1); 	Device.Button[ Button_TASK_Sleep ].SelectButton_OLD =1;		isRun = false;	break;
			case TASK_Status_Wait:			Device.Button[ Button_TASK_Sleep	].SetSelectButton(2);	Device.Button[ Button_TASK_Sleep ].SelectButton_OLD =2;		isRun = false;	break;
			case TASK_Status_Run:			Device.Button[ Button_TASK_Sleep	].SetSelectButton(3);	Device.Button[ Button_TASK_Sleep ].SelectButton_OLD =3;		isRun = true;	break;
		}


		Device.Button[Button_TASK_Sleep	    ].isClick = false;
		Device.Button[Button_TASK_Sleep	    ].ClickPoint_B.x =-1;
		Device.Button[Button_TASK_Sleep	    ].ClickPoint_B.y =-1;





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



	


	////////////////////////////////////////////////
	//フリックボタンの描写
	////////////////////////////////////////////////
	if( Device.Button[ Button_TASK_Sleep ].DrawButton( Button_TASK_Sleep, 190 )  == true){	isDraw =true;	DrawMSG +="Button Sleep \t";}

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