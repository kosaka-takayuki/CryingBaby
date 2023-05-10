#pragma once 
#ifndef BUTTONINFO_H
#define BUTTONINFO_H

#include <M5Core2.h>
#include "Global/Enum.h"


	//********************************
	//ButtonInfo class
	//********************************
	class ButtonInfo{
		public:
			int 		ButtonType;			//ボタンの種類
			ButtonArea 	ButtoClickArea;		//ボタンエリア
			
			String		Title;				//文字	
			String 		MSG[5];				//文字

			uint32_t 	BackColor[5];		//背景色
			
			int 		SelectButton;		//選択されたボタン 
			int 		SelectButton_OLD;		//選択されたボタン 

			boolean 	isClick;			//クリックされたかどうが？
			Point		ClickPoint;			//クリックポイント	
			Point		ClickPoint_B;		//クリックポイント



			int 		DrawX;
			int 		DrawX_OLD;

			int 		SelectButtonMoveing;			//選択させたボタン
			int 		SelectButtonMoveing_OLD =-1;	//選択させたボタン

			boolean		isDraw =true;


			int _Bar_StartX;   							//スタートX座標
			int _Bar_Width;    							//バーの全体のよこ幅
			int _Button_Width; 							//ボタンの幅 
			float _Button_StartX;							//次のボタンとの距離　A---この距離---B 　　　X座標の先端

			/////////////////////////////////////////////////////
			//関数群
			/////////////////////////////////////////////////////
			ButtonInfo();    //コンストラクタ

			void Initialize(int _bar_w, int _but_w, String m1, String m2, 			 		    uint32_t _c1, uint32_t _c2 );
			void Initialize(int _bar_w, int _but_w, String m1, String m2, String m3, 		    uint32_t _c1, uint32_t _c2,  uint32_t _c3 );
			void Initialize(int _bar_w, int _but_w, String m1, String m2, String m3, String m4, uint32_t _c1, uint32_t _c2,  uint32_t _c3,  uint32_t _c4 );
			void Initialize(int _bar_w, int _but_w, String m1, String m2, String m3, String m4, String m5, uint32_t _c1, uint32_t _c2,  uint32_t _c3,  uint32_t _c4,  uint32_t _c5 );

			boolean DrawButton(int _no, int y);

			void SetSelectButton(	int SelectButton);

//			void CreateButton(int x, int y, int witdh,  String _msg, int _fsize);
	}; 


#endif
