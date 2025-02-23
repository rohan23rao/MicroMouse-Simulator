#include "micromouseserver.h"
#include <iostream>
using namespace std;

void cardinal_cartesian(int &x, int &y, int current_direction, int (&position)[20][20]) {
    /* Function which updates the x and y values based on the current direction carinal->coordinate, and
     * updates the position matrix
     */
    switch (current_direction) {
        case 0:
            y++;
            break;
        case 1:
            x++;
            break;
        case 2:
            y--;
            break;
        case 3:
            x--;
            break;
    }
    position[x][y]++;
}



void microMouseServer::timesLRF(int &times_forward, int &times_left, int &times_right, int (position)[20][20],
    int current_direction, int x, int y) {
    /* Function with updates the times forward, left and right by checking the position matrix
     * If there is a wall, then the times is temporarily set to INT_MAX to override the other times the mouse has
     * been to the other locations.
     */
    switch (current_direction) {
        case 0:
            times_forward = position[x][y++];
            times_left = position[x--][y];
            times_right = position[x+1][y];
            break;
        case 1:
            times_forward = position[x+1][y];
            times_left = position[x][y+1];
            times_right = position[x][y-1];
            break;
        case 2:
            times_forward = position[x][y-1];
            times_left = position[x+1][y];
            times_right = position[x-1][y];
            break;
        case 3:
            times_forward = position[x+1][y];
            times_left = position[x][y-1];
            times_right = position[x][y+1];
            break;
    }
    if (isWallForward()) times_forward = INT_MAX;
    if (isWallLeft()) times_left = INT_MAX;
    if (isWallRight()) times_right = INT_MAX;
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

    static int position[20][20] = {{0}}; // Initialize position matrix
    int times_left = 0, times_right = 0, times_forward = 0; // initialize number of times left, right, forward
    static int x = 0, y = 0;
    static int ending = 0; // Ending case: 3 left turns in a row
    static int current_direction = 0; // 0 is facing north, 1 is facing east, 2 is facing south, 3 is facing west

//    cout << "Current Direction: " << current_direction << endl;
//    cout << "Ending: " << ending << endl;
//    cout << "Times Left: " << times_left << endl;
//    cout << "Times Right: " << times_right << endl;
//    cout << "Times Forward: " << times_forward << endl;
//    cout << position[0][1] << endl;
//    cout << "X, Y: " << x << ", " << y << endl;
    // Calculate the number of previous times right, left, and forward the mouse has been

    timesLRF(times_forward, times_left, times_right, position, current_direction, x, y); // Method to update refrences of the times left, right and forward


    if (!isWallLeft() && times_left<=times_right && times_left<=times_forward) { // check if wall to the left and if been left less times than forward and right

        turnLeft(); // turn left
        times_left++; // increase times_left
        current_direction = (current_direction + 3) % 4; // update current direction to left turn

        cardinal_cartesian(x, y, current_direction, position); // update position matrix and change cardinal directions to cartesian coordinates


        ending = 0; // set left turn ending to 0
    }

    else if (!isWallForward()  && times_forward<=times_right && times_forward<=times_left) {
        // move forward at end
        cardinal_cartesian(x, y, current_direction, position); // update position matrix and change cardinal directions to cartesian coordinates


        ending = 0; // set right turn ending to 0
    }

    else if (!isWallRight() && times_right <= times_left && times_right <= times_forward) {

        turnRight(); // turn right
        times_right++; // increase times been right

        current_direction = (current_direction + 1) % 4; // update current direction with turn right
        cardinal_cartesian(x, y, current_direction, position); // update position matrix and change cardinal directions to cartesian coordinates


        ending++; // right turn so update ending
    }
    else { // turn around
    turnRight();
    turnRight(); // turn around
    current_direction = (current_direction + 2) % 4; // update current direction

    cardinal_cartesian(x, y, current_direction, position); // update position matrix and change cardinal directions to cartesian coordinates

    ending = 0; // change ending right turns to 0
    }

    moveForward(); // move forward once

    if (ending == 3) {
    foundFinish(); // if three consectuive right turns, found finish
    }

}

