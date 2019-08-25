#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(void)
{
    World *world = world_create(150, "LR");
    if (world == NULL)
    {
        fprintf(stderr, "Error: unable to initialize world");
        exit(EXIT_FAILURE);
    }
    State *state = graphics_init();
    state->world = world;
    graphics_run(state);
    graphics_quit(state);
    /* world_destroy(world); */
    return EXIT_SUCCESS;
}
