#include "Device/Sensor/SensorData.h"


// #include "Gloabal/Variable.h"
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// コンストラクタ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		SensorData::SensorData(){

		}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// コンストラクタ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void SensorData::Initialize(){


			this->SensorTMP = new DataStock[18];

			//第1引数 int _avg_max	 		平均回数
			//第2引数 int _min				閾値の最小
			//第3引数 int _max				閾値の最大
			//第4引数 float _TPM_min		閾値TPM　最小　
			//第5引数 float _TPM_max		閾値TPM　最大
						
			

			this->SensorTMP[ Sensor_Eyes		].Initialize( 50,	 3, 4,	-1,  -1);   // 0  Eyes      	平均回数10回 
			this->SensorTMP[ Sensor_Microhone	].Initialize( 50,	 1, 2,	-1,  -1);   // 1 Microhone 		平均回数10回

			// マイクロフォンだけ、平均値の格納配列の初期値を0ではなく1915に設定
			for(int i=0;i<this->SensorTMP[ Sensor_Microhone	].AVG_MAX;i++ ){	this->SensorTMP[ Sensor_Microhone ].Datas[i] = 1915;			}


			this->SensorTMP[ Sensor_Mouth		].Initialize( 40,	7,  8,		-1,  -1);   // 2 Mouth     		平均回数10回
			this->SensorTMP[ Sensor_Temperature ].Initialize( 20,	9, 10,		-1,  -1);   // 3 Temperature	平均回数10回
			
			this->SensorTMP[ Sensor_IMU			].Initialize( 10, 	0,  0, 	0.1f,  0.5f);   // 6 IMU	     	平均回数の最大値

			this->SensorTMP[ Sensor_CROTCH		].Initialize( 30, 	5,  6, 		-1,  -1);   // 7 CROTCH    		平均回数10回
			this->SensorTMP[ Sensor_Level01		].Initialize( 10, 	0,  0, 		-1,  -1);   // 8 Level01    	平均回数10回
			this->SensorTMP[ Sensor_Level02		].Initialize( 10, 	0,  0, 		-1,  -1);   // 9 Level02    	平均回数10回
			this->SensorTMP[ Sensor_Level03		].Initialize( 10, 	0,  0, 		-1,  -1);   //10 Level03   		平均回数10回
			this->SensorTMP[ Sensor_Level04		].Initialize( 10, 	0,  0, 		-1,  -1);   //11 Level04    	平均回数10回
			this->SensorTMP[ Sensor_Level05		].Initialize( 10, 	0,  0, 		-1,  -1);   //12 Level05    	平均回数10回
			this->SensorTMP[ Sensor_Level06		].Initialize( 10, 	0,  0, 		-1,  -1);   //13 Level06    	平均回数10回
			this->SensorTMP[ Sensor_Level07		].Initialize( 10, 	0,  0, 		-1,  -1);   //14 Level07    	平均回数10回
			this->SensorTMP[ Sensor_Level08		].Initialize( 10, 	0,  0, 		-1,  -1);   //15 Level08    	平均回数10回
			this->SensorTMP[ Sensor_LCD_Touch	].Initialize(  5, 	0,  0, 	 	 0,   1);   //16 LCD_Touch    	平均回数10回

		}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// JudgeThreshold MAX
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	boolean SensorData::JudgeThreshold( SensorDataInfo data, int TC){
		switch (TC){

			//////////////////////////////////////////
			case ThresholdConditions_Max:
				if(data.Data >= data.Max){
						return true;
				}else{
						return false;
				}
				break;

			//////////////////////////////////////////
			case ThresholdConditions_Min:
				if(data.Data <= data.Min){
						return true;
				}else{
						return false;
				}
				break;

			//////////////////////////////////////////
			case ThresholdConditions_MinMAX:
				if((data.Data >= data.Min) && (data.Data <= data.Max)){
						return false;
				}else{
						return true;
				}
				break;

		}	
		return false;

	}

		