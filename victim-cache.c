/*
 * victim-cache.c
 *
 *  Created on: Jun 8, 2017
 *      Author: igen206
 */

//

//  victim-cache.c

//  CacheSubsystem

//

//  Created by Alex Baker on 6/1/17.

//  Copyright © 2017 Alex Bakera. All rights reserved.

//

#include<stdio.h>
#include <stdlib.h>
#include "l1-controller.h"
#include "cpu.h"


int Victim_Cache(struct State *L1_state, int tag, int index, int offset) {

char VC[64][2];
    for(int i=0; i<=63; i++) {
        for(int j=0;j<=1;j++) {
            if ((VC[offset][index] != 0)) {
                L1_state->hit_flag =  1;
            }
        }
    }
return 0;

}
