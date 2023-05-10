#include "Device/SystemCheck.h"
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SystemCheck
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SystemCheck(){
    OutPutLogs(LogCode_Info,1,"--- SystemCheck Begin--");    //Log出力

    int _DrawY;

	int _AnimationTime =100;

	/////////////////////////////////////////////////////////////////////////////////////
	//初期値設定
	/////////////////////////////////////////////////////////////////////////////////////
		Device.isCheck.isSDCard 		= false;     //SDカードの有無
		Device.isCheck.isFile_Threshold	= false;     //ファイル読み込みの有無
		Device.isCheck.isFile_Interval 	= false;     //ファイル読み込みの有無
		Device.isCheck.isDFPlayer 		= false;     //DFPlayer接続の有無
		Device.isCheck.isIMU 			= false;     //IMU接続の有無
    
	/////////////////////////////////////////////////////////////////////////////////////
    //画面設定
	/////////////////////////////////////////////////////////////////////////////////////
//			Device.AquesTalk.playK("システムチェック", 50, Device.isAquesTalk);                          //AquesTalkで会話　会話スピードは最低の50


	/////////////////////////////////////////////////////////////////////////////////////
    // 時間経過アニメーション　徐々にフェードイン
	/////////////////////////////////////////////////////////////////////////////////////
			Device.TimeModeChangeElapsed = millis();  //時間初期化
			DrawTitle("System Check", 0, 600, BaseColor_Cyan);

			_DrawY = 40;

	///////////////////////////////////////////////////////////////////////////////
	//DFPlayer
	///////////////////////////////////////////////////////////////////////////////
				OutPutLogs(LogCode_Info,3,"+-- DFPlayer --");    //Log出力

				DrawBox("DFPlayer",_DrawY,_AnimationTime);	//アニメーション付きBOX描写

				//接続トライ
				xTaskCreatePinnedToCore( GetDFPlayer, "GetDFPlayer",   4096, NULL, 1, NULL, 1);
				DrawTimeGauge(170,_DrawY+2, 120, 20-4,  20 , 4000 , 2);

				for(int i=0;i<3;i++){
					Device.MP3_PlayBackNo[i] =-1;
				}

				///////////////////////////////////////////////////////////////////////////////
				// 接続チェック
				///////////////////////////////////////////////////////////////////////////////
				if (Device.isMp3DeviceCheckStatus == 0 && MP3.error_code == 0) {
					//失敗
					Device.isCheck.isDFPlayer= false;
					DrawBoxResult("not stuck", _DrawY, _AnimationTime, false);
					OutPutLogs(LogCode_Error,4,"+-- card is not stuck");    //Log出力
					} else if (Device.isMp3DeviceCheckStatus == 0 &&  MP3.error_code == 129) {
					//失敗
					Device.isCheck.isDFPlayer= false;
					DrawBoxResult("not found", _DrawY, _AnimationTime, false);
					OutPutLogs(LogCode_Error,4,"+-- device not found");    //Log出力
				} else if (Device.isMp3DeviceCheckStatus == 512 && MP3.error_code == 0) {
					//成功
					Device.isCheck.isDFPlayer= true;
					DrawBoxResult("Success", _DrawY, _AnimationTime, true);
					OutPutLogs(LogCode_Info,4,"+-- success ");    //Log出力
				}else{
					//成功
					Device.isCheck.isDFPlayer= true;
					DrawBoxResult("Success", _DrawY, _AnimationTime, true);
					OutPutLogs(LogCode_Info,4,"+-- success");    //Log出力
				}



				///////////////////////////////////////////////////
				//ファイルの中身を確認
				///////////////////////////////////////////////////
				OutPutLogs(LogCode_Info,4,"+-- MP3 File Check --");    //Log出力

				int FCount =  MP3.getTotalFolderCount();
				OutPutLogs(LogCode_Info,5,"+-- MP3 Folder Count " + String(FCount));    //Log出力
					
				for(int i=3;i<11;i++){
					int no =MP3.getFolderTrackCount(i);
					Device.MP3_FoolderNo[ i ] = no;
					OutPutLogs(LogCode_Info,6,"+-- Folder(" + String(i) + ") \t" + NoToMP3FolderString(i) +"\t"+ String(no) +" Files");    //Log出力
				}



	///////////////////////////////////////////////////////////////////////////////
	//　バッテリー
	///////////////////////////////////////////////////////////////////////////////
				_DrawY +=22;
			OutPutLogs(LogCode_Info,3,"+- Battery Check --");    //Log出力

			DrawBox("Battery",_DrawY,_AnimationTime);	//アニメーション付きBOX描写
			GetBattery();  					//バッテリー接続状況チェック
			Device.Battery.GetTime = millis();


			String tmp="";
			if(Device.Battery.isUSB == true){
				tmp =  "USB (" + String((int)Device.Battery.Level) + "%)"; //USB充電中
				DrawBoxResult(  tmp, _DrawY, _AnimationTime, true);
			}else{
				tmp =  "Battery (" + String((int)Device.Battery.Level) + "%)"; //バッテリー起動中
				if( (int)Device.Battery.Level >30){
					DrawBoxResult( tmp, _DrawY, _AnimationTime, true);
				}else{
					DrawBoxResult( tmp, _DrawY, _AnimationTime, true);
				}
			}
			OutPutLogs(LogCode_Info,4,"+-- Level:"+String(Device.Battery.Level)+" %" );    //Log出力
			OutPutLogs(LogCode_Info,4,"+-- Voltl:"+String(Device.Battery.Volt) +" V");         //Log出力


	///////////////////////////////////////////////////////////////////////////////
	//SD CARD
	///////////////////////////////////////////////////////////////////////////////
			_DrawY +=22;
			OutPutLogs(LogCode_Info,3,"+- SD CARD Check --");    //Log出力

			DrawBox("SD Card",_DrawY,_AnimationTime);	//アニメーション付きBOX描写

			sdcard_type_t Type = SD.cardType();
			if( Type == CARD_UNKNOWN || Type == CARD_NONE ){
				//ファイル読み込み失敗
				Device.isCheck.isSDCard = false;            //SDカードの有無
				DrawBoxResult("Not Stuck", _DrawY, _AnimationTime, false);
				OutPutLogs(LogCode_Error,4,"+-- SD CARD not stuck" );    //Log出力
			}else{
				//ファイル読み込み成功
				Device.isCheck.isSDCard = true;            //SDカードの有無
				DrawBoxResult("Success", _DrawY, _AnimationTime, true);
				OutPutLogs(LogCode_Info,4,"+-- SD CARD success" );    //Log出力
			}


	///////////////////////////////////////////////////////////////////////////////
	//LoadThreshold File
	///////////////////////////////////////////////////////////////////////////////
			_DrawY +=22;
			OutPutLogs(LogCode_Info,3,"+-- Load_Threshold File --");    //Log出力
			DrawBox("Threshold File",_DrawY,_AnimationTime);	//アニメーション付きBOX描写
			////////////////////////////////////////////////
			//ファイル読み込み
			////////////////////////////////////////////////
			if( Load_Threshold_File() == true){
				//ファイル読み込み成功
				Device.isCheck.isFile_Threshold =true;
				DrawBoxResult("Success", _DrawY,_AnimationTime, true);
			}else{
				//ファイル読み込み失敗
				Device.isCheck.isFile_Threshold =false;
				DrawBoxResult("Failure", _DrawY, _AnimationTime, false);
			}


	///////////////////////////////////////////////////////////////////////////////
	//Interval_File
	///////////////////////////////////////////////////////////////////////////////
       	 _DrawY +=22;
        	OutPutLogs(LogCode_Info,2,"--- Load_Interval_File --");    //Log出力
			DrawBox("Interval File",_DrawY,_AnimationTime);	//アニメーション付きBOX描写
			////////////////////////////////////////////////
			//ファイル読み込み
			////////////////////////////////////////////////
        	if( Load_Interval_Check_Files() == true){
            	//ファイル読み込み成功
            	Device.isCheck.isFile_Interval = true;            //SDカードの有無
				DrawBoxResult("Success", _DrawY,_AnimationTime, true);

       		}else{
            	//ファイル読み込み失敗
            	Device.isCheck.isFile_Interval = false;            //SDカードの有無
				DrawBoxResult("Failure", _DrawY, _AnimationTime, false);
        }
		TASK_Sort();		//ソート
		

	///////////////////////////////////////////////////////////////////////////////
	//Load_Preferences_File
	//設定ファイル　ボリュームなど
	//重要な設定ファイルではないため、ファイルが読み込めなくても問題なく起動させる。
	///////////////////////////////////////////////////////////////////////////////
       	 _DrawY +=22;
        	OutPutLogs(LogCode_Info,2,"--- Load_Preferences_File --");    //Log出力
			DrawBox("Preferences File",_DrawY,_AnimationTime);	//アニメーション付きBOX描写
			////////////////////////////////////////////////
			//ファイル読み込み
			////////////////////////////////////////////////
        	if( Load_Preferences_File("/Preferences/Preferences.txt") == true){
            	//ファイル読み込み成功
				DrawBoxResult("Success", _DrawY,_AnimationTime, true);
				Device.AquesTalk.SetVolume(Device.M5Volume);
      		}else{
            	//ファイル読み込み失敗
				DrawBoxResult("Failure", _DrawY, _AnimationTime, false);
        }


	///////////////////////////////////////////////////////////////////////////////
	//IMU
	///////////////////////////////////////////////////////////////////////////////
		_DrawY +=22;
		OutPutLogs(LogCode_Info,3,"+-- IMU Device --");    //Log出力
		DrawBox("IMU",_DrawY,_AnimationTime);	//アニメーション付きBOX描写

        if( M5.IMU.Init() == 0 ){
            //成功
			Device.isCheck.isIMU= true;
			DrawBoxResult("Success", _DrawY, _AnimationTime, true);
			OutPutLogs(LogCode_Info, 4,"+-- IMU Device success --");    //Log出力
        }else{
			//失敗
			Device.isCheck.isIMU= false;
			DrawBoxResult("failure", _DrawY, _AnimationTime, false);
			OutPutLogs(LogCode_Error, 4, "+-- IMU Device failure --");    //Log出力
        }


	///////////////////////////////////////////////////////////////////////////////
	//RTC Date
	///////////////////////////////////////////////////////////////////////////////
		_DrawY +=22;
		OutPutLogs(LogCode_Info,3,"+-- RTC --" );    //Log出力
		DrawBox("RTC Date",_DrawY,_AnimationTime);	//アニメーション付きBOX描写

		// Get RTC time
		RTC_TimeTypeDef TimeStruct;
		RTC_DateTypeDef DateStruct;
		M5.Rtc.GetDate(&DateStruct);
		M5.Rtc.GetTime(&TimeStruct);

		OutPutLogs(LogCode_Info,4,"+-- Date:\t" + String(DateStruct.Year) +"/" + String(DateStruct.Month) +"/" + String(DateStruct.Date) +" "+ String(TimeStruct.Hours) +":" + String(TimeStruct.Minutes) +":" + String(TimeStruct.Seconds) );    //Log出力

		char tmpS[40];
		sprintf(tmpS, "/logs/%04u_%02u_%02u.txt", DateStruct.Year, DateStruct.Month, DateStruct.Date );

		Device.OutPutFileName = String(  tmpS  );
		OutPutLogs(LogCode_Info,4,"+-- FileName:\t" + Device.OutPutFileName );    //Log出力

		DrawBoxResult(String(DateStruct.Year) +"/" + String(DateStruct.Month) +"/" + String(DateStruct.Date), _DrawY, _AnimationTime,true);

	///////////////////////////////////////////////////////////////////////////////
	//RTC Time
	///////////////////////////////////////////////////////////////////////////////
		_DrawY +=22;
		DrawBox("RTC Time",_DrawY,_AnimationTime);	//アニメーション付きBOX描写
		DrawBoxResult(String(TimeStruct.Hours) +":" + String(TimeStruct.Minutes) +":" + String(TimeStruct.Seconds), _DrawY, _AnimationTime, true);


	///////////////////////////////////////////////////////////////////////////////
    // 最終エラーチェック起動チェック可能か？
	///////////////////////////////////////////////////////////////////////////////
		OutPutLogs(LogCode_Info, 2,"\n");    //Log出力
		OutPutLogs(LogCode_Info, 2,"---------------------------------------------");    //Log出力
		OutPutLogs(LogCode_Info, 2,"--- Total Error Check --");    //Log出力
		OutPutLogs(LogCode_Info, 2,"---------------------------------------------");    //Log出力


		OutPutLogs(LogCode_Info, 3,"+--       DFPlayer:" + String(Device.isCheck.isDFPlayer));   	 	//Log出力
		OutPutLogs(LogCode_Info, 3,"+--        SD Card:" + String(Device.isCheck.isSDCard));    		//Log出力
		OutPutLogs(LogCode_Info, 3,"+-- File Threshold:" + String(Device.isCheck.isFile_Threshold));    //Log出力
		OutPutLogs(LogCode_Info, 3,"+--            IMU:" + String(Device.isCheck.isIMU));    		 	//Log出力


		/////////////////////////////////////////////////////////////////////////////
		//ファイル保存
		/////////////////////////////////////////////////////////////////////////////
		SaveLogs();
		delay(100);

		if( Device.isCheck.isDFPlayer       == true &&  //SDFPlayer接続の有無
			Device.isCheck.isSDCard   		== true &&  //Dカードの有無 
			Device.isCheck.isFile_Threshold == true &&  //ファイル読み込みの有無
			Device.isCheck.isFile_Interval 	== true &&  //ファイル読み込みの有無
			Device.isCheck.isIMU            == true     //IMU接続の有無
		){
			///////////////////////////////////////////////////////////////////////////////
			// 問題ないとき
			///////////////////////////////////////////////////////////////////////////////
			Device.isCheck.isDeviceClear = true;
			OutPutLogs(LogCode_Info, 3,"+-- Total Error Check: success --\n");    //Log出力
			SetTapeLEDs(64 , 255,0,0); //LEDセット 

			Device.AquesTalk.playK("起動します", 50, Device.isAquesTalk);                          //AquesTalkで会話　会話スピードは最低の50
//			Device.AquesTalk.playK("なにぬねの まみむめも", 50, Device.isAquesTalk);                          //AquesTalkで会話　会話スピードは最低の50

        }else{
			Device.ScreenNo = -1;
			

		}
		OutPutLogs(LogCode_Info,1,"--- SystemCheck End---\n");    //Log出力

}
