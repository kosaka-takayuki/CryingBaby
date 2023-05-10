#include "Global/Function.h"


    ///////////////////////////////////////////////////////////////////////////
    // maps 
    ///////////////////////////////////////////////////////////////////////////
    long maps(long x, long in_min, long in_max, long out_min, long out_max) {

		if(in_min != in_max){
			if( ((x - in_min) * (out_max - out_min))!=0 &&  ((in_max - in_min) + out_min)!=0){

				long tmp =(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
				if(x  <= in_min) {  tmp = out_min;}
				if(x  >= in_max) {  tmp = out_max;}
				return tmp;
			}else{
				long tmp =0;
				if(x  <= in_min) {  tmp = out_min;}
				if(x  >= in_max) {  tmp = out_max;}
				return tmp;

			}
		}else{
				return out_min;
		}
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// OutPutLogs
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void OutPutLogs(int _code ,int _tabLevel, String _msg){

		String Code="";
		switch(_code){
			case LogCode_Info:		Code ="[I]:";	break;
			case LogCode_Error:		Code ="[EE]:";	break;
			case LogCode_Command:	Code ="[C]:";	break;
			case LogCode_Action:	Code ="[A]:";	break;
			case LogCode_FILESAVE:	Code ="[S]:";	break;
			case LogCode_TASK:		Code ="[T]:";	break;

		}

		String tab="";
		for(int i=0;i<_tabLevel;i++){
			tab +="   ";
		}


		String SendMSG = Device.TimeString  +"\t"+ Code+ tab + _msg;
		

		Serial.println(SendMSG);

		Device.OutPutMSG+= SendMSG+"\n";



	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SaveLogs
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void SaveLogs(){

		if(Device.OutPutMSG!=""){
			// ファイルを開く

			File file = SD.open(Device.OutPutFileName,FILE_APPEND);//設定ファイルの書き込み
			if (file){
				file.println(Device.OutPutMSG);


				file.close();
				Device.OutPutMSG="";
			}
		}



	}



//////////////////////////////////////////////////////////////
	// split
	//////////////////////////////////////////////////////////////
	int split(String data, char delimiter, String *dst){
		int index = 0;
//		int arraySize = (sizeof(data)/sizeof((data)[0]));  
		int datalength = data.length();




		for (int i = 0; i < datalength; i++) {
			char tmp = data.charAt(i);
			if ( tmp == delimiter ) {
				index++;
//				if ( index > (arraySize - 1)) return -1;
			}
			else dst[index] += tmp;
		}

		return (index + 1);
	}



    ///////////////////////////////////////////////////////////////////////////
    // maps_Between 
	//		int g =  maps_Between( (millis()%len),  Device.TASK[ no ].LED_START.TimeStart ,Device.TASK[ no ].LED_START.TimeEnd , (long)start_G ,(long)end_G,  Device.TASK[ no ].LED_END.TimeStart   ,Device.TASK[ no ].LED_END.TimeEnd   , (long)end_G,(long)start_G);
	                                
    ///////////////////////////////////////////////////////////////////////////
    long maps_Between(long x,	 long Ain_min, long Ain_max, long Aout_min, long Aout_max, 	long Bin_min, long Bin_max, long Bout_min, long Bout_max){

			if( x >=Ain_min && x<= Ain_max){
				return   map( x , Ain_min,  Ain_max, Aout_min, Aout_max );
			}else if( x >=Bin_min && x<= Bin_max){
				return   map( x , Bin_min,  Bin_max, Bout_min, Bout_max );
			}else{
				return 0;
			}
	}

 	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// FPS計算
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void FPS(int _no ){
		Device.FPS[ _no ].Count++;
		Device.FPS[ _no ].Sec = millis() / 1000;
		if(Device.FPS[ _no ].Sec   != Device.FPS[ _no ].pSec ){
		   Device.FPS[ _no ].pSec 	= Device.FPS[ _no ].Sec;
		   Device.FPS[ _no ].FPS 	= Device.FPS[ _no ].Count;
		   Device.FPS[ _no ].Count	= 0;
		}
	}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NoToTaskStrings
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String NoToTaskStrings( int _no ){

	String msg="";
	switch ( _no ){
		case TASK_Name_Hungry :		msg ="Hungry";	break;	
		case TASK_Name_Sleep :		msg ="Sleep";	break;	
		case TASK_Name_Mood :		msg ="Mood";	break;	
		case TASK_Name_Wait :		msg ="Wait";	break;	
		case TASK_Name_Emerg :		msg ="Emerg";	break;	
		case TASK_Name_Shit :		msg ="Shit";	break;	
		case TASK_Name_Power :		msg ="Power";	break;	
		case TASK_Name_Diapers :	msg ="Diapers";	break;	
		case TASK_Name_Burp :		msg ="Bur";		break;	
		case TASK_Name_Sleeping :	msg ="Sleeping";break;	

	}
	return msg;

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SwipeScreen
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SwipeScreen(){


			///////////////////////////////////////////////////////////////////
			//判定処理
			///////////////////////////////////////////////////////////////////
			if(Device.ScreenButton.Status ==0){
				if(Device.LCD_Tocuh.x !=-1 && (Device.LCD_Tocuh.x <40 || Device.LCD_Tocuh.x >280)){
					Device.ScreenButton.ClickPoint = Device.LCD_Tocuh;	//クリックポイントを記録
					Device.ScreenButton.Status = 1;						//ステータス設定

					if(Device.LCD_Tocuh.x < 40){	Device.ScreenButton.LR =-1;	}//向きを計算
					if(Device.LCD_Tocuh.x >280){	Device.ScreenButton.LR = 1;	}//向きを計算


				}
			}else if(Device.ScreenButton.Status ==1){
				Device.ScreenButton.Length = abs( Device.ScreenButton.ClickPoint.x - Device.LCD_Tocuh.x);		//長さを検出
			}
			//何も押されていない時
			if(Device.LCD_Tocuh.x ==-1){
						Device.ScreenButton.Status = 0;						//ステータス設定
						Device.ScreenButton.Length = 0;
			}

			//////////////////////////////////////////////////////////////
			//フリック処理
			//////////////////////////////////////////////////////////////
			if(Device.ScreenButton.Length >=50){	//20を超えた場合

				//画面推移
				if(Device.ScreenButton.LR == -1){	Device.ScreenNo--; 	Device.isModeChangeFirstTime =false;	Device.TimeModeChangeElapsed = millis();	}
				if(Device.ScreenButton.LR ==  1){	Device.ScreenNo++;	Device.isModeChangeFirstTime =false;	Device.TimeModeChangeElapsed = millis();	}
				if(Device.ScreenNo <0){	Device.ScreenNo =10;}
				if(Device.ScreenNo >11){	Device.ScreenNo =0;}

				ScreenChangeNo( Device.ScreenNo );	//スクリーン移動



				Device.ScreenButton.Status = 0;						//ステータス設定
				Device.ScreenButton.Length = 0;
			}

			if(Device.ScreenButton.Status!=0){			}

		//描写処理
		switch (Device.ScreenButton.Status){
			case 0:	//何もない時
						if(Device.ScreenButton.Status != Device.ScreenButton.Status_OLD){
							Device.LCD_Message.createSprite(10,240);	//生成
							Device.LCD_Message.pushSprite(&Device.LCD,  0,0);
							Device.LCD_Message.pushSprite(&Device.LCD,310,0);
						}
				break;
			
			case 1:	//何もない時
						if(Device.ScreenButton.Status != Device.ScreenButton.Status_OLD){
							Device.LCD_Message.createSprite(10,240);	//生成
							Device.LCD_Message.fillRoundRect (2, 70,6,100,3,BaseColor_Cyan);	
							Device.LCD_Message.drawRoundRect (2, 70,6,100,3,BaseColor_CyanDark);	

							if(	Device.ScreenButton.LR ==-1){	Device.LCD_Message.pushSprite(&Device.LCD,0,0);		}
							if(	Device.ScreenButton.LR == 1){	Device.LCD_Message.pushSprite(&Device.LCD,310,0);	}
						}
				break;
		}
		Device.ScreenButton.Status_OLD = Device.ScreenButton.Status;


}



///////////////////////////////
//TimeChangeS2M
///////////////////////////////
int TimeToSting(int no, int Stime){

	int rno =0;

	switch (no){ 
		case Time_S:	rno = (int)Stime%60;		    break; 
		case Time_M:	rno = (int)(Stime/60)%60;		break; 
		case Time_H:	rno = (int)(Stime/60/60);		break; 

    }
	if(rno >=100){	rno = 0;}else if(rno <=  0){	rno = 0;}

  return rno;
}


///////////////////////////////
//TimeToString
///////////////////////////////
String TimeToStrings( unsigned long _time ){
	char tmpS[20];
	int H = TimeToSting( Time_H , _time);
	int M = TimeToSting( Time_M , _time);
	int S = TimeToSting( Time_S , _time);
	sprintf(tmpS, "%02d:%02d:%02d", H, M,S );
	return (String)tmpS;
}


///////////////////////////////
//NoToMP3FolderString
///////////////////////////////
String NoToMP3FolderString( int _no ){
	
	String msg ="";
	switch (_no){
		case  3:		msg = "Mood";		break;
		case  4:		msg = "Emerg";		break;
		case  5:		msg = "Burp";		break;
		case  6:		msg = "Shit";		break;
		case  7:		msg = "Happy";		break;
		case  8:		msg = "Goku";		break;
		case  9:		msg = "Hungry";		break;
		case 10:		msg = "Sleep";		break;
	}
	return msg;
}

///////////////////////////////
//ScreenChangeNo
///////////////////////////////
void ScreenChangeNo( int _no ){

	//Screen_Hungryの時にモータ制御を行うこともできる。。
	//画面チェンジジに、モータ制御をＡｕｔｏに設定する
	if(Device.ScreenNo == Screen_Hungry){
		Device.Sensor.Mouth.isHack 		= false;
	}


	Device.ScreenNo = _no;
	Device.TimeModeChangeElapsed = millis();
	Device.isModeChangeFirstTime =false;
}