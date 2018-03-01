#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "simpletools.h"
#include "abdrive.h"
#include "simpletools.h"
#include "ping.h"
#include "basics.h"

enum dir {
    up,
    down,
    left,
    right
};

struct node {
    int x;
    int y;
    struct node *connected[20];
    int counter;
};


int counter = 0;
enum dir direction = up; // direction can be 'u' 'd' 'l' 'r'
struct node current_node;
const int SQUARE_LENGTH = 124; // in ticks
const int LR_THRESHOLD = 45; // in LRdis()
const int FRONT_THRESHOLD = 25; // in cm


int front_clear() {
    int front_dis = ping_cm(8);
    printf("Front distance is: %d\n", front_dis);
    if (front_dis >= FRONT_THRESHOLD) {
        return 1;
    }
    return 0;
}

int left_clear() {
    float left_dis = leftDis();
    printf("Left distance is: %f\n", left_dis);
    if (left_dis >= LR_THRESHOLD) {
        return 1;
    }
    return 0;
}

int right_clear() {
    float right_dis = rightDis();
    printf("Right distance is: %f\n", right_dis);
    if (right_dis >= LR_THRESHOLD) {
        return 1;
    }
    return 0;
}

void turn_right_counter() {
    turn_right();
    counter++;
}

void turn_left_counter() {
    turn_left();
    counter--;
}

void move_forward() {
    drive_goto(SQUARE_LENGTH, SQUARE_LENGTH);
    if (direction == up) {
        current_node = nodes[current_node.x, current_node.y + 1];
    } else if (direction == down) {
        current_node = nodes[current_node.x, current_node.y - 1];
    } else if (direction == left) {
        current_node = nodes[current_node.x - 1, current_node.y];
    } else {
        current_node = nodes[current_node.x + 1, current_node.y];
    }

}


int main() { // Trémaux's Algorithm
    drive_goto(30, 30); // initialize to first middle point
    current_node.x = 1;
    current_node.y = 1;
    current_node.counter = 0;
    for (int i = 0; i < 20; i++) {
        current_node.connected[i] = nullptr;
    }
}

//int main() { // Pledge Algorithm
//    drive_goto(30, 30); // initialize to first middle point
//    while (1) {
//        if (counter < 0) {
//            if (right_clear()) {
//                turn_right_counter();
//                move_forward();
//                continue;
//            }
//            if (front_clear()) {
//                move_forward();
//                continue;
//            }
//            turn_left_counter();
//
//        } else if (counter > 0) {
//            if (left_clear()) {
//                turn_left_counter();
//                move_forward();
//                continue;
//            }
//            if (front_clear()) {
//                move_forward();
//                continue;
//            }
//            turn_right_counter();
//
//        } else {
//            if (front_clear()) {
//                move_forward();
//            } else {
//                turn_right_counter();
//            }
//        }
//    }
//}


// Pledge algorithm
// 1) reach obstacle in front, start pledge algorithm
// 2) turn right
// 3) for every movement below:
//    (a) Obstacle: LEFT, No Obstacle: FRONT -----> move forward
//    (b) Obstacle: LEFT + FRONT -----------------> turn right
// 4) keep looping until counter reach 0
// 5) end Pledge algorithm