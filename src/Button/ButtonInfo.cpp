#include "Button/ButtonInfo.h"

#include "Global/Serial.h"
#include "Draw/Draw_Function.h"

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// コンストラクタ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		ButtonInfo::ButtonInfo(){ }



					
/*int _Bar_StartX    =  30;
							//スタートX座標
					int _Bar_Width     = 240;							//バーの全体のよこ幅
					int _Button_Width  =  60; 
					*/

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Initialize
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void ButtonInfo::Initialize(int _bar_w, int _but_w, String m1, String m2, 			 		   uint32_t _c1, uint32_t _c2 ){
		this->ButtonType = Button_Type2;
		this->_Bar_StartX    =  20;							//スタートX座標
		this->_Bar_Width     =  _bar_w;							//バーの全体のよこ幅
		this->_Button_Width  =  _but_w; 

		this->MSG[0] = m1;			this->MSG[1] = m2;				
		this->BackColor[0] = _c1;	this->BackColor[1] = _c2;		

		this->SelectButton =1;		//STOP選択
		this->SelectButtonMoveing=1;
		SetSelectButton(this->SelectButton);	//ボタンの設定

		this->isClick =false;

	}
	void ButtonInfo::Initialize(int _bar_w, int _but_w, String m1, String m2, String m3, 		   uint32_t _c1, uint32_t _c2,  uint32_t _c3 ){
		this->ButtonType = Button_Type3;
		this->_Bar_StartX    =  20;							//スタートX座標
		this->_Bar_Width     =  _bar_w;							//バーの全体のよこ幅
		this->_Button_Width  =  _but_w; 

		this->MSG[0] = m1;			this->MSG[1] = m2;				this->MSG[2] = m3;				
		this->BackColor[0] = _c1;	this->BackColor[1] = _c2;		this->BackColor[2] = _c3;		

		this->SelectButton =1;		//STOP選択
		this->SelectButtonMoveing=1;
		SetSelectButton(this->SelectButton);	//ボタンの設定

		this->isClick =false;
	}
	void ButtonInfo::Initialize(int _bar_w, int _but_w, String m1, String m2, String m3, String m4, uint32_t _c1, uint32_t _c2,  uint32_t _c3,  uint32_t _c4 ){
		this->ButtonType = Button_Type4;
		this->_Bar_StartX    =  20;							//スタートX座標
		this->_Bar_Width     =  _bar_w;							//バーの全体のよこ幅
		this->_Button_Width  =  _but_w; 

		this->MSG[0] = m1;			this->MSG[1] = m2;				this->MSG[2] = m3;				this->MSG[3] = m4;
		this->BackColor[0] = _c1;	this->BackColor[1] = _c2;		this->BackColor[2] = _c3;		this->BackColor[3] = _c4;

		this->SelectButton =1;		//STOP選択
		this->SelectButtonMoveing=1;
		SetSelectButton(this->SelectButton);	//ボタンの設定

		this->isClick =false;
	}

	void ButtonInfo::Initialize(int _bar_w, int _but_w, String m1, String m2, String m3, String m4, String m5, uint32_t _c1, uint32_t _c2,  uint32_t _c3,  uint32_t _c4,  uint32_t _c5 ){
		this->ButtonType = Button_Type5;
		this->_Bar_StartX    =  20;							//スタートX座標
		this->_Bar_Width     =  _bar_w;							//バーの全体のよこ幅
		this->_Button_Width  =  _but_w; 

		this->MSG[0] = m1;			this->MSG[1] = m2;				this->MSG[2] = m3;				this->MSG[3] = m4;			this->MSG[4] = m5;
		this->BackColor[0] = _c1;	this->BackColor[1] = _c2;		this->BackColor[2] = _c3;		this->BackColor[3] = _c4;	this->BackColor[4] = _c5;

		this->SelectButton =1;		//STOP選択
		this->SelectButtonMoveing=1;
		SetSelectButton(this->SelectButton);	//ボタンの設定

		this->isClick =false;
	}



	

