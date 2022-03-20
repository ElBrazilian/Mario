/**
 * @file main.h
 * @author Nathan Schiffmacher (nathan.schiffmacher@student.isae-supaero.fr)
 * @brief 
 * @date 19-03-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "game.h"

#define WIDTH 1280
#define HEIGHT 720

#define MAX_TITLE_LENGTH 200

typedef struct {
    int rendererFlags;
    int windowFlags;
    char windowTitle[MAX_TITLE_LENGTH];

    SDL_Window *window;
    SDL_Renderer *renderer;

} App;

#endif