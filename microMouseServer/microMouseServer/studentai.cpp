#include <iostream>
#include "micromouseserver.h"

void turn_store(int (&position)[20][20], int &current_facing, int moving_direction, int x, int y) {
    switch (current_facing) {
        case 0:
            switch (moving_direction) {
                case 0:
                    y++;
                    break;
                case 1:
                    current_facing = 1;
                    break;
                case 2:
                    current_facing = 3;
                    break;
            }
            break;
        case 1:
            switch (moving_direction) {
                case 0:
                    x++;
                    break;
                case 1:
                    current_facing = 2;
                    break;
                case 2:
                    current_facing = 0;
                    break;
            }
            break;
        case 2:
            switch (moving_direction) {
                case 0:
                    y--;
                    break;
                case 1:
                    current_facing = 3;
                    break;
                case 2:
                    current_facing = 1;
                    break;
            }
            break;
        case 3:
            switch (moving_direction) {
                case 0:
                    x--;
                    break;
                case 1:
                    current_facing = 0;
                    break;
                case 2:
                    current_facing = 2;
                    break;
            }
            break;
    }

}


void microMouseServer::studentAI()
{
/*
 * The following are the eight functions that you can call. Feel free to create your own fuctions as well.
 * Remember that any solution that calls moveForward more than once per call of studentAI() will have points deducted.
 *
 *The following functions return if there is a wall in their respective directions
 *bool isWallLeft();
 *bool isWallRight();
 *bool isWallForward();
 *
 *The following functions move the mouse. Move forward returns if the mouse was able to move forward and can be used for error checking
 *bool moveForward();
 *void turnLeft();
 *void turnRight();
 *
 * The following functions are called when you need to output something to the UI or when you have finished the maze
 * void foundFinish();
 * void printUI(const char *mesg);
*/
    static int position[20][20] = {{0}};
    static int ending = 0;
    position[0][0] = 0;
    static int x = 0, y = 0;
    static int current_facing = 0; // 0 is facing north, 1 is facing east, 2 is facing south, 3 is facing west
//    static int moving_direction = 0;  // 0 is move forward, 1 is turn right, 2 is turn left

    if (!isWallLeft()) {
//    turnLeft();
//    moveForward();
    turn_store(position, current_facing, 2, x, y);
    turn_store(position, current_facing, 0, x, y);
    ending = 0;
    }
    else if (!isWallForward()) {
    moveForward();
    ending = 0;
    }
    else if (!isWallRight()) {
    turnRight();
    moveForward();
    ending++;
    }
    else { // turn around
    turnRight();
    turnRight();
    moveForward();
    ending = 0;
    }

    if (ending == 3) {
    foundFinish();
    }
}