/////////////////////////////////////////////////////////////////////////////////////////////////////
	// SetSelectButton
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void ButtonInfo::SetSelectButton(	int SelectButton){
		this->SelectButton =SelectButton;	//STOP選択

		this->_Button_StartX =  (float)((this->_Bar_Width - (this->_Button_Width* this->ButtonType))/(this->ButtonType-1)+this->_Button_Width);
		this->DrawX     = (int)(this->_Bar_StartX+(this->SelectButton * this->_Button_StartX));
		this->DrawX_OLD = -1;

	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Buton
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     boolean ButtonInfo::DrawButton(int _no, int y){


		if(Device.M5Touch == true){

			uint32_t color_BackGround		= BaseColor_Cyan;
			int raito = 0;

			Device.LCD_Sprite.setTextColor(BaseColor_Black);			//文字色設定(文字色、背景色)
				
				this->_Button_StartX =  (float)((this->_Bar_Width - (this->_Button_Width* this->ButtonType))/(this->ButtonType-1)+this->_Button_Width);

				///////////////////////////////////////////
				//3タイプ用
				///////////////////////////////////////////
					//タッチ判定
					if(Device.LCD_Tocuh_Sprite.x !=-1){
						if(Device.LCD_Tocuh_Sprite.y >=y &&  Device.LCD_Tocuh_Sprite.y <=y+12){	//Y軸範囲設定
							int dx = _Bar_StartX+(this->SelectButton*_Button_StartX);	//ゲージ位置計算
							///////////////////////////////////////////
							//初めてタッチされた
							///////////////////////////////////////////
							if(Device.LCD_Tocuh_Sprite.x >=dx &&  Device.LCD_Tocuh_Sprite.x <=dx + _Button_Width){	//Y軸範囲設定
									if(this->isClick == false){
										this->ClickPoint = Device.LCD_Tocuh_Sprite;	//クリックした場所を記録
										this->isClick =true;						//クリックフラグ
//										Serial.println(String(this->Title) +"\t FirstClick");
									}
							}
						}
						this->DrawX = _Bar_StartX+((float)this->SelectButton*_Button_StartX);

						////////////////////////////////////////////////////////////////////
						//クリックして移動中の処理
						////////////////////////////////////////////////////////////////////
						if(this->isClick == true){
//							Serial.println(String("\t" + this->Title) +"\t Moveing");
							int R = (320 / this->ButtonType);

							this->SelectButtonMoveing = this->ClickPoint_B.x / R;
							switch (this->SelectButtonMoveing){
								case 0:		color_BackGround = BaseColor_Orange;	break;
								case 1:		color_BackGround = BaseColor_Cyan; 		break;
								case 2:		color_BackGround = BaseColor_Tomato; 	break;
							}
							if(this->SelectButtonMoveing_OLD != this->SelectButtonMoveing){
//								SetVibration(125);	//バイブレーション設定
							}
							this->DrawX = _Bar_StartX+(this->SelectButton*_Button_StartX)-(this->ClickPoint.x -Device.LCD_Tocuh_Sprite.x);
							int lastX   =  _Bar_StartX + _Bar_Width - _Button_Width;

							if( this->DrawX <= _Bar_StartX	 ){	this->DrawX = _Bar_StartX;		}
							if( this->DrawX >= lastX		 ){	this->DrawX =lastX;				}
							this->SelectButtonMoveing_OLD = this->SelectButtonMoveing;
						}
					}else{
						if(this->isClick ==true){
							////////////////////////////////////////////////////////////////////
							//タッチが解除されたとき
							////////////////////////////////////////////////////////////////////

							int R = (320 / this->ButtonType);
							this->SelectButton = this->ClickPoint_B.x / R;

//							Serial.println(String(this->Title) +"\t Out of Click\t" + String(this->SelectButton) ) ;

							this->DrawX = _Bar_StartX+((float)this->SelectButton*_Button_StartX);

							this->DrawX_OLD = -1;
						}
						this->isClick =false;
					}
					////////////////////////////////////////////////////////////////////
					//描写処理
					////////////////////////////////////////////////////////////////////
					if(this->DrawX != this->DrawX_OLD){

						color_BackGround = this->BackColor[this->SelectButton];
							
						Device.LCD_Sprite.fillRoundRect (_Bar_StartX, y, _Bar_Width,	24,	12,	WHITE);				//背景棒

							//一番右端の時　（通常計算だとFloatの関数で誤差が生まれずれるので、右端の場合のみ補正）
							if(this->ButtonType == (this->SelectButton+1) ){
									this->DrawX = _Bar_StartX+_Bar_Width - _Button_Width;


							}

						Device.LCD_Sprite.fillRoundRect (this->DrawX, y, _Button_Width,	24,	12,	color_BackGround);		//選択枠


						//文字の描写
						for(int i=0; i<this->ButtonType; i++){
							if(i== this->SelectButton){
								DrawString( this->MSG[i], _Bar_StartX+30 + (i*_Button_StartX), y+12, 128, middle_center);	//文字描写
							}else{
								DrawString( this->MSG[i], _Bar_StartX+30 + (i*_Button_StartX), y+12, 12, middle_center);	//文字描写
							}
						}
						this->isDraw = true;
						this->DrawX_OLD = this->DrawX;
						this->ClickPoint_B = Device.LCD_Tocuh_Sprite;
					}else{
						this->isDraw = false;

					}
			


			
		//////////////////////////////////////////////////////////////
		//ボタン処理
		//////////////////////////////////////////////////////////////
		if(this->SelectButton != this->SelectButton_OLD){

			this->SelectButton_OLD = this->SelectButton; 


			switch(_no){
				//////////////////////////////////////////////////////////
				//　緊急
				//////////////////////////////////////////////////////////
				case Button_TASK_Emerg: 
				//////////////////////////////////////////////////////////
						switch (this->SelectButton){
							case 0:	 	Device.TASK[ GetNo_TASK_Mood(TASK_Name_Emerg) ].Enable =true;	//有効可
										TASK_End( TASK_Name_Emerg );

			//							Device.TASK[ GetNo_TASK_Mood(TASK_Name_Emerg) ].isRun = true;
										ScreenChangeNo( Screen_Emergency );	//画面推移
										SendTASK();	//TASK送信

										break;
							case 1:	 	Device.TASK[ GetNo_TASK_Mood(TASK_Name_Emerg) ].Enable =true;	//有効可
										TASK_ForcedExecution( TASK_Name_Emerg );
										TASK_Sort( );		//データソートおよび正規化
				//						Device.TASK[ GetNo_TASK_Mood(TASK_Name_Emerg) ].isRun = true;
										ScreenChangeNo( Screen_Emergency );	//画面推移
										SendTASK();	//TASK送信

										break;
							case 2:	 	Device.TASK[ GetNo_TASK_Mood(TASK_Name_Emerg) ].Enable =false;	//無効可	 センサ値が超えても反応しないように設定
										SendTASK();	//TASK送信

										break;
						}
					break;


				//////////////////////////////////////////////////////////
				//　機嫌
				//////////////////////////////////////////////////////////
				case Button_TASK_Mood:
				//////////////////////////////////////////////////////////
						switch (this->SelectButton){
							case 0:	 	//STOP
										TASK_End( TASK_Name_Mood );
										ScreenChangeNo( Screen_Mood );	//画面推移
										SendTASK();	//TASK送信
										break;
							case 1:	 	//REcount
										TASK_ReStart( TASK_Name_Mood );
										ScreenChangeNo( Screen_Mood );	//画面推移
										SendTASK();	//TASK送信

										break;
							case 2:	 	//Wait
										break;
							case 3:	 	//RUN
										TASK_ForcedExecution( TASK_Name_Mood );
										TASK_Sort( );		//データソートおよび正規化
										SendTASK();	//TASK送信

										ScreenChangeNo( Screen_Mood );	//画面推移
										break;
						}
					break;

				//////////////////////////////////////////////////////////
				//　眠たい
				//////////////////////////////////////////////////////////
				case Button_TASK_Sleep:
				//////////////////////////////////////////////////////////
						switch (this->SelectButton){
							case 0:	 	//STOP
Serial.println("************ STOP");

										TASK_End( TASK_Name_Sleep );
										ScreenChangeNo( Screen_Sleep );	//画面推移
										SendTASK();	//TASK送信

										break;
							case 1:	 	//REcount
Serial.println("************ RESTART");
										TASK_ReStart( TASK_Name_Sleep );
										ScreenChangeNo( Screen_Sleep );	//画面推移
										SendTASK();	//TASK送信

										break;
							case 2:	 	//Wait
										break;
							case 3:	 	//RUN
Serial.println("************ RUN");

										TASK_ForcedExecution( TASK_Name_Sleep );
										TASK_Sort( );		//データソートおよび正規化
										ScreenChangeNo( Screen_Sleep );	//画面推移
										SendTASK();	//TASK送信

										break;
						}
					break;
				//////////////////////////////////////////////////////////
				//　空腹
				//////////////////////////////////////////////////////////
				case Button_TASK_Hungry:
				//////////////////////////////////////////////////////////
						switch (this->SelectButton){
							case 0:	 	//STOP
										TASK_End( TASK_Name_Hungry );
										ScreenChangeNo( Screen_Hungry );	//画面推移
										SendTASK();	//TASK送信

										break;
							case 1:	 	//REcount
										TASK_ReStart( TASK_Name_Hungry );
										ScreenChangeNo( Screen_Hungry );	//画面推移
										SendTASK();	//TASK送信

										break;
							case 2:	 	//Wait
										break;
							case 3:	 	//RUN
										TASK_ForcedExecution( TASK_Name_Hungry );
										TASK_Sort( );		//データソートおよび正規化
										ScreenChangeNo( Screen_Hungry );	//画面推移
										SendTASK();	//TASK送信

										break;
						}
					break;
				//////////////////////////////////////////////////////////					
				case Button_TASK_Hungry_Motor:
				//////////////////////////////////////////////////////////
						switch (this->SelectButton){
							case 0:	 	//STOP
										Device.Sensor.Mouth.isHack 		= true;
										Device.Sensor.Mouth.HackData 	=  0;
										break;
							case 1:	 	//Auto
										Device.Sensor.Mouth.isHack 		= false;
										break;
							case 2:	 	//ON
										Device.Sensor.Mouth.isHack 		= true;
										Device.Sensor.Mouth.HackData 	=  6000;
										break;
						}
					break;



				//////////////////////////////////////////////////////////
				//　ゲップ
				//////////////////////////////////////////////////////////
				case Button_TASK_Burp:
				//////////////////////////////////////////////////////////
						switch (this->SelectButton){
							case 0:	 	//STOP
										TASK_End( TASK_Name_Burp );
										ScreenChangeNo( Screen_Burp );	//画面推移
										SendTASK();	//TASK送信

										break;
							case 1:	 	//Wait
										break;
							case 2:	 	//RUN
										TASK_ForcedExecution( TASK_Name_Burp );
										TASK_Sort( );		//データソートおよび正規化
										ScreenChangeNo( Screen_Burp );	//画面推移
										SendTASK();	//TASK送信

										break;
						}
					break;

				//////////////////////////////////////////////////////////
				//　排泄
				//////////////////////////////////////////////////////////
				case Button_TASK_Shit:
				//////////////////////////////////////////////////////////
						switch (this->SelectButton){
							case 0:	 	//STOP

										TASK_End( TASK_Name_Shit );
										ScreenChangeNo( Screen_Shit );	//画面推移
										SendTASK();	//TASK送信

										break;
							case 1:	 	//Wait
										break;
							case 2:	 	//RUN
										TASK_ForcedExecution( TASK_Name_Shit );
										TASK_Sort( );		//データソートおよび正規化
										ScreenChangeNo( Screen_Shit );	//画面推移
										SendTASK();	//TASK送信

										break;
						}
					break;

				//////////////////////////////////////////////////////////
				//　排泄 インク
				//////////////////////////////////////////////////////////
				case Button_TASK_Shit_INK:
				//////////////////////////////////////////////////////////
						switch (this->SelectButton){
							case 0:	 	//RED
										Device.Motor[ Motor_Ink_Red    ].Ratio =100;
										Device.Motor[ Motor_Ink_Yellow ].Ratio =  0;


										break;

							case 1:	 	//Wait
										raito =(int)random(0,100);
										if(raito > 50){
											Device.Motor[ Motor_Ink_Red ].Ratio =100;
											Device.Motor[ Motor_Ink_Yellow ].Ratio =  0;

										}else{
											Device.Motor[ Motor_Ink_Red ].Ratio =   0;
											Device.Motor[ Motor_Ink_Yellow ].Ratio = 100;
										}
										break;

							case 2:	 	//Yellow
										Device.Motor[ Motor_Ink_Red ].Ratio =   0;
										Device.Motor[ Motor_Ink_Yellow ].Ratio = 100;
										break;
						}
					break;


				//////////////////////////////////////////////////////////
				//　おむつ替え
				//////////////////////////////////////////////////////////
				case Button_TASK_Diapers:
				//////////////////////////////////////////////////////////
						switch (this->SelectButton){
							case 0:	 	//STOP

										TASK_End( TASK_Name_Diapers );
										ScreenChangeNo( TASK_Name_Diapers );	//画面推移
										SendTASK();	//TASK送信

										break;
							case 1:	 	//Wait
										break;
							case 2:	 	//RUN
										TASK_ForcedExecution( TASK_Name_Diapers );
										TASK_Sort( );		//データソートおよび正規化
										ScreenChangeNo( Screen_Diapers );	//画面推移
										SendTASK();	//TASK送信

										break;
						}
					break;


				//////////////////////////////////////////////////////////
				//　寝ている
				//////////////////////////////////////////////////////////
				case Button_TASK_Sleeping:
				//////////////////////////////////////////////////////////
						switch (this->SelectButton){
							case 0:	 	//STOP
										TASK_End( TASK_Name_Sleeping );
										ScreenChangeNo( Screen_Sleeping );	//画面推移
										SendTASK();	//TASK送信

										break;
							case 1:	 	//Wait
										break;
							case 2:	 	//RUN
										TASK_ForcedExecution( TASK_Name_Sleeping );
										TASK_Sort( );		//データソートおよび正規化
										ScreenChangeNo( Screen_Sleeping );	//画面推移
										SendTASK();	//TASK送信

										break;
						}
					break;

				//////////////////////////////////////////////////////////
				//　Error
				//////////////////////////////////////////////////////////
				case Button_SystemCheck:
				//////////////////////////////////////////////////////////
						switch (this->SelectButton){
							case 0:	 	//STOP

										break;
							case 1:	 	//Igore	強制起動
										Device.AquesTalk.playK("強制起動します", 50, Device.isAquesTalk);
										OutPutLogs(LogCode_Error,0,"+-- Ignore Start --");    //Log出力
										delay(2000); 
										Device.ScreenNo =0;
										Device.TimeModeChangeElapsed = millis(); //画面更新
										Device.isModeChangeFirstTime = false; 	//画面更新フラグ


										break;
							case 2:	 	//Reset	リセット
										Device.AquesTalk.playK("再起動します", 50, Device.isAquesTalk); 
										OutPutLogs(LogCode_Error,0,"+-- reboot --");    //Log出力
										delay(2000);
										esp_restart();                            //Reset
										break;
							case 3:	 	//Shoutdown シャットダウン
										Device.AquesTalk.playK("シャットダウンします。", 50, Device.isAquesTalk); 
										OutPutLogs(LogCode_Error,0,"+-- shutdown --");    //Log出力
										delay(2000);
										M5.Axp.PowerOff();                        //電源を落とす
										break;
						}
					break;


				//////////////////////////////////////////////////////////
				//　Mp3
				//////////////////////////////////////////////////////////
				case Button_MP3_Speaker:
				//////////////////////////////////////////////////////////
						switch (this->SelectButton){
							case 0:	 	//0
										Device.Mp3Volume =0;
										break;
							case 1:	 	//25
										Device.Mp3Volume =25;
										break;
							case 2:	 	//50
										Device.Mp3Volume =50;
										break;
							case 3:	 	//75
										Device.Mp3Volume =75;
										break;
							case 4:	 	//100
										Device.Mp3Volume =100;
										break;
						}
						Save_Preferences_File("/Preferences/Preferences.txt");

					break;					


				//////////////////////////////////////////////////////////
				//　M5
				//////////////////////////////////////////////////////////
				case Button_M5_Speaker:
				//////////////////////////////////////////////////////////
						switch (this->SelectButton){
							case 0:	 	//0
										Device.M5Volume =0;			
										break;
							case 1:	 	//25
										Device.M5Volume =25;
										break;
							case 2:	 	//50
										Device.M5Volume =50;
										break;
							case 3:	 	//75
										Device.M5Volume =75;
										break;
							case 4:	 	//100
										Device.M5Volume =100;
										break;
						}
						Device.AquesTalk.SetVolume(Device.M5Volume);
						Save_Preferences_File("/Preferences/Preferences.txt");

					break;					

				//////////////////////////////////////////////////////////
				//　Touch
				//////////////////////////////////////////////////////////
				case Button_M5_Touch:
				//////////////////////////////////////////////////////////
						switch (this->SelectButton){
							case 0:	 	//0
										Device.M5Touch =0;	
										break;
							case 1:	 	//25
										Device.M5Touch =1;
										break;
							case 2:	 	//50
										Device.M5Touch =2;
										break;
						}

					break;			
			}

		}
		}

		return this->isDraw;

	 }


