/**
 * @file tileset.h
 * @author Nathan Schiffmacher (nathan.schiffmacher@student.isae-supaero.fr)
 * @brief 
 * @date 22-03-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TILESET_H
#define TILESET_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

typedef struct {
    SDL_Renderer *renderer;         // the renderer onto which the tiles will be drawn
    SDL_Texture *texture;           // The texture corresponding to the whole tileset
    int width, height;              // The width and the height of the whole tileset
    int tile_width, tile_height;    // the width and the height of a single sprite
    int num_tiles_x, num_tiles_y;   // the number of cols and rows in the Tileset
    
    Uint32 format; // texture parameter
    int access; // texture parameter
    // int total_sprites;              // Useless ? 
} Tileset;

typedef struct { // This structure can be used to keep a specific part of the tileset in a specific variable, for instance you could keep a grass block from a tileset variable ts in a "grass" tile
    Tileset *p_tileset; // A pointer to the current 
    int num_tile_x, num_tile_y;
} Tile;


/**
 * @brief Loads a tileset in the memory
 * 
 * @param renderer      the renderer
 * @param filename      the filename of the tileset
 * @param num_tiles_x   the number of cols in the tileset
 * @param num_tiles_y   the number of rows in the tileset
 * @return Tileset* 
 */
Tileset *load_tileset(SDL_Renderer *renderer, char *filename, int num_tiles_x, int num_tiles_y);

/**
 * @brief Draws a tile (num_tile_x, num_tile_y) on a renderer at a specific location (pos_x, pos_y)
 * 
 * @param tileset 
 * @param renderer 
 * @param num_tile_x 
 * @param num_tile_y 
 * @param pos_x 
 * @param pos_y 
 */
void draw_tile_in_tileset(Tileset *tileset, int num_tile_x, int num_tile_y, int pos_x, int pos_y);

/**
 * @brief Removes the tileset from memory
 * 
 * @param tileset 
 */
void destroy_tileset(Tileset *tileset);


/**
 * @brief Create a tile from tileset object
 * 
 * @param tileset a pointer to an existing tileset
 * @param num_tile_x col number in the tileset for the current tile
 * @param num_tile_y row number in the tileset for the current tile
 * @return Tile* 
 */
Tile *create_tile_from_tileset(Tileset *tileset, int num_tile_x, int num_tile_y);

/**
 * @brief Draws a specif tile on the screen at pos (pos_x, pos_y)
 * 
 * @param tile 
 * @param pos_x 
 * @param pos_y 
 */
void draw_tile(Tile *tile, int pos_x, int pos_y);

/**
 * @brief Removes a tile from memory
 * 
 * @param tile 
 */
void destroy_tile(Tile *tile);

#endif