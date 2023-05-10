#include "Screen/TASKMonitor.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SystemInfo
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TASKMonitor(){	//

	String DrawMSG ="";
	
	boolean isDraw = false;	//更新する必要があるかどうか
	int _DrawX=10;
	int _DrawY=40;
	int level =0;

	/////////////////////////////////////////////////////////////////////////////////////
    //画面設定
	/////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////
    // 時間経過アニメーション　徐々にフェードイン
	/////////////////////////////////////////////////////////////////////////////////////
	DrawTitle("TASK Monitor", 0, 600, BaseColor_Cyan);

	if( Device.isModeChangeFirstTime == false ){

		if(Device.isHelp == true){
			Device.AquesTalk.playK("タスク / モニター。", 50,Device.isAquesTalk);                          //AquesTalkで会話　会話スピードは最低の50
		}
		Device.isModeChangeFirstTime = true; 

		for(int i=0;i<TASK_Name_End;i++){
			Device.TASK_Title[  i  ].DrawY_OLD =-1;
			Device.TASK[i].isDraw = true ;
		}
	}
	

	/////////////////////////////////////////////////////////////////////
	//FPS表示
	/////////////////////////////////////////////////////////////////////
		isDraw =DrawFPS(BaseColor_Cyan);

	//////////////////////////////////////////////
	//　各項目の文字描写
	//////////////////////////////////////////////
	for(int i=0;i<4;i++){
		if( Device.TASK_Title[  i  ].isEnable == true){		//もし実行中のタスクがある場合のみ表示
			if(Device.TASK_Title[  i  ].DrawY !=  Device.TASK_Title[  i  ].DrawY_OLD){
				Device.LCD_Sprite.fillRect(0, Device.TASK_Title[  i  ].DrawY,300,12,BaseColor_Black);		//背景塗
				Device.LCD_Sprite.setTextColor(BaseColor_Beige);	//文字色設定(文字色、背景色)
				DrawString( Device.TASK_Title[  i  ].Title , 5,  Device.TASK_Title[  i  ].DrawY, 12, top_left);	//文字描写
				Device.TASK_Title[  i  ].DrawY_OLD =  Device.TASK_Title[  i  ].DrawY;
				isDraw = true;	//更新する

				if(i ==TASK_Status_Count ){
					Device.TASK[ i ].ElapsedTime_OLD =-1;
				}
			}
		}
	}

	///////////////////////////////////////////////////////////////////
	//　タスク表示　実行中  Execution
	///////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//　タスク枠表示　実行中のタスクを描写
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			for(int i=0;i<TASK_Name_End;i++){

				if( Device.TASK[i].Status == TASK_Status_Run){


//Serial.println("##" + (String)i );
					_DrawX = 10;

					if( Device.TASK[ i ].RunTime_RemainingTime_OLD != Device.TASK[ i ].RunTime_RemainingTime){
						Device.TASK[ i ].RunTime_RemainingTime_OLD  = Device.TASK[ i ].RunTime_RemainingTime;				
						isDraw =true; //描写指示


						_DrawY = Device.TASK[  i  ].DrawY;	//座標を格納
						Device.TASK[  i  ].DrawX = _DrawX;	//座標を格納
						////////////////////////////////////////////////////////////////////////////////////////////
						//実行中の処理
						////////////////////////////////////////////////////////////////////////////////////////////
						Device.LCD_Sprite.fillRect (0, _DrawY,300,TASK_H_Exe,BaseColor_Black);		//背景塗
						Device.LCD_Sprite.fillRoundRect (_DrawX, _DrawY,290,TASK_H_Exe,2,BaseColor_Tomato);		//背景塗
						Device.LCD_Sprite.drawRoundRect (_DrawX, _DrawY,290,TASK_H_Exe,2,BaseColor_Beige);		//外枠
						Device.LCD_Sprite.setTextColor(BaseColor_Black);	//文字色設定(文字色、背景色)
						DrawString(Device.TASK[i].Name 				, _DrawX+5,   _DrawY-1	, 16, top_left);	//文字描写　タスクの名前表示
						String TimeString =TimeToStrings(Device.TASK[i].RunTime_RemainingTime);					//残り時間の表示
						DrawString("Remaining: "+ TimeString,  _DrawX+210, _DrawY+1, 14, top_right);			//文字描写　残り時間表示
						DrawString(String(Device.TASK[i].Priority) 	, _DrawX+287, _DrawY+1	, 12, top_right);	//文字描写　優先度表示

						////////////////////////////////////////////////////////////////////////////
						//ゲージの描写	
						////////////////////////////////////////////////////////////////////////////
						level =  maps(( Device.TASK[i].RunTime_RemainingTime),0,Device.TASK[i].RunTime_ElapsedOver,15,0);
						DrawDataGauge(_DrawX+215,_DrawY+3, level ,BaseColor_Cyan );
						Device.TASK[i].isDraw =false; //描写終了

						DrawMSG+="EXE \t";

					}
				}
			}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//　タスク表示　待機中 Wait
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			///////////////////////////////////////////////////////////////
			// 　タスク枠表示　Wait
			///////////////////////////////////////////////////////////////
			for(int i=0;i<TASK_Name_End;i++){
				_DrawX = 10;


				if( Device.TASK[i].Status == TASK_Status_Wait   &&  Device.TASK[i].isDraw == true ){
					_DrawY = Device.TASK[  i  ].DrawY;	//座標を格納
					Device.TASK[  i  ].DrawX = _DrawX;	//座標を格納

					Device.LCD_Sprite.fillRect (0, _DrawY,300,TASK_H_Wait,BaseColor_Black);		//背景塗
					Device.LCD_Sprite.fillRoundRect (_DrawX, _DrawY,290,TASK_H_Wait,2,BaseColor_Orange);		//背景塗
					Device.LCD_Sprite.drawRoundRect (_DrawX, _DrawY,290,TASK_H_Wait,2,BaseColor_Beige);		//外枠
					Device.LCD_Sprite.setTextColor(BaseColor_Black);	//文字色設定(文字色、背景色)
					DrawString(Device.TASK[i].Name 				, _DrawX+5,   _DrawY-1	, 16, top_left);	//文字描写　タスクの名前表示
					DrawString(String(Device.TASK[i].Priority) 	, _DrawX+287, _DrawY+1	, 12, top_right);	//文字描写　優先度表示
					Device.TASK[i].isDraw =false; //描写終了
					DrawMSG+="Wait \t";

				}
			}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//　タスク表示　　カウント中
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////
			//　タスク枠表示　　カウント中
			///////////////////////////////////////////////////////////////////
			for(int i=0;i<TASK_Name_End;i++){
				if( Device.TASK[i].Status == TASK_Status_Count ){
					_DrawX = 10;


					if(Device.TASK[ i ].ElapsedTime_OLD != Device.TASK[ i ].ElapsedTime){
						isDraw =true; //描写指示
 					    Device.TASK[ i ].ElapsedTime_OLD =Device.TASK[ i ].ElapsedTime;				
						_DrawY = Device.TASK[  i  ].DrawY;	//座標を格納
						Device.LCD_Sprite.fillRect (0, _DrawY,300,TASK_H_Count,BaseColor_Black);		//背景塗
						Device.LCD_Sprite.fillRoundRect (_DrawX, _DrawY,290,TASK_H_Count,2,BaseColor_Green);		//背景塗
						Device.LCD_Sprite.drawRoundRect (_DrawX, _DrawY,290,TASK_H_Count,2,BaseColor_Beige);		//外枠

						Device.LCD_Sprite.setTextColor(BaseColor_Black);	//文字色設定(文字色、背景色)
					

///////////////////////////////////////
						DrawString(Device.TASK[i].Name 				, _DrawX+5,   _DrawY-1	, 16, top_left);	//文字描写　タスクの名前表示
						String TimeString =TimeToStrings(Device.TASK[i].RemainingTime);					//残り時間の表示
						DrawString("Remaining: "+ TimeString,  _DrawX+210, _DrawY+1, 14, top_right);			//文字描写　残り時間表示
						DrawString(String(Device.TASK[i].Priority) 	, _DrawX+287, _DrawY+1	, 12, top_right);	//文字描写　優先度表示

						////////////////////////////////////////////////////////////////////////////
						//ゲージの描写	
						////////////////////////////////////////////////////////////////////////////
						level =  maps(( Device.TASK[i].ElapsedTime),0,Device.TASK[i].IntervalTime,0,15);

						DrawDataGauge(_DrawX+215,_DrawY+3, level ,BaseColor_Cyan );
						Device.TASK[i].DrawY_OLD = Device.TASK[i].DrawY;
						Device.TASK[i].isDraw =false; //描写終了
						DrawMSG+="Count \t";

					}
				}
			}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//　タスク表示　　非実行
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			///////////////////////////////////////////////////////////////////
			//↓の余白を消す
			///////////////////////////////////////////////////////////////////
			int max_non =Device.TASK_Title[TASK_Status_Non   ].TASK_Count;
			int non_c =0;
			///////////////////////////////////////////////////////////////////
			//　タスク枠表示　　非実行
			///////////////////////////////////////////////////////////////////
			for(int i=0;i<TASK_Name_End;i++){

				_DrawX = 10;



				if( Device.TASK[i].Status == TASK_Status_Non  && Device.TASK[i].isDraw == true ){
					non_c++;
					_DrawY = Device.TASK[  i  ].DrawY;	//座標を格納
					Device.TASK[  i  ].DrawX = _DrawX;	//座標を格納

					if( non_c== max_non){
						Device.LCD_Sprite.fillRect (0, _DrawY,300,220-_DrawY+10,BaseColor_Black);		//背景塗
					}

					Device.LCD_Sprite.fillRect (0, _DrawY+1,300,TASK_H_Non,BaseColor_Black);		//背景塗

					Device.LCD_Sprite.fillRoundRect (_DrawX, _DrawY,290,TASK_H_Non,2,BaseColor_Gray);		//背景塗
					Device.LCD_Sprite.drawRoundRect (_DrawX, _DrawY,290,TASK_H_Non,2,BaseColor_Beige);		//外枠

					Device.LCD_Sprite.setTextColor(BaseColor_Black);	//文字色設定(文字色、背景色)

					DrawString(Device.TASK[i].Name 				, _DrawX+5, _DrawY	, 12, top_left);	//文字描写　タスクの名前表示
					DrawString(String(Device.TASK[i].Priority) 	, _DrawX+287, _DrawY	, 12, top_right);	//文字描写　優先度表示

//					Device.TASK[i].DrawY_OLD = Device.TASK[i].DrawY;
					Device.TASK[i].isDraw =false; //描写終了
					DrawMSG+="Non \t";


				}
		
			}   




/*
/


	


	Device.DD_IMG.pushSprite(0, 0);    //画面描写
	*/

	SwipeScreen();		//スワイプ

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




