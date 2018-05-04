#define INPUT_FILE "input.txt"

#include <cstdio> //in out
#include <deque>
#include <fstream> //file
#include <iomanip> //setprecision
#include <iostream> //cin cout
#include <queue>
#include <sstream> // iss
#include <string>

/**	structs
 */
struct algorithm{
	std::string name;
	int number_of_proc;

	//for rr
	int time_quantum;
};

struct Qu{
	int proc_num;
	int arrival_time;
	int cpu_burst;
	int priority;
	int total_burst;	

	int time_start;

	int time_completed;
	int time_waiting;

	int flag_touched;
};

/**	functions
 */
struct Qu createQu();
void cycle(std::queue<Qu> *);
void init();
void print();
void PriorityNoPre();
void priority_sort(std::string);
void PriorityWithPre();
void read_and_store();
void ready_to_completed(int);
void RoundRobin();
void ShortestJobFirst();
void waiting_to_ready(int);

/**	globals
 */
std::ifstream in;
std::ofstream out;
std::string input = INPUT_FILE;
std::string output = "output.txt";
struct algorithm alg;
std::queue<Qu> master; //should only use once.
std::queue<Qu> waiting;
std::queue<Qu> ready;
std::queue<Qu> completed;
std::deque<Qu> priority;

//MAIN/////////////////////////////////////////////////////////
int main(){

	//init globals
	init();

	//read file and store into queues
	read_and_store();

	//based off of alg.name, determine which functino to call
	if(alg.name.compare("PR_noPREMP") == 0) PriorityNoPre(); 
	else if(alg.name.compare("PR_withPREMP") == 0) PriorityWithPre(); 
	else if(alg.name.compare("RR") == 0) RoundRobin(); 
	else if(alg.name.compare("SJF") == 0) ShortestJobFirst(); 
	else std::cout << "ERROR: algorithm name not recognized" << std::endl; 
	
	in.close();
	out.close();

	return 0;
}
//END MAIN//////////////////////////////////////////////////////////


//ALGORITHMS/////////////////////////////////////////////////////

void PriorityNoPre(){
	out << alg.name << std::endl;

	int timer = 0;

	//who is ready at 0 seconds, add to priority
	while(!master.empty()){
		struct Qu t = master.front();
		if(t.arrival_time == 0) priority.push_back(t);	
		else	waiting.push(t);
		master.pop();
	}

	while(completed.size() != alg.number_of_proc){
		int flag_inner = 0;
		
		//sort lowest cpu first
		int min_cpu;
		while(!priority.empty()){
			flag_inner = 1;
			if(priority.size() == 1){
				ready.push(priority.front());
				priority.pop_front();
			}
			else{
				//if priority is bigger than 1, then need to sort
				int s = priority.size();
				struct Qu t[s];
				int i = 0;
				while(!priority.empty()){
					t[i] = priority.front();
					++i;
					priority.pop_front();
				}
				//sort in array, then add back to prioroity
				int j;
				for(j=0; j<s; ++j){
					int k;
					for(k=1; k<s; ++k){
						if(t[j].priority>t[k].priority && j<k){
							struct Qu u = t[j];
							t[j] = t[k];
							t[k] = u;
							
						} } }
				for(j=0; j<s; ++j) ready.push(t[j]);
			}	
		}
		//now in ready, run all, set var, timer
		while(!ready.empty()){	
			flag_inner = 1;
			ready.front().time_start = timer;
			out << timer << "\t" << ready.front().proc_num << std::endl;

			while(ready.front().cpu_burst != 0){
				--ready.front().cpu_burst;
				++timer;
			}
			ready_to_completed(timer);	
		}

		//increment timer
		if(flag_inner == 1) flag_inner = 0;
		else	++timer;

		int i;
		for(i=0; i<waiting.size(); ++i){
			if(waiting.front().arrival_time <= timer){
				priority.push_back(waiting.front());
				waiting.pop();
				--i;
			} }
	}

	//calculate waiting time, sum of all starts
	double total_w = 0;
	while(!completed.empty()){
		total_w += completed.front().time_start;
		completed.pop();
	}
	total_w /= alg.number_of_proc;
	out << std::setprecision(3)  << "AVG Waiting Time: " << total_w << std::endl;
}

