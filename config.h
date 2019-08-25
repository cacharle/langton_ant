#ifndef __CONFIG_H__
# define __CONFIG_H__

/* #define UNVISITED_CELL -1 */

#define WINDOW_TITLE "Langton's Ant"
#define WINDOW_X 10
#define WINDOW_Y 10
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define CELL_SIZE 4
#define TIME_WORLD_NEXT 10

#define MAIN_LOOP_DELAY 2
#define WORLD_STEP_SIZE 10

#define CYCLE_MAX 5
#define CYCLE_MIN 2


#define COLOR_RGB_UNVISITED 0x555555
#define COLOR_RGB_WHITE 0xFFFFFF
#define COLOR_RGB_BLACK 0x000000
#define COLOR_RGB_RED   0xFF0000
#define COLOR_RGB_GREEN 0x00FF00
#define COLOR_RGB_BLUE  0x0000FF

#define RGB_TO_NUM(rgb) rgb | 0xFF0000, rgb | 0x00FF00, rbg | 0x0000FF

#endif
