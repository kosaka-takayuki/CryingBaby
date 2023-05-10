#include "File/File_Function.h"
  


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Threshold
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		boolean Load_Threshold_File(){
			OutPutLogs(LogCode_Info,4,"--- Threshold FileOpen --");    //Log出力
			String result[13];

			// ファイルを開く
			File file = SD.open("/Preferences/Threshold.txt");//設定ファイルの読み込み
			if (!file){
				OutPutLogs(LogCode_Error,5,"+-- Failure:Can not open Threshold.txt --");    //Log出力
				return false;
			}else{
				// ファイルの中身をテキストとして読み込む
				int cnt = 0;
				while(file.available()){
					result[cnt] = result[cnt] + char(file.read());
					if (result[cnt].indexOf('\n') != -1) {
						result[cnt] = result[cnt].substring(0, result[cnt].length()-1);
						cnt++;
						if (cnt == 12) {	break;	}
					}
				}
				file.close();
				OutPutLogs(LogCode_Info, 5,"+-- Success --");    //Log出力

				///////////////////////////////////////////////////////////////////////////////
				//データを処理する
				///////////////////////////////////////////////////////////////////////////////
				String Data[20];
				split(result[0],',', Data);				//データスプリット タブ区切りで切る

				Device.Sensor.Battery.Min 		=  Data[0].toInt();
				Device.Sensor.Battery.Max 		=  Data[1].toInt();
				Device.Sensor.Microphone.Min 	=  Data[2].toInt();
				Device.Sensor.Microphone.Max 	=  Data[3].toInt();
				Device.Sensor.Eye.Min 			=  Data[4].toInt();
				Device.Sensor.Eye.Max 			=  Data[5].toInt();
				Device.Sensor.Diapers.Min 		=  Data[6].toInt();
				Device.Sensor.Diapers.Max 		=  Data[7].toInt();
				Device.Sensor.Mouth.Min 		=  Data[8].toInt();
				Device.Sensor.Mouth.Max 		=  Data[9].toInt();
				Device.Sensor.Temperature.Min 	=  Data[10].toInt();
				Device.Sensor.Temperature.Max 	=  Data[11].toInt();
				Device.Sensor.Level.Min 		=  Data[12].toInt();
				Device.Sensor.Level.Max 		=  Data[13].toInt();
				Device.Sensor.TPM.Min 			=  Data[14].toInt();
				Device.Sensor.TPM.Max 			=  Data[15].toInt();
				Device.Sensor.IMU.Min 			=  Data[16].toInt();
				Device.Sensor.IMU.Max 			=  Data[17].toInt();
				Device.Sensor.Position.Min 		=  Data[18].toInt();
				Device.Sensor.Position.Max 		=  Data[19].toInt();

				OutPutLogs(LogCode_Info, 5,"+-- Battery\tMin: " 	+ (String)(Device.Sensor.Battery.Min) 		+"\t Max: "+ (String)(Device.Sensor.Battery.Max) );   		//Log出力
				OutPutLogs(LogCode_Info, 5,"+-- Mic\tMin: " 		+ (String)(Device.Sensor.Microphone.Min) 	+"\t Max: "+ (String)(Device.Sensor.Microphone.Max) );    	//Log出力
				OutPutLogs(LogCode_Info, 5,"+-- Eye\tMin: " 		+ (String)(Device.Sensor.Eye.Min) 			+"\t Max: "+ (String)(Device.Sensor.Eye.Max) );    			//Log出力
				OutPutLogs(LogCode_Info, 5,"+-- Diapers\tMin: " 	+ (String)(Device.Sensor.Diapers.Min) 		+"\t Max: "+ (String)(Device.Sensor.Diapers.Max) );    		//Log出力
				OutPutLogs(LogCode_Info, 5,"+-- Mouth\tMin: " 		+ (String)(Device.Sensor.Mouth.Min) 		+"\t Max: "+ (String)(Device.Sensor.Mouth.Max) );    		//Log出力
				OutPutLogs(LogCode_Info, 5,"+-- Level\tMin: " 		+ (String)(Device.Sensor.Level.Min) 		+"\t Max: "+ (String)(Device.Sensor.Level.Max) );    		//Log出力
				OutPutLogs(LogCode_Info, 5,"+-- TPM\tMin: " 		+ (String)(Device.Sensor.TPM.Min) 			+"\t Max: "+ (String)(Device.Sensor.TPM.Max) );   	 		//Log出力
				OutPutLogs(LogCode_Info, 5,"+-- IMU\tMin: " 		+ (String)(Device.Sensor.IMU.Min) 			+"\t Max: "+ (String)(Device.Sensor.IMU.Max) );    			//Log出力
				OutPutLogs(LogCode_Info, 5,"+-- Position\tMin: " 	+ (String)(Device.Sensor.Position.Min) 		+"\t Max: "+ (String)(Device.Sensor.Position.Max) );    	//Log出力

				return true;
			}
		}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Save_Threshold
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		boolean Save_Threshold_File(){
		OutPutLogs(LogCode_Info,4,"--- Threshold FileOpen --");    //Log出力
			String result[10];
			File file = SD.open("/Preferences/Threshold.txt",FILE_WRITE);//設定ファイルの書き込み

			if (!file){
				OutPutLogs(LogCode_Error,	5,	"+- Threshold File not Open" );    //Log出力
				return false;
			}else{
				OutPutLogs(LogCode_Info,	5,	"+-- Threshold File Open" );    //Log出力
				///////////////////////////////////////////////////
				// 1行出力
				///////////////////////////////////////////////////
				file.print( (int)Device.Sensor.Battery.Min    );	file.print(",");	
				file.print( (int)Device.Sensor.Battery.Max    );	file.print(",");	
				file.print( (int)Device.Sensor.Microphone.Min ); 	file.print(",");
				file.print( (int)Device.Sensor.Microphone.Max ); 	file.print(",");	
				file.print( (int)Device.Sensor.Eye.Min 		  );	file.print(",");
				file.print( (int)Device.Sensor.Eye.Max 		  );	file.print(",");
				file.print( (int)Device.Sensor.Diapers.Min 	  );	file.print(",");
				file.print( (int)Device.Sensor.Diapers.Max 	  );	file.print(",");
				file.print( (int)Device.Sensor.Mouth.Min 	  );	file.print(",");
				file.print( (int)Device.Sensor.Mouth.Max 	  );	file.print(",");
				file.print( (int)Device.Sensor.Temperature.Min);	file.print(",");
				file.print( (int)Device.Sensor.Temperature.Max);	file.print(",");
				file.print( (int)Device.Sensor.Level.Min  	  );	file.print(",");
				file.print( (int)Device.Sensor.Level.Max  	  );	file.print(",");
				file.print( (int)Device.Sensor.TPM.Min 		  );	file.print(",");
				file.print( (int)Device.Sensor.TPM.Max 		  );	file.print(",");
				file.print( (int)Device.Sensor.IMU.Min  	  );	file.print(",");
				file.print( (int)Device.Sensor.IMU.Max  	  );	file.print(",");
				file.print( (int)Device.Sensor.Position.Min   );	file.print(",");
				file.print( (int)Device.Sensor.Position.Max   );	file.print(",");
				file.close();
				return true;
			}
		}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Get_FileSize ファイルサイズの取得
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned long Get_FileSize(String filename){
		unsigned long filesize =-1;
		File file = SD.open(filename);//設定ファイルの読み込み
		if (!file){
		}else{
			filesize = file.size();
			file.close();
		}

		return filesize;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Interval_Check_Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	boolean Load_Interval_Check_Files(){
		OutPutLogs(LogCode_Info, 4,"--- Load_Interval_Check_Files --");    //Log出力

		unsigned long FileSizeMain = Get_FileSize("/Preferences/CryInterval.csv"); 			//ファイルサイズをチェック
		unsigned long FileSizeTEMP = Get_FileSize("/Preferences/CryInterval_tmp.csv"); ;	//ファイルサイズをチェック
		OutPutLogs(LogCode_Info,5,"+-- " + String(FileSizeMain) + " byte \tCryInterval.csv "  );    //Log出力
		OutPutLogs(LogCode_Info,5,"+-- " + String(FileSizeTEMP) + " byte \tCryInterval_tmp.csv "  );    //Log出力

		//異常終了時に設定ファイルが壊れてしまうことがあるので、"CryInterval.csv"と"CryInterval_tmp"を切り分けている
		//２つのファイルサイズを見る。　壊れていると0byeのファイル
		boolean isF = false;
 		if(FileSizeMain == 0){
			OutPutLogs(LogCode_Info,5,"+-- CryInterval.csv  is Broken"  );    //Log出力
			OutPutLogs(LogCode_Info,6,"+-- Load CryInterval_tmp.csv"  );    //Log出力
			isF = Load_Interval_File("/Preferences/CryInterval_tmp.csv");
		}else{
			OutPutLogs(LogCode_Info,5,"+-- CryInterval.csv  is success"  );    //Log出力
			OutPutLogs(LogCode_Info,6,"+-- Load CryInterval.csv"  );    //Log出力
			isF = Load_Interval_File("/Preferences/CryInterval.csv");
		}

		
		return  isF;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CryInterval_FileOpen 単体のファイル読み込みと設定
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	boolean  Load_Interval_File(String filename){
		OutPutLogs(LogCode_Info, 4,"---Interval_FileOpen --");    //Log出力
		//データ初期化
		OutPutLogs(LogCode_Info, 5,"+-- Info Data CLS --");    //Log出力
		Device.TASK[0].Initialize(TASK_Name_Hungry,		"Hungry", 	15, 5, TASK_Status_Count, 	0,	500);	
		Device.TASK[1].Initialize(TASK_Name_Sleep,		"Sleep" , 	20, 5, TASK_Status_Count, 	0,	 10);
		Device.TASK[2].Initialize(TASK_Name_Mood,		"Mood"  , 	15, 5, TASK_Status_Count, 	0,	 10);
		Device.TASK[3].Initialize(TASK_Name_Wait,		"Wait"  , 	25, 5, TASK_Status_Non, 	0,	 30);
		Device.TASK[4].Initialize(TASK_Name_Emerg,		"Emerg"	, 	50, 5, TASK_Status_Non, 	0,	300);	//最後の引数は、タイムアウト秒
		Device.TASK[5].Initialize(TASK_Name_Shit,		"Shit"	, 	15, 10, TASK_Status_Count, 	0,	10);
		Device.TASK[6].Initialize(TASK_Name_Power,		"Power"	, 	20, 10, TASK_Status_Non, 	0,	10);
		Device.TASK[7].Initialize(TASK_Name_Diapers,	"Diapers", 	20, 10, TASK_Status_Non,	0,	10);	//おむつ
		Device.TASK[8].Initialize(TASK_Name_Burp,		"Burp", 	20, 10, TASK_Status_Non,	0,	10);	//ゲップ
		Device.TASK[9].Initialize(TASK_Name_Sleeping,	"Sleeping", 20, 10, TASK_Status_Non,	0,	10);	//眠っている

		//データ初期化
		OutPutLogs(LogCode_Info,5,"+-- Action CLS --");    //Log出力
		String result[20];

		// ファイルを開く
		OutPutLogs(LogCode_Info,5,"+-- Open" +String(filename)  +" --");    //Log出力
		File file = SD.open(filename);//設定ファイルの読み込み
		if (!file){
			OutPutLogs(LogCode_Error,6,"+-- failure --");    //Log出力
			return false;
		}else{
			OutPutLogs(LogCode_Info,6,"+-- success --");    //Log出力
			// ファイルの中身をテキストとして読み込む
			int cnt = 0;
			while(file.available()){
				result[cnt] = result[cnt] + char(file.read());
				if (result[cnt].indexOf('\n') != -1) {
					result[cnt] = result[cnt].substring(0, result[cnt].length()-1);
					cnt++;
					if (cnt == 12) {		break;		}
				}
			}
			file.close();
			int DataMatchCount =0;
			
			//データを処理する
			for(int i=0;i<cnt;i++){
				String Data[20];
				//データスプリット タブ区切りで切る
				split(result[ i ] ,',', Data);




				for(int j=0;j<TASK_Name_End;j++){
					if( Data[0] ==   Device.TASK[ j ].Name ){
						Device.TASK[ j ].IntervalTime  			= Data[1].toInt();   //インターバル時間
						Device.TASK[ j ].ElapsedTime   			= Data[2].toInt();   //経過時間
						Device.TASK[ j ].IntervalTime_Set		= Data[3].toInt();   //インターバル時間　規定値
						Device.TASK[ j ].IntervalTime_Random	= Data[4].toInt();   //インターバル時間　規定値ランダム
						Device.TASK[ j ].RunTime_Elapsed		= Data[5].toInt();   //実行中の経過時間
						Device.TASK[ j ].RunTime_ElapsedOver	= Data[6].toInt();   //実行中の経過時間 あきらめ時間
						Device.TASK[ j ].Status      			= Data[7].toInt();   //状態
						Device.TASK[ j ].Priority      			= Data[8].toInt();   //優先順位

						//残り計算
						Device.TASK[ j ].RemainingTime = Device.TASK[ j ].IntervalTime - Device.TASK[ j ].ElapsedTime;

	


						OutPutLogs(LogCode_Info , 7,"+-- "+
							String(Device.TASK[ j ].Name)        			+ "\t" +                     
							String(Device.TASK[ j ].IntervalTime)        	+ "\t" +                     
							String(Device.TASK[ j ].ElapsedTime)        	+ "\t" +                     
							String(Device.TASK[ j ].IntervalTime_Random)    + "\t" +                     
							String(Device.TASK[ j ].RunTime_Elapsed)        + "\t" +                     
							String(Device.TASK[ j ].ElapsedTime) 			+ "\t" +                     
							String(Device.TASK[ j ].RunTime_ElapsedOver)	+ "\t" + 
							String(GetStatus( Device.TASK[ j ].Status ))	+ "\t" + 
							String(Device.TASK[ j ].Priority )				+ "\t" 
						);


						DataMatchCount++;        //ファイルデータと一致する個数をカウントする　マッチ数		
					}
				}
			}

			boolean isF = false;
			OutPutLogs(LogCode_Info,6,"+-- DataMatch Check " + String(DataMatchCount) + " --");    //Log出力
			if(DataMatchCount ==TASK_Name_End){
				//全てのデータの読み込みに成功
				OutPutLogs(LogCode_Info,6,"+-- DataMatch success --");    //Log出力
				isF =  true;
			}else{
				//データの読み込みに失敗
				OutPutLogs(LogCode_Error,6,"+-- DataMatch failure --");    //Log出力
				isF = false;
			}
			return isF;
		}
	}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Save_yInterval_File
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Save_Interval_File(String filename){
		String result[10];

		// ファイルを開く
		File file = SD.open(filename,FILE_WRITE);//設定ファイルの書き込み

		if (!file){
			OutPutLogs(LogCode_FILESAVE,1,"--- " + filename + " Error");    //Log出力
		}else{
			///////////////////////////////////////////////////
			// 1行目出力
			///////////////////////////////////////////////////
				//https://www.edu.i.hosei.ac.jp/~sigesada/kyouzai/mojicodehenkan.html

				file.print("\x96\xbc\x91\x4f,");																					// Name名前
				file.print("\x8c\xbb\x8d\xdd\x82\xcc\x83\x43\x83\x93\x83\x5e\x81\x5b\x83\x6f\x83\x8b\x83\x5e\x83\x43\x83\x80,");	// IntervalTime 現在のインターバルタイム
				file.print("\x8c\xbb\x8d\xdd\x82\xcc\x8c\x6f\x89\xdf\x8e\x9e\x8a\xd4,");											// ElapsedTime 現在の経過時間

				file.print("\x95\x57\x8f\x80\x82\xcc\x83\x43\x83\x93\x83\x5e\x81\x5b\x83\x6f\x83\x8b\x83\x5e\x83\x43\x83\x80,");	//IntervalTimeSet　標準のインターバルタイム
				file.print("\x95\x57\x8f\x80\x82\xcc\x83\x89\x83\x93\x83\x5f\x83\x80\x8e\x9e\x8a\xd4,");							//RandomTime 標準のランダム時間
				file.print("\x8e\xc0\x8d\x73\x92\x86\x82\xcc\x8c\x6f\x89\xdf\x8e\x9e\x8a\xd4,");									//RunTime_Elapsed	実行中の経過時間
				file.print("\x8e\xc0\x8d\x73\x92\x86\x82\xcc\x83\x5e\x83\x43\x83\x80\x83\x41\x83\x45\x83\x67\x8e\x9e\x8a\xd4,");	//RunTime_Over 　	実行中のタイムアウト時間
				file.print("Status( 0:Count   1:Wait   2:Run   3:Non   4:Suspend ),");												//Status　0:カウント中　1:待ち中				
				file.print("Priority\n");																							//Priority	優先度



			///////////////////////////////////////////////////
			// 2行目以降出力
			///////////////////////////////////////////////////
				 for(int i=0;i<TASK_Name_End;i++){
					file.print(String(Device.TASK[ i ].Name) +",");
					file.print(String(Device.TASK[ i ].IntervalTime) +",");
					file.print(String(Device.TASK[ i ].ElapsedTime) +",");

					file.print(String(Device.TASK[ i ].IntervalTime_Set) +",");
					file.print(String(Device.TASK[ i ].IntervalTime_Random) +",");

					file.print(String(Device.TASK[ i ].RunTime_Elapsed) +",");
					file.print(String(Device.TASK[ i ].RunTime_ElapsedOver) +",");

					file.print(String(Device.TASK[ i ].Status) +",");
					file.print(String(Device.TASK[ i ].Priority) +"\n");
			      }


			file.close();
		}

	}





	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Load_Preferences_File 単体のファイル読み込みと設定
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	boolean  Load_Preferences_File(String filename){

		String result[13];

		OutPutLogs(LogCode_Info, 4,"---Preferences_FileOpen --");    //Log出力

		// ファイルを開く
		OutPutLogs(LogCode_Info,5,"+-- Open" +String(filename)  +" --");    //Log出力
		File file = SD.open(filename);//設定ファイルの読み込み
		if (!file){
			OutPutLogs(LogCode_Error,6,"+-- failure --");    //Log出力
			return false;
		}else{
			OutPutLogs(LogCode_Info,6,"+-- success --");    //Log出力
			// ファイルの中身をテキストとして読み込む
			int cnt = 0;
			while(file.available()){
				result[cnt] = result[cnt] + char(file.read());
				if (result[cnt].indexOf('\n') != -1) {
					result[cnt] = result[cnt].substring(0, result[cnt].length()-1);
					cnt++;
					if (cnt == 12) {		break;		}
				}
			}
			file.close();

			//データを処理する
			for(int i=0;i<cnt;i++){
				String Data[20];
				//データスプリット タブ区切りで切る
				split(result[ i ] ,',', Data);
			
				if( Data[0] =="BabyName" ){		Device.BabyName =Data[1]; 			}
				if( Data[0] =="MP3 Volume" ){	Device.Mp3Volume =Data[1].toInt(); 	}
				if( Data[0] =="M5 Volume" ){	Device.M5Volume =Data[1].toInt();   }
				

			}

			return true;
		}
	}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Save_Preferences_File
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Save_Preferences_File(String filename){
		String result[10];

		// ファイルを開く
		File file = SD.open(filename,FILE_WRITE);//設定ファイルの書き込み

		if (!file){
			OutPutLogs(LogCode_FILESAVE,1,"--- " + filename + " Error");    //Log出力
		}else{
			///////////////////////////////////////////////////
			// 1行目出力
			///////////////////////////////////////////////////
			file.print("BabyName,"   + String(Device.BabyName)  +"\n");
			file.print("MP3 Volume," + String(Device.Mp3Volume) +"\n");																					// Name名前
			file.print("M5 Volume,"  + String(Device.M5Volume)  +"\n");																					// Name名前

			file.close();
		}

	}
