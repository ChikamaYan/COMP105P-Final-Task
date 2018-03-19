//
// Created by ChikamaYan on 3/19/2018.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "simpletools.h"
#include "abdrive.h"
#include "simpletools.h"
#include "ping.h"
#include "basics.h"
#include "simulator.h"

int left, right;
int preL, preR;

void turnRightAfterInit() {
    drive_getTicks(&preL, &preR);
    drive_ramp(128, 64);
    pause(710);
    drive_getTicks(&left, &right);
    printf("turnRightAfterInit: Travelled for (%d,%d)\n", left - preL, right - preR);
    drive_ramp(128, 128);
    pause(170);
}

void turnRight() { // tested: after forwarding, after turning left
    drive_getTicks(&preL, &preR);
    drive_ramp(128, 64);
    pause(785);
    drive_getTicks(&left, &right);
    printf("turnRight: Travelled for (%d,%d)\n", left - preL, right - preR);
    drive_ramp(128, 128);
    pause(170);
}

void turnRightAfterRightTurn(){
    drive_ramp(128, 128);
    pause(110);
    drive_ramp(128, 64);
    pause(625);
    drive_getTicks(&left, &right);
    printf("turnRightAfterRightTurn: Travelled for (%d,%d)\n", left - preL, right - preR);
    drive_ramp(128, 128);
    pause(170);
}

void turnLeft() { // tested: after forwarding, after turning right, after turning init right
    drive_getTicks(&preL, &preR);
    drive_ramp(64, 128);
    pause(785);
    drive_getTicks(&left, &right);
    printf("turnLeft: Travelled for (%d,%d)\n", left - preL, right - preR);
    drive_ramp(128, 128);
    pause(170);
}

void turnLeftAfterLeftTurn(){
    drive_ramp(128, 128);
    pause(110);
    drive_ramp(64, 128);
    pause(625);
    drive_getTicks(&left, &right);
    printf("turnLeftAfterLeftTurn: Travelled for (%d,%d)\n", left - preL, right - preR);
    drive_ramp(128, 128);
    pause(170);
}

void moveForward() {
    drive_getTicks(&preL, &preR);
    drive_ramp(128, 128);
    pause(940);
    drive_getTicks(&left, &right);
    printf("moveForward: Travelled for (%d,%d)\n", left - preL, right - preR);
}

//void moveForwardAfterTurn() {
//    drive_getTicks(&preL, &preR);
//    drive_ramp(128, 128);
//    pause(1100);
//    drive_getTicks(&left, &right);
//    printf("moveForwardAfterTurn: Travelled for (%d,%d)\n", left - preL, right - preR);
//}

void initMove() {
    drive_ramp(128, 128);
    pause(1150);
    drive_getTicks(&left, &right);
    printf("Travelled for (%d,%d)\n", left - preL, right - preR);
}

int main() {
    drive_setRampStep(2000);
    simulator_startNewSmokeTrail();

    initMove();

    turnRightAfterInit();
    turnLeft();
    moveForward();
    turnLeft();
    turnLeftAfterLeftTurn();


    drive_ramp(128, 128);
    while (1);
}
