/*
 * memory.c
 *
 *  Created on: Jun 8, 2017
 *      Author: igen206
 */


//

//  memory.c

//  CacheSubsystem

//

//  Created by Alex Baker on 6/1/17.

//  Copyright © 2017 Alex Bakera. All rights reserved.

//

#include "memory.h"
#include<stdio.h>
#include <stdlib.h>
/*#include "l1-controller.h"*/

#include "cpu.h"

int Memory(struct State *L1_state, mem_addr addr) {

    char MEM[131072];


    for(int i=0; i<=131071; i++) {
            if ((MEM[addr] != 0)) {
                L1_state->hit_flag =  1;

            }
    }

    return 0;
}
