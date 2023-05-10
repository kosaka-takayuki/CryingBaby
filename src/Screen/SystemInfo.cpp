#include "Screen/SystemInfo.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SystemInfo
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Info(){	



	int _DrawY =0;
	boolean isDraw = false;	//更新する必要があるかどうか

	int _DrawX_MSG_L = 189-20;
	int _DrawX_MSG_C = 233-10;

	char tmpA[40],tmpB[40];

	int ShowNo;

	String DrawMSG ="";


	bool isFirstDraw =false;	//画面更新時に表示されない問題を防ぐ
	

	/////////////////////////////////////////////////////////////////////////////////////
    //画面設定
	/////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////
    // 時間経過アニメーション　徐々にフェードイン
	/////////////////////////////////////////////////////////////////////////////////////
	DrawTitle("System Info", 0, 600, BaseColor_Cyan);




	//最初の一度だけ実行
	if( Device.isModeChangeFirstTime == false ){



		isFirstDraw = true;	//画面更新時に表示されない問題を防ぐ
		if(Device.isHelp == true){
			Device.AquesTalk.playK("システム / インフォメーション", 50, Device.isAquesTalk);                          //AquesTalkで会話　会話スピードは最低の50
		}
		Device.InfoData[ 0].Name = "Date/Time";
		Device.InfoData[ 1].Name = "Baby Name";
		Device.InfoData[ 2].Name = "Power";

		Device.InfoData[ 3].Name = "Microphone";
		Device.InfoData[ 4].Name = "Eye Sensor";
		Device.InfoData[ 5].Name = "Diapers Sensor";
		Device.InfoData[ 6].Name = "Mouth Sensor";
		Device.InfoData[ 7].Name = "Milk Temperature";
		Device.InfoData[ 8].Name = "Drink Level";

		Device.InfoData[ 9].Name = "Ton Per Minutes";
		Device.InfoData[10].Name = "IMU";
		Device.InfoData[11].Name = "Position";

		_DrawY = 40;
		for(int i=0;i<12;i++){
			//Y軸座標計算
			Device.InfoData[ i ].Draw_Y =  _DrawY +(i*15);	//座標を格納
			Device.InfoData[ i ].Gauge_OLD =-1;
			Device.InfoData[ i ].MSG_A_OLD ="-1";
			Device.InfoData[ i ].MSG_B_OLD ="-1";
			Device.InfoData[ i ].MSG_C_OLD ="-1";


			uint32_t DColor= BaseColor_Green;

			//左側色分け設定
			switch (i){
				case 0:
				case 1:
				case 2:		DColor = BaseColor_Green;
				break;
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
				case 11:	DColor = BaseColor_Orange;
				break;
			}

			Device.LCD_Sprite.fillRoundRect (0, Device.InfoData[ i ].Draw_Y,130,13,2,DColor);		//左側の枠描写
			//右側ゲージの背景色の設定
//			if(i>=2 && i<=11){
					Device.LCD_Sprite.fillRoundRect (233, Device.InfoData[ i ].Draw_Y, 67,13,2,DColor);		//背景塗
//			}
			DrawString( Device.InfoData[ i ].Name   , 125,Device.InfoData[ i ].Draw_Y+6, 14, middle_right);	//文字描写
			isDraw = true;
		}
			

		
		/////////////////////////////////////////////////////////////////////
		//Macアドレス表示
		/////////////////////////////////////////////////////////////////////
		DrawBackGround(1, Device.InfoData[ 1 ].Draw_Y,BaseColor_Green);	//背景塗
		DrawString( Device.BabyName , 221, Device.InfoData[ 1 ].Draw_Y+6, 14, middle_center);	//文字描写

							
		
		
		for(int i=0;i<12;i++){
			Device.InfoData[ i ].MSG_A_OLD ="-1";
			Device.InfoData[ i ].MSG_B_OLD ="-1";
			Device.InfoData[ i ].MSG_C_OLD ="-1";
		}












		Device.isModeChangeFirstTime = true;
	}




	/////////////////////////////////////////////////////////////////////
	//FPS表示
	/////////////////////////////////////////////////////////////////////
		isDraw =DrawFPS(BaseColor_Cyan);




	/////////////////////////////////////////////////////////////////////
	//日時管理
	/////////////////////////////////////////////////////////////////////
					ShowNo =0;
					Device.InfoData[ ShowNo ].MSG_A =Device.TimeString;	//データ格納
					if(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD){		//過去データと今のデータが異なる場合のみ描写
						Device.LCD_Sprite.fillRoundRect (135, Device.InfoData[ ShowNo ].Draw_Y,80,13,2,BaseColor_Green);		//背景塗
						Device.LCD_Sprite.fillRoundRect (220, Device.InfoData[ ShowNo ].Draw_Y,80,13,2,BaseColor_Green);		//背景塗

						DrawString( Device.DateString, 175, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_center);	//文字描写
						DrawString( Device.TimeString, 260, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_center);	//文字描写
						isDraw = true;	//更新する

		//				DrawMSG +="Time(";
		//				DrawMSG +=Device.TimeString;
		//				DrawMSG +=")\t";

					}
					Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納



	/////////////////////////////////////////////////////////////////////
	//Battery
	/////////////////////////////////////////////////////////////////////
					ShowNo =2;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						sprintf(tmpA, "%3.1f%%",(float)Device.Sensor.Battery.Data );	//%値表示
						sprintf(tmpB, "%3.1fV" , Device.Battery.Volt );			//V値表示
						
						Device.InfoData[ ShowNo ].MSG_A = tmpA;	//データ格納A
						Device.InfoData[ ShowNo ].MSG_B = tmpB;	//データ格納B

						//データ格納B
						if (Device.Battery.isUSB == true) {			Device.InfoData[ ShowNo ].MSG_C ="USB Power";			} 
								else {								Device.InfoData[ ShowNo ].MSG_C ="Battery Power";		}

						if(	(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD) ||
							(Device.InfoData[ ShowNo ].MSG_B != Device.InfoData[ ShowNo ].MSG_B_OLD) ||
							(Device.InfoData[ ShowNo ].MSG_C != Device.InfoData[ ShowNo ].MSG_C_OLD)){

							//左側項目文字の変更
							Device.LCD_Sprite.fillRoundRect (0, Device.InfoData[ ShowNo ].Draw_Y,130,13,2,BaseColor_Green);			//背景塗
							if (Device.Battery.isUSB == true) {			Device.InfoData[ ShowNo ].Name ="USB Power";			} 
									else {								Device.InfoData[ ShowNo ].Name ="Battery Power";		}
							DrawString( Device.InfoData[ ShowNo ].Name, 125, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_right);	//文字描写 左側の項目

							//左側の数値描写
							DrawBackGround(3, Device.InfoData[ ShowNo ].Draw_Y,BaseColor_Green);	//背景塗
							DrawString( tmpA, _DrawX_MSG_L+5, Device.InfoData[ ShowNo ].Draw_Y+6, 12, middle_right);	//文字描写
							DrawString( tmpB, _DrawX_MSG_C, Device.InfoData[ ShowNo ].Draw_Y+6, 12, middle_right);	//文字描写

							////////////////////////////////////////////////////////////////////////////
							//ゲージの描写	
							////////////////////////////////////////////////////////////////////////////
							Device.InfoData[ ShowNo ].Gauge = maps(Device.Battery.Level,0,100,0,15);
							DrawDataGauge(233+4,Device.InfoData[ ShowNo ].Draw_Y+1,Device.InfoData[ ShowNo ].Gauge,BaseColor_Tomato);	//データゲージの描写

							DrawMSG +="Battery \t";
							isDraw = true;	//更新する
						}
						Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納
						Device.InfoData[ ShowNo ].MSG_B_OLD =Device.InfoData[ ShowNo ].MSG_B;	//データ格納
						Device.InfoData[ ShowNo ].MSG_C_OLD =Device.InfoData[ ShowNo ].MSG_C;	//データ格納




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
	//Cds  Diapers Sensor
	/////////////////////////////////////////////////////////////////////
					ShowNo =5;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						Device.InfoData[ ShowNo ].MSG_A  =Device.Sensor.Diapers.SData;
						if(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD){
							//FPSを稼ぐために前のデータを比べて5以上であるときのみ描写
							if((abs(Device.Sensor.Diapers.Data_Old - Device.Sensor.Diapers.Data)  >= 5)|| (Device.Sensor.Diapers.Data==0)||(isFirstDraw == true)){
								DrawBackGround(2, Device.InfoData[ ShowNo ].Draw_Y,BaseColor_Orange, BaseColor_Tomato, Device.Sensor.Diapers.isActive );	//背景塗
								DrawString(Device.InfoData[ ShowNo ].MSG_A, _DrawX_MSG_C, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_right);	//文字描写
								isDraw = true;	//更新する
								DrawMSG +="Diapers \t";
							}
							Device.Sensor.Diapers.Data_Old =   Device.Sensor.Diapers.Data ;		//描写用

							////////////////////////////////////////////////////////////////////////////
							//ゲージの描写	
							////////////////////////////////////////////////////////////////////////////
								Device.InfoData[ ShowNo ].Gauge = maps((int)Device.Sensor.Diapers.Data,Device.Sensor.Diapers.Min,Device.Sensor.Diapers.Max,0,15);
								if(Device.InfoData[ ShowNo ].Gauge != Device.InfoData[ ShowNo ].Gauge_OLD){
									DrawDataGauge(233+4,Device.InfoData[ ShowNo ].Draw_Y+1,Device.InfoData[ ShowNo ].Gauge,BaseColor_White, BaseColor_Tomato,Device.Sensor.Diapers.isActive );	//データゲージの描写
										DrawMSG +="Diapers  G\t";
								}
								Device.InfoData[ ShowNo ].Gauge_OLD =Device.InfoData[ ShowNo ].Gauge;	//データ格納
						}
						Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納




	/////////////////////////////////////////////////////////////////////
	//Mouth Sensor
	/////////////////////////////////////////////////////////////////////
				ShowNo =6;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						Device.InfoData[ ShowNo ].MSG_A  =Device.Sensor.Mouth.SData;
						Device.InfoData[ ShowNo ].MSG_B  =(String)Device.Sensor.Mouth.isActive;
						if(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD  || Device.InfoData[ ShowNo ].MSG_B != Device.InfoData[ ShowNo ].MSG_B_OLD){
							//FPSを稼ぐために前のデータを比べて5以上であるときのみ描写
							if((abs(Device.Sensor.Mouth.Data_Old - Device.Sensor.Mouth.Data)  >= 5)|| (Device.Sensor.Mouth.Data==0)||(isFirstDraw == true)|| Device.InfoData[ ShowNo ].MSG_B != Device.InfoData[ ShowNo ].MSG_B_OLD){
								DrawBackGround(2, Device.InfoData[ ShowNo ].Draw_Y,BaseColor_Orange, BaseColor_Tomato, Device.Sensor.Mouth.isActive );	//背景塗
								DrawString(Device.InfoData[ ShowNo ].MSG_A, _DrawX_MSG_C, Device.InfoData[ ShowNo ].Draw_Y+6, 14, middle_right);	//文字描写
								isDraw = true;	//更新する
								DrawMSG +="Mouth \t";
							}
							Device.Sensor.Mouth.Data_Old =   Device.Sensor.Mouth.Data ;		//描写用

							////////////////////////////////////////////////////////////////////////////
							//ゲージの描写	
							////////////////////////////////////////////////////////////////////////////
								Device.InfoData[ ShowNo ].Gauge = maps((int)Device.Sensor.Mouth.Data,Device.Sensor.Mouth.Min,Device.Sensor.Mouth.Max,0,15);
								if(Device.InfoData[ ShowNo ].Gauge != Device.InfoData[ ShowNo ].Gauge_OLD){
									DrawDataGauge(233+4,Device.InfoData[ ShowNo ].Draw_Y+1,Device.InfoData[ ShowNo ].Gauge,BaseColor_White, BaseColor_Tomato,Device.Sensor.Mouth.isActive );	//データゲージの描写
										DrawMSG +="Mouth  G\t";
								}
								Device.InfoData[ ShowNo ].Gauge_OLD =Device.InfoData[ ShowNo ].Gauge;	//データ格納
						}
						Device.InfoData[ ShowNo ].MSG_A_OLD =Device.InfoData[ ShowNo ].MSG_A;	//データ格納
						Device.InfoData[ ShowNo ].MSG_B_OLD =Device.InfoData[ ShowNo ].MSG_B;	//データ格納




	/////////////////////////////////////////////////////////////////////
	//Milk Temperature
	/////////////////////////////////////////////////////////////////////
				ShowNo =7;
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
	//Level　Sensor
	/////////////////////////////////////////////////////////////////////
					ShowNo =8;
					////////////////////////////////////////////////////////////////////////////
					//データ文字の描写	
					////////////////////////////////////////////////////////////////////////////
						Device.InfoData[ ShowNo ].MSG_A  =Device.Sensor.Level.SData+" %";
						if(Device.InfoData[ ShowNo ].MSG_A != Device.InfoData[ ShowNo ].MSG_A_OLD){
							//FPSを稼ぐために前のデータを比べて5以上であるときのみ描写
							if((abs(Device.Sensor.Level.Data_Old - Device.Sensor.Level.Data)  >= 1)|| (Device.Sensor.Level.Data==0)||(isFirstDraw == true)){
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



	/////////////////////////////////////////////////////////////////////
	//TPM
	/////////////////////////////////////////////////////////////////////
					ShowNo =9;
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
					ShowNo =10;
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
					ShowNo =11;
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