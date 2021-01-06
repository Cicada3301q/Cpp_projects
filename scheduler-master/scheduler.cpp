
// you need to modify this file
#include <iostream>
#include "scheduler.h"
#include "common.h"
#include <unordered_map>
#include <queue>
// this is the function you should edit
//
// runs Round-Robin scheduling simulator
// input:
//   quantum = time slice
//   max_seq_len = maximum length of the reported executing sequence
//   processes[] = list of process with populated IDs, arrival_times, and bursts
// output:
//   seq[] - will contain the execution sequence but trimmed to max_seq_len size
//         - idle CPU will be denoted by -1
//         - other entries will be from processes[].id
//         - sequence will be compressed, i.e. no repeated consecutive numbers
//   processes[]
//         - adjust finish_time and start_time for each process
//         - do not adjust other fields
//
void simulate_rr(
    int64_t quantum, 
    int64_t max_seq_len,
    std::vector<Process> & processes,
    std::vector<int> & seq
    
) {
    // replace the wrong implementation below with your own!!!!

    seq.clear();
	int curr_time = 0;
	int curr_proc = 0;
	int jobs_remaining = processes.size();
//	std::map<int, int> burst_copy;
	bool is_idle = true;
	int64_t quantum_check = 0;
	std::queue<Process> RQ;
//	int i = 0;
        std::vector<int> id_copy;
//	for(auto p : processes){
//	id_copy.push_back(p.finish_time);
//}

	while(1){

//                  std::cout<<"check 0"<<std::endl;
//		seq.push_back(12);
		if(jobs_remaining == 0){
			break;
		}
//		std::cout<< jobs_remaining<<std::endl;
//		seq.push_back(9);
		//if process is done
//                  std::cout<<"check here"<<std::endl;
//		  std::cout<< RQ.size()<<std::endl;
		if(!RQ.empty()){
		if(RQ.front().burst == 0 && !is_idle ){
			processes[RQ.front().id].finish_time = curr_time;
		//	processes[k].finish_time = curr_time;

			RQ.pop();
			quantum_check = 0;
			jobs_remaining --;
			is_idle = true;
			continue;
		}}
  //              std::cout<< "checkkk" << std::endl;
//		seq.push_back(5);
//                 std::cout<<"check"<<std::endl;
		if(processes[curr_proc].arrival_time == curr_time){
			RQ.push(processes[curr_proc]);
			curr_proc += 1;
			continue;
}
    //                           std::cout<<"check 1"<<std::endl;



		if(RQ.size() != 0 ){
			is_idle = false;
//			std::cout<<RQ.front().burst<< "RQ " << processes[curr_proc].burst << "curr " <<std::endl;
			if(RQ.front().burst == processes[RQ.front().id].burst){
    			processes[RQ.front().id].start_time = curr_time;
		//		i++;
				}
			RQ.front().burst -= 1;
			if(seq.size() == 0){
				seq.push_back(RQ.front().id);
}
			if(seq.size() > 0){
			if(seq.back() != RQ.front().id && seq.size() < max_seq_len ){
			seq.push_back(RQ.front().id);}
}
			quantum_check += 1;
		//	std::cout<<"quantum check  "<< curr_time <<" "<< quantum_check<< "RQ" << RQ.front().id <<  std::endl;
			if(quantum_check >= quantum && RQ.front().burst != 0){
				RQ.push(RQ.front());
				RQ.pop();
				quantum_check = 0;
			}


		}   //            std::cout<<"check 2"<<std::endl;

		if(is_idle && RQ.size() == 0){
			seq.push_back(-1);
		}

	/*	if(processes[curr_proc].arrival_time == curr_time){
			RQ.push(processes[curr_proc]);
			curr_proc += 1;
			continue;
		}*/

//		seq.push_back(12);
		curr_time ++;




	}
/*    for (auto & p : processes) {
        p.finish_time = p.arrival_time + p.burst;
        p.start_time = p.arrival_time;
        seq.push_back(p.id);
    }*/
}


