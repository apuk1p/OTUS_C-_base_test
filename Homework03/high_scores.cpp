#include<iostream>
#include<fstream>
#include<string>

#include "check_value.h"

const std::string high_scores_filename = "high_scores.txt";

void read_from_file(){
	std::ifstream in_file(high_scores_filename);
	if (!in_file.is_open()){
		std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
	}

	std::cout << "High scores table:" << std::endl;
	std::string username;
	int high_score = 0;
	while (true){
		in_file >> username;
		in_file >> high_score;
		in_file.ignore();

		if(in_file.fail()){
			break;
		}
		std::cout << username << '\t' << high_score << '\t' << std::endl;
	}
}

int high_scores(const int &level){

	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;
	//const int attempts_amount = check_value(level);
	{	
		std::fstream io_file(high_scores_filename, std::ios_base::in | std::ios_base::out | std::fstream::app);

		std::string previous_name;
		int previous_score = 0;

		if(!io_file.is_open()){
			std::cout <<"Failed to open file for write: " << high_scores_filename << "!" << std::endl;
			return -1;
		}
		//io_file >> previous_name;
		io_file.seekp(0);
		io_file.put('x');
		
		//io_file >> previous_score;

		// while(true){
		// 	io_file >> previous_name;
		// 	io_file >> previous_score;

		// 	if( previous_name == user_name ){
		// 		io_file.seekp(0, std::ios::cur);

		// 		break;
		// 	}

		// 	io_file.ignore();
		// 	if(io_file.fail()){
		// 		break;
		// 	}
		// }

		//std::cout << previous_name << std::endl;
		std::cout << previous_name << '\t' << previous_score << std::endl;
		

		// std::ofstream out_file(high_scores_filename, std::ios_base::app);
		// if(!out_file.is_open()){
		// 	std::cout <<"Failed to open file for write: " << high_scores_filename << "!" << std::endl;
		// 	return -1;
		// }
		// out_file << user_name << '\t';
		// out_file << attempts_amount;

		// out_file << std::endl;
	
	}
	//read_from_file();

	return 0;
}