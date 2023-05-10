#pragma once 
#ifndef _AQUESTALK_TTS_H_
#define _AQUESTALK_TTS_H_


  class AquesTalkTTS {	
    public:

//	  float SPgain =0.3f;
      int create(const char *licencekey);//heap:400B
      int createK(const char *licencekey);//heap:21KB
      void release();

      int play(const char *koe, int speed);//koe: onsei-kigouretu(roman)
      int playK(const char *kanji, int speed,boolean isTalk);//kanji: kanji-text (UTF8)

      void stop();
      bool isPlay();
      int getLevel();

	  void SetVolume(int _volume);

  };
//  extern AquesTalkTTS AquesTalk;


#endif // !defined(_AQUESTALK_TTS_H_)