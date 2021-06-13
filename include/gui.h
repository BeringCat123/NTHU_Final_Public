#ifndef gui_h
#define gui_h
#include "SDL2/SDL.h"
#include"bool.h"
#include"map.h"

#define block_size 24

bool init(SDL_Window** window,SDL_Surface** screenSurface,int w,int h);
bool loadMedia(SDL_Surface** gui_texture,char *file_name);
bool close(SDL_Window** window,SDL_Surface** gui_texture);
void show(MAP map,SDL_Window** window,SDL_Surface** screenSurface,SDL_Surface** gui_texture);

#endif