#include "Draw/Draw_Function.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DrawTitle
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawTitle(String msg, int _dy, unsigned int BreakTime, uint32_t _backcolor){


	if( (millis()- Device.TimeModeChangeElapsed) < BreakTime){

		Device.LCD_Sprite.setFont(&fonts::efontJA_24_b);		//Font設定
		Device.LCD_Sprite.setTextColor(BaseColor_Black);	//文字色設定(文字色、背景色)
		Device.LCD_Sprite.setTextDatum( middle_center );

		while(1){
			int x = maps( millis()- Device.TimeModeChangeElapsed ,0,BreakTime-100,150,0);
			int w = maps( millis()- Device.TimeModeChangeElapsed ,0,BreakTime-100,0,300);

				Device.LCD_Sprite.fillScreen( BaseColor_Black);  // 指定色で塗り潰し
				Device.LCD_Sprite.fillRoundRect (x,_dy,w,30,5,_backcolor);

			Device.LCD_Sprite.drawString(msg,  150, _dy+15);
			Device.LCD_Sprite.pushSprite(&Device.LCD,10,10);		//描写

			if ( millis() - Device.TimeModeChangeElapsed > BreakTime) {      break;    }
		}
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DrawTitle
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawTitle(String msg, unsigned int BreakTime, int _Status){


	if( (millis()- Device.TimeModeChangeElapsed) < BreakTime){

//Serial.println("****");

		Device.LCD_Sprite.setFont(&fonts::efontJA_24_b);		//Font設定
		Device.LCD_Sprite.setTextColor(BaseColor_Black);	//文字色設定(文字色、背景色)
		Device.LCD_Sprite.setTextDatum( middle_center );


		uint32_t _backcolor;
		switch(_Status){
				case TASK_Status_Run: 		_backcolor = BaseColor_Tomato; 	break;
				case TASK_Status_Wait: 		_backcolor = BaseColor_Orange; 	break;
				case TASK_Status_Count: 	_backcolor = BaseColor_Gray; 	break;
				case TASK_Status_Non: 		
				default:
											_backcolor = BaseColor_Gray; 	break;
		}

		while(1){
			int x = maps( millis()- Device.TimeModeChangeElapsed ,0,BreakTime-100,150,0);
			int w = maps( millis()- Device.TimeModeChangeElapsed ,0,BreakTime-100,0,300);

				Device.LCD_Sprite.fillScreen( BaseColor_Black);  // 指定色で塗り潰し
				Device.LCD_Sprite.fillRoundRect (x,0,w,30,5,_backcolor);

			Device.LCD_Sprite.drawString(msg,  150, 0+15);
			Device.LCD_Sprite.pushSprite(&Device.LCD,10,10);		//描写

			if ( millis() - Device.TimeModeChangeElapsed > BreakTime) {      break;    }
		}
	}

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DrawBOX
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawBox(String msg, int _dy,unsigned int BreakTime){

//	BreakTime =100;

	SetTapeLEDs(64 , 0,0,0); //LEDセット 

	Device.TimeModeChangeElapsed = millis();	//時間記録
	
	int _DrawX =320;

	Device.LCD_Sprite.setFont(&fonts::efontJA_16_b);		//Font設定 24 16 14 12 10
	Device.LCD_Sprite.setTextColor(BaseColor_Black);			//文字色設定(文字色、背景色)

	while(1){
		_DrawX = maps( millis()- Device.TimeModeChangeElapsed ,0,(BreakTime-200),320,0);
		Device.LCD_Sprite.setTextDatum( middle_right );

		Device.LCD_Sprite.fillRect (0,_dy,300,20,BaseColor_Black);	
		Device.LCD_Sprite.fillRoundRect (_DrawX,_dy,300,20,2,BaseColor_Beige);	
		Device.LCD_Sprite.drawString(msg, 150+_DrawX, _dy+10);

		Device.LCD_Sprite.fillRoundRect (170+_DrawX, _dy+2,120,20-4,2,BaseColor_Orange);	
		Device.LCD_Sprite.setTextDatum( middle_center );
		Device.LCD_Sprite.drawString("Checking", 235+_DrawX, _dy+10);



		Device.LCD_Sprite.pushSprite(&Device.LCD,10,10);

		int r = map(millis() - Device.TimeModeChangeElapsed, 0, BreakTime, 0, 128);
		SetTapeLEDs(64 , r, 0, 0); //LEDセット 

		if ( millis() - Device.TimeModeChangeElapsed > BreakTime) {     break;    }
	}
	Device.LCD_Sprite.fillRoundRect (170, _dy+2,120,20-4,2,BaseColor_Beige);	
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DrawBoxResult 結果を表示する
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawBoxResult(String msg,int _dy,unsigned int BreakTime, boolean isTF){
	if(isTF== true){
		//OK
		Device.LCD_Sprite.fillRoundRect (170,_dy+2,120,20-4,2,BaseColor_Cyan);	
		SetTapeLEDs(64 , 255,0,0); //LEDセット 

	}else{
		//NG
		Device.LCD_Sprite.fillRoundRect (170,_dy+2,120,20-4,2,BaseColor_Tomato);	
		SetTapeLEDs(64 , 0,0,255); //LEDセット 
	}

	Device.LCD_Sprite.setTextDatum( middle_center );
	Device.LCD_Sprite.drawString(msg, 235, _dy+10);
	Device.LCD_Sprite.pushSprite(&Device.LCD,10,10);
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DrawBackGround
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawString(String msg, int _dx, int _dy, int _font, textdatum_t _position){

	Device.LCD.startWrite();	

		switch (_font){
			case 10: 	Device.LCD_Sprite.setFont(&fonts::efontJA_10);		break;	//Font設定
			case 12: 	Device.LCD_Sprite.setFont(&fonts::efontJA_12);		break;	//Font設定
			case 14: 	Device.LCD_Sprite.setFont(&fonts::efontJA_14);		break;	//Font設定
			case 16: 	Device.LCD_Sprite.setFont(&fonts::efontJA_16);		break;	//Font設定
//			case 24: 	Device.LCD_Sprite.setFont(&fonts::efontJA_24);		break;	//Font設定

			case 128: 	Device.LCD_Sprite.setFont(&fonts::efontJA_12_b);	break;	//Font設定
//			case 148: 	Device.LCD_Sprite.setFont(&fonts::efontJA_14_b);	break;	//Font設定
		}
		Device.LCD_Sprite.setTextDatum( _position );		//文字位置設定

		Device.LCD_Sprite.drawString( msg, _dx, _dy); //タイトルの表示
	Device.LCD.endWrite();	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DrawBackGround
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawBackGround( int no ,int dy,uint32_t color){
	switch ( no ){
		case 1:	//1列
			Device.LCD_Sprite.fillRoundRect (135, dy,165,13,2,color);		//背景塗
		break;

		case 2:	//2列
			Device.LCD_Sprite.fillRoundRect (135, dy,93,13,2,color);		//背景塗
//			Device.LCD_Sprite.fillRoundRect (233, dy,67,13,2,BaseColor_Beige);		//背景塗
		break;

		case 3:	//3列
			Device.LCD_Sprite.fillRoundRect (135, dy, 44,13,2,color);		//背景塗
			Device.LCD_Sprite.fillRoundRect (184, dy, 44,13,2,color);		//背景塗
//			Device.LCD_Sprite.fillRoundRect (233, dy, 67,13,2,BaseColor_Beige);		//背景塗
		break;

		case 11:	//Pumpセッティング用
			Device.LCD_Sprite.fillRoundRect (120, dy,100,13,2,color);		//背景塗
//			Device.LCD_Sprite.fillRoundRect (233, dy,67,13,2,BaseColor_Beige);		//背景塗
		break;

	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DrawBackGround
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawBackGround( int no,int dy,uint32_t colorA,uint32_t colorB,boolean isActive){

	uint32_t color;

	if(isActive == false){
		color = colorA;
	}else{
		color = colorB;
	}


	switch ( no ){
		case 1:	//1列
			Device.LCD_Sprite.fillRoundRect (135, dy,165,13,2,color);		//背景塗
		break;

		case 2:	//2列
			Device.LCD_Sprite.fillRoundRect (135, dy,93,13,2,color);		//背景塗
//			Device.LCD_Sprite.fillRoundRect (233, dy,67,13,2,BaseColor_Beige);		//背景塗
		break;

		case 3:	//3列
			Device.LCD_Sprite.fillRoundRect (135, dy, 44,13,2,color);		//背景塗
			Device.LCD_Sprite.fillRoundRect (184, dy, 44,13,2,color);		//背景塗
//			Device.LCD_Sprite.fillRoundRect (233, dy, 67,13,2,BaseColor_Beige);		//背景塗
		break;

		case 11:	//Pumpセッティング用
			Device.LCD_Sprite.fillRoundRect (120, dy,100,13,2,color);		//背景塗
//			Device.LCD_Sprite.fillRoundRect (233, dy,67,13,2,BaseColor_Beige);		//背景塗
		break;

	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DrawDataGauge
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawDataGauge(int _dx,int _dy, int _data ,uint32_t color_gauge){
		Device.LCD.startWrite();	
			for(int i=0;i<=14;i++){
				if(i <=_data){
					Device.LCD_Sprite.fillRect ( _dx+(i*4), _dy,3,11-1,BaseColor_Beige);		//背景塗
				}else{
					Device.LCD_Sprite.fillRect ( _dx+(i*4), _dy,3,11-1,BLACK);		//背景塗
				}
			}
		Device.LCD.endWrite();	

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DrawDataGauge
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawDataGauge(int _dx,int _dy, int _data ,uint32_t color_gaugeA, uint32_t color_gaugeB, boolean isActive ){

	uint32_t color;

	if(isActive == false){
		color = color_gaugeA;
	}else{
		color = color_gaugeB;
	}


		Device.LCD.startWrite();	
			for(int i=0;i<=14;i++){
				if(i <=_data){
//					Device.LCD_Sprite.fillRect ( _dx+(i*4), _dy+2,3,11-2,color);		//背景塗
					Device.LCD_Sprite.fillRect ( _dx+(i*4), _dy+2,3,11-2,color);		//背景塗
				}else{
					Device.LCD_Sprite.fillRect ( _dx+(i*4), _dy+2,3,11-2,BLACK);		//背景塗
				}
			}
		Device.LCD.endWrite();	

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DrawFPS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boolean DrawFPS(uint32_t _backcolor){

	bool isDrawA = false;
	if( Device.FPS[ 0 ].FPS != Device.FPS[ 0 ].FPS_B){
		Device.LCD_Sprite.setTextColor(BaseColor_Black);	//文字色設定(文字色、背景色)
		Device.LCD_Sprite.fillRect( 230,5,65,10, BaseColor_Orange); //タイトルの表示
		DrawString( String(Device.FPS[ 0 ].FPS)+" FPS", 290, 10, 12, middle_right);	//文字描写
		isDrawA = true;	//更新する
	}
	Device.FPS[ 0 ].FPS_B = Device.FPS[  0 ].FPS;


	bool isDrawB = false;
	if( Device.FPS[ 1 ].FPS != Device.FPS[ 1 ].FPS_B){
		Device.LCD_Sprite.setTextColor(BaseColor_Black);	//文字色設定(文字色、背景色)
		Device.LCD_Sprite.fillRect( 230,15,65,10, BaseColor_Red); //タイトルの表示
		DrawString( String(Device.FPS[ 1 ].FPS)+" FPS", 290, 20, 12, middle_right);	//文字描写
		isDrawB = true;	//更新する
	}
	Device.FPS[ 1 ].FPS_B = Device.FPS[  1 ].FPS;

	
	if(isDrawA == true || isDrawB == true){
		return true;
	}else{
		return false;
	}


}

