#include "tileset.h"

Tileset *load_tileset(SDL_Renderer *renderer, char *filename, int num_tiles_x, int num_tiles_y){
    // Load the image as a surface 
    SDL_Surface *tmp_surface = IMG_Load(filename);
    if (tmp_surface == NULL) {
        printf("[IMG ERROR] tileset.c, IMG_Load: %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    // Create the texture
    Tileset *tileset        = malloc(sizeof(Tileset));
    tileset->texture        = SDL_CreateTextureFromSurface(renderer, tmp_surface);
    if (tileset->texture == NULL) {
        printf("[SDL ERROR] tileset.c, SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(tmp_surface);

    // Set all the variables in the tileset
    tileset->renderer       = renderer;
    tileset->num_tiles_x    = num_tiles_x;
    tileset->num_tiles_y    = num_tiles_y;

    tileset->width          = 0;
    tileset->height         = 0;
    tileset->format         = 0;
    tileset->access         = 0;
    SDL_QueryTexture(tileset->texture, &(tileset->format), &(tileset->access), &(tileset->width), &(tileset->height));

    tileset->tile_width     = tileset->width / tileset->num_tiles_x;
    tileset->tile_height    = tileset->height / tileset->num_tiles_y;

    return tileset;
}

void draw_tile(Tileset *tileset, int num_tile_x, int num_tile_y, int pos_x, int pos_y){
    SDL_Delay(2);
}


void destroy_tileset(Tileset *tileset){
    SDL_DestroyTexture(tileset->texture);
    free(tileset);
}