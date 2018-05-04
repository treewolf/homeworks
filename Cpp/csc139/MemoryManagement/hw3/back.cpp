#include <algorithm> //sort
#include <cstdio> //in out
#include <cstring> //strtok
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

	int time_start;

	int time_completed;
	int time_waiting;

	int flag_touched;

	/*arrival time at
	complete time ct
	turn around tt = ct - at
	waiting time wt = tt - bt => (ct - at) - burst for non preemptivea

	non preempt = waiting = start - arrival
	turnarorund = burst + wait = completed - arrival
	*/
};

/**	functions
 */
void add_to_priority(struct Qu, std::string);
struct Qu createQu();
void cycle(std::queue<Qu> *);
void init();
void print();
void read_and_store();
void ready_to_completed(int);
void RoundRobin();
void ShortestJobFirst();
void sort_priority_helper(struct Qu, struct Qu);
void waiting_to_ready(int);

/**	globals
 */
std::ifstream in;
std::ofstream out;
std::string input = "sjf_input.txt"; //change to input.txt later
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

	//debug calls
	print();
	std::cout << "calling Shortest";
	ShortestJobFirst();

	in.close();
	out.close();

	return 0;
}
//END MAIN//////////////////////////////////////////////////////////


//ALGORITHMS/////////////////////////////////////////////////////

void RoundRobin(){
	//print algorithm
	out << alg.name << " " << alg.time_quantum << "\n";
	out.flush();

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
			out << timer << "\t" << ready.front().proc_num << "\n";
			out.flush();
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
				}
			}

		}
		
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
	out << std::setprecision(3)  << "AVG WaitingTime: " << total_w;
	out << "\n";
	out.flush();
}

void ShortestJobFirst(){
	out << alg.name << "\n";
	out.flush();

	int timer = 0;

	//who is ready at 0 seconds, add to priority
	std::cout << "b";
	while(!master.empty()){
		struct Qu t = master.front();
		if(t.arrival_time == timer) priority.push_back(t);
		else	waiting.push(t);
	}	
	out << "t";out.flush();
	std::cout <<"c";

	//while loop
		//sort priority, whenever prioirty changes must adjust		

	while(completed.size() != alg.number_of_proc){
		//sort lowest cpu first
		int min_cpu;
		while(!priority.empty()){
			if(priority.size() == 1){
				ready.push(priority.front());
				priority.pop_front();
			}
			else{
				//if priority is bigger than 1, then need to sort
				//use array[]
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
						if(t[j].cpu_burst>t[k].cpu_burst){
							struct Qu u = t[j];
							t[j] = t[k];
							t[k] = u;
							--k;
						}
					}
				}
				for(j=0; j<s; ++j){
					std::cout << t[j].proc_num;
					ready.push(t[j]);
				}
			}	
		}
	}
}

void PriorityNoPre(){
	out << alg.name << "\n";
	out.flush();

	while(completed.size() != alg.number_of_proc){

	}	
}

void PriorityWithPre(){
	out << alg.name << "\n";
	out.flush();

	while(completed.size() != alg.number_of_proc){

	}	
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
	std::cout << "\n";
	int i;
	for(i=0; i<master.size(); ++i){
		struct Qu t = master.front();
		std::cout << "master: " << t.proc_num << "\n";
		master.pop();
		master.push(t);
	}
	for(i=0; i<ready.size(); ++i){
		struct Qu t = ready.front();
		std::cout << "ready: " << t.proc_num << "\n";
		ready.pop();
		ready.push(t);
	}
	for(i=0; i<waiting.size(); ++i){
		struct Qu t = waiting.front();
		std::cout << "waiting: " << t.proc_num << "\n";
		waiting.pop();
		waiting.push(t);
	}
	for(i=0; i<completed.size(); ++i){
		struct Qu t = completed.front();
		std::cout << "completed: " << t.proc_num << "\n";
		completed.pop();
		completed.push(t);
	}
	for(i=0; i<priority.size(); ++i){
		struct Qu t = priority.front();
		std::cout << "priority " << t.proc_num << "\n";
		priority.pop_front();
		priority.push_back(t);
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
