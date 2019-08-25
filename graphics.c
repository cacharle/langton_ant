#include <SDL2/SDL.h>
#include "config.h"
#include "header.h"

#define RGB_RED_MASK   0xFF0000
#define RGB_GREEN_MASK 0x00FF00
#define RGB_BLUE_MASK  0x0000FF
#define RGB_EXTRACT_RED(rgb)   ((rgb & RGB_RED_MASK) >> (8 * 2))
#define RGB_EXTRACT_GREEN(rgb) ((rgb & RGB_GREEN_MASK) >> (8 * 1))
#define RGB_EXTRACT_BLUE(rgb)  (rgb & RGB_BLUE_MASK)

#define SET_DRAW_COLOR_WHITE(renderer) ( \
    SDL_SetRenderDrawColor((renderer), 255, 255, 255, SDL_ALPHA_OPAQUE))
#define SET_DRAW_COLOR_BLACK(renderer) ( \
    SDL_SetRenderDrawColor((renderer), 50, 50, 50, SDL_ALPHA_OPAQUE))
#define SET_DRAW_COLOR_RED(renderer) ( \
    SDL_SetRenderDrawColor((renderer), 255, 0, 0, SDL_ALPHA_OPAQUE))

static void update_renderer(State *state);
static void draw_world(State *state);
static void event_handler(State *state);
static void set_cell_draw_color(State *state, Color color);
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
        world_current_time = SDL_GetTicks();
        if (SDL_TICKS_PASSED(world_current_time, world_next_time))
        {
            update_renderer(state);
            world_next_time = world_current_time + TIME_WORLD_NEXT;
            for (int i = 0; i < WORLD_STEP_SIZE; i++)
                if (world_next(state->world) < 0)
                {
                    SDL_Delay(1000);
                    state->running = false;
                    break;
                }
        }
        SDL_Delay(MAIN_LOOP_DELAY);
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
            set_cell_draw_color(state, current);
            current = state->world->grid[i][j];
            tmp_rect.y = j * CELL_SIZE;
            SDL_RenderFillRect(state->renderer, &tmp_rect);
        }
    }
    /* printf("\n"); */
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

static void set_cell_draw_color(State *state, Color color)
{
    long unsigned int rgb = 0;
    switch (color)
    {
        case COLOR_UNVISITED:
            rgb = COLOR_RGB_UNVISITED;
            break;
        case COLOR_WHITE:
            rgb = COLOR_RGB_WHITE;
            break;
        case COLOR_BLACK:
            rgb = COLOR_RGB_BLACK;
            break;
        case COLOR_RED:
            rgb = COLOR_RGB_RED;
            break;
        case COLOR_GREEN:
            rgb = COLOR_RGB_GREEN;
            break;
        case COLOR_BLUE:
            rgb = COLOR_RGB_BLUE;
            break;
        default:
            error_exit_state(state, "invalid color");
    }
    /* printf("rgb: %06lx, %06lx, %06lx\n", RGB_EXTRACT_RED(rgb), */
    /*         RGB_EXTRACT_GREEN(rgb), RGB_EXTRACT_BLUE(rgb)); */
    SDL_SetRenderDrawColor(state->renderer, RGB_EXTRACT_RED(rgb),
                           RGB_EXTRACT_GREEN(rgb), RGB_EXTRACT_BLUE(rgb),
                           SDL_ALPHA_OPAQUE);
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

