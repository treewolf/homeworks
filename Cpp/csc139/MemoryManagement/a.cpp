#include <cstdio>
#include <deque>
#include <fstream> //file
#include <iostream> //cin cout
#include <sstream> // iss
#include <string> //string

/* Page, Frames, page access Requests */
struct PFR{
	int pages;
	int frames;
	int num_requests;
	std::deque<int> requests;
};

/* functions */
void first_in_first_out();
void lru();
int next_occurence(int,int);
void optimal();
void read_and_store();

/* global vars */
std::ifstream in;
std::ofstream out;
struct PFR pfr; 

int main(){
	/* open files */
	in.open("input.txt", std::ios::in);
	out.open("output.txt", std::ios::out | std::ios::trunc);
	
	/* read and parse input file */
	read_and_store();

	/* fifo */
	first_in_first_out();
	out<<std::endl;

	/* optimal */
	optimal();
	out<<std::endl;

	/* lru */
	lru();

	/* close files */
	in.close();
	out.close();
	
	return 0;
}

void first_in_first_out(){
	out<<"FIFO"<<std::endl;
	int i;

	// set up for frame count and indexes, and copy of fpr
	std::deque<int> queue;
	for(i=0; i<pfr.num_requests; ++i){
		queue.push_back(pfr.requests[i]);
	}

	//deque front is current frame number
	int frame_index = 0;
	int frame[pfr.frames] = {0};
		
	//deque for page requests that have been called
	std::deque<int> loaded;

	//algorithm
	int errors=0;
	while(!queue.empty()){
		int p = queue.front();
		queue.pop_front();

		//load page into frame
		//check if frame index needs to cycle
		if(frame_index == pfr.frames)
			frame_index = 0;

		//check if loaded contains page already
		bool isLoaded = false;
		int j;
		for(j=0; j<loaded.size(); ++j){
			if(loaded.at(j) == p){
				isLoaded = true;
				break;
			}
		}
		if(isLoaded){
			int page_in;
			for(j=0; j<pfr.frames; ++j){
				if(frame[j] == p)
					page_in = j; 
			}
			out<<"Page "<<p<<" already in Frame "<<page_in<<std::endl;
		}
		else{
			//check if check if there is a page existing in frame if array value is 0
			//check if replace. if value is 0 or is replacing, error
			if(frame[frame_index] == 0){
				frame[frame_index] = p;
				loaded.push_back(p);
				out<<"Page "<<p<<" loaded into Frame "<<frame_index<<std::endl;
			}
			else{
				int oldpage = frame[frame_index];
				frame[frame_index] = p;
				loaded.push_back(p);

				//search loaded to remove old page
				while(!loaded.empty()){
					if(loaded.front() == oldpage){
						loaded.pop_front();
						break;
					}
					loaded.push_back(loaded.front());
					loaded.pop_front();
				}
				out<<"Page "<<oldpage<<" unloaded from Frame "<<frame_index<<", Page "<<p<<" loaded into Frame "<<frame_index<<std::endl;
			}
			++errors;
			++frame_index;
		}	
	}
	out<<errors<<" page faults"<<std::endl;		
}

void lru(){
	out<<"LRU"<<std::endl;
	int i;
	int timer = 0;

	//initialize queue
	std::deque<int> queue;
	for(i=0; i<pfr.num_requests; ++i){
		queue.push_back(pfr.requests[i]);
	}

	//initialize frame holding pages to 0
	int frame[pfr.frames] = {0};

	//initinalize frame time array
	int frame_time[pfr.frames] = {0};

	bool all_touched = false;
	int frame_index = 0;
	int errors = 0;
	while(!queue.empty()){
		int p = queue.front();
		queue.pop_front();

		//cycle frame index and dtermine if touched all
		if(frame_index == pfr.frames){
			frame_index = 0;
			all_touched = true;
		}

		//determine if already loaded, and say if is
		//since requested, must update frame time if found
		bool already_loaded = false;
		for(i=0; i<pfr.frames; ++i){
			if(frame[i] == p){
				already_loaded = true;

				//update time accessed
				frame_time[i] = timer;

				out<<"Page "<<p<<" already in Frame "<<i<<std::endl;
				break;
			}	
		}

		if(!all_touched && !already_loaded){
			frame[frame_index] = p;
			out<<"Page "<<p<<" loaded into Frame "<<frame_index<<std::endl;;

			//update calc
			frame_time[frame_index] = timer;

			++frame_index;
			++errors;
		}	

		else if(all_touched && !already_loaded){
			//determine longest time and load
			frame_index = 0;
			for(i=0; i<pfr.frames; ++i){
				if(frame_time[i] < frame_time[frame_index])
					frame_index = i;
			}	
			
			out<<"Page "<<frame[frame_index]<<" unloaded from Frame "<<frame_index<<", Page "<<p<<" loaded into Frame "<<frame_index<<std::endl;
			frame[frame_index] = p;
		
			//update calc
			frame_time[frame_index] = timer;
			++errors;
		}
		++timer;
	}
	out<<errors<<" page faults"<<std::endl;		
}

