#include <iostream>
using namespace std;
#include "micromouseserver.h"
//void turn_store(int (&position)[20][20], int &current_facing, int moving_direction, int x, int y);

int *turn_store(int &current_facing, int moving_direction, int x, int y) {
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
    static int xy[2] = {x, y};
    return xy;

}


int timesLeft_(int (&position)[20][20], int current_facing, int x, int y, bool is_left) {
    if (is_left) {
        return INT_MAX;
    }
    current_facing = ((current_facing+3) % 4);
    int *ptr = turn_store(current_facing, 0, x, y);
    return position[ptr[0]][ptr[1]];
}

bool timesForward_(int (&position)[20][20], int current_facing, int x, int y, bool is_forward) {
    if (is_forward) {
        return INT_MAX;
    }
    current_facing = ((current_facing+1) % 4);
    int *ptr = turn_store(current_facing, 0, x, y);
    return position[ptr[0]][ptr[1]];
}

bool timesRight_(int (&position)[20][20], int current_facing, int x, int y, bool is_right) {
    if (is_right) {
        return INT_MAX;
    }
    current_facing = ((current_facing+2) % 4);
    int *ptr = turn_store(current_facing, 0, x, y);
    return position[ptr[0]][ptr[1]];
}

void update(int (&position)[20][20], int current_facing, int moving_direction, int x, int y) {
    int *ptr = turn_store(current_facing, moving_direction, x, y);
    position[ptr[0]][ptr[1]]++;
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
//    bool wall_locations[3] = {isWallLeft(), isWallRight(), isWallForward()};
    bool timesLeft = timesLeft_(position, current_facing, x, y, isWallLeft());
    bool timesRight = timesRight_(position, current_facing, x, y, isWallRight());
    bool timesForward = timesForward_(position, current_facing, x, y, isWallForward());
    cout << "Times Left: " << timesLeft << endl;
    cout << "Times Right: " << timesRight << endl;
    cout << "Times Forward: " << timesForward << endl;
    if (!isWallLeft() && timesLeft<=timesForward && timesForward<=timesRight) {
//    turnLeft();
//    moveForward();
        update(current_facing, 2, x, y);
        turnLeft();
        update(current_facing, 0, x, y);
        moveForward();

        ending = 0;
    }

    else if (!isWallForward() && timesForward<=timesRight) {
        update(current_facing, 0, x, y);
        moveForward();
        ending = 0;
    }

    else if (!isWallRight()) {
        update(current_facing, 1, x, y);
        turnRight();
        update(current_facing, 0, x, y);
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
