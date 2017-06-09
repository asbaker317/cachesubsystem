/*
 * l1-instruction-cache.c
 *
 *  Created on: Jun 8, 2017
 *      Author: igen206
 */


//

//  l1-instruction-cache.c

//  CacheSubsystem

//

//  Created by Alex Baker on 6/1/17.
//  Copyright � 2017 Alex Bakera. All rights reserved.
//
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include "queue.h" */
#include "cpu.h"
#include "l1-controller.h"


struct State *instr_register[32];
int num_items = 0;




void add_instr_register (struct State *instr_register, struct State a){
    if ( num_items < 32 )
    {
        instr_register[num_items] = a;
        num_items += 1;
    }


}

int scan_register (struct State state){

    int a;
    for(a = 0; a < 32; a++)
    {
        if (
            state.offset == instr_register[a].offset &&
            state.index == instr_register[a].index &&
            instr_register[a].dirtybit == 1
            ){
            (void)strncpy(state.addr_state, "MissD", sizeof(state.in_msg));
            return 1;
        }

        if (
            state.offset == instr_register[a].offset &&
            state.index == instr_register[a].index &&
            instr_register[a].dirtybit == 0 &&
            state.data != instr_register[a].data
            ){
            (void)strncpy(state.addr_state, "MissC", sizeof(state.in_msg));
        }

    }
    return 0;
}
