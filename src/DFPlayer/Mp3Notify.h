#pragma once 
#ifndef MP3NOTIFY_H
#define MP3NOTIFY_H

#include <M5Core2.h>
#include <DFMiniMp3.h>


class Mp3Notify; 
typedef DFMiniMp3<HardwareSerial, Mp3Notify> DfMp3;
extern DfMp3 MP3;

		 extern int     ErrorCode;          //エラーコード

class Mp3Notify{
	public:

//		 void Setup(DfMp3& mp3);
		 static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action);
		 static void OnError(DfMp3& mp3, uint16_t errorCode);
		 static void OnPlayFinished(DfMp3& mp3, DfMp3_PlaySources source, uint16_t track);
		 static void OnPlaySourceOnline(DfMp3& mp3, DfMp3_PlaySources source);
		 static void OnPlaySourceInserted(DfMp3& mp3, DfMp3_PlaySources source);
		 static void OnPlaySourceRemoved(DfMp3& mp3, DfMp3_PlaySources source);


};


#endif
