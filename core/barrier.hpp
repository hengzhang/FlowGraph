#ifndef _BARRIER_
#define _BARRIER_

class flowgraph_barrier{

	volatile unsigned long count[2];
	volatile unsigned long sense;
	unsigned long expected;
public:
	flowgraph_barrier(unsigned long expected_in):sense(0), expected(expected_in){
		count[0] = 0;
		count[1] = 0;
	}
	void wait(){
		unsigned long sense_used = sense;
		unsigned long arrived = __sync_fetch_and_add(&count[sense_used], 1);
		if(arrived == (expected -1)){
			sense = 1 - sense_used;
			count[sense_used] = 0;
		}
		while(count[sense_used] != 0);
		__sync_synchronize();
	}
};

#endif
