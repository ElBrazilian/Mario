#include "main.h"

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

    app->continuer = true;
}

void destroy_app(App *app){
    destroy_timekeeper(app->keeper);

    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
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

    while(app->continuer){
        // HANDLING EVENTS
        handle_events(app);
        update_timekeeper_handle(app->keeper);

        // UPDATE 
        update(app);
        update_timekeeper_update(app->keeper);

        // DRAW
        draw(app);
        update_timekeeper_draw(app->keeper);

        // DELAY TO STAY AT TARGET FPS
        timekeeper_limit(app->keeper);
        timekeeper_computeFPS(app->keeper);

        printf("FPS: %f\n", app->keeper->currentFPS);
    }


    // Destroy everything
    destroy_app(app);
    return 0;
}