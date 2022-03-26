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

void draw_tile_in_tileset(Tileset *tileset, int num_tile_x, int num_tile_y, int pos_x, int pos_y){
    SDL_Rect src = {num_tile_x * tileset->tile_width,num_tile_y*tileset->tile_height,tileset->tile_width,tileset->tile_height};
    SDL_Rect dst = {pos_x,pos_y,tileset->tile_width,tileset->tile_height};
    SDL_RenderCopy(tileset->renderer, tileset->texture, &src, &dst);
}

void destroy_tileset(Tileset *tileset){
    SDL_DestroyTexture(tileset->texture);
    free(tileset);
}

Tile *create_tile_from_tileset(Tileset *tileset, int num_tile_x, int num_tile_y){
    Tile *tile = malloc(sizeof(Tile));
    tile->p_tileset     = tileset;
    tile->num_tile_x    = num_tile_x;
    tile->num_tile_y    = num_tile_y;
}

void draw_tile(Tile *tile, int pos_x, int pos_y){
    draw_tile_in_tileset(tile->p_tileset, tile->num_tile_x, tile->num_tile_y, pos_x, pos_y);
}

void destroy_tile(Tile *tile){
    free(tile);
}