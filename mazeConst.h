/*
 * mazeConst.h
 *
 *  Created on: Jun 11, 2014
 *      Author: Elis Pogace
 */

#ifndef MAZECONST_H_
#define MAZECONST_H_

#define PX_PER_UNIT 40
#define MAZE_HEIGHT 20
#define MAZE_WIDTH 20
#define MAZE_HEIGHT_PX PX_PER_UNIT*MAZE_HEIGHT
#define MAZE_WIDTH_PX PX_PER_UNIT*MAZE_WIDTH

#define WALL_THICKNESS_PX 2

#define DISPLAY_WINDOW_NAME "Micro Mouse Simulator"
#define SAVE_FILE "mazeFile.txt"

#define MOUSE_OUTLINE_THICKNESS 9
#define MOUSE_RADIUS 7

#define UI_INPUT_LOCATION Point(0,MAZE_HEIGHT_PX-PX_PER_UNIT/4)
#define GUI_MAXLEN 40
#define GUI_MAXLINE 18

#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3



#endif /* MAZECONST_H_ */
