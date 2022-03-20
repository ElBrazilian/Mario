#include "timekeeper.h"
#include <SDL2/SDL.h>

#include "assert.h"

void test_timekeeper(TimeKeeper *keeper, int handle_time, int update_time, int draw_time){
    for (int i = 0; i < 2; i++){
        // handle
        SDL_Delay(handle_time);
        update_timekeeper_handle(keeper);


        // update
        SDL_Delay(update_time);
        update_timekeeper_update(keeper);

        // draw
        SDL_Delay(draw_time);
        update_timekeeper_draw(keeper);

        // wait for framerate
        timekeeper_limit(keeper);
        timekeeper_computeFPS(keeper);
    }
    assert(abs(keeper->handle_events_time - handle_time) <= 4);
    assert(abs(keeper->update_time - update_time) <= 4);
    assert(abs(keeper->draw_time - draw_time) <= 4);
    assert(abs(keeper->frame_length_raw - handle_time-update_time-draw_time) <= 6);

}

int main(int argc, char *argv[]){
    printf("* Starting timekeeper tests...\n");
    
    printf("  | testing timekeeper creation... "); fflush(stdout);
    TimeKeeper *keeper = create_timekeeper(2);

    assert(abs(keeper->target_frame_length - 500) <= 2);
    assert(fabs(keeper->targetFPS - 2) <= 0.05);
    printf("OK!\n");

    // Testing with > 0 delay 
    printf("  | testing timekeeper update with positive delay... "); fflush(stdout);
    test_timekeeper(keeper, 52, 87, 174);
    assert(fabs(keeper->currentFPS - keeper->targetFPS) <= 0.01);
    printf("OK!\n");

    // Testing with < 0 delay 
    printf("  | testing timekeeper update with positive delay... "); fflush(stdout);
    test_timekeeper(keeper, 52, 87, 574);
    assert(abs(keeper->frame_length - keeper->frame_length_raw) <= 2);
    printf("OK!\n");



    // printf("Frame_length %d\n", keeper->target_frame_length);
    // printf("last_handle_events_ticks %d\n", keeper->last_handle_events_ticks);
    // printf("last_update_ticks %d\n", keeper->last_update_ticks);
    // printf("last_draw_ticks %d\n", keeper->last_draw_ticks);
    // printf("frame_length %d\n", keeper->frame_length);
    // printf("frame_length_raw %d\n", keeper->frame_length_raw);
    // printf("currentFPS %f\n", keeper->currentFPS);
    // printf("update_time %d\n", keeper->update_time);
    // printf("draw_time %d\n", keeper->draw_time);
    // printf("handle_events_time %d\n", keeper->handle_events_time);
    // printf("last_delay %d\n", keeper->last_delay);

    destroy_timekeeper(keeper);

    printf("  +-> OK!\n\n");
    return 0;
}