// Read files and prints top k word by frequency

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
#include <future>
#include <string>
#include <numeric>
#include "waiting_queue.h"

const size_t TOPK = 10;


using Counter = std::map<std::string, std::size_t>;
using WorkQueue = WaitingQueue<std::string>;
using cntIterator = std::vector<Counter::const_iterator>;

std::string tolower(const std::string &str);

void count_words(std::atomic<bool>&, WorkQueue&, std::istream& stream);

void print_topk(WorkQueue& ,std::ostream& stream, Counter&, cntIterator&);

void print(cntIterator& , const size_t k, std::ostream& stream);

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: topk_words [FILES...]\n";
		return EXIT_FAILURE;
	}

	auto start = std::chrono::high_resolution_clock::now();

	Counter freq_dict;
	WorkQueue work_queue;
	cntIterator Words;

	std::ifstream input;
	int n_threads;
	std::atomic<bool> stop_flag = false;

	for (int i = 1; i < argc; ++i) {
		if( i == 1) input.open(argv[i], std::ios_base::in);

		if (!input.is_open()) {
			std::cerr << "Failed to open file " << argv[i] << '\n';
			return EXIT_FAILURE;
		}
		n_threads = (i == 2) ? std::stoi( argv[2] ) : std::thread::hardware_concurrency();

		if(n_threads < 1)
		{
			std::cerr << "threads nums should be positive\n";
			return EXIT_FAILURE;
		}
	}
	std::vector<std::thread> thrPool;
	
	for(int i = 1; i < n_threads; i++)
	{
		if(i == 1) thrPool.push_back(std::thread(count_words, std::ref(stop_flag), std::ref(work_queue), std::ref(input)));

		thrPool.push_back(std::thread(print_topk, std::ref(work_queue), std::ref(std::cout), std::ref(freq_dict), std::ref(Words)));
	}
	for(int i = 0; i < thrPool.size(); i++)
	{
		thrPool[i].join();
	}

	print(Words, TOPK, std::cout);
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}

std::string tolower(const std::string &str) {
	std::string lower_str;
	auto lambda = [&](unsigned char ch) { return std::tolower(ch); };
	auto rmLambda =[&lower_str](unsigned char c){ 
					if( !std::isalpha(c) ){ lower_str.erase( std::remove( lower_str.begin(), lower_str.end(), c ), lower_str.end() ); }
					};
	std::transform(std::cbegin(str), std::cend(str),
					std::back_inserter(lower_str),
					lambda );
	std::for_each(lower_str.begin(), lower_str.end(), 
				rmLambda );
	
	return lower_str;
};

void count_words(std::atomic<bool>& stop_flag, WorkQueue& queue, std::istream& stream) {
	std::for_each(std::istream_iterator<std::string>(stream),
				std::istream_iterator<std::string>(),
				 [&](const std::string &s) { 
				 if(!stop_flag) queue.push(tolower(s));
				  });
				  
	stop_flag = true;
	queue.stop();
}

void print_topk(WorkQueue& queue, std::ostream& stream, Counter& counter, cntIterator& words) {
	std::string val;

	while(queue.pop(val))
	{
		++counter[val];
	};

	words.reserve(counter.size());

	for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
		words.push_back(it);
	}
	

	// std::partial_sort(
	// 	std::begin(words), std::begin(words) + k, std::end(words),
	// 	[](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

	// std::for_each(
	// 	std::begin(words), std::begin(words) + k,
	// 	[&stream](const Counter::const_iterator &pair) {
	// 		stream << std::setw(4) << pair->second << " " << pair->first
	// 				 << '\n';
	// 	});
	// std::cout << " I'M HERE " << std::endl;
	// queue.stop();
}

void print(cntIterator& words, const size_t k, std::ostream& stream)
{
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