#ifndef map_h
#define map_h
#include<stdio.h>
#include<stdlib.h>
#include"bool.h"
#include "SDL2/SDL.h"
struct map_s{
    int **map;
    int x;
    int y;
    bool is_target;
    int n_target;
    int *target_x;
    int *target_y;
};

typedef struct map_s * MAP;

MAP read_map();

#endif