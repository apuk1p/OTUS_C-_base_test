#include <iostream>
#include <string>

#include "levels.h"
#include "random_value.h"

int check_value(const int &level){
	const int max_random_value = levels(level);

	const int target_value = random_value(max_random_value);
	int current_value = 0;
	bool not_win = true;
	int attempts_counter = 0;

	std::cout << "Enter your guess: " << std::endl;

	do{
		std::cin >> current_value;
		if(current_value < target_value){
			std::cout << current_value << " less than our number" << std::endl;
			attempts_counter++;
		}
		else if(current_value > target_value){
			std::cout << current_value <<" greater than our number" << std::endl;
			attempts_counter++;
		}
		else{
			attempts_counter++;
			std::cout << "you win! Attempts: " << attempts_counter << std::endl;
			not_win = false;
		}

	}while(not_win);

	return attempts_counter;
}