void PriorityWithPre(){
	out << alg.name << std::endl;

	int timer = 0;

	//who is ready at 0 seconds, add to priority
	while(!master.empty()){
		struct Qu t = master.front();
		if(t.arrival_time == 0) priority.push_back(t);	
		else	waiting.push(t);
		master.pop();
	}
	while(completed.size() != alg.number_of_proc){
		int flag_inner = 0;
		//sort lowest cpu first
		while(!priority.empty()){
			flag_inner = 1;
			priority_sort("priority");
		}
		//now in ready, run all, set var, timer
		while(!ready.empty()){
			flag_inner = 1;

			if(ready.front().flag_touched == 0){
				ready.front().flag_touched = 1;
				ready.front().time_start = timer;
			}
			out << timer << "\t" << ready.front().proc_num << std::endl;

			//is front highest priority? check every time timer incs
			bool stillWorking = true;
			while(ready.front().cpu_burst != 0){
				--ready.front().cpu_burst;
				++timer;

				//if proc not finished, prepare for possible preempt
				if(ready.front().cpu_burst != 0)
					stillWorking = true;
				else
					stillWorking = false;

				//CHECK waiting IF NEW PRC
				int i;
				for(i=0; !waiting.empty() && i<waiting.size(); ++i){
					if(waiting.front().arrival_time <= timer){
						priority.push_back(waiting.front());
						waiting.pop();
						--i;
					}
					else cycle(&waiting);
				}

				//add all from ready to priority list, if front not highest priority
				// then break
				struct Qu tt = ready.front();
				while(!ready.empty()){
					priority.push_back(ready.front());
					ready.pop();
				}
				priority_sort("priority");	
				if(tt.proc_num != ready.front().proc_num) break; 
			}
			if(!stillWorking) ready_to_completed(timer);	
		}

		//increment timer
		if(flag_inner == 1) flag_inner = 0;
		else ++timer;  
		int i;
		for(i=0; i<waiting.size(); ++i){
			if(waiting.front().arrival_time <= timer){
				priority.push_back(waiting.front());
				waiting.pop();
				--i;
			} }
	}

	//calculate waiting time, wt = complete time - cpuburst - arrival 
	int i;
	for(i=0; i<completed.size(); ++i){
		completed.front().time_waiting = completed.front().time_completed - completed.front().total_burst - completed.front().arrival_time;
		cycle(&completed);
	}

	double total_w = 0;
	while(!completed.empty()){
		total_w += completed.front().time_waiting;
		completed.pop();
	}
	total_w /= alg.number_of_proc;
	out << std::setprecision(3)  << "AVG Waiting Time: " << total_w << std::endl;
}

void RoundRobin(){
	//print algorithm
	out << alg.name << " " << alg.time_quantum << std::endl;

	int quantum_counter = 0, timer = 0;

	//determine which queue to enqueue, if ready queue set start time
	while(!master.empty()){
		struct Qu t = master.front();
		if(t.arrival_time == 0) ready.push(t);
		else waiting.push(t);
		master.pop();
	}

	while(completed.size() != alg.number_of_proc){
		int flag_inner = 0;
	
		//print process and timer, also save value if not been touched yet	
		if(!ready.empty()){
			if(ready.front().flag_touched == 0){
				ready.front().time_start = timer;
				ready.front().flag_touched = 1;
			}
			out << timer << "\t" << ready.front().proc_num << std::endl;
		}

		//task being processesd
		while(quantum_counter<alg.time_quantum && ready.front().cpu_burst != 0){
			flag_inner = 1;
			++timer;
			++quantum_counter;
			--ready.front().cpu_burst;
			if(ready.size() > 1){
				int i;
				cycle(&ready);
				for(i=0; i<ready.size()-1; ++i){
					++ready.front().time_waiting;
					cycle(&ready);
				} } }
		
		//reset counter
		quantum_counter = 0;

		if(flag_inner == 0) ++timer;	

		//check for new processes, add old one after if same time
		int i;
		for(i=0; i<waiting.size(); ++i){
			if(waiting.front().arrival_time <= timer){
				waiting_to_ready(timer); 
				--i;
			}
		}
		if(ready.front().cpu_burst == 0) ready_to_completed(timer);	
		else cycle(&ready); 
	}

	//now calculate waiting time, cannot use cpu_burst since is zero
	double total_w = 0;
	int i;
	for(i=0; i<alg.number_of_proc; ++i){
		total_w += completed.front().time_waiting;
		completed.pop();
	}
	total_w /= alg.number_of_proc;
	out << std::setprecision(3)  << "AVG WaitingTime: " << total_w << std::endl;
}

void ShortestJobFirst(){
	out << alg.name << std::endl;

	int timer = 0;

	//who is ready at 0 seconds, add to priority
	while(!master.empty()){
		struct Qu t = master.front();
		if(t.arrival_time == 0) priority.push_back(t);	
		else	waiting.push(t);
		master.pop();
	}

	while(completed.size() != alg.number_of_proc){
		int flag_inner = 0;

		//sort lowest cpu first
		while(!priority.empty()){
			flag_inner = 1;
			priority_sort("sjf");	
		}
		//now in ready, run all, set var, timer
		while(!ready.empty()){
			flag_inner = 1;	
			if(ready.front().flag_touched == 0){
				ready.front().flag_touched = 1;
				ready.front().time_start = timer;
			}
			out << timer << "\t" << ready.front().proc_num << std::endl;

			while(ready.front().cpu_burst != 0){
				--ready.front().cpu_burst;
				++timer;
			}
			ready_to_completed(timer);	
			
			//add ready and waiting to priority
			int i;
			for(i=0; i<ready.size(); ++i){
				priority.push_back(ready.front());
				ready.pop();
				--i;
			}
			for(i=0; i<waiting.size(); ++i){
				if(waiting.front().arrival_time <= timer){
					priority.push_back(waiting.front());
					waiting.pop();
					--i;
				} }
		}

		//increment timer
		if(flag_inner == 1) flag_inner = 0;
		else	++timer;
	}

	//calculate waiting time, started - arrival 
	int i;
	for(i=0; i<completed.size(); ++i){ //started - arrival
		completed.front().time_waiting = completed.front().time_start - completed.front().arrival_time;
		cycle(&completed);
	}

	double total_w = 0;
	while(!completed.empty()){
		total_w += completed.front().time_waiting;
		completed.pop();
	}
	total_w /= alg.number_of_proc;
	out << std::setprecision(3)  << "AVG Waiting Time: " << total_w << std::endl;
}

