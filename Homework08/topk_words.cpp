#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>
#include "waiting_queue.h"

const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;
using WorkQueue = WaitingQueue<Counter>;


std::string tolower(const std::string &str);
int count_words(std::string file, WorkQueue&);
void print_topk(std::ostream& stream, Counter&, const size_t k);


int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: topk_words [FILES...]\n";
		return EXIT_FAILURE;
	}

	auto start = std::chrono::high_resolution_clock::now();
	// std::ifstream input;

	WorkQueue work_queue;
	std::vector<std::string> filesArray;
	std::vector<std::thread> threaReader;
	std::vector<std::thread> threaWriter;
	for (int i = 1; i < argc; ++i) 
	{
		filesArray.push_back(argv[i]);
	}

	threaReader.reserve(filesArray.size());

	for(const auto& file : filesArray)
	{
		threaReader.push_back( std::thread( count_words, file, std::ref(work_queue)));
	}

	for(int i = 0; i < threaReader.size(); i++)
	{
		threaReader[i].join();
	}

	work_queue.stop();

	Counter temp;
	Counter freq_dict;
	
	while(work_queue.pop(temp))
	{
		for(const auto& left : temp)
		{
			freq_dict[left.first] += left.second;
		}
	}

	print_topk(std::cout, freq_dict, TOPK);
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}

std::string tolower(const std::string &str) {
	std::string lower_str( str.size(), ' ' );
	std::transform(str.begin(), str.end(), lower_str.begin(),
				[](unsigned char ch) { return std::tolower(ch); });

	//still incorrect
	auto isNotAlpha = [](unsigned char c) { return !std::isalpha(c); };
	lower_str.erase( std::remove_if( lower_str.begin(), lower_str.end(), isNotAlpha),  
					lower_str.end() );
	return lower_str;
};

int count_words(std::string file, WorkQueue& queue) {
	std::ifstream input{file};
	
	if (!input.is_open()) {
		std::cerr << "Failed to open file " << file << '\n';
		return EXIT_FAILURE;
	}

	Counter counter;
	std::for_each(std::istream_iterator<std::string>(input),
				std::istream_iterator<std::string>(),
				[&counter](const std::string &s) { ++counter[tolower(s)]; });
	queue.push(counter);
	return 0;
}

void print_topk(std::ostream& stream, Counter& counter, const size_t k) {
	std::vector<Counter::const_iterator> words;

	for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
		words.push_back(it);
	}
	std::partial_sort(
		std::begin(words), std::begin(words) + k, std::end(words),
		[](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

	std::for_each(
		std::begin(words), std::begin(words) + k,
		[&stream](const Counter::const_iterator &pair) {
			stream << std::setw(4) << pair->second << " " << pair->first
					<< '\n';
		});
}