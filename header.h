#ifndef __HEADER_H__
# define __HEADER_H__

# include <stdbool.h>
# include <stddef.h>
# include <SDL2/SDL.h>

/* typedef enum */
/* { */
/*     COLOR_RGB_WHITE = 0xFFFFFF, */
/*     COLOR_RGB_BLACK = 0x000000, */
/*     COLOR_RGB_RED   = 0xFF0000, */
/*     COLOR_RGB_GREEN = 0x00FF00, */
/*     COLOR_RGB_BLUE  = 0x0000FF */
/* } ColorRGB; */

typedef enum
{
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_BLACK,
    COLOR_WHITE,
    COLOR_UNVISITED
} Color;

typedef enum
{
    DIRECTION_UP = 0,  // turning the ant relies on the directions values
    DIRECTION_RIGHT = 1,
    DIRECTION_DOWN = 2,
    DIRECTION_LEFT = 3
} Direction;

typedef Direction* Cycle;

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
    Cycle cycle;
    size_t cycle_len;
} World;

typedef struct
{
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    World *world;
} State;

// world.c
World *world_create(size_t size, char *cycle_str);
void world_destroy(World *world);
int world_next(World *world);

// graphics.c
State *graphics_init(void);
void graphics_quit(State *state);
void graphics_run(State *state);

#endif
