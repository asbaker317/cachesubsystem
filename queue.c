/*
 * queue.c
 *
 *  Created on: Jun 8, 2017
 *      Author: igen206
 */

//

//  queue.c

//  CacheSubsystem

//

//  Created by Alex Baker on 6/3/17.

//  Copyright � 2017 Alex Bakera. All rights reserved.

//
#include <stdlib.h>
#include "queue.h"*
#include "cpu.h"


struct Node {
    struct State *state;
    struct Node *next;
};

struct Queue {
    int size;
    int max_size;
    struct Node *head;
    struct Node *tail;
};

struct Queue* newQueue(int capacity)
{
    struct Queue *q;
    q = malloc(sizeof(struct Queue));

    if (q == NULL) {
        return q;
    }

    q->size = 0;
    q->max_size = capacity;
    q->head = NULL;
    q->tail = NULL;

    return q;
}

int enqueue(struct Queue *q, struct State *state)
{
    if ((q->size + 1) > q->max_size) {
        return q->size;
    }

    struct Node *node = malloc(sizeof(struct Node));

    if (node == NULL) {
        return q->size;
    }

    node->state = state;
    node->next = NULL;

    if (q->head == NULL) {
        q->head = node;
        q->tail = node;
        q->size = 1;

        return q->size;
    }


    q->tail->next = node;
    q->tail = node;
    q->size += 1;

    return q->size;
}



struct State *dequeue(struct Queue *q)
{
    if (q->size == 0) {
        return NULL;
    }

    void *state = NULL;
    struct Node *tmp = NULL;

    state = q->head->state;
    tmp = q->head;
    q->head = q->head->next;
    q->size -= 1;

    free(tmp);

    return state;
}

void freeQueue(struct Queue *q)
{
    if (q == NULL) {
        return;
    }

    while (q->head != NULL) {
        struct Node *tmp = q->head;
        q->head = q->head->next;
        if (tmp->state != NULL) {
            free(tmp->state);
        }

        free(tmp);
    }

    if (q->tail != NULL) {
        free(q->tail);
    }
    free (q);
}
