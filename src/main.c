#include<stdio.h>
#include<math.h>
#include<limits.h>
#include"map.h"
#include"a_star.h"
#include "SDL2/SDL.h"
#include"bool.h"
#include"gui.h"
#include"find_way.h"

extern const int cost[6];



int main(int argc, char **argv){
    SDL_Window* window = NULL;	
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* gui_texture = NULL;
    SDL_Event event;

    bool quit = false,*is_visted = NULL;
    int i,j,start,last,times = 0,min,k,total_cost = 0;
    MAP map = read_map();
    if(!map){
        printf("load map file error");
        exit(1);
    }
    
    
    for(i = 0;i < map -> y;i++){
        for(j = 0;j < map -> x;j++){
            printf("%d ",map -> map[i][j]);
        }
        printf("\n");
    }
    NODE init_pos = find_car(map);
    NODE new_pos = NULL;
    STEP final  = NULL;
    STEP ptr = NULL;
    if(!init(&window,&screenSurface,map -> x * block_size ,map -> y * block_size)){
        printf("SDL init error\n");
        exit(-2);
    }
    if(!loadMedia(&gui_texture,"texture.bmp")){
        printf("SDL load inage error\n");
        exit(-3);
    } 
    final = find_way(map,&window,&screenSurface,&gui_texture);
    ptr = final;
    for(i =0;i < map-> y;i++){
        for(j = 0;j <map -> x;j++){
            if(map -> map[i][j] == 4|| map -> map[i][j] == 5) map -> map[i][j] = 1;
        }
    }
    while(!quit){
        start = SDL_GetTicks();
		while( SDL_PollEvent( &event ) != 0 ){
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        show(map,&window,&screenSurface,&gui_texture);
        
        if(!(times % 2)){
            if(ptr && ptr -> next){
                total_cost += (ptr -> node -> move_dir) == -1? 0:cost[ptr -> node -> move_dir];
                printf("%d %d\n",ptr -> node -> move_dir,total_cost);
                for(i = 0;i < map-> n_target;i++){
                    map -> map[map -> target_y[i]][map -> target_x[i]] = 3;
                }
                for(i = ptr -> node -> y1;i < ptr -> node -> y2 + 1;i++){
                    for(j = ptr -> node -> x1;j <ptr -> node -> x2 + 1;j++){
                        map -> map[i][j] = 7;
                    }
                }
                for(i = init_pos -> y1;i < init_pos -> y2 + 1;i++){
                    for(j = init_pos -> x1;j <init_pos -> x2 + 1;j++){
                        map -> map[i][j] = 6;
                    }
                }
                ptr = ptr -> next;
                for(i = ptr -> node -> y1;i < ptr -> node -> y2 + 1;i++){
                    for(j = ptr -> node -> x1;j <ptr -> node -> x2 + 1;j++){
                        map -> map[i][j] = 2;
                    }
                }
            }
        }
        times++;
        last = SDL_GetTicks();
		if(last - start < 100 ) SDL_Delay(100 - last + start);
	}
    close(&window,&gui_texture);
    return 0;
}

