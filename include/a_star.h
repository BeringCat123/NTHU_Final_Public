#ifndef a_star_h
#define a_star_h
#include"map.h"
#include"bool.h"
#include "SDL2/SDL.h"
struct node{
    int x1;
    int y1;
    int x2;
    int y2;
    int angle;
    int move_dir;
    struct node * parent;
};

typedef struct node * NODE;

struct step{
    bool is_lowest;
    int cost;
    struct step * next;
    NODE node;
};

typedef struct step * STEP;

typedef char byte;

NODE find_car(MAP);

NODE move_forward(NODE);
NODE move_backward(NODE);
NODE move_left(NODE);
NODE move_right(NODE);
NODE turn_count(NODE);
NODE turn_clock(NODE);

STEP A_star(MAP,int,int,int,SDL_Window** window,SDL_Surface** screenSurface,SDL_Surface** gui_texture);

byte can_move(MAP,NODE);

bool node_is_same(NODE,NODE);
#endif