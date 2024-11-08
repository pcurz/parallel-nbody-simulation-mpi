#include "timer.h"
#include <sys/time.h>
#include <stdlib.h>

static struct timeval timerStart;

/**
 * @brief Starts the timer by capturing the current time.
 */
void StartTimer() {
    gettimeofday(&timerStart, NULL);
}

/**
 * @brief Returns the elapsed time in milliseconds since the last call to StartTimer.
 * 
 * @return double The elapsed time in milliseconds.
 */
double GetTimer() {
    struct timeval timerStop, timerElapsed;
    gettimeofday(&timerStop, NULL);
    timersub(&timerStop, &timerStart, &timerElapsed);
    return timerElapsed.tv_sec * 1000.0 + timerElapsed.tv_usec / 1000.0;
}
