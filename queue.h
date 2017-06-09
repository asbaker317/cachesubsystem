/*
 * queue.h
 *
 *  Created on: Jun 8, 2017
 *      Author: igen206
 */

//

//  queue.h

//  CacheSubsystem

//

//  Created by Alex Baker on 6/3/17.

//  Copyright � 2017 Alex Bakera. All rights reserved.

//

#define queue_h

/*#include "cpu.h" */
#include <stdio.h>
#ifndef __SIMPLE_QUEUE__
#define __SIMPLE_QUEUE__


struct Queue;
/*struct State; */

extern struct Queue*
newQueue(int capacity);

extern int
/*enqueue(struct Queue *q, struct State *value);*/


struct State* dequeue(struct Queue *q);


extern void freeQueue(struct Queue *q);





#endif /* queue_h */
