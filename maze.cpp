#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "status.hpp"
#include "stack.hpp"
#include "bitmap_2d.hpp"

typedef Bitmap2D Maze;

Status maze_start(Maze maze, Pos &p) {
    if (maze.w < 1 && maze.h < 1) return ERROR;
    p.x = 0;
    p.y = 0;
    return OK;
}

Status maze_end(Maze maze, Pos &p) {
    if (maze.w < 1 && maze.h < 1) return ERROR;
    p.x = maze.w - 1;
    p.y = maze.h - 1;
    return OK;
}

Pos elem_to_pos(Maze maze, ElemType e) {
    Pos p;
    p.x = e % maze.w;
    p.y = e / maze.w;
    return p;
}

ElemType pos_to_elem(Maze maze, Pos p) {
    ElemType e;
    e = p.y * maze.w + p.x;
    return e;
}

Status check_pos(Maze maze, Bitmap2D mark, Pos p) {
    int b;
    if(!Bitmap2DGet(mark, p, b) || b == BIT_ON) return FALSE;
    if(!Bitmap2DGet(maze, p, b) || b == BIT_ON) return FALSE;
    return TRUE;
}

Status get_next_pos(Maze maze, Bitmap2D mark, Pos cur, Pos &next) {
    // Right
    next.x = cur.x + 1;
    next.y = cur.y;
    if (check_pos(maze, mark, next)) return TRUE;

    // Down
    next.x = cur.x;
    next.y = cur.y + 1;
    if (check_pos(maze, mark, next)) return TRUE;

    // Left
    if (cur.y < maze.h-2) {
        next.x = cur.x - 1;
        next.y = cur.y;
        if (check_pos(maze, mark, next)) return TRUE;
    }

    // Top
    if (cur.x < maze.w-2){
        next.x = cur.x;
        next.y = cur.y - 1;
        if (check_pos(maze, mark, next)) return TRUE;
    }

    // No way
    return FALSE;
}

void print_maze(Maze maze, Bitmap2D mark) {
    Pos p; p.x = 0; p.y = 0;
    int b;
    for(int i = 0; i < maze.w+2; ++i) printf("\033[47m  \033[0m");
    printf("\n");
    for (p.y = 0; p.y < maze.h; ++p.y) {
        for (p.x = 0; p.x < maze.w; ++p.x) {
            if(p.x == 0) {
                if (p.y == 0) printf("\033[42m  \033[0m");
                else printf("\033[47m  \033[0m");
            } 
            Bitmap2DGet(maze, p, b);
            if (b == BIT_ON) printf("\033[47m  \033[0m");
            else {
                Bitmap2DGet(mark, p, b);
                if (b == BIT_ON) printf("\033[42m  \033[0m");
                else printf("  ");
            };
            if(p.x == maze.w-1){
                if (p.y == maze.h-1) printf("\033[42m  \033[0m");
                else printf("\033[47m  \033[0m"); 
            } 
        }
        printf("\n");
    }
    for(int i = 0; i < maze.w+2; ++i) printf("\033[47m  \033[0m");
    printf("\n");
}

Status print_e(ElemType e) {
    printf("->%d", e);
    return OK;
}

Status InitMaze(Maze &maze, int w, int h, int l) {
    srand(time(0));
    if (!InitBitmap2D(maze, w, h)) return ERROR;
    Pos p; p.x = 0; p.y = 0;
    for (p.y = 0; p.y < maze.h; ++p.y) {
        for (p.x = 0; p.x < maze.w; ++p.x) {
            int b = BIT_OFF;
            int r = rand();
            if (r % l == 0) b = BIT_ON;
            Bitmap2DSet(maze, p, b);
        }
    }
    p.x = 0; 
    p.y = 0;
    Bitmap2DSet(maze, p, BIT_OFF);
    p.x = maze.w - 1; 
    p.y = maze.h - 1;
    Bitmap2DSet(maze, p, BIT_OFF);
    return OK;
}

void ExploreMaze(Maze maze) {
    SqStack path;
    Pos cur, end, next;
    Bitmap2D mark, path_mark;
    ElemType e;
    Status dead = FALSE;

    InitStack(path);
    InitBitmap2D(mark, maze.w, maze.h);
    InitBitmap2D(path_mark, maze.w, maze.h);

    maze_start(maze, cur);
    maze_end(maze, end);
    Bitmap2DSet(mark, cur, BIT_ON);
    Bitmap2DSet(path_mark, cur, BIT_ON);
    Push(path, pos_to_elem(maze, cur));

    printf("\033[?25l");
    printf("\033[2J\033[0;0H");
    print_maze(maze, path_mark);
    printf("cur: %d, %d\033[K\n", cur.x, cur.y);
    StackTraverse(path, print_e);
    printf("\033[K\n");

    while(dead != TRUE && !PosEqual(cur, end)) {
        if(!get_next_pos(maze, mark, cur, next)) { 
            Pop(path, e);
            Bitmap2DSet(path_mark, elem_to_pos(maze, e), BIT_OFF);
            if (StackEmpty(path)) {
                dead = TRUE;
            } else {
                GetTop(path, e);
                cur = elem_to_pos(maze, e);
            }
        } else {
            Push(path, pos_to_elem(maze, next));
            Bitmap2DSet(mark, next, BIT_ON);
            Bitmap2DSet(path_mark, next, BIT_ON);
            cur = next;
        }
        printf("\033[0;0H");
        print_maze(maze, path_mark);
        printf("cur: %d, %d\n\033[K", cur.x, cur.y);
        StackTraverse(path, print_e);
        printf("\n\033[K");
        usleep(50000);
    }

    if (dead == TRUE) printf("no way!\n");
    else printf("find the outlet!\n");
    printf("\033[?25h");
}

int main() {
    int w, h, l;
    printf("请输入迷宫参数<宽,高,稀疏程度>, 以空格分隔：");
    scanf("%d %d %d", &w, &h, &l);
    Maze m;
    InitMaze(m, w, h, l);
    ExploreMaze(m);
}
