#ifndef FIND_WAY_H
#define FIND_WAY_H
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"a_star.h"
#include"bool.h"
#include "SDL2/SDL.h"

STEP find_way(MAP map,SDL_Window** window,SDL_Surface** screenSurface,SDL_Surface** gui_texture);

int get_distance(NODE node,int x2,int y2);

#endif




