#include <iostream>
#include <string>
#include "high_scores.h"


int main(int argc, char**argv){
	if(argc>=2){
		const std::string arg1_value = argv[1];

		if(arg1_value == "-table"){
			read_from_file();
		}
		else if(arg1_value == "-level"){
			int level = 0;
			if(argc < 3){
				std::cout << "Wrong usage! The argument '-level' requires 1,2 or 3 values!" << std::endl;
				return -1;
			}
			level = std::stoi(argv[2]);
			if(level == 1 || level == 2 || level == 3){
				high_scores(level);
			}
			else{
				std::cout << "Please, choose proper value 1,2 or 3!" << std::endl;
				return -1;
			}
		}
	}
	else{
		high_scores(0);
	}

	return 0;
}