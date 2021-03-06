//
//  cpu.c
//  CacheSubsystem
//
//  Created by Alex Baker on 6/1/17.
//  Copyright � 2017 Alex Bakera. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <strings.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "cpu.h"
#include "queue.h"
#include "queue.c"
#include "l1-controller.h"
#include "l1-controller.c"
#include "l2-controller.c"






/*
char (*input_file) = NULL;
 */
FILE *file = NULL;



/* open file, read file lines, and put each line in queue to CPU */
void read_str(struct Address address){ /*maybe switch and only deal with "address" in CPU.c instead of state */

    FILE *file;
    char filename[9];
 /*   int temp;  */

    printf("Type in: 'input.txt'\n");
    scanf("%s",&filename[9]);
    file =fopen(filename, "r");
    if (file == NULL) {
        perror("Error");
    }
    else {
        while(!feof(file)) {

          /*  struct Text_input *input_element = (struct Text_input);malloc(sizeof(struct Text_input));   */
            fscanf(file,"%c %llu [%s][;]", &address.operation, &address.addr, &address.size[8]);
            address.next = NULL;

            enqueue(FiletoCPUQ, &address);

            read_str(*address.next);

            /*
            if(filetoCPUQ->head == NULL) {
                filetoCPUQ->head=n;
            }
            else {
               filetoCPUQ->tail->next=n;
            }

            filetoCPUQ->tail=n;
            filetoCPUQ->size++;
             */
        }
    }
}


void scheduler(struct State state) { /*maybe switch and only deal with "address" in CPU.c instead of state */
    int cycle = 1;

    do {
          CPUexec(state);
          L1Controller_exec();
          L2Controller_exec(state);
          Memory_exec(state);
        cycle ++;

        if(
           FiletoCPUQ->size == 0 &&
        /*   CPUtoL1Q == 0 && */
           CPUWtoL1Q->size == 0 &&
           CPURtoL1Q->size == 0 &&
           L1oL2Q->size == 0 &&
           L2toMemQ->size == 0 &&
           MemtoL2Q->size == 0 &&
           L2toL1Q->size == 0 &&
           L1toCPUQ->size == 0
           ){ cycle = 0;}
    } while (cycle !=0);
}


void CPUexec(struct State state){ /*maybe switch and only deal with "address" in CPU.c instead of state */
    /*  dequeue from filetoCPUQ */
    while (FiletoCPUQ->size != 0){
        dequeue(FiletoCPUQ), &state;
        FiletoCPUQ->size = FiletoCPUQ->size -1;

        if (state.address.operation == 'R')
            enqueue(CPURtoL1Q, &state);
        	CPURtoL1Q->size = CPURtoL1Q->size -1;

        if (state.address.operation == 'W')
            enqueue(CPUWtoL1Q, &state);
        	CPUWtoL1Q->size = CPUWtoL1Q->size -1;
    }
};

void  CPUmain(struct State state){ /*maybe switch and only deal with "address" in CPU.c instead of state */

    read_str(state);
    scheduler(state);



    /*

     call read_str()

     call scheduler

     */

}


/*


 void open_read_file(){


 while ( fscanf(file, "%c %llx,%d[;]", &(input_element.operation), &(addr), &(size)) == 3) {
 if (operation == 'L'){
 CPURtoL1Q.enqueue();
 }
 if (operation == 'W'){
 CPUWtoL1Q.enqueue();
 }
 analyze_cache();
 CPUtoL1Q.enqueue();
 }
 };

 void analyze_cache() {
 int low = INT_MAX;
 __evict = 0;
 addr_tag = addr >> (param_s + param_b);
 int tag_size = (64 - (param_s + param_b));
 unsigned long long aux = addr << (tag_size);
 cache = cache_sets[(aux >> (tag_size + param_b))];

 int e = 0;
 while (e < param_A) {
 if ((cache.lines[e].bits & 1) == 1) {
 if (cache.lines[e].tag == addr_tag) {
 if (param_R == 1) { cache.lines[e].timestamp = __sim_time__; }
 if (param_W == 0 && operation == 'S' && verbosity) {
 printf(
 " store instruction -> write data to addr %lli (main memory)\n",
 addr);
 }
 if (operation == 'S' && param_W == 1) {
 cache.lines[e].bits = (cache.lines[e].bits | 2);
 } else {
 cache.lines[e].bits = cache.lines[e].bits & 1;
 }

 __hit__ = 1;
 __sim_time__++;
 num_hits++;
 }
 if (cache.lines[e].timestamp < low) {
 low = cache.lines[e].timestamp;
 __evict = e;
 }
 }

 else if (__empty__ == -1) { __empty__ = e; }
 e++;
 }
 }

 */
