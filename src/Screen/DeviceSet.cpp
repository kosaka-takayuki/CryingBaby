#include "Screen/DeviceSet.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DeviceSet
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceSet(){	



//	int _DrawY =0;
	boolean isDraw = false;	//更新する必要があるかどうか

//	int _DrawX_MSG_L = 189-20;
//	int _DrawX_MSG_C = 233-10;

//	char tmpA[40],tmpB[40];

//	int ShowNo;

	String DrawMSG ="";

//	bool isFirstDraw =false;	//画面更新時に表示されない問題を防ぐ

//	bool isFirstDraw =false;	//画面更新時に表示されない問題を防ぐ
	

	/////////////////////////////////////////////////////////////////////////////////////
    //画面設定
	/////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////
    // 時間経過アニメーション　徐々にフェードイン
	/////////////////////////////////////////////////////////////////////////////////////
	DrawTitle("Device Set", 0, 600, BaseColor_Cyan);


	//最初の一度だけ実行
	if( Device.isModeChangeFirstTime == false ){
		//isFirstDraw = true;	//画面更新時に表示されない問題を防ぐ
		if(Device.isHelp == true){
			Device.AquesTalk.playK("デバイス / セット", 50, Device.isAquesTalk);                          //AquesTalkで会話　会話スピードは最低の50
		}
		Device.isModeChangeFirstTime = true;

		Device.LCD_Sprite.setTextColor(BaseColor_White);			//文字色設定(文字色、背景色)
		DrawString("MP3 Volume", 10 , 50, 12, middle_left);	//文字描写
		DrawString("M5  Volume", 10 , 100, 12, middle_left);	//文字描写
		DrawString("M5  Touch" , 10 , 150, 12, middle_left);	//文字描写

		switch (Device.Mp3Volume){
			case   0:	Device.Button[ Button_MP3_Speaker	].SetSelectButton(0);	Device.Button[ Button_MP3_Speaker ].SelectButton_OLD =0;	break;
			case  25:	Device.Button[ Button_MP3_Speaker	].SetSelectButton(1);	Device.Button[ Button_MP3_Speaker ].SelectButton_OLD =1;	break;
			case  50:	Device.Button[ Button_MP3_Speaker	].SetSelectButton(2);	Device.Button[ Button_MP3_Speaker ].SelectButton_OLD =2;	break;
			case  75:	Device.Button[ Button_MP3_Speaker	].SetSelectButton(3);	Device.Button[ Button_MP3_Speaker ].SelectButton_OLD =3;	break;
			case 100:	Device.Button[ Button_MP3_Speaker	].SetSelectButton(4);	Device.Button[ Button_MP3_Speaker ].SelectButton_OLD =4;	break;
		}
		Device.Button[Button_MP3_Speaker	    ].isClick = false;
		Device.Button[Button_MP3_Speaker	    ].ClickPoint_B.x =-1;
		Device.Button[Button_MP3_Speaker	    ].ClickPoint_B.y =-1;


		switch (Device.M5Volume){
			case   0:	Device.Button[ Button_M5_Speaker	].SetSelectButton(0);	Device.Button[ Button_M5_Speaker ].SelectButton_OLD =0;	break;
			case  25:	Device.Button[ Button_M5_Speaker	].SetSelectButton(1);	Device.Button[ Button_M5_Speaker ].SelectButton_OLD =1;	break;
			case  50:	Device.Button[ Button_M5_Speaker	].SetSelectButton(2);	Device.Button[ Button_M5_Speaker ].SelectButton_OLD =2;	break;
			case  75:	Device.Button[ Button_M5_Speaker	].SetSelectButton(3);	Device.Button[ Button_M5_Speaker ].SelectButton_OLD =3;	break;
			case 100:	Device.Button[ Button_M5_Speaker	].SetSelectButton(4);	Device.Button[ Button_M5_Speaker ].SelectButton_OLD =4;	break;
		}
		Device.Button[Button_M5_Speaker	    ].isClick = false;
		Device.Button[Button_M5_Speaker	    ].ClickPoint_B.x =-1;
		Device.Button[Button_M5_Speaker	    ].ClickPoint_B.y =-1;


		switch (Device.M5Touch){
			case   0:	Device.Button[ Button_M5_Touch	].SetSelectButton(0);	Device.Button[ Button_M5_Touch ].SelectButton_OLD =0;	break;
			case   1:	Device.Button[ Button_M5_Touch	].SetSelectButton(1);	Device.Button[ Button_M5_Touch ].SelectButton_OLD =1;	break;
			case   2:	Device.Button[ Button_M5_Touch	].SetSelectButton(2);	Device.Button[ Button_M5_Touch ].SelectButton_OLD =2;	break;
		}
		Device.Button[Button_M5_Touch	    ].isClick = false;
		Device.Button[Button_M5_Touch	    ].ClickPoint_B.x =-1;
		Device.Button[Button_M5_Touch	    ].ClickPoint_B.y =-1;



	}




	/////////////////////////////////////////////////////////////////////
	//FPS表示
	/////////////////////////////////////////////////////////////////////
		isDraw =DrawFPS(BaseColor_Cyan);


	////////////////////////////////////////////////
	//フリックボタンの描写
	////////////////////////////////////////////////
	if( Device.Button[ Button_MP3_Speaker ].DrawButton( Button_MP3_Speaker,  60 )  == true){	isDraw =true;	DrawMSG +="Button \t";}

	if( Device.Button[ Button_M5_Speaker  ].DrawButton( Button_M5_Speaker,  110 )  == true){	isDraw =true;	DrawMSG +="Button \t";}

	if( Device.Button_Square[ ButtonSuare_Touch_ON 	 ].DrawButton( ButtonSuare_Touch_ON,      20,  160) == true){ isDraw =true;	DrawMSG +="Button A \t";}
	if( Device.Button_Square[ ButtonSuare_Touch_OFF  ].DrawButton( ButtonSuare_Touch_OFF, 	 162,  160) == true){ isDraw =true;	DrawMSG +="Button A \t";}

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