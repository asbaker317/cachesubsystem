/*
 * l2_controller.c
 *
 *  Created on: Jun 8, 2017
 *      Author: igen206
 */

//  l2-controller.c
//  CacheSubsystem
//
//  Created by Alex Baker on 6/1/17.
//  Copyright © 2017 Alex Bakera. All rights reserved.
//

#include "l2-controller.h"

/* memory addresses: 64-bit variable */
typedef unsigned long long int mem_addr_t;

typedef struct {
    int index_bits;         /* number of bits needed to address cache sets, s = log2(S)   */
    int offset_bits;         /* number of bits needed for the cacheline block, b = log2(B) */
    int no_of_lines;        /* num of cachelines per set                           */
    int no_of_sets;         /* num of sets(index), derived from S = 2**s                  */
    int block_size;         /* cacheline block size (bytes), derived from B = 2**b */
} cache_param;

int index_bits = 8;
int offset_bits = 6;
int no_of_lines = 256;
int no_of_sets = 2; /* 2 way associative */
int block_size = 64;

/* Line */
typedef struct {
    int bits;
    int timestamp;
    mem_addr_t tag;
} line_structure;

/* Set: an array of lines */
typedef struct { line_structure *lines;  } cache_set;

/* Cache: an array of sets */
typedef struct { cache_set *sets; } cache_structure;

typedef struct {
    char instr;            /* L,S,M                        */
    int size;              /* Size read in from file       */
    int lru_flag;          /* Value for LRU                */
    int empty;             /* Index of empty space         */
    int hit_flag;          /* Cache hit flag               */
    int evict_flag;        /* Cache eviction flag          */
    int to_evict;          /* Keeps track of what to evict */

    /* Counters */
    int hit_count;
    int miss_count;
    int eviction_count;

    /* Memory addrs */
    mem_addr_t addr;
    mem_addr_t addr_tag;
    cache_set  set;
} simulation_state_t;
