#ifndef FPSTIMER_H
#define FPSTIMER_H

#include "SDL.h"

class FPSTimer
{
private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

public:
    //Initializes variables
    FPSTimer();
	~FPSTimer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool has_started();
    bool is_paused();

	void capFrameRate(int frameRate);
};

#endif