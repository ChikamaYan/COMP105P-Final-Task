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


enum dir direction = up;
struct node *current_node = malloc(sizeof(struct node));
struct node *nodes[4][5];
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
    switch (direction) {
        case up:
            direction = right;
            break;
        case right:
            direction = down;
            break;
        case down:
            direction = left;
            break;
        case left:
            direction = up;
    }
}

void turn_left_counter() {
    turn_left();
    switch (direction) {
        case up:
            direction = left;
            break;
        case right:
            direction = up;
            break;
        case down:
            direction = right;
            break;
        case left:
            direction = down;
    }
}

void move_forward() {
    drive_goto(SQUARE_LENGTH, SQUARE_LENGTH);
    switch (direction) {
        case up:
            current_node = nodes[current_node.x, current_node.y + 1];
            break;
        case right:
            current_node = nodes[current_node.x + 1, current_node.y];
            break;
        case down:
            current_node = nodes[current_node.x, current_node.y - 1];
            break;
        case left:
            current_node = nodes[current_node.x - 1, current_node.y];
    }

}

void initialise_node() {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 5; y++) {
            nodes[x][y] = malloc(sizeof(struct node));
            nodes[x][y]->x = x;
            nodes[x][y]->y = y;
            nodes[x][y]->counter = 0;
            for (int i = 0; i < 20; i++) {
                nodes[x][y]->connected[i] = malloc(sizeof(struct node));
                nodes[x][y]->connected[i] = NULL;
            }
        }
    }
}

int main() { // Trémaux's Algorithm
    drive_goto(30, 30); // initialize to first middle point

}

void initialize_position() {
    drive_goto(30, 30);
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

void dead_end(){
    if (front_clear() == 0 && left_clear() == 0 && right_clear() == 0){
        turn_around();

    }
}

// Pledge algorithm
// 1) reach obstacle in front, start pledge algorithm
// 2) turn right
// 3) for every movement below:
//    (a) Obstacle: LEFT, No Obstacle: FRONT -----> move forward
//    (b) Obstacle: LEFT + FRONT -----------------> turn right
// 4) keep looping until counter reach 0
// 5) end Pledge algorithm

// Tremaux's Algorithm
// 1) Enter new junction: (current_pos != X)
//      a) current_pos = X
//      b) new_passage = N
//      c) march to new_passage
//
// 2) Enter old junction (current_pos == X, previous_junction_pos != current_pos)
//      a) current_passage = N
//      b) turn around and march back
//
// 3) Dead_end (sensor)
//      a) turn around and march back
//
// 4) Return old junction + unlabeled passage (current_pos == X, previous_junction == current_pos)
//      a) new_passage_2 = N
//      b) march to new_passage_2
//
//  5) Return old junction + no unlabeled passage (current_pos == X, previous_juntion == current_pos)
//      a) return to X