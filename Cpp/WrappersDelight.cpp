/**
	@author - treewolf
	Documentation:
		Wrapper's Delight 2015 ICPC @ CSUS
	
		Description - Wraps text to a user-defined width. Width must be as big as the 
			longest word in the text. Each line in the file should start and end
			with a printable non-space character. There are no tabs, and whenever
			a space occurs, there is only one. Words are not broken-up across lines.
			
		Input - First line consist of two numbers:
					First number is the number of lines of text that needs to be
						formatted.
					Second number is the maximum width.
				Second line asks for the path of the the text file that contains the
					text to be formatted.
					
			ex:
				8	20								
				I said a hip hop, Hippie				  I said a hip hop,
				to the hippie, The hip,			\		  Hippie to the
				hip a hop, and you don't	==	 \		  hippie, The hip, hip
				stop, a rock it To the 		==	 /		  a hop, and you don't
				bang bang boogie, say, up		/		  stop, a rock it To
				jump the boogie, To the					  the bang bang
				rythm of the boogie, the			  	  boogie, say, up jump
				beat.							  the boogie, To the
				          			                          rhythm of the 
			    		    		                            	  boogie, the beat.		
			
**/
#include <cstdio>	//printf(), flose();
#include <vector>	//std::vector<>, push_back()
#include <fstream>	//ifstream(), is_open()
#include <sstream>	//streamstream(), getline()
#include <cstring>	//std::string, c_str(), size()

unsigned int lines, max_width;
std::string text;
char file_path [100];

//Gets all user input and required information.
void setup(){
	printf("Enter number of lines of text: ");
	scanf("%d", &lines);
	printf("Enter new maximum line width: ");
	scanf("%d", &max_width);
	printf("Enter full file name: ");
	scanf("%99s", file_path);
}

//Reads text from a file.
//Puts all stdin into a std::string.
void read_file(){
	std::ifstream file;
	file.open(file_path);
	if(file.is_open()){
		int temp_int = lines;
		int count = 0;
		std::string temp_str;
		while(!file.eof() && temp_int != 0){
			std::getline(file, temp_str);	
			text += ' ' + temp_str;
			++count;
			--temp_int;
		}	
		text = text.substr(1,text.size() - 1);
	}
	file.close();
}

//Formats into expected text form.
//Also error checks with max_width against the longest word in text.
void format_and_print(){
	std::vector<std::string> temp_words, formatted;
	std::stringstream ss(text);
	std::string word;
	unsigned int longest_word_size = 0;
		
	while(std::getline(ss, word, ' ')){
		temp_words.push_back(word);
		if(longest_word_size < word.size()){
			longest_word_size = word.size();
		}
	}
	
	//error check for longer word than width allowed
	if(longest_word_size > max_width){
		printf("Error. Expected width too small for text. Program will terminate.");
		exit(1);
	}
	else{}
	
	//formatting algorithm
	unsigned int c, temp_width = max_width;
	for(c = 0; c < temp_words.size(); ++c){
		if(temp_words.at(c).size() + 1 < temp_width){
			printf("%s ",temp_words.at(c).c_str());
			temp_width -= (temp_words.at(c).size() + 1);
		}
		else{
			printf("\n%s ",temp_words.at(c).c_str());
			temp_width = max_width - (temp_words.at(c).size() + 1);
		}
	}
}

//Main method.
//Should return a value of 0 if successfully run.
int main(void){
	setup();
	read_file();	
	format_and_print();
	return 0;
}
