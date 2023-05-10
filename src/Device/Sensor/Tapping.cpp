#include "Device/Sensor/Tapping.h"
#include "Global/Function.h"

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// コンストラクタ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		TappingInfo::TappingInfo(){


		}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// AddData
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void TappingInfo::Initialize(float min , float max){
			this->ThresholdMin = min;
			this->ThresholdMax = max;

			this->isFlag =false;         	//閾値を超えているかのフラグ
			for(int i=0;i<5;i++){
				this->Datas[i] =0;   		//データ格納用
			}
			this->Counter = 0; 			//カウント用
		    this->TPM = 0;                //TPM
		    this->TPM_Tmp =0;            //TPM テンプ
		}
			


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// AddData
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int TappingInfo:: AddData( float val ){
			//閾値を上回ったとき

//			Serial.println("***********************:" + val + "\t" + this->ThresholdMax );

			if(( val >= this->ThresholdMax)){
//				Serial.println("\t Over **************");
				if( millis() - Time_Elapsed_S >= 250 && isFlag == false){   //250ms以上の時のみ
					this->Time_Elapsed_S   = millis();   //開始時間の登録
					float tmp   = 60000.0f /(this->Time_Elapsed_S - this->Time_Elapsed_B);    //BPM計算

					this->Datas[ this->Counter ]= tmp;   //データ格納
					this->Counter++;
					if (this->Counter >= 5) {
						this->Counter = 0; //カウンターリセット
					}
					//過去データを格納
					int sum =0;
					for(int i=0;i<5;i++){
						sum += this->Datas[ i ];
					}

				//平均時間を算出
				this->TPM_Tmp= sum / 5.0f;
				if(this->TPM_Tmp>=200){          //200TTPMを超えないように調整
					this->TPM_Tmp= 200.0f;
				}
				this->Time_Elapsed_B = this->Time_Elapsed_S;   
				this->isFlag = true; //Flag ON
			}
		}

		//閾値を下回った時
		if( val <= this->ThresholdMin){
			isFlag = false; //Flag ON
		}

		//時間経過とともに減衰
		this->TPM = this->TPM_Tmp;
		if( millis() - this->Time_Elapsed_S >= 3000){
			this->TPM = maps((millis() - Time_Elapsed_S) ,3000,5000, this->TPM_Tmp,0.0f);
			if((int)this->TPM==0){
				this->TPM_Tmp=0.0f;
				for(int i=0;i<5;i++){
					this->Datas[ i ] = 0.0f;
				}
			}
		}

		return  this->TPM;

	}
