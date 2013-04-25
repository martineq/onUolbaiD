#pragma once

#include <SDL.h>

typedef unsigned int uint;


class Timer
{
    private:
    //The clock time when the timer started
	uint startTicks;

    //The ticks stored when the timer was paused
    uint pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    uint get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};
