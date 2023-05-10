#include "Button/Button_Square.h"

#include "Draw/Draw_Function.h"

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// コンストラクタ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		ButtonSquare::ButtonSquare(){ }



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Initialize
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void ButtonSquare::Initialize(int _dw, int _dh, int _boder, String m1, uint32_t _ColorLine, uint32_t _ColorBack){
		this->DrawW = _dw;
		this->DrawH = _dh;
		this->Border= _boder;

		this->Title = m1;

		this->ColorLine		= _ColorLine;
		this->ColorBack 	= _ColorBack;

		this->isDraw = true;

//		this->isClicking_old = true;
		this->isClicking = false;


	}

	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Buton
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     boolean ButtonSquare::DrawButton(int _no, int _dx, int _dy){


		for(int i=0;i<TASK_Name_End;i++){
			if(this->Title == Device.TASK[i].Name){
//					this->ColorBack = Device.TASK[i].colorBack;
			}
		}

		uint32_t 	_boderColor  = this->ColorLine;
		uint32_t 	_backColor   = this->ColorBack;
		this->DrawX = _dx;
		this->DrawY = _dy;
		




		//判定処理		
		if(Device.LCD_Tocuh_Sprite.x !=-1){
			//枠内に入っているか確認
			if( Device.LCD_Tocuh_Sprite.y >= this->DrawY &&   Device.LCD_Tocuh_Sprite.y <= this->DrawY+ this->DrawH && 
				Device.LCD_Tocuh_Sprite.x >= this->DrawX &&   Device.LCD_Tocuh_Sprite.x <= this->DrawX+ this->DrawW){
					if(this->isClicking == false){
						this->isDraw =true;  //描写あり
						this->isClicking = true;			//クリックされている
						this->TimeCountClick = millis();	//クリックした時間を記録
					}else{
						this->isDraw =false;  //描写なし
					}
					//２秒以上おされていたら
					if( (millis() -this->TimeCountClick) >2000 ){
						this->isDeeptClicking = true;
					}else{
						this->isDeeptClicking = false;

					}
				}
		}else{
					this->isDraw =false;  //描写あり
					if(this->isClicking == true){
						this->isShortClicked = true;			//クリックされている
						this->isDraw =true;  //描写あり
					}
					if(this->isDeeptClicking == true){
						this->isDeeptClicked = true;			//クリックされている
						this->isDraw =true;  //描写あり
					}
					this->isClicking = false;					//クリックされていない
					this->isDeeptClicking = false; 				//長押しされていない
		}
		
		if(this->isDeeptClicking  == true){
			_boderColor = BaseColor_Tomato;
			_backColor = this->ColorBack - 0x444444u;
//			Serial.println("\t\tisDeeptClicking");
		}else{
			if(this->isClicking  == true){
	//			Serial.println("Cliking");
				_boderColor = BaseColor_Tomato;
				_backColor = this->ColorBack - 0x222222u;
			}
		}

		if(this->isShortClicked  == true){
//			Serial.println("\tisShortClick");
		}
		if(this->isDeeptClicked  == true){
//			Serial.println("\t\t\tisDeeptClicked");
		}



		////////////////////////////////////////////////////////////////////
		//判定処理
		////////////////////////////////////////////////////////////////////
	
			if(this->isDeeptClicked == true){
				switch (_no){
					case ButtonSuare_Touch_ON:		Device.M5Touch = true;		break;
					case ButtonSuare_Touch_OFF:		Device.M5Touch = false; 	break;
				}
			}


		////////////////////////////////////////////////////////////////////
		//描写処理
		////////////////////////////////////////////////////////////////////
//			if(_no == Device.SelectTASK){
//				_boderColor = BaseColor_Red;
//			}

			Device.LCD_Sprite.fillRoundRect ( this->DrawX, this->DrawY, this->DrawW, this->DrawH, 12,	_boderColor);	//背景
			Device.LCD_Sprite.fillRoundRect ( this->DrawX+this->Border, this->DrawY+this->Border, this->DrawW-(this->Border*2), this->DrawH-(this->Border*2), 12-(this->Border),	_backColor);	//背景
			Device.LCD_Sprite.setTextColor(BaseColor_Black);	//文字色設定(文字色、背景色)
			DrawString( this->Title  , this->DrawX + (this->DrawW/2) , this->DrawY + (this->DrawH/2) , 16, middle_center);	//文字描写



		//解放設定
		this->isShortClicked  = false;
		this->isDeeptClicked  = false;



		return this->isDraw;

	 }