//END ALGORITHMS/////////////////////////////////////////////////


//METHODS//////////////////////////////////////////////////////

/**	create a default struct with default values */
struct Qu createQu(){
	struct Qu t;
	
	t.proc_num = -1;
	t.arrival_time = -1;
	t.cpu_burst = -1;
	t.priority = -1;
	t.total_burst = -1;
	
	t.time_start = -1;
	t.time_completed = -1;
	t.time_waiting = 0;

	t.flag_touched = 0;
	return t;
}

/**	cycles a queue by one */
void cycle(std::queue<Qu> * a){
	struct Qu t = (* a).front();
	(* a).pop();
	(* a).push(t);
}

/**	initialize files */
void init(){
	in.open(input.c_str(), std::ios::in);
	out.open(output.c_str(), std::ios::out | std::ios::trunc);
}

/**	print queues */
void print(){
	std::cout << "\n" << std::endl;
	int i;
	for(i=0; i<master.size(); ++i){
		struct Qu t = master.front();
		std::cout << "master: " << t.proc_num << std::endl;
		master.pop();
		master.push(t);
	}
	
	for(i=0; i<ready.size(); ++i){
		struct Qu t = ready.front();
		std::cout << "ready: " << t.proc_num << std::endl;
		ready.pop();
		ready.push(t);
	}
	for(i=0; i<waiting.size(); ++i){
		struct Qu t = waiting.front();
		std::cout << "waiting: " << t.proc_num << std::endl;
		waiting.pop();
		waiting.push(t);
	}
	for(i=0; i<completed.size(); ++i){
		struct Qu t = completed.front();
		std::cout << "completed: " << t.proc_num << std::endl;
		completed.pop();
		completed.push(t);
	}
	for(i=0; i<priority.size(); ++i){
		struct Qu t = priority.front();
		std::cout << "priority " << t.proc_num << std::endl;
		priority.pop_front();
		priority.push_back(t);
	}
}

/**	sorts a priority list by filter*/
void priority_sort(std::string filter){
	if(priority.size() == 1){
		ready.push(priority.front());
		priority.pop_front();
	}
	else{
		//if priority is bigger than 1, then need to sort
		int s = priority.size();
		struct Qu t[s];
		int i = 0;
		while(!priority.empty()){
			t[i] = priority.front();
			++i;
			priority.pop_front();
		}
		//sort in array, then add back to prioroity
		int j;
		for(j=0; j<s; ++j){
			int k;
			for(k=1; k<s; ++k){
				if(filter.compare("priority") == 0){
					if(t[j].priority>t[k].priority && j<k){
						struct Qu u = t[j];
						t[j] = t[k];
						t[k] = u;
					} }
				else if(filter.compare("sjf") == 0){
					if(t[j].cpu_burst>t[k].cpu_burst && j<k){
						struct Qu u = t[j];
						t[j] = t[k];
						t[k] = u;
					}
					else if(t[j].cpu_burst==t[k].cpu_burst && j<k){
						if(t[j].arrival_time > t[k].arrival_time){
							struct Qu u = t[j];
							t[j] = t[k];
							t[k] = u;
						} } }
				} }
		for(j=0; j<s; ++j) ready.push(t[j]);
	}
}

/** read files and store data into proper vars */
void read_and_store(){

	//spcial case read first line, if rr then tokenize and get quantum
	std::string line;
	std::getline(in, line);
	std::istringstream iss(line);
	if(!(iss >> alg.name >> alg.time_quantum))
		iss >> alg.name;
	
	//get 2nd line
	in >> alg.number_of_proc;

	//get process info
	int i;
	for(i=0; i<alg.number_of_proc; ++i){
		struct Qu t = createQu();
		in >> t.proc_num >> t.arrival_time >> t.cpu_burst >> t.priority;
		t.total_burst = t.cpu_burst;
		master.push(t);
	}	
}

/** moves front ready to completed, sets values */
void ready_to_completed(int timer){
	struct Qu t = ready.front();
	t.time_completed = timer;
	ready.pop();
	completed.push(t);
}

/** moves front of waiting to ready, pops waiting and pushes ready, sets ready vals */
void waiting_to_ready(int timer){
	struct Qu t = waiting.front();
	t.time_start = timer;
	waiting.pop();
	ready.push(t);
}
//END METHODS//////////////////////////////////////////////////////
