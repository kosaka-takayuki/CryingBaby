#pragma once 
#ifndef BUTTON_SQUARE_H
#define BUTTON_SQUARE_H

#include <M5Core2.h>
#include "Global/Enum.h"

	//********************************
	//ButtonInfo class
	//********************************
	class ButtonSquare{
		public:
			
			String		Title;				//文字	
			int 		DrawX;				//X座標
			int 		DrawY;				//Y座標
			int			DrawW;				//横幅
			int 		DrawH;				//縦幅
			int 		Border; 
			uint32_t 	ColorLine;			//ラインカラー
			uint32_t 	ColorBack;			//通常カラー

			boolean		isDraw =true;		//描写するどうか


			boolean  	isClicking 		= false;		//カーソルがボタン内にとどまっているかどうか？
			boolean  	isShortClicked 	= false;		//軽いクリックをしたかどうか

			boolean  	isDeeptClicking	= false;		//深いクリック中かどうか
			boolean  	isDeeptClicked	= false;		//深いクリック後か
			
			unsigned long  	TimeCountClick;				//クリック時間を計測	
			

			boolean 	isActive   = false;

			boolean 	isHack	   = false;

/*
			boolean		isClicking_old = false;

			boolean		isClicking = false;
			boolean		isClicked  = false;

			boolean 	isActive   = false;

			boolean			isDeepClick = false;	
*/

			/////////////////////////////////////////////////////
			//関数群
			/////////////////////////////////////////////////////
			ButtonSquare();    //コンストラクタ

			void Initialize(int _dw, int _dh, int _boder,  String m1, uint32_t _ColorLine, uint32_t _ColorBack);
			boolean DrawButton(int _no, int _dx, int _dy);
	}; 


#endif
