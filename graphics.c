#include <SDL2/SDL.h>
#include "header.h"

#define WINDOW_TITLE "Langton's Ant"
#define WINDOW_X 10
#define WINDOW_Y 10
#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 360
#define CELL_SIZE 5
#define TIME_WORLD_NEXT 0

#define SET_DRAW_COLOR_WHITE(renderer) ( \
    SDL_SetRenderDrawColor((renderer), 255, 255, 255, SDL_ALPHA_OPAQUE))
#define SET_DRAW_COLOR_BLACK(renderer) ( \
    SDL_SetRenderDrawColor((renderer), 0, 0, 0, SDL_ALPHA_OPAQUE))
#define SET_DRAW_COLOR_RED(renderer) ( \
    SDL_SetRenderDrawColor((renderer), 255, 0, 0, SDL_ALPHA_OPAQUE))

static void update_renderer(State *state);
static void draw_world(State *state);
static void event_handler(State *state);
static void destroy_state(State *state);
static void error_exit(char *message);
static void error_exit_state(State *state, char *message);

State *graphics_init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        error_exit("unable to initialize SDL");
    State *state = (State*)malloc(sizeof(State));
    state->window = SDL_CreateWindow(
            WINDOW_TITLE, WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (state->window == NULL)
        error_exit("unable to create window");
    state->renderer = SDL_CreateRenderer(state->window, -1, 0);
    if (state->renderer == NULL)
        error_exit_state(state, "unable to create renderer");
    state->running = false;
    state->world = NULL;
    return state;
}

void graphics_quit(State *state)
{
    if (state != NULL)
        destroy_state(state);
    SDL_Quit();
}

void graphics_run(State *state)
{
    unsigned int world_next_time = 0, world_current_time;
    state->running = true;
    while (state->running)
    {
        event_handler(state);
        update_renderer(state);
        world_current_time = SDL_GetTicks();
        if (SDL_TICKS_PASSED(world_current_time, world_next_time))
        {
            world_next_time = world_current_time + TIME_WORLD_NEXT;
            if (world_next(state->world) < 0)
            {
                SDL_Delay(1000);
                state->running = false;
            }
        }
        SDL_Delay(10);
    }
}

static void update_renderer(State *state)
{
    if (SET_DRAW_COLOR_BLACK(state->renderer) < 0)
        error_exit_state(state, "unable to set render clear color");
    if (SDL_RenderClear(state->renderer) < 0)
        error_exit_state(state, "unable to clear render");
    draw_world(state);
    SDL_RenderPresent(state->renderer);
}

static void draw_world(State *state)
{
    Color current;
    SDL_Rect tmp_rect;
    tmp_rect.w = CELL_SIZE;
    tmp_rect.h = CELL_SIZE;

    for (size_t i = 0; i < state->world->size; i++)
    {
        tmp_rect.x = i * CELL_SIZE;
        for (size_t j = 0; j < state->world->size; j++)
        {
            current = state->world->grid[i][j];
            if (i == state->world->ant.y && j == state->world->ant.x)
                SET_DRAW_COLOR_RED(state->renderer);
            else if (current == COLOR_WHITE)
                SET_DRAW_COLOR_WHITE(state->renderer);
            else if (current == COLOR_BLACK)
                SET_DRAW_COLOR_BLACK(state->renderer);
            tmp_rect.y = j * CELL_SIZE;
            SDL_RenderFillRect(state->renderer, &tmp_rect);
        }
    }
}

static void event_handler(State *state)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                state->running = false;
                break;
        }
    }
}

static void destroy_state(State *state)
{
    if (state == NULL)
        return;
    world_destroy(state->world);
    SDL_DestroyWindow(state->window);
    SDL_DestroyRenderer(state->renderer);
}

static void error_exit(char *message)
{
    SDL_Log("ERROR: %s: %s", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

static void error_exit_state(State *state, char *message)
{
    destroy_state(state);
    error_exit(message);
}

