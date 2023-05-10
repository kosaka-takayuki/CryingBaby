#include "CryTASK/CryTASK_Function.h"

	//////////////////////////////////////////////////////////////
	//TASK_Sort
	//タスクのソート
	//////////////////////////////////////////////////////////////
	void TASK_Sort( ){

//		OutPutLogs(LogCode_Info,6,"**** TASK Sort ****"  );    //Log出力
//		for(int i=0;i<TASK_Name_End;i++){	
//			Serial.println( "B:"+ String(i) + "\t" + Device.TASK[i].Name );
//		}
		CryTASK TMP[TASK_Name_End];
		CryTASK tmp;

		//データのコピー
		for(int i=0;i<TASK_Name_End;i++){			TMP[i] = Device.TASK[i];		}

		///////////////////////////////////////////////////////////
		//通常ソート RemainingTime　残り時間
		///////////////////////////////////////////////////////////
		for (int i = 0; i < TASK_Name_End; i++){
			for (int j = i + 1; j < TASK_Name_End; j++){
				if ( TMP[i].RemainingTime > TMP[j].RemainingTime){
					tmp = TMP[i];
					TMP[ i ] = TMP[ j ];
					TMP[ j ] = tmp;
				}
			}
		}

		///////////////////////////////////////////////////////////
		//通常ソート 優先度でソート
		///////////////////////////////////////////////////////////
		for (int i = 0; i < TASK_Name_End; i++){
			for (int j = i + 1; j < TASK_Name_End; j++){
				if (TMP[ i ].Priority > TMP[ j ].Priority){
					tmp = TMP[ i ];
					TMP[ i ] = TMP[ j ];
					TMP[ j ] = tmp;
				}
			}
		}
		///////////////////////////////////////////////////////////
		//プライオリティの正規化　 
		//優先順位は1,2,3,4,5をする
		//優先順位は1,5,6,7,10はダメ
		///////////////////////////////////////////////////////////
		int P_count =1;
		for(int i=0;i<TASK_Name_End;i++){
			if(TMP[i].Status == TASK_Status_Run || TMP[i].Status == TASK_Status_Wait){
				TMP[i].Priority = P_count;
				P_count++;
			}
		}

		///////////////////////////////////////////////////////////
		//プライオリティ1の実行設定　 
		///////////////////////////////////////////////////////////
		for(int i=0;i<TASK_Name_End;i++){
			if(TMP[i].Priority ==1 ){
				if(TMP[i].Status != TASK_Status_Run){
//					Serial.println("*** *** ***TimeSET: " +Device.TASK[ i ].Name );
					TMP[i].Status = TASK_Status_Run;
				}
			}
		}

		///////////////////////////////////////////////////////////
		//元に戻す
		///////////////////////////////////////////////////////////
		for(int i=0;i<TASK_Name_End;i++){
			Device.TASK[i] = TMP[i];
		}


		///////////////////////////////////////////////////////////////
		// statusの数を数えるt
		///////////////////////////////////////////////////////////////
			for(int i=0;i<TASK_Name_End;i++){
				Device.TASK_Title[i].TASK_Count =0; 
			}
			//加算する
			for(int i=0;i<TASK_Name_End;i++){
				if( Device.TASK[i].Status == TASK_Status_Run	){	Device.TASK_Title[TASK_Status_Run   ].TASK_Count++;		}
				if( Device.TASK[i].Status == TASK_Status_Wait 	){  Device.TASK_Title[TASK_Status_Wait  ].TASK_Count++;		}
				if( Device.TASK[i].Status == TASK_Status_Count 	){	Device.TASK_Title[TASK_Status_Count ].TASK_Count++;		}
				if( Device.TASK[i].Status == TASK_Status_Non 	){	Device.TASK_Title[TASK_Status_Non   ].TASK_Count++;		}
			}

			//比較する
			for(int i=0;i<TASK_Name_End;i++){
				if( Device.TASK_Title[ i ].TASK_Count > 0){
					Device.TASK_Title[ i ].isEnable = true;
				}else{
					Device.TASK_Title[ i ].isEnable = false;
					Device.TASK_Title[ i ].DrawY_OLD = -1;
				}
			}



		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//　Y軸計算 一度、全ての縦の順番を計算して、各項目のY軸値を取得しておく
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			SendTASK_Sort();	//TASKの送信と座標計算

	}


	//////////////////////////////////////////////////////////////
	//GetTASK_Status
	//ステータスとプライオリティ変更
	//////////////////////////////////////////////////////////////
	int GetTASK_Status(int _no){
		for(int i=0;i<TASK_Name_End;i++){
			if(Device.TASK[i].Name_No == _no ){
				return  Device.TASK[i].Status;
			} 
		}
		return  -1;
	}



	int GetTASK_RunTASK_No(){
		int _no =-1;
		for(int i=0;i<TASK_Name_End;i++){
			if(Device.TASK[i].Status == TASK_Status_Run ){
				_no = i;
			}
		}
		return _no;
	}

	//////////////////////////////////////////////////////////////
	//SetTASK_Status_Priority
	//ステータスとプライオリティ変更
	//////////////////////////////////////////////////////////////
	void SetTASK_Status_Priority(int _no, int _status, int _priority, boolean _isrun){

		//モータを停止
		Device.Motor[Motor_Main  ].SetSpeed( Motor_STOP);	//モータセット
		Device.Motor[Motor_ValveA].SetSpeed( Motor_STOP);	//モータセット
		Device.Motor[Motor_ValveB].SetSpeed( Motor_STOP);	//モータセット

		for(int i=0;i<TASK_Name_End;i++){
			if(Device.TASK[i].Name_No == _no ){

//					Serial.println("*** *** SetTASK_Status_Priority: " +Device.TASK[ i ].Name );
//					Serial.println("*** *** irRun : " + (String)Device.TASK[ i ].isRun);

					Device.TASK[i].Status	= 	_status;
					Device.TASK[i].Priority	=	_priority;
					Device.TASK[i].isFirtstTime	=	_isrun;

//						OutPutLogs(LogCode_TASK ,0,"BB false");     //Log出力

				
					

					if(_status ==TASK_Status_Run ){
						//Device.TASK[i].RunTime_Start = millis();
						Device.TASK[i].ElapsedTime  	= 0;	//経過時間


					}
	
					//タスク終了処理の時のみ実行
					if( Device.TASK[i].Name_No == TASK_Name_Emerg &&  _isrun==false){
//						Serial.println("*END TASK**********" );
						Device.Sensor.IMU.isRun 	 	=false;
						Device.Sensor.Position.isRun 	=false;
						Device.Sensor.Temperature.isRun	=false;
						Device.Sensor.Eye.isRun 		=false;
						Device.Sensor.Microphone.isRun 	=false;
					}

			} 
		}
	}

	//////////////////////////////////////////////////////////////
	//SetTASK_Status_Procedure
	//ステータスとプライオリティ変更
	//////////////////////////////////////////////////////////////
	void SetTASK_Status_Procedure(int _no , int _procedure_no, int _procedure){
		for(int i=0;i<TASK_Name_End;i++){
			if(Device.TASK[i].Name_No == _no ){
					Device.TASK[i].Procedure[_procedure_no]	= _procedure;

			} 
		}
	}





	//////////////////////////////////////////////////////////////
	//SetTASK_Status_SET
	//ステータス変更
	/*
					file.print(String(Device.TASK[ i ].Name) +",");
					file.print(String(Device.TASK[ i ].IntervalTime) +",");
					file.print(String(Device.TASK[ i ].ElapsedTime) +",");
					file.print(String(Device.TASK[ i ].IntervalTime_Random) +",");

					file.print(String(Device.TASK[ i ].RunTime_Elapsed) +",");
					file.print(String(Device.TASK[ i ].RunTime_ElapsedOver) +",");

					file.print(String(Device.TASK[ i ].Status) +",");
					file.print(String(Device.TASK[ i ].Priority) +"\n");

	*/
	//////////////////////////////////////////////////////////////
	void SetTASK_SET(int _no , int _IntervalTime,	int _ElapsedTime,	int _IntervalTime_Set, int _IntervalTime_Random, int _RunTime_Elapsed, int _RunTime_ElapsedOver, int _Status, int _Priority){
		for(int i=0;i<TASK_Name_End;i++){
			if(Device.TASK[i].Name_No == _no ){
					Device.TASK[i].IntervalTime 		= _IntervalTime;
					Device.TASK[i].ElapsedTime 			= _ElapsedTime;

					Device.TASK[i].IntervalTime_Set 	= _IntervalTime_Set;
					Device.TASK[i].IntervalTime_Random 	= _IntervalTime_Random;

					Device.TASK[i].RunTime_Elapsed 		= _RunTime_Elapsed;
					Device.TASK[i].RunTime_ElapsedOver 	= _RunTime_ElapsedOver;
					Device.TASK[i].Status 				= _Status;
					Device.TASK[i].Priority 			= _Priority;


//					Serial.print("Set:\t"+Device.TASK[i].Name +"\t"   );
//					Serial.println(Device.TASK[i].Priority  );

			} 
		}
	}	

	//////////////////////////////////////////////////////////////
	//GetNo_TASK_Mood
	//指定のTASKの配列番号を求める
	//////////////////////////////////////////////////////////////
	int GetNo_TASK_Mood(int _no ){
		for(int i=0;i<TASK_Name_End;i++){
			if(Device.TASK[i].Name_No == _no ){
				return i;			
			} 
		}
		return -1;			
	}


	//////////////////////////////////////////////////////////////
	//TASK_MoodReset
	//実行中の場合は、機嫌のみリセット
	//////////////////////////////////////////////////////////////
	void TASK_MoodReset( int _no ){
		///////////////////////////////////////////////////////////////////////////////////
		//機嫌設定　初期値に変更
		///////////////////////////////////////////////////////////////////////////////////
		for(int i=0;i<TASK_Name_End;i++){
			
			if(Device.TASK[i].Name_No == _no ){
				Device.TASK[i].MoodReset();		//機嫌のリセット
			}
		}
	}





	//////////////////////////////////////////////////////////////
	//TASK_ForcedExecution
	//強制実行　スタート _noを強制実行
	//////////////////////////////////////////////////////////////
	void TASK_ForcedExecution( int _no ){

		OutPutLogs(LogCode_TASK,0, "TASK Execution:" + NoToTaskStrings( _no )  );     //Log出力

		MP3.stop();

		//Wait　と Emergを強制停止
		SetTASK_Status_Priority(TASK_Name_Wait 	, TASK_Status_Non , -1, false);		//Wait が実行中に関わらず停止、優先度を-1に設定
		SetTASK_Status_Priority(TASK_Name_Emerg , TASK_Status_Non , -1, false);		//Emergが実行中に関わらず停止、優先度を-1に設定

		//データ正規化
		for(int i=0;i<TASK_Name_End;i++){	
			//もし既に、TASK_Status_RUNのタスクがいたら、Waitに設定
			if(Device.TASK[i].Status == TASK_Status_Run){
				Device.TASK[i].Status  = TASK_Status_Wait;
			}
			//優先度インクリメント　正規化は、ソートで行う
			if(Device.TASK[i].Status == TASK_Status_Run || Device.TASK[i].Status == TASK_Status_Wait){
				Device.TASK[i].Priority++;
			}
		}

//		Device.Sensor.IMU.isRun= false;
//Serial.println("TASK_ForcedExecution C");

		SetTASK_Status_Priority(_no 	, TASK_Status_Run , 1, true);		//_noを実行、優先度を1に設定

		


		///////////////////////////////////////////////////////////////////////////////////
		//機嫌設定　初期値に変更
		///////////////////////////////////////////////////////////////////////////////////
		for(int i=0;i<TASK_Name_End;i++){
			
			if(Device.TASK[i].Name_No == _no ){
				Device.TASK[i].MoodReset();		//機嫌のリセット
			}
		}




//		TASK_Sort( );		//データソートおよび正規化
	}


	//////////////////////////////////////////////////////////////
	//TASK_End
	//TASK リスタート　指定したTASKの再起動
	//////////////////////////////////////////////////////////////
	void TASK_End( int _no ){
		MP3.stop();

//Serial.println("TASK_END");
		
		//モータを停止
	Device.Motor[	Motor_Main  			].SetSpeed( Motor_STOP);	//モータセット
		Device.Motor[	Motor_ValveA		].SetSpeed( Motor_STOP);	//モータセット
		Device.Motor[	Motor_ValveB		].SetSpeed( Motor_STOP);	//モータセット
		Device.Motor[	Motor_Ink_Red		].SetSpeed( Motor_STOP);	//モータセット
		Device.Motor[	Motor_Ink_Yellow	].SetSpeed( Motor_STOP);	//モータセット


		SetTASK_Status_Priority( _no, TASK_Status_Non , -1, false);		//Wait が実行中に関わらず停止、優先度を-1に設定
		TASK_Sort();		//ソート


	}

	//////////////////////////////////////////////////////////////
	//TASK_Wait
	//TASK_Wait 指定したTASKをWaitに加える
	//////////////////////////////////////////////////////////////
	void TASK_Wait( int _no ){
		//モータを停止
		Device.Motor[Motor_Main  ].SetSpeed( Motor_STOP);	//モータセット
		Device.Motor[Motor_ValveA].SetSpeed( Motor_STOP);	//モータセット
		Device.Motor[Motor_ValveB].SetSpeed( Motor_STOP);	//モータセット
		Device.Motor[Motor_Ink_Red].SetSpeed( Motor_STOP);	//モータセット
		Device.Motor[Motor_Ink_Yellow].SetSpeed( Motor_STOP);	//モータセット


		Serial.println("\tWait START-------------------------");
			for(int i=0;i<TASK_Name_End;i++){
				if(Device.TASK[i].Name_No == _no ){

							//通常タスクの場合
							Device.TASK[ i ].Status  				= TASK_Status_Wait;   //アクティブに設定
							Device.TASK[ i ].isFirtstTime 			= true;

							//優先順位を設定 優先度の一番高い番号を検出
							int MaxPriority = 0;
							for(int j=0;j<TASK_Name_End;j++){
								if(Device.TASK[ j ].Priority  > MaxPriority ){
									MaxPriority = Device.TASK[ j ].Priority;
								}
							}
							//Serial.println("MaxMaxPriority:" + String(MaxPriority));
							Device.TASK[ i ].Priority = MaxPriority+1;
							TASK_Sort( );		//データソートおよび正規化

				} 
			}


	}




	//////////////////////////////////////////////////////////////
	//TASK_ReStart
	//TASK リスタート　指定したTASKの再起動
	//////////////////////////////////////////////////////////////
	void TASK_ReStart( int _no ){


		Serial.println("\tReStart START-------------------------");


		//モータを停止
		Device.Motor[Motor_Main  ].SetSpeed( Motor_STOP);	//モータセット
		Device.Motor[Motor_ValveA].SetSpeed( Motor_STOP);	//モータセット
		Device.Motor[Motor_ValveB].SetSpeed( Motor_STOP);	//モータセット
		Device.Motor[Motor_Ink_Red].SetSpeed( Motor_STOP);	//モータセット
		Device.Motor[Motor_Ink_Yellow].SetSpeed( Motor_STOP);	//モータセット
		
		
			for(int i=0;i<TASK_Name_End;i++){
				if(Device.TASK[i].Name_No == _no ){
						Device.TASK[i].Status	= 	TASK_Status_Count;
						Device.TASK[i].Priority	=	-1;
						int R = random(-1*Device.TASK[i].IntervalTime_Random,Device.TASK[i].IntervalTime_Random) ;
						Device.TASK[i].IntervalTime 	= Device.TASK[i].IntervalTime_Set +  (unsigned long )R ;
						Device.TASK[i].ElapsedTime  	= 0;	//経過時間
						Device.TASK[i].RemainingTime  	= Device.TASK[i].IntervalTime;	//残り時間
						Device.TASK[i].isFirtstTime		= false;

//						OutPutLogs(LogCode_TASK ,0,"B false");     //Log出力
	

//						Serial.println("\t" + Device.TASK[i].Name);
//						Serial.println("\t" + String(Device.TASK[i].Priority));
//						Serial.println("\t" + String(Device.TASK[i].IntervalTime));


				} 
			}
			TASK_Sort( );		//データソートおよび正規化
	}


	//////////////////////////////////////////////////////////////
	//TASK_Run
	//タスクの実行
	//////////////////////////////////////////////////////////////
	void TASK_Run( ){
		int RunNo =-1;
		//ステータスが実行中のタスクを検索
		for(int i=0;i<TASK_Name_End;i++){
			if(Device.TASK[i].Status == TASK_Status_Run){
				RunNo = i;
			}

		}

		if(RunNo != -1){

			switch (Device.TASK[ RunNo].Name_No ){
				case  TASK_Name_Wait:
					Serial.println(" WAIT RUN ");
					break;
			
			}
		}
	}


	//////////////////////////////////////////////////////////////
	//SendTASK_Sort
	//TASKの送信と座標計算
	//////////////////////////////////////////////////////////////
	void SendTASK_Sort( ){

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//　Y軸計算 一度、全ての縦の順番を計算して、各項目のY軸値を取得しておく
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			Device.TaskSendMSG ="Task,"; 	
			int  _DrawY =40;

			////////////////////////////////////
			// 実行中のタイトル
			////////////////////////////////////
			if( Device.TASK_Title[  TASK_Status_Run  ].isEnable == true){		//もし実行中のタスクがある場合のみ表示
				Device.TASK_Title[  TASK_Status_Run  ].DrawY =_DrawY;
				_DrawY +=TASK_H_MSG;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//　タスク枠表示　実行中のタスクを描写
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			for(int i=0;i<TASK_Name_End;i++){
				if( Device.TASK[i].Status == TASK_Status_Run){
					Device.TASK[i].DrawY =  _DrawY;
					_DrawY+=TASK_H_Exe;

					Device.TaskSendMSG += Device.TASK[i].Name;
					Device.TaskSendMSG += ",";
					Device.TaskSendMSG += Device.TASK[i].Status;
					Device.TaskSendMSG += ",";
					Device.TaskSendMSG += Device.TASK[i].Priority;
					Device.TaskSendMSG += ",";


				}
			}
			//////////////////////////////////////////////
			//　待機中のタイトル
			//////////////////////////////////////////////
			if( Device.TASK_Title[  TASK_Status_Wait  ].isEnable == true){		//もし実行中のタスクがある場合のみ表示
				Device.TASK_Title[  TASK_Status_Wait  ].DrawY =_DrawY;
				_DrawY +=TASK_H_MSG;
			}
			///////////////////////////////////////////////////////////////
			// 　タスク枠表示　Wait
			///////////////////////////////////////////////////////////////
			for(int i=0;i<TASK_Name_End;i++){
				if( Device.TASK[i].Status == TASK_Status_Wait ){
					Device.TASK[i].isDraw = true;
					Device.TASK[i].DrawY =  _DrawY;
					_DrawY+=TASK_H_Wait;

					Device.TaskSendMSG += Device.TASK[i].Name;
					Device.TaskSendMSG += ",";
					Device.TaskSendMSG += Device.TASK[i].Status;
					Device.TaskSendMSG += ",";
					Device.TaskSendMSG += Device.TASK[i].Priority;
					Device.TaskSendMSG += ",";

				}
			}
			//////////////////////////////////////////////
			//　カウント中のタイトル
			//////////////////////////////////////////////
			if( Device.TASK_Title[  TASK_Status_Count  ].isEnable == true){		//もし実行中のタスクがある場合のみ表示
				Device.TASK_Title[  TASK_Status_Count  ].DrawY =_DrawY;
				_DrawY +=TASK_H_MSG;
			}
			///////////////////////////////////////////////////////////////
			// 　タスク枠表示　Wait
			///////////////////////////////////////////////////////////////
			for(int i=0;i<TASK_Name_End;i++){
				if( Device.TASK[i].Status == TASK_Status_Count ){
					Device.TASK[i].DrawY =  _DrawY;
					_DrawY+=TASK_H_Count;

					Device.TaskSendMSG += Device.TASK[i].Name;
					Device.TaskSendMSG += ",";
					Device.TaskSendMSG += Device.TASK[i].Status;
					Device.TaskSendMSG += ",";
					Device.TaskSendMSG += Device.TASK[i].Priority;
					Device.TaskSendMSG += ",";
				}
			}

			//////////////////////////////////////////////
			//　非実行のタイトル
			//////////////////////////////////////////////
			if( Device.TASK_Title[  TASK_Status_Non ].isEnable == true){		//もし実行中のタスクがある場合のみ表示
				Device.TASK_Title[  TASK_Status_Non  ].DrawY =_DrawY;
				_DrawY +=TASK_H_MSG;
			}
			///////////////////////////////////////////////////////////////
			// 　タスク枠表示　非実行
			///////////////////////////////////////////////////////////////
			for(int i=0;i<TASK_Name_End;i++){
				if( Device.TASK[i].Status == TASK_Status_Non ){
					Device.TASK[i].isDraw = true;
					Device.TASK[i].DrawY =  _DrawY;
					_DrawY+=TASK_H_Non;

					Device.TaskSendMSG += Device.TASK[i].Name;
					Device.TaskSendMSG += ",";
					Device.TaskSendMSG += Device.TASK[i].Status;
					Device.TaskSendMSG += ",";
					Device.TaskSendMSG += Device.TASK[i].Priority;
					Device.TaskSendMSG += ",";
				}
			}
	}




//////////////////////////////////////////////////////////////
	//GetStatus_Name
	//ステータスの状態を表示する
	//////////////////////////////////////////////////////////////
	String GetStatus_Name(int _no){
		String msg="";
		switch (_no){
			case TASK_Status_Count:			msg ="Count";		break;
			case TASK_Status_Wait:			msg ="Wait";		break;
			case TASK_Status_Run:			msg ="Run";			break;
			case TASK_Status_Non:			msg ="Non";			break;
			case TASK_Status_RunSuspend:	msg ="Suspend";		break;
		}
		return msg;
	}
