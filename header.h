#ifndef __HEADER_H__
# define __HEADER_H__

# include <stddef.h>
# include <SDL2/SDL.h>

typedef enum
{
    COLOR_WHITE,
    COLOR_BLACK
} Color;

typedef enum
{
    DIRECTION_UP = 0,  // turning the ant relies on the directions values
    DIRECTION_RIGHT = 1,
    DIRECTION_DOWN = 2,
    DIRECTION_LEFT = 3
} Direction;

typedef struct
{
    int y;
    int x;
    Direction direction;
} Ant;

typedef struct
{
    Color **grid;
    Ant ant;
    size_t size;
} World;

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} State;

// world.c
World *world_create(size_t size);
void world_destroy(World *world);
void world_next(World *world);


#endif
