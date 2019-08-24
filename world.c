#include <stdlib.h>
#include <stddef.h>
#include "header.h"

static void turn_left(Ant *ant);
static void move_right(Ant *ant);
static void update_position(Ant *ant);

World *world_create(size_t size)
{
    if (size == 0)
        return NULL;
    World *world = (World*)malloc(sizeof(World));
    if (world == NULL)
        return NULL;
    world->grid = (Color**)malloc(sizeof(Color*) * size);
    if (world->grid == NULL)
    {
        free(world);
        return NULL;
    }
    for (size_t i = 0; i < size; i++)
    {
        world->grid[i] = (Color*)malloc(sizeof(Color) * size);
        if (world->grid[i] == NULL)
        {
            world_destroy(world);
            return NULL;
        }
        for (size_t j = 0; j < size; j++)
            world->grid[i][j] = COLOR_BLACK;
    }
    world->size = size;
    world->ant.x = size / 2;
    world->ant.y = size / 2;
    world->ant.direction = DIRECTION_UP;
    return world;
}

void world_destroy(World *world)
{
    if (world == NULL)
        return;
    for (size_t i = 0; i < world->size && world->grid[i] != NULL; i++)
        free(world->grid[i]);
    free(world->grid);
    free(world);
}

int world_next(World *world)
{
    if (world->ant.y >= world->size || world->ant.x >= world->size)
        return -1;
    Color *current = &world->grid[world->ant.y][world->ant.x];
    if (*current == COLOR_WHITE)
    {
        move_right(&world->ant);
        *current = COLOR_BLACK;
    }
    else if (*current == COLOR_BLACK)
    {
        turn_left(&world->ant);
        *current = COLOR_WHITE;
    }
    return 0;
}

static void move_right(Ant *ant)
{
    ant->direction = (ant->direction + 1) % 4;
    update_position(ant);
}

static void turn_left(Ant *ant)
{
    ant->direction = (ant->direction - 1) % 4;
    update_position(ant);
}

static void update_position(Ant *ant)
{
    switch (ant->direction)
    {
        case DIRECTION_UP:
            ant->y--;
            break;
        case DIRECTION_DOWN:
            ant->y++;
            break;
        case DIRECTION_LEFT:
            ant->x--;
            break;
        case DIRECTION_RIGHT:
            ant->x++;
            break;
    }
}
