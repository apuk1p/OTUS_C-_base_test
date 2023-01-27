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

	//check an input values
	const int attempts_amount = check_value(level);

	{	
		std::fstream io_file(high_scores_filename, std::ios_base::in | std::ios_base::out );

		std::string previous_name;
		int previous_score = 0;
		bool name_in_file = false;
		bool first_launch = true;

		//check if it is the first launch, skip this check
		if(!io_file.is_open() && !first_launch){
			std::cout <<"Failed to open file for write: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

		while(io_file >> previous_name || io_file >> previous_score){
			
			if(previous_name == user_name){
				name_in_file = true;
				io_file >> previous_score;
				if(previous_score > attempts_amount){
					if(previous_score < 9){
						io_file.seekg(-1, std::ios::cur);
						io_file << attempts_amount;
						io_file.seekg(io_file.tellg(), std::ios::beg);
					}
					else if( previous_score >= 10 ) {
						io_file.seekg(-2, std::ios::cur);
						io_file << attempts_amount << " ";
						io_file.seekg(io_file.tellg(), std::ios::beg);
					}
				}
			}

			io_file >> previous_score;
		}

		//write in a file, if name not in file
		if(!name_in_file){
			std::fstream i_file(high_scores_filename, std::ios::out | std::ios::app);

			if(!i_file.is_open()){
				std::cout <<"Failed to open file for write: " << high_scores_filename << "!" << std::endl;
				return -1;
			}

			i_file << user_name << '\t';
			i_file << attempts_amount;
			i_file << std::endl;
		}

		first_launch = false;
	}
	
	read_from_file();

	return 0;
}