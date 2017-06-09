/*
 * main.c
 *
 *  Created on: Jun 8, 2017
 *      Author: igen206
 */

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <strings.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "cpu.h"
#include "l1-controller.h"



int main(int argc){

    struct State state;
    CPUmain(state);
    /*
     call read_str()
     call scheduler
     */
    return 0;
}