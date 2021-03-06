/**
 * @file app.h
 * @author Nathan Schiffmacher (nathan.schiffmacher@student.isae-supaero.fr)
 * @brief 
 * @date 19-03-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "timekeeper.h"

#define WIDTH 1280
#define HEIGHT 720

#define MAX_TITLE_LENGTH 200
#define DEBUG_FONT_SIZE 15


typedef struct {
    int rendererFlags;
    int windowFlags;
    char windowTitle[MAX_TITLE_LENGTH];

    SDL_Window *window;
    SDL_Renderer *renderer;

    TimeKeeper *keeper;

    TTF_Font *debug_font;



    bool continuer;
} App;

#endif