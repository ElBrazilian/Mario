#include "timekeeper.h"

TimeKeeper *create_timekeeper(double targetFPS){
    TimeKeeper *keeper                  = malloc(sizeof(TimeKeeper));
    keeper->draw_time                   = 0;
    keeper->handle_events_time          = 0;

    Uint32 ticks = SDL_GetTicks();
    keeper->last_draw_ticks             = ticks;
    keeper->last_handle_events_ticks    = ticks;
    keeper->last_update_ticks           = ticks;
    keeper->last_frame_ticks            = ticks;
    
    keeper->last_delay                  = 0;
    keeper->frame_length                = 0;
    keeper->frame_length_raw            = 0;
    keeper->currentFPS                  = 0;
    keeper->update_time                 = 0;
    keeper->draw_time                   = 0;
    keeper->handle_events_time          = 0;
    
    set_timekeeper_framerate(keeper, targetFPS);

    for (int i = 0; i < FPS_NUM_AVERAGES; i++){
        keeper->last_frame_lengths_array[i] = keeper->target_frame_length;
    }
    keeper->current_average_index           = 0;
    keeper->last_frame_lengths_sum          = keeper->target_frame_length * FPS_NUM_AVERAGES;


    return keeper;
}
void set_timekeeper_framerate(TimeKeeper *keeper, double FPS){
    keeper->targetFPS = FPS;
    keeper->target_frame_length = (Uint32)((1/FPS) * 1000);
}
void update_timekeeper_handle(TimeKeeper *keeper){
    keeper->last_handle_events_ticks = SDL_GetTicks();
    keeper->handle_events_time = keeper->last_handle_events_ticks - keeper->last_frame_ticks;
}
void update_timekeeper_update(TimeKeeper *keeper){
    keeper->last_update_ticks = SDL_GetTicks();
    keeper->update_time = keeper->last_update_ticks - keeper->last_handle_events_ticks;
}
void update_timekeeper_draw(TimeKeeper *keeper){
    keeper->last_draw_ticks = SDL_GetTicks();
    keeper->draw_time = keeper->last_draw_ticks - keeper->last_update_ticks;

    keeper->frame_length_raw = keeper->handle_events_time + keeper->update_time + keeper->draw_time;
}

void timekeeper_limit(TimeKeeper *keeper){
    keeper->last_delay = keeper->target_frame_length - keeper->frame_length_raw;
    if ((int)keeper->last_delay < 0) {
        keeper->last_delay = 0;
    }
    else {
        SDL_Delay(keeper->last_delay);
    }
}
void timekeeper_computeFPS(TimeKeeper *keeper){
    Uint32 now = SDL_GetTicks();
    keeper->frame_length = now - keeper->last_frame_ticks;

    
    keeper->last_frame_lengths_sum = keeper->last_frame_lengths_sum - keeper->last_frame_lengths_array[keeper->current_average_index] + keeper->frame_length;
    keeper->last_frame_lengths_array[keeper->current_average_index] = keeper->frame_length;
    keeper->current_average_index = (keeper->current_average_index + 1) % FPS_NUM_AVERAGES;

    keeper->currentFPS = 1000. * FPS_NUM_AVERAGES / ((int) keeper->last_frame_lengths_sum);
    keeper->last_frame_ticks = now;
}
void destroy_timekeeper(TimeKeeper *keeper){
    free(keeper);
}