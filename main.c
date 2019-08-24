#include <stdio.h>
#include "header.h"

#include <SDL2/SDL.h>
int main(void)
{
    World *world = world_create(5);
    world_destroy(world);
    return 0;
}
