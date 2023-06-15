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
int counter1 = 0;

using Counter = std::map<std::string, std::size_t>;
using WorkQueue = WaitingQueue<Counter>;


std::string tolower(const std::string &str);
void count_words(std::istream& stream, WorkQueue&, std::atomic<bool>& stop_flag);
void print_topk(std::ostream& stream, WorkQueue&, const size_t k);


int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: topk_words [FILES...]\n";
		return EXIT_FAILURE;
	}

	auto start = std::chrono::high_resolution_clock::now();
	std::ifstream input;
	std::atomic<bool> stop_flag = false;

	Counter freq_dict;
	WorkQueue work_queue;
	std::vector<std::string> filesArray;
	std::vector<std::thread> threadPool;

	for (int i = 1; i < argc; ++i) 
	{
		filesArray.push_back(argv[i]);
	}

	threadPool.reserve(filesArray.size());

	for(const auto& val : filesArray)
	{
		input.open(val, std::ios_base::in);
		// std::ifstream input{val};
		if (!input.is_open()) {
			std::cerr << "Failed to open file " << val << '\n';
			return EXIT_FAILURE;
		}
		threadPool.push_back( std::thread( count_words, std::ref(input), std::ref(work_queue), std::ref(stop_flag)));
		// count_words(input, work_queue);
		input.close();
		// freq_dict.merge(temp);
	}

	for(int i = 0; i < threadPool.size(); i++)
	{
		threadPool[i].join();
	}
	while(work_queue.pop(freq_dict))
	{
		std::cout << "CHECING" << std::endl;
	}
	// stop_flag = true;
	// work_queue.stop();
	// print_topk(std::cout, work_queue, TOPK);
	std::cout << "TEST1 " << counter1 << std::endl;
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

void count_words(std::istream& stream, WorkQueue& queue, std::atomic<bool>& stop_flag) {
	Counter counter;
	std::for_each(std::istream_iterator<std::string>(stream),
				std::istream_iterator<std::string>(),
				[&counter](const std::string &s) { ++counter[tolower(s)]; });
	if(!stop_flag) queue.push(counter);
	++counter1;
	// queue.stop();
}

void print_topk(std::ostream& stream, WorkQueue& queue, const size_t k) {
	std::vector<Counter::const_iterator> words;
	Counter counter;
	std::cout << queue.pop(counter) << std::endl;
	while(queue.pop(counter))
	{
		std::cout << "TEST" << std::endl;
		std::cout << queue.pop(counter) << std::endl;
		// for(auto [k,v] : counter)
		// {
		// 	// std::cout << "4LEN" << std::endl;
		// }
	}

	// for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
	// 	words.push_back(it);
	// }
	// std::partial_sort(
	// 	std::begin(words), std::begin(words) + k, std::end(words),
	// 	[](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

	// std::for_each(
	// 	std::begin(words), std::begin(words) + k,
	// 	[&stream](const Counter::const_iterator &pair) {
	// 		stream << std::setw(4) << pair->second << " " << pair->first
	// 				<< '\n';
	// 	});
}