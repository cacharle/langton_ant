#ifndef __HEADER_H__
# define __HEADER_H__

# include <stdbool.h>
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
    size_t y;
    size_t x;
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
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    World *world;
} State;

// world.c
World *world_create(size_t size);
void world_destroy(World *world);
int world_next(World *world);

// graphics.c
State *graphics_init(void);
void graphics_quit(State *state);
void graphics_run(State *state);

#endif
