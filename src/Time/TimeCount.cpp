#include "Time/TimeCount.h"

    ///////////////////////////////////////////////////////////////////////////
    // TimeCount 
    ///////////////////////////////////////////////////////////////////////////
	void TimeCount(float _speed){

		/////////////////////////////////////////
		//時間計算
		/////////////////////////////////////////
		/*
				float CountValue =1000;  	//再生速度  x1  リアルタイム
					  CountValue = 500;  	//再生速度  x2  2倍速
					  CountValue = 250;  	//再生速度  x4  4倍速
					  CountValue = 100;  	//再生速度 x10 10倍速
			
		*/
		float	CountValue  =  1000.0f / _speed;	//時間再生速度設定

		//前の時間と今の時間が異なるとき、CountValue秒経過したとき　加算
		if( (millis() - Device.TimeCountTASKBack) >= CountValue  ){
			for(int i=0;i<TASK_Name_End;i++){
				//カウント中かどうか判断  0:TASK_Status_Count
				if( Device.TASK[ i ].Status  ==  TASK_Status_Count){	
					//時間カウントするときのみ実行
					Device.TASK[ i ].ElapsedTime  	+= 1;  //時間加算
					Device.TASK[ i ].RemainingTime 	=  Device.TASK[ i ].IntervalTime  - Device.TASK[ i ].ElapsedTime;  //残り時間計算 秒
					Device.TASK[ i ].ElapsedTime_OLD =-1;

					//残り時間が0以下になったら
					if( Device.TASK[ i ].RemainingTime <=0 ){
						// ステータスがCountの時だけ実行
						if(Device.TASK[ i ].Status == TASK_Status_Count ){
							//通常タスクの場合
							Device.TASK[ i ].Status  				= TASK_Status_Wait;   //アクティブに設定
	
							//優先順位を設定 優先度の一番高い番号を検出
							int MaxPriority = 0;
							for(int j=0;j<TASK_Name_End;j++){
								if(Device.TASK[ j ].Priority  > MaxPriority ){
									MaxPriority = Device.TASK[ j ].Priority;
								}
							}
							//Serial.println("MaxMaxPriority:" + String(MaxPriority));
							Device.TASK[ i ].Priority = MaxPriority+1;

							TASK_Sort( );
						}
					}
				}
			}
			Device.TimeCountTASKBack = millis();
		}
  	}
