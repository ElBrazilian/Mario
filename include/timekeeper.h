/**
 * @file timekeeper.h
 * @author Nathan Schiffmacher (nathan.schiffmacher@student.isae-supaero.fr)
 * @brief 
 * @date 19-03-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TIME_KEEPER_H
#define TIME_KEEPER_H

#include <SDL2/SDL.h>

#define FPS_NUM_AVERAGES 200

typedef struct {
    double targetFPS;
    Uint32 target_frame_length; // in MS

    Uint32 last_handle_events_ticks;
    Uint32 last_update_ticks;
    Uint32 last_draw_ticks;
    Uint32 last_frame_ticks;
    Uint32 last_delay;
    Uint32 frame_length_raw; // without the delay
    Uint32 frame_length;

    // FPS computing average
    Uint32 last_frame_lengths_array[FPS_NUM_AVERAGES];
    Uint32 last_frame_lengths_sum;
    int current_average_index;

    double currentFPS;
    Uint32 update_time;
    Uint32 draw_time;
    Uint32 handle_events_time;
} TimeKeeper;

/**
 * @brief Creates and initializes a timekeeper object
 * 
 * @param targetFPS 
 * @return TimeKeeper* 
 */
TimeKeeper *create_timekeeper(double targetFPS);
/**
 * @brief Set the target FPS accordingly
 * 
 * @param keeper 
 * @param FPS 
 */
void set_timekeeper_framerate(TimeKeeper *keeper, double FPS);
/**
 * @brief needs to be called after handle_events(); to register the time it takes
 * 
 * @param keeper 
 */
void update_timekeeper_handle(TimeKeeper *keeper);
/**
 * @brief needs to be called after update(); to register the time it takes
 * 
 * @param keeper 
 */
void update_timekeeper_update(TimeKeeper *keeper);
/**
 * @brief needs to be called after draw(); to register the time it takes
 * 
 * @param keeper 
 */
void update_timekeeper_draw(TimeKeeper *keeper);
/**
 * @brief waits the necessary amount of time to stay at the target framerate
 * 
 * @param keeper 
 */
void timekeeper_limit(TimeKeeper *keeper);

/**
 * @brief Computes the length of the frame + the framerate
 * 
 * @param keeper 
 */
void timekeeper_computeFPS(TimeKeeper *keeper);

/**
 * @brief Destroys the timekeeper object
 * 
 * @param keeper 
 */
void destroy_timekeeper(TimeKeeper *keeper);



#endif


