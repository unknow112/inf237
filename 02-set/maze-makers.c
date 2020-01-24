#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


int field[50][50]; 
int H=0;
int W=0;

int visited[2500];
int visited_c = 0; 
int is_cyclic = 0;
int exits_found = 0;   

int hash_pos(int x, int y)
{
        return y*W + x ;
}

int n2i(char a)
{
        if (a <= '9') {
                return a-'0';
        } else { 
                return 10 + a - 'A';
        }
}

const int DOWN= 1<<1;
const int UP= 1<<3;
const int LEFT = 1 ;
const int RIGHT = 1<<2;

int can_down(unsigned int a)
{
        return !( a & DOWN);
}
int can_up(unsigned int a)
{
        return !( a & UP);
}
int can_left(unsigned int a)
{
        return !( a & LEFT);
}
int can_right(unsigned int a)
{
        return !( a & RIGHT);
}

int is_exit(int x, int y)
{
        if (!(x == 0 || y == 0 || y == H-1 || x == W - 1)){
                return 0;
        }
        if ( x == 0 && can_left(field[y][x])){
                return 1;
        }
        if ( y == 0 && can_up(field[y][x])){
                return 1;
        }
        if ( x == W -1 && can_right(field[y][x])){
                return 1;
        }
        if ( y == H-1 && can_down(field[y][x])){
                return 1;
        }
        
        return 0 ;
}

int is_out_of_maze(int x, int y)
{
        if (x < 0 || y < 0 || x >= W || y >= H ){
                return 1;
        } else { 
                return 0;
        }
}

void solve( int x, int y, int skip )
{
        if (is_out_of_maze(x,y)){
                return;
        }
        if (visited[hash_pos(x,y)]){
                is_cyclic = 1 ;
                return;
        }
        visited[hash_pos(x,y)] = 1;
        visited_c++;
         
        exits_found += is_exit(x, y);

        int pos = field[y][x] + skip;        

        if (can_left(pos)){
                solve(x-1, y, RIGHT);
        }
        if (can_up(pos)){
                solve(x, y-1, DOWN);
        }
        if (can_right(pos)){
                solve(x+1, y, LEFT);
        }
        if (can_down(pos)){
                solve(x, y+1, UP);
        }
        
}



int load_and_solve()
{
        for (int y = 0; y< H ; y++){
                char line[52];
                fgets(line, 52, stdin);
                for (int x = 0 ; x < W ; x++){
                        field[y][x] = n2i(line[x]);
                }
        }
        
        solve(0,0,0);

        if (exits_found == 1 ){
                printf("NO SOLUTION\n");
                return 0;
        }       
        if (exits_found == 2){
                if (visited_c == H * W ){
                        if (is_cyclic){
                                printf("MULTIPLE PATHS\n");
                                return 0;
                        } else {
                                printf("MAZE OK\n");
                                return 0;
                        }
                } else {
                        printf("UNREACHABLE CELL\n");
                        return 0;
                }
        }
        

        for (int y = 0; y< H ; y++){
                for (int x = 0 ; x < W ; x++){
                        if (!(visited[hash_pos(x,y)])){
                                solve(x,y,0);
                                switch(exits_found){
                                case 2:
                                        printf("UNREACHABLE CELL\n");
                                        return 0;
                                case 1:
                                        printf("NO SOLUTION\n");
                                        return 0;
                                }
                        }
                }
        }
        assert(!"whoa dont go here!\n");
        return 0;                 
}



int main(){

        while(1){

                scanf("%d %d\n", &H, &W);
                if (H == 0 || W == 0){
                        return 0;
                }
                memset(visited,0,2500);
                visited_c = 0; 
                is_cyclic = 0;
                exits_found = 0;   
                load_and_solve();
        }
}
