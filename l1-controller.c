
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#include "cpu.h"
#include "l1-controller.h"
#include "l1-controller.c"


int L1tag = 0;
int L1index = 0;
int L1offset = 0;
unsigned long long addressW;
unsigned long long addressR;



/* Cache: an array of sets */
/*typedef struct { cache_set *sets; } cache_structure;*/



void parse_address(struct State state){
    long long int address = state.addr;
    /*state.addr = a.addr;*/
    int size = 17;
    long long int int addr_arr[17];
    long long int int *ptr;
    int tag = 0;
    int index = 0;
    int offset = 0;
    ptr = &addr_arr[size - 1];
    for (int i = size - 1; i >= 0; i--){
        addr_arr[i] = address %2;
    }
    for (int i = 0; i < 2; i++)
    {
        int digits = floor(log10(addr_arr[i])) + 1;
        tag *= pow(10, digits);
        tag += addr_arr[i];
        state.tag = tag;
    }
    for (int i = 2; i < 8; i++)
    {
        int digits = floor(log10(addr_arr[i])) + 1;
        index *= pow(10, digits);
        index += addr_arr[i];
        state.index = index;
    }
    for (int i = 8; i < 13; i++)
    {
        int digits = floor(log10(addr_arr[i])) + 1;
        offset *= pow(10, digits);
        offset += addr_arr[i];
        state.offset = offset;
    }

}



void L1Controller_exec(){

	if (CPUWtoL1Q != NULL) {
		state = dequeue(CPUWtoL1Q);
		(void) strncpy(state->in_msg, "CPUWrite", sizeof(state->in_msg));
		parse_address(*state);
	}

	if (CPURtoL1Q != NULL){
		state = dequeue(CPURtoL1Q);
		(void)strncpy(state->in_msg, "CPURead", sizeof(state->in_msg));
		parse_address(*state);





		/* next few lines may not belong here */
		add_instr_register(add_instr_register, state);
	    L1data_cache(state, 2, state.index, state.offset);
	    if (strcmp(state.addr_state, "HIT") == 0){

	    }
	}

	switch (state->addr_state) //maybe check to see if L1data results in hit,miss,etc before entering switch?

	/*
	if (state.addr_state == 'NULL'){
		// make default case, see next line   */

/*
	case "Idle": /* or make this the default case
		if 'R'
		    check L1data if hit/miss/d/c
			// L1data will send message back to here and go from there
		if 'W'
		    same as above
*/
	case "Hit":
	    if (state.in_msg == "CPURead"){
		/* state.l1_addr_state - "RdWaitd"; // maybe have seperate state for each controller? */
	    	L1data(state); /*L1data switches in_msg to "Data"*/
			("RdWaitd", state->addr_state)  /* change this format to switch(state.addr_state)*/
			switch(*(state->addr_state));
	    }
	    if (state.in_msg == "CPUWrite"){
	    	state.in_msg = "Data";
	    	L1data(state);
	    	state.addr_state = "Done";
			switch(*(state->addr_state));
	    }

	case "MissD":
	    if (state.in_msg == "CPURead"){
		state.in_msg = "Victimize";
		L1data(state);
		state.in_msg = "CPURead";
		L2cache(state);
		case = "Rd2Waitd"; /* change this format to switch(state.addr_state)*/

	    }
	    if (state.in_msg == "CPUWrite"){

	    }

	case "MissC":
	    if (state.in_msg == "CPURead"){
		L2cache(state);
		case = "RdL2Waitd";

	    }
	    if (state.in_msg == "CPUWrite"){

	    }

	case "MissI":
	    if (state.in_msg == "CPURead"){
		L2cache(state);
		case = "RdL2Waitd";

	    }
	    if (state.in_msg == "CPUWrite"){

	    }

	case "Rdwaitd":
	    if (state.in_msg == "Data"){
		state.addr_state = "HIT";
		CPU(state); /*will finish pipeline here*/
	    }
	    else {
		case = "Rdwaitd"; /* change this format to switch(state.addr_state) */
	    }
	    /* instead of above format, could maybe do something like:

	    do{
	    } while (state.in_msg != "Data")
	    state.addr_state = "HIT"
	    CPU(state) //will finish pipeline here
	    */

	case "RdL2waitd":
	    if (state.in_msg == "Data"){
		L1data(state);
		CPU(state);
		case = "HIT";
	    }
	    else {
		case = "RdL2waitd";
	    }

	case "Rd2waitd":
	    if (state.in_msg == "DataVC"){
		case = "Rdwait1d"; /*once Victimization is complete, will send back in_msg = data */
	    }
	    else {
		case = "Rd2waitd"; /* change this format to switch(state.addr_state) */
	    }

	case "Rd1waitd":
	    if (state.in_msg == "Data"){
		state.
		L1data_cache(state.data);
		L2Cache(state.data);
		CPU(state.data);
		state.addr_state = "HIT"; /*or 'DONE'? */

	    }
	case "Wrwaitd":
	    if (state.in_msg == "Data"){

	    }
	case "Wrwait2d":
	    if (state.in_msg == "Data"){

	    }
	case "Wrwait1d":
	    if (state.in_msg == "Data"){

	    }
	case "Wralloc":
	    if (state.in_msg == "Data"){

	    }
	case "Done":
		if (state.addr_state == "Done"){
			break;
		}









    /*
    struct State *input_elementR = &state;
    parse_address(*input_elementR);



    addressW = input_elementW->addr;
    instr = x.operation;

    addressR = input_elementR->addr;

    */


}


void L1_to_l2_bus (){



}


void mainL1(){
    L1cache.index_bits = 6;
    L1cache.offset_bits = 6;
    L1cache.no_of_lines = 64;
    L1cache.no_of_sets = 256; /* 4 way associative */
    L1cache.block_size = 64;
}
