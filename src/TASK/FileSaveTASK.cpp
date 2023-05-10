#include "TASK/FileSaveTASK.h"
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FileSaveTASK
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileSaveTASK(void* arg){

 // OutPutLogs(LogCode_Info,2,"--- START TASK FileSaveTASK ---");    //Log出力


	while (1) {

		//前の時間と今の時間が異なるとき、10秒経過したとき　加算
		if( (millis() - Device.TimeFileSaveBack) >=Device.CryIntervalFileSaveTime  ){
			//1秒に1回保存する
			OutPutLogs(LogCode_FILESAVE,0,"--- Save_CryIntervalFile --");    //Log出力
			Save_Interval_File("/Preferences/CryInterval.csv");	//ファイルに保存
			vTaskDelay(100);
			Save_Interval_File("/Preferences/CryInterval_tmp.csv");//ファイルに保存
			Device.TimeFileSaveBack = millis();
		}

		if(Device.OutPutMSG!=""){
			// ファイルを開く
			File file = SD.open(Device.OutPutFileName,FILE_APPEND);//設定ファイルの書き込み
			if (file){
				file.println(Device.OutPutMSG);
				file.close();
				Device.OutPutMSG="";
			}
		}


		vTaskDelay(100);
		
	}

}


