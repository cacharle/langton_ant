#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(void)
{
    World *world = world_create(100);
    if (world == NULL)
    {
        fprintf(stderr, "Error: unable to initialize world");
        exit(EXIT_FAILURE);
    }
    State *state = graphics_init();
    state->world = world;
    graphics_run(state);
    graphics_quit(state);
    return EXIT_SUCCESS;
}
