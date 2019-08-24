#include <stdio.h>
#include "header.h"

#include <SDL2/SDL.h>
int main(void)
{
    /* World *world = world_create(5); */


    State *state = graphics_init();
    graphics_run(state);
    graphics_quit(state);

    /* world_destroy(world); */
    return 0;
}
