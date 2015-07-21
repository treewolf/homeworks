#include <iostream>

//this is the character that will be forming triangle
#define c '|'

void level(int k);
int n, m = 1;

int main(){
	std::string str;
	std::cout<<"How many levels? ";
	std::cin>>n;
	str.assign(n-1,' ');
	std::cout<<str<<c<<"\n";
	if(n<2){	return 0;	}
	else{	level(n);	}
	return 0;	
}

void level(int k){
	std::string str;
	if(k!=1){
		str.assign(k-2,' ');
		std::cout<<str;
		str.assign(m+2,c);
		m+=2;
		std::cout<<str<<"\n";
		level(k-1);	
	}
}
