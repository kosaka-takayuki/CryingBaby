#pragma once 
#ifndef TIMELED_H
#define TIMELED_H

#include <M5Core2.h>

	//********************************
	//TimeLED
	//********************************
	class TimeLED{
		public:
			int TimeStart;
			int TimeEnd;
			uint32_t Color;

			TimeLED(int TimeStart ,int TimeEnd , uint32_t Color );
			TimeLED();
	};
	

#endif
