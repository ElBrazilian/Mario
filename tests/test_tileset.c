#include <stdbool.h>

#include <SDL2/SDL_image.h>

#include "tileset.h"
#include "app.h"

#define TARGET_FPS 60

void initialize_app(App *app){
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create the window
    app->window = SDL_CreateWindow(app->windowTitle, 2000, 0, WIDTH, HEIGHT, app->windowFlags);
    if (!app->window){
        printf("Failed to open the window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create the renderer
    app->renderer = SDL_CreateRenderer(app->window, -1, app->rendererFlags);
    if (!app->renderer){
        printf("Failed to open the renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create the timekeeper object
    app->keeper = create_timekeeper(TARGET_FPS);

    // Load the debug font and init TTF
    TTF_Init();
    app->debug_font = TTF_OpenFont("fonts/SpaceMono-Regular.ttf", DEBUG_FONT_SIZE);

    app->continuer = true;
}

void destroy_app(App *app){
    destroy_timekeeper(app->keeper);

    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    TTF_Quit();
    SDL_Quit();
    free(app);
}

int main(int argc, char *argv[]){
    // Creating and initializing the app
    App *app = malloc(sizeof(App));
    app->rendererFlags  = SDL_RENDERER_ACCELERATED;
    app->windowFlags    = 0;
    strcpy(app->windowTitle, "Yo");

    initialize_app(app);
    IMG_Init(0);
    SDL_Surface *img = IMG_Load("tiles/blocs.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app->renderer, img);
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL ,&w, &h);
    w = w/4;
    h = h/4;
    SDL_FreeSurface(img);

    // Load a tileset
    Tileset *ts = load_tileset(app->renderer, "tiles/blocs.png", 4, 4);

    // force draw to 0 in the 
    for (int i = 0; i < NUM_AVERAGES; i++){
        app->keeper->draw_array[i] = 0;
    }
    app->keeper->draw_average = 0;
    app->keeper->draw_sum = 0;
    app->keeper->draw_time = 0;

    while(app->continuer){
        // HANDLING EVENTS
        update_timekeeper_handle(app->keeper);

        // UPDATE 

        // DRAW
        SDL_SetRenderDrawColor(app->renderer, 0,0,255,255);
        
        SDL_Rect src = {2*w,2*h,w,h};
        SDL_Rect dst = {300,300,w,h};
        SDL_RenderCopy(app->renderer, texture, &src, &dst);
        
        timekeeper_draw_debug_info(app->keeper, app->renderer, app->debug_font);
        SDL_RenderPresent(app->renderer);

        update_timekeeper_update(app->keeper);
        draw_tile(ts, 0, 0, 200, 200);
        update_timekeeper_draw(app->keeper);

        // DELAY TO STAY AT TARGET FPS
        timekeeper_limit(app->keeper);
        timekeeper_computeFPS(app->keeper);

        //printf("FPS: %f\n", app->keeper->currentFPS);
        // printf("frame: %d\n", app->keeper->frame_length_raw);
    }

    // Destroy the tileset
    destroy_tileset(ts);

    SDL_DestroyTexture(texture);
    // Destroy everything
    IMG_Quit();
    destroy_app(app);

    return 0;
}