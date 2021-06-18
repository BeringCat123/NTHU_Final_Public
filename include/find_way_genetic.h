#ifndef FIND_WAY_GENETIC_H
#define FIND_WAY_GENETIC_H
#include<stdio.h>
#include<stdlib.h>
#include"a_star.h"
#include"bool.h"
#include "SDL2/SDL.h"
#define GENE_NUM 20

struct gene{
    bool is_cacul;
    STEP path;
    int * target_list;
    int score;
};

typedef struct gene * GENE;

STEP find_way_genetic(MAP map,SDL_Window** window,SDL_Surface** screenSurface,SDL_Surface** gui_texture);

GENE gene_init(int,int *);

GENE cross(GENE,GENE,int);
#endif