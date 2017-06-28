#include <windows.h>

#include "FPSTimer.h"

FPSTimer::FPSTimer()
	: startTicks(0),
	pausedTicks(0),
	paused(false),
	started(false)
{
}

FPSTimer::~FPSTimer()
{
}

void FPSTimer::start()
{
    // Start the timer
    started = true;

    // Unpause the timer
    paused = false;

    // Get the current clock time
    startTicks = SDL_GetTicks();
}

void FPSTimer::stop()
{
    // Stop the timer
    started = false;

    // Unpause the timer
    paused = false;
}

void FPSTimer::pause()
{
    // If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        // Pause the timer
        paused = true;

        // Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void FPSTimer::unpause()
{
    // If the timer is paused
    if( paused == true )
    {
        // Unpause the timer
        paused = false;

        // Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        // Reset the paused ticks
        pausedTicks = 0;
    }
}

int FPSTimer::get_ticks()
{
    // If the timer is running
    if( started == true )
    {
        // If the timer is paused
        if( paused == true )
        {
            // Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            // Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    // If the timer isn't running
    return 0;
}

bool FPSTimer::has_started()
{
    return started;
}

bool FPSTimer::is_paused()
{
    return paused;
}

void FPSTimer::capFrameRate(int frameRate)
{
	if(get_ticks() < 1000 / frameRate)
		SDL_Delay((1000 / frameRate) - get_ticks());
}