void optimal(){
	out<<"Optimal"<<std::endl;
	int i;

	//initialize queue
	std::deque<int> queue;
	for(i=0; i<pfr.num_requests; ++i){
		queue.push_back(pfr.requests[i]);
	}

	//initialize timing queue
	int frame[pfr.frames] = {0};
	int count_time[pfr.frames] = {0};
	int counter = 0;

	//loop for algorithm
	int errors = 0;
	int frame_index = 0;
	bool all_touched = false;
	while(!queue.empty()){
		int p = queue.front();
		queue.pop_front();

		//check if need to cycle frame index
		if(frame_index == pfr.frames){
			frame_index = 0;
			all_touched = true;
		}

		//if not all frames have been touched, cycle
		if(!all_touched){
			bool hit = false;
			//determine if value already loaded
			for(i=0; i<pfr.frames; ++i){
				if(frame[i] == p){
					hit = true;
					break;
				}
			}

			//if loaded then say so
			if(hit){
				out<<"Page "<<p<<" already in Frame "<<i<<std::endl;
			}

			//if not loaded, load
			if(!hit){
				frame[frame_index] = p;
				out<<"Page "<<p<<" loaded into Frame "<<frame_index<<std::endl;
				++frame_index;
				++errors;

				//since frame[] changed, recalc occurences
				for(i=0; i<pfr.frames; ++i){
					count_time[i] = next_occurence(frame[i], counter);
				}
			}
		}
		else if(all_touched){
			bool hit = false;
			//determine if value already loaded
			for(i=0; i<pfr.frames; ++i){
				if(frame[i] == p){
					hit = true;
					break;
				}
			}

			//if loaded then say so
			if(hit){
				out<<"Page "<<p<<" already in Frame "<<i<<std::endl;
			}

			//if not loaded, if has infinity, replace there, else replace longest
			if(!hit){
				//if infinity then break, else continue for longest
				for(i=0; i<pfr.frames; ++i){
					if(count_time[i] == -1){
						frame_index = i;
						break;
					}
					else{
						//here for not infinity
						if(count_time[i] > count_time[frame_index]){
							frame_index = i;
						}
					}

				}

				//now act on replacement
				out<<"Page "<<frame[frame_index]<<" unloaded from Frame "<<frame_index<<", Page "<<p<<" loaded into Frame "<<frame_index<<std::endl;
				frame[frame_index] = p;
	
				//since frame[] changed, recalc occurences
				for(i=0; i<pfr.frames; ++i){
					count_time[i] = next_occurence(frame[i], counter);
				}

				++errors;
			}		
		}
		++counter;
	}
	out<<errors<<" page faults"<<std::endl;
}

/* return -1 if infinite */
int next_occurence(int page, int current_queue_index){
	int i;
	int count = 0;
	bool found = false;
	for(i=current_queue_index; i<pfr.num_requests; ++i){
		if(pfr.requests[i] == page && current_queue_index != i){
			count = i - current_queue_index;
			found = true;
			break;
		}
	}
	if(!found)
		return -1;
	else	return count;
}

void read_and_store(){
	std::string line;
	std::getline(in, line);
	std::istringstream iss(line);
	
	/* get pfr info */
	iss >> pfr.pages >> pfr.frames >> pfr.num_requests; 
	
	int i;
	for(i=0; i< pfr.num_requests; ++i){
		int r;
		in >> r;	
		pfr.requests.push_back(r);
	}
}
