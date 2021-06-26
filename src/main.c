#include<stdio.h>
#include<math.h>
#include<string.h>
#include"map.h"
#include"a_star.h"
#include "SDL2/SDL.h"
#include"bool.h"
#include"gui.h"
#include"find_way.h"
#include "find_way_genetic.h"

extern const int cost[6];

void read_config(int *,int *,int *,bool *);

int main(int argc, char **argv){
    SDL_Window* window = NULL;	
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* gui_texture = NULL;
    SDL_Event event;


    bool quit = false,*is_visted = NULL,use_gene,end = false;
    char ch;
    int i,j,start,last,times = 0,min,k,total_cost = 0,max_generation,gene_num,mutation_rate;
    MAP map = read_map();
    if(!map){
        printf("load map file error\n");
        exit(1);
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
    read_config(&max_generation,&gene_num,&mutation_rate,&use_gene);
    if(map -> is_target){
        if(use_gene){
            printf("GA\n");
            final = find_way_genetic(max_generation,gene_num,mutation_rate,map,&window,&screenSurface,&gui_texture);
        }else{
            printf("normal\n");
            final = find_way(map,&window,&screenSurface,&gui_texture);
        }
    }else{
        final = find_way(map,&window,&screenSurface,&gui_texture);
    }
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
        
        if(!(times % 5)){
            if(ptr){
                if(!end){
                    total_cost += (ptr -> node -> move_dir) == -1? 0:cost[ptr -> node -> move_dir];
                    if(ptr -> node -> move_dir == 5){
                        printf("%-15s","trun right");
                    }else if(ptr -> node -> move_dir == 4){
                        printf("%-15s","trun left");
                    }else if(ptr -> node -> move_dir == 0){
                        if(ptr -> node -> angle == 0 || ptr -> node -> angle == 270){
                            printf("%-15s","move forward");
                        }else{
                            printf("%-15s","move backward");
                        }
                    }else if(ptr -> node -> move_dir == 1){
                        if(ptr -> node -> angle == 0 || ptr -> node -> angle == 270){
                            printf("%-15s","move backward");
                        }else{
                            printf("%-15s","move forward");
                        }
                    }else if(ptr -> node -> move_dir == 2){
                        if(ptr -> node -> angle == 0 || ptr -> node -> angle == 270){
                            printf("%-15s","move left");
                        }else{
                            printf("%-15s","move right");
                        }
                    }else if(ptr -> node -> move_dir == 3){
                        if(ptr -> node -> angle == 0 || ptr -> node -> angle == 270){
                            printf("%-15s","move right");
                        }else{
                            printf("%-15s","move left");
                        }
                    }else{
                        printf("%-15s","stop");
                    }
                    printf("fuel cost:%3d\n",total_cost);
                }
                if(ptr -> next){
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
                    if(ptr -> node -> angle == 0){
                        map -> map[ptr -> node -> y1][ptr -> node -> x2] = 5;
                    }else if(ptr -> node -> angle == 90){
                        map -> map[ptr -> node -> y1][ptr -> node -> x1] = 5;
                    }else if(ptr -> node -> angle == 180){
                        map -> map[ptr -> node -> y2][ptr -> node -> x1] = 5;
                    }else if(ptr -> node -> angle == 270){
                        map -> map[ptr -> node -> y2][ptr -> node -> x2] = 5;
                    }
                }else{
                    end = true;
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

void read_config(int * max_generation,int * gene_num,int * mutation_rate,bool * use_gene){
    *max_generation = 10;
    *gene_num = 10;
    *mutation_rate = 25;
    *use_gene = true;
    char str[30], *ptr = NULL;
    int temp = 0;
    FILE * fptr = fopen("gene.ini","r");
    if(!fptr) return;
    while(!feof(fptr)){
        fscanf(fptr,"%s",str);
        printf("%s\n",str);
        if(str[0] == '#') continue;
        if(!(str - strstr(str,"use_genetic")) && strstr(str,"use_genetic")){
            ptr = strstr(str,"=");
            if(!ptr) continue;
            ptr = ptr  + 1;
            if(!strcmp(ptr,"false")){
                *use_gene = !(*use_gene);
            }
            
        }
        if(!(str - strstr(str,"max_generation")) && strstr(str,"max_generation")){
            ptr = strstr(str,"=");
            if(!ptr) continue;
            *max_generation = 0;
            ptr = ptr + 1;
            while(ptr[0]  != '\0'){
                *max_generation *= 10;
                *max_generation += ptr[0] - '0';
                ptr = ptr + 1;
            }
        }
        if(!(str - strstr(str,"gene_num")) && strstr(str,"gene_num")){
            ptr = strstr(str,"=");
            if(!ptr) continue;
            *gene_num = 0;           
            ptr = ptr + 1;
            while(ptr[0]  != '\0'){
                *gene_num *= 10;
                *gene_num += ptr[0] - '0';
                ptr = ptr + 1;
            }
            if(*gene_num&1){
                *gene_num = *gene_num + 1;
            }
        }
        if(!(str - strstr(str,"mutation_rate")) && strstr(str,"mutation_rate")){
            ptr = strstr(str,"=");
            if(!ptr) continue;
            *mutation_rate = 0;            
            ptr = ptr + 1;
            while(ptr[0] != '\0'){
                *mutation_rate *= 10;
                *mutation_rate += ptr[0] - '0';
                ptr = ptr + 1;
            }
            if(!(*mutation_rate)) *mutation_rate = 100;
        }
    }
}