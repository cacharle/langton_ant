#include <SDL2/SDL.h>
#include "header.h"

#define SET_DRAW_COLOR_WHITE(renderer) ( \
    SDL_SetRenderDrawColor((renderer), 255, 255, 255, SDL_ALPHA_OPAQUE))
#define SET_DRAW_COLOR_BLACK(renderer) ( \
    SDL_SetRenderDrawColor((renderer), 0, 0, 0, SDL_ALPHA_OPAQUE))

static void update_renderer(State *state);
static void event_handler(State *state);
static void destroy_state(State *state);
static void error_exit(char *message);
static void error_exit_state(State *state, char *message);

State *graphics_init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        error_exit("unable to initialize SDL");
    State *state = (State*)malloc(sizeof(State));
    state->window = SDL_CreateWindow("Langton's Ant", 10, 10, 480, 360, 0);
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
    state->running = true;
    while (state->running)
    {
        event_handler(state);
        update_renderer(state);
        SDL_Delay(30);
    }
}

static void update_renderer(State *state)
{
    SET_DRAW_COLOR_BLACK(state->renderer);
    SDL_RenderClear(state->renderer);

    SDL_RenderPresent(state->renderer);
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

