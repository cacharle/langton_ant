#include <stdlib.h>
#include <stddef.h>
#include "header.h"
#include "config.h"

static Cycle parse_cycle(char *cycle_str);
static void turn_left(Ant *ant);
static void move_right(Ant *ant);
static void update_position(Ant *ant);

World *world_create(size_t size, char *cycle_str)
{
    if (size == 0)
        return NULL;
    World *world = (World*)malloc(sizeof(World));
    if (world == NULL)
        return NULL;
    if ((world->cycle = parse_cycle(cycle_str)) == NULL)
        return NULL;
    world->cycle_len = strlen(cycle_str);
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
            world->grid[i][j] = COLOR_UNVISITED;
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
    free(world->cycle);
    free(world);
}

int world_next(World *world)
{
    if (world->ant.y >= world->size || world->ant.x >= world->size)
        return -1;
    Color *current = &world->grid[world->ant.y][world->ant.x];
    if (*current == COLOR_UNVISITED)
        *current = 1;
    switch (world->cycle[*current])
    {
        case DIRECTION_LEFT:
            turn_left(&world->ant);
            break;
        case DIRECTION_RIGHT:
            move_right(&world->ant);
            break;
        default:
            return -1;
    }
    *current = (*current + 1) % world->cycle_len;
    return 0;
}

static Cycle parse_cycle(char *cycle_str)
{
    for (int i = 0; cycle_str[i]; i++)
        if (cycle_str[i] != 'L' && cycle_str[i] != 'R')
            return NULL;
    size_t cycle_len = strlen(cycle_str);
    if (cycle_len > CYCLE_MAX || cycle_len < CYCLE_MIN)
        return NULL;
    Cycle cycle = (Cycle)malloc(sizeof(Direction) * cycle_len);
    if (cycle == NULL)
        return NULL;
    for (int i = 0; cycle_str[i]; i++)
        cycle[i] = cycle_str[i] == 'L' ? DIRECTION_LEFT : DIRECTION_RIGHT;
    return cycle;
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
