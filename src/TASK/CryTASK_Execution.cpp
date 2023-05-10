#include "TASK/CryTASK_Execution.h"

	//////////////////////////////////////////////////////////////
	//CryTASK_Execution
	//タスクの実行
	//////////////////////////////////////////////////////////////
	void CryTASK_Execution(float _speed){

		int RunNo =-1;
		//ステータスが実行中のタスクを検索
		for(int i=0;i<TASK_Name_End;i++){
			if(Device.TASK[i].Status == TASK_Status_Run){
				RunNo = i;
			}

		}

		if(RunNo != -1){
			////////////////////////////////////////////////////////////////////////////////
			// 実行中の処理
			////////////////////////////////////////////////////////////////////////////////

			//前の時間と今の時間が異なるとき、CountValue秒経過したとき　加算
			float	CountValue  =  1000.0f / _speed;	//時間再生速度設定
			if( (millis() - Device.TimeCountRunBack) >= CountValue  ){

				Device.TASK[ RunNo ].RunTime_Elapsed  	+= 1;  //時間加算
				Device.TASK[ RunNo ].RunTime_RemainingTime 	=  Device.TASK[RunNo ].RunTime_ElapsedOver  - Device.TASK[ RunNo ].RunTime_Elapsed;  //残り時間計算 秒
				Device.TimeCountRunBack = millis();
			}


			////////////////////////////////////////////////////////////
			//初回のみ実行
			////////////////////////////////////////////////////////////
			if(Device.TASK[ RunNo ].isFirtstTime ==true){
				OutPutLogs(LogCode_TASK ,0,"****************** TASK START\t" + Device.TASK[ RunNo ].Name );     //Log出力
				Device.TASK[ RunNo ].isFirtstTime =false;
				Device.TASK[ RunNo ].RunTime_Elapsed = 0;
				Device.TASK[ RunNo ].RunTime_RemainingTime 	=  Device.TASK[RunNo ].RunTime_ElapsedOver  - Device.TASK[ RunNo ].RunTime_Elapsed;  //残り時間計算 秒
				Device.TimeCountRunBack = millis();
				MP3.stop();			//MP3再生停止

//				Serial.println("************** ALL STOP");

				//モータを停止
				Device.Motor[	Motor_Main  ].SetSpeed( Motor_STOP);	//モータセット
				Device.Motor[	Motor_ValveA].SetSpeed( Motor_STOP);	//モータセット
				Device.Motor[	Motor_ValveB].SetSpeed( Motor_STOP);	//モータセット

				Device.Motor[	Motor_Ink_Red		].SetSpeed( Motor_STOP);	//モータセット
				Device.Motor[	Motor_Ink_Yellow	].SetSpeed( Motor_STOP);	//モータセット


				////////////////////////////////////////////////
				///////////////////////////////////////////////
				if(Device.TASK[ RunNo ].Name_No == TASK_Name_Shit){
					int raito =(int)random(0,100);
					if(raito > 50){

						Device.Motor[ Motor_Ink_Red ].Ratio =100;
						Device.Motor[ Motor_Ink_Yellow ].Ratio =  0;

					}else{
						Device.Motor[ Motor_Ink_Red ].Ratio =   0;
						Device.Motor[ Motor_Ink_Yellow ].Ratio = 100;
					}					

					Device.Motor[	Motor_Ink_Red		].SetSpeed( maps( Device.Motor[ Motor_Ink_Red    ].Ratio , 0,100,0,255 ));	//モータセット
					Device.Motor[	Motor_Ink_Yellow	].SetSpeed( maps( Device.Motor[ Motor_Ink_Yellow ].Ratio , 0,100,0,255 ));	//モータセット


				}



				////////////////////////////////////////////////////
				//個々の処理
				//LED表示
				////////////////////////////////////////////////////
				Serial.println("LED:" + String(Device.TASK[ RunNo ].Name_No) );

				switch (Device.TASK[ RunNo ].Name_No ){
					case  TASK_Name_Emerg:		Device.TASK[ RunNo ].SetLED_Loop(new TimeLED(0, 250, Device.LEDs.Color(255, 0, 0)), new TimeLED( 250, 500, Device.LEDs.Color( 64,  0,  0)) ); break;
					case  TASK_Name_Hungry:		Device.TASK[ RunNo ].SetLED_Loop(new TimeLED(0, 350, Device.LEDs.Color(250, 0, 0)), new TimeLED( 350, 700, Device.LEDs.Color(128, 16, 16)) ); break;
					case  TASK_Name_Power:		Device.TASK[ RunNo ].SetLED_Loop(new TimeLED(0, 500, Device.LEDs.Color(  0, 0, 0)), new TimeLED( 500,1000, Device.LEDs.Color(  0,  0,255)) ); break;
					case  TASK_Name_Mood:		Device.TASK[ RunNo ].SetLED_Loop(new TimeLED(0, 400, Device.LEDs.Color(200,32,32)), new TimeLED( 400, 800, Device.LEDs.Color(128, 32, 32)) ); break;
					case  TASK_Name_Sleep:		Device.TASK[ RunNo ].SetLED_Loop(new TimeLED(0, 600, Device.LEDs.Color(180, 0, 0)), new TimeLED( 600,1200, Device.LEDs.Color(128, 32, 32)) ); break;
					case  TASK_Name_Shit:		Device.TASK[ RunNo ].SetLED_Loop(new TimeLED(0,1000, Device.LEDs.Color( 64, 0, 0)), new TimeLED(1000,2000, Device.LEDs.Color( 32,  0,  0)) ); break;
					case  TASK_Name_Diapers:	Device.TASK[ RunNo ].SetLED_Loop(new TimeLED(0, 400, Device.LEDs.Color(200, 0, 0)), new TimeLED( 400, 800, Device.LEDs.Color(128, 32, 32)) ); break;

					case  TASK_Name_Sleeping:	Device.TASK[ RunNo ].SetLED_Loop(new TimeLED(0,1000, Device.LEDs.Color(  0, 0, 0)),  new TimeLED(1000,2000, Device.LEDs.Color( 0,  0,  0)) ); break;

					default:
												Device.TASK[ RunNo ].SetLED_Loop(new TimeLED(0,1000, Device.LEDs.Color( 64, 0, 0)), new TimeLED(1000,2000, Device.LEDs.Color( 32,  0,  0)) ); break;

				}

				SendTASK();

			}else{
				////////////////////////////////////////////////////////////
				//実行中
				////////////////////////////////////////////////////////////
			//	Serial.print("START:"  + String(Device.TASK[ RunNo ].LED_START.TimeStart) +"\tE:" + String(Device.TASK[ RunNo ].LED_START.TimeEnd)  );
			//	Serial.println("\t END:" + String(Device.TASK[ RunNo ].LED_END.TimeStart) +"\tE:" + String(Device.TASK[ RunNo ].LED_END.TimeEnd)  );

				SetTapeLEDsLoop(RunNo);									//LED描写
				
				
				//MP3再生
				int KindNo=-1;
				switch (Device.TASK[ RunNo ].Name_No ){
					case  TASK_Name_Mood:		KindNo =  3;	MP3_KingLoopPlay( KindNo , Device.Mp3Volume );	break;
					case  TASK_Name_Hungry:			
												
												if(Device.Sensor.Mouth.isActive == true){
													KindNo =  8; 
//													Serial.println(" GOKUGOKU -----------------------------------");
													MP3_KingLoopPlay( KindNo , Device.Mp3Volume );	
												}else{
													KindNo =  9;
													MP3_KingLoopPlay( KindNo , Device.Mp3Volume );	
												}

												
												break;
					case  TASK_Name_Sleep:		KindNo = 10;	MP3_KingLoopPlay( KindNo , Device.Mp3Volume );	break;
//					case  TASK_Name_Shit:		KindNo =  6;	MP3_KingLoopPlay( KindNo , Device.Mp3Volume );	break;
					case  TASK_Name_Emerg:		KindNo =  4;	MP3_KingLoopPlay( KindNo , Device.Mp3Volume );	break;
					case  TASK_Name_Diapers:	KindNo =  6;	MP3_KingLoopPlay( KindNo , Device.Mp3Volume );	break;

				}

				////////////////////////////////////////////////////////////
				//おむつ交換
				////////////////////////////////////////////////////////////
				if (Device.TASK[ RunNo ].Name_No == TASK_Name_Diapers){
					if(Device.Sensor.Diapers.isActive == true){
								OutPutLogs(LogCode_TASK ,1,"+--- TASK Clear\t" + Device.TASK[ RunNo ].Name );     //Log出力
								TASK_End(TASK_Name_Diapers);		//タスクの終了後、Nonに格納
								TASK_ForcedExecution( TASK_Name_Wait );		//タスク終了後にWaitを入れる
								TASK_Sort();		//ソート
								ScreenChangeNo( Screen_TASKMonitor );	//スクリーン移動

					}
				}

				////////////////////////////////////////////////////////////
				//おしっこ
				////////////////////////////////////////////////////////////
				if (Device.TASK[ RunNo ].Name_No == TASK_Name_Shit){

					SendDATA();		//データの送信

					//Mouth Sensor Active
					if(Device.Sensor.Level_Min.isActive == false){
//					if(true){
						//メインモータ を動作さる
						Device.Motor[Motor_Main  ].SetSpeed( Motor_Back);	//モータセット
						Device.Motor[Motor_ValveA].SetSpeed( Motor_Forward);		//モータセット
						Device.Motor[Motor_ValveB].SetSpeed( Motor_STOP);	//モータセット


						//インクモータを動作させる
						int InkA_Speed =maps( (int)Device.Motor[ Motor_Ink_Red    ].Ratio , 0,100, Motor_STOP, Motor_Forward);
						int InkB_Speed =maps( (int)Device.Motor[ Motor_Ink_Yellow ].Ratio , 0,100, Motor_STOP, Motor_Forward);

						if(InkA_Speed >InkB_Speed ){
//							Serial.println("Ink Red:\t ON \t\t InkB:\t OFF");
							Device.Motor[Motor_Ink_Red  ].SetSpeed( Motor_Forward);	//モータセット
							Device.Motor[Motor_Ink_Yellow  ].SetSpeed( Motor_STOP);	//モータセット
						}else{
//							Serial.println("Ink Yellow:\t OFF \t\t InkB:\t ON");
							Device.Motor[Motor_Ink_Red  ].SetSpeed( Motor_STOP);	//モータセット
							Device.Motor[Motor_Ink_Yellow  ].SetSpeed( Motor_Back);	//モータセット
						}

					}else{
						//モータを停止
						Device.Motor[Motor_Main  ].SetSpeed( Motor_STOP);	//モータセット
						Device.Motor[Motor_ValveA].SetSpeed( Motor_STOP);	//モータセット
						Device.Motor[Motor_ValveB].SetSpeed( Motor_STOP);	//モータセット

						//インクモータを動作させる
						Device.Motor[Motor_Ink_Red  ].SetSpeed( Motor_STOP );	//モータセット
						Device.Motor[Motor_Ink_Yellow  ].SetSpeed( Motor_STOP );		//モータセット

					}

					//もしミルクレベルが指定したレベルを超えたら、げっぷタスクを起動させて、Hungryは終了する
					if(Device.Sensor.Level_Min.isActive == true){
								OutPutLogs(LogCode_TASK ,1,"+--- TASK Clear\t" + Device.TASK[ RunNo ].Name );     //Log出力
								TASK_End(TASK_Name_Shit);		//タスクの終了後、Nonに格納

								TASK_ForcedExecution( TASK_Name_Diapers );		//タスク終了後にWaitを入れる
								TASK_Sort();		//ソート
								ScreenChangeNo( Screen_TASKMonitor );	//スクリーン移動
								SendTASK();	//TASK送信

					}
				}

				////////////////////////////////////////////////////////////
				//おなかすいた
				////////////////////////////////////////////////////////////
				if (Device.TASK[ RunNo ].Name_No == TASK_Name_Hungry){

					SendDATA();		//データの送信

					//Mouth Sensor Active
					if(Device.Sensor.Mouth.isActive == true){
						//モータを動作さる
						Device.Motor[Motor_Main  ].SetSpeed( 200);	//モータセット
						Device.Motor[Motor_ValveA].SetSpeed( Motor_STOP);		//モータセット
						Device.Motor[Motor_ValveB].SetSpeed( 200);	//モータセット


					}else{
						//モータを停止
						Device.Motor[Motor_Main  ].SetSpeed( Motor_STOP);	//モータセット
						Device.Motor[Motor_ValveA].SetSpeed( Motor_STOP);	//モータセット
						Device.Motor[Motor_ValveB].SetSpeed( Motor_STOP);	//モータセット

					}

					//もしミルクレベルが指定したレベルを超えたら、げっぷタスクを起動させて、Hungryは終了する
					if(Device.Sensor.Level.isActive == true){
							OutPutLogs(LogCode_TASK ,1,"+--- TASK Clear\t" + Device.TASK[ RunNo ].Name );     //Log出力
							Serial.println("*******************##################");
							TASK_ReStart( TASK_Name_Hungry );
							TASK_ForcedExecution( TASK_Name_Burp );		//タスク終了後にBurpを入れる

							TASK_ReStart( TASK_Name_Shit );	//Shitタスクのカウントを起動
//							TASK_ForcedExecution( TASK_Name_Wait );		//タスク終了後にWaitを入れる

							TASK_Sort();		//ソート
							ScreenChangeNo( Screen_Burp );	//スクリーン移動
							SendTASK();	//TASK送信
					}
					
				}

				////////////////////////////////////////////////////////////
				//機嫌加算
				////////////////////////////////////////////////////////////
				switch (Device.TASK[ RunNo ].Name_No ){
					case  TASK_Name_Sleep:
						//もしTPMが指定範囲外であれば　弱すぎる、強すぎる振動であれば
						if(	Device.Sensor.TPM.isActive == true){
							Device.TASK[RunNo].MoodTPMReset();		//TPMの時間をリセット
						}
							Device.TASK[RunNo].MoodCount(20,10);					//適正TPMであれば、加算



							if(Device.TASK[RunNo].MoodTotalCount >=100){
								OutPutLogs(LogCode_TASK ,1,"+--- TASK Clear\t" + Device.TASK[ RunNo ].Name );     //Log出力
								TASK_ReStart( TASK_Name_Sleep );
								TASK_ForcedExecution( TASK_Name_Sleeping );		//タスク終了後にWaitを入れる
								TASK_Sort();		//ソート
								ScreenChangeNo( Screen_TASKMonitor );	//スクリーン移動
								SendTASK();	//TASK送信
								Device.isMoodHack = false;	//ハックを解除

							}					
						break;


					case  TASK_Name_Mood:
						//もしTPMが指定範囲外であれば　弱すぎる、強すぎる振動であれば
						if(	Device.Sensor.TPM.isActive == true){
							Device.TASK[RunNo].MoodTPMReset();		//TPMの時間をリセット
						}
							Device.TASK[RunNo].MoodCount(20,10);					//適正TPMであれば、加算

							if(Device.TASK[RunNo].MoodTotalCount >=100){
								OutPutLogs(LogCode_TASK ,1,"+--- TASK Clear\t" + Device.TASK[ RunNo ].Name );     //Log出力
								TASK_ReStart( TASK_Name_Mood );
								TASK_ForcedExecution( TASK_Name_Wait );		//タスク終了後にWaitを入れる
								TASK_Sort();		//ソート
								ScreenChangeNo( Screen_TASKMonitor );	//スクリーン移動
								SendTASK();	//TASK送信
								Device.isMoodHack = false;	//ハックを解除

							}					
						break;

					case  TASK_Name_Emerg:	
						//もしTPMが指定範囲外であれば　弱すぎる、強すぎる振動であれば
						if(	Device.Sensor.TPM.isActive == true){
							Device.TASK[RunNo].MoodTPMReset();		//TPMの時間をリセット
						}
							Device.TASK[RunNo].MoodCount(20,10);					//適正TPMであれば、加算

							if(Device.TASK[RunNo].MoodTotalCount >=100){
								OutPutLogs(LogCode_TASK ,1,"+--- TASK Clear\t" + Device.TASK[ RunNo ].Name );     //Log出力
								TASK_End(TASK_Name_Emerg);		//タスクの終了後、Nonに格納
								TASK_ForcedExecution( TASK_Name_Wait );		//タスク終了後にWaitを入れる
								TASK_Sort();		//ソート
								ScreenChangeNo( Screen_TASKMonitor );	//スクリーン移動
								SendTASK();	//TASK送信
								Device.isMoodHack = false;	//ハックを解除

							}					
						break;

					/////////////////////////////////////////////////////////////////////////
					case  TASK_Name_Burp:		//げっぷ
					/////////////////////////////////////////////////////////////////////////
							//もしTPMが指定範囲外であれば　弱すぎる、強すぎる振動であれば
							if(	Device.Sensor.TPM.isActive == true){
								Device.TASK[RunNo].MoodTPMReset();		//TPMの時間をリセット
							}
							Device.TASK[RunNo].MoodCount(10,10);					//適正TPMであれば、加算

							if(Device.TASK[RunNo].MoodTotalCount >=100){
								if( Device.TASK[RunNo].isAction == false){
									MP3.setVolume( 30 );
									int SoundNo = random(1,  Device.MP3_FoolderNo[ 5 ] ) +1 ;
									MP3.stop();
									MP3.playFolderTrack( 5 , SoundNo );
									MP3.start();
									Device.TASK[RunNo].isAction 		= true;
									Device.TASK[RunNo].ActionTime_Set 	= millis();	//時間を記録


								}

							}else{
								if( (millis()-Device.TASK[RunNo].ActionTime_Set) <= 3000) {
									Device.TASK[RunNo].isAction = true;
								}else{
									Device.TASK[RunNo].isAction = false;
								}
							}					

							//条件を満たしつつ、再生が終了していたら
							if( (Device.TASK[RunNo].isAction == true)  &&  ((millis()-Device.TASK[RunNo].ActionTime_Set) >= 3000) ){
								OutPutLogs(LogCode_TASK ,1,"+--- TASK Clear\t" + Device.TASK[ RunNo ].Name );     //Log出力
								TASK_End( TASK_Name_Burp );		//終了
								TASK_Sort();		//ソート
//								ScreenChangeNo( Screen_Shit );	//スクリーン移動
								ScreenChangeNo( Screen_TASKMonitor );	//スクリーン移動

								SendTASK();	//TASK送信
								Device.isMoodHack = false;	//ハックを解除
							}

						break;

				}

				////////////////////////////////////////////////////////////
				//指定時間経過した　タイムアウト時の処理
				////////////////////////////////////////////////////////////
				if(Device.TASK[ RunNo ].RunTime_RemainingTime<=0){
					OutPutLogs(LogCode_TASK ,1,"+--- TimeOUT TASK \t" + Device.TASK[ RunNo ].Name );     //Log出力

					////////////////////////////////////////////////////
					//個々のタイムアウト時の処理
					////////////////////////////////////////////////////
					switch (Device.TASK[ RunNo ].Name_No ){
						case  TASK_Name_Burp:
								TASK_ForcedExecution( TASK_Name_Wait );		//タスク終了時にWaitを入れる
								TASK_End(TASK_Name_Burp);		//タスクの終了後、Nonに格納
								TASK_Sort();					//ソート
								break;
						case TASK_Name_Diapers:
								TASK_ForcedExecution( TASK_Name_Wait );		//タスク終了時にWaitを入れる
								TASK_End(TASK_Name_Diapers);	//ReStart
								TASK_Sort();					//ソート

								break;
						case  TASK_Name_Hungry:
								TASK_ForcedExecution( TASK_Name_Wait );		//タスク終了時にWaitを入れる
								TASK_Wait(TASK_Name_Hungry);	//タイムアウト時に指定タスクを待ちタスクに入れる
								break;
						case  TASK_Name_Shit:
								TASK_ForcedExecution( TASK_Name_Wait );		//タスク終了時にWaitを入れる
								TASK_Wait(TASK_Name_Shit);	//タイムアウト時に指定タスクを待ちタスクに入れる
								break;
						case  TASK_Name_Mood:
								TASK_ForcedExecution( TASK_Name_Wait );		//タスク終了時にWaitを入れる
								TASK_Wait(TASK_Name_Mood);	//タイムアウト時に指定タスクを待ちタスクに入れる
								break;
						case  TASK_Name_Sleep:
								TASK_ForcedExecution( TASK_Name_Wait );		//タスク終了時にWaitを入れる
								TASK_Wait(TASK_Name_Sleep);	//タイムアウト時に指定タスクを待ちタスクに入れる
								break;
						case  TASK_Name_Power:
								TASK_ForcedExecution( TASK_Name_Wait );		//タスク終了時にWaitを入れる
								TASK_ReStart(TASK_Name_Emerg);	//ReStart
								break;

						case  TASK_Name_Wait:
								TASK_End(TASK_Name_Wait);		//タスクの終了後、Nonに格納
								TASK_Sort();					//ソート
								break;

						case  TASK_Name_Sleeping:
								TASK_End(TASK_Name_Sleeping);	//タスクの終了後、Nonに格納
								TASK_Sort();					//ソート
								break;


					}
					SendTASK();	//TASK送信

				}
			}			
		}else{
			//何もないとき　寝ている？　タスク待ち状態
			
			SetTapeLEDsLoop(-1);

//			SetTapeLEDs(2 , 255,64,64); //LEDセット 
//			Device.TASK[ RunNo ].SetLED_Loop(new TimeLED(0,1000, Device.LEDs.Color( 64, 0, 0)), new TimeLED(1000,2000, Device.LEDs.Color( 32,  0,  0)) ); 

		}

	}
