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
using WorkQueue = WaitingQueue<Counter>;
using Words = std::vector<Counter::const_iterator>;


std::string tolower(const std::string &str);
void count_words(WorkQueue& queue, std::istream& stream, Counter&);
void print_topk(WorkQueue& queue, std::ostream& stream, const Counter&, Words&);
void print(Words& words, std::ostream& stream, const size_t k );


int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: topk_words [FILES...]\n";
		return EXIT_FAILURE;
	}

	auto start = std::chrono::high_resolution_clock::now();
	// Pool test;

	WorkQueue work_queue;
	std::atomic<bool> stop_flag = false;

	Counter freq_dict;
	std::ifstream input;
	Words words;
	int n_threads;

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
	
	std::thread thr1(count_words, std::ref(work_queue), std::ref(input), std::ref(freq_dict));
	std::thread thr2(print_topk, std::ref(work_queue), std::ref(std::cout), std::cref(freq_dict), std::ref(words));
	std::thread thr3(print_topk, std::ref(work_queue), std::ref(std::cout), std::cref(freq_dict), std::ref(words));

	std::this_thread::sleep_for(std::chrono::seconds{15});
	// stop all threads
	stop_flag = true;
	// // need this to unblock all threads, witch are waiting the queue
	work_queue.stop();
	// wait all threads
	thr1.join();
	thr2.join();
	thr3.join();

	// std::this_thread::sleep_for(std::chrono::seconds{10});
	// print(words, std::cout, TOPK);
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

void count_words(WorkQueue& queue, std::istream& stream, Counter& counter) {
	auto cnt = [&](const std::string &s) {++counter[tolower(s)];
										std::cout << " IN " << std::endl;
										queue.push(counter);};

	std::for_each(std::istream_iterator<std::string>(stream),
				std::istream_iterator<std::string>(),
				cnt);
	
	
	
}

void print_topk(WorkQueue& queue, std::ostream& stream, const Counter& counter, Words& words ) {
	words.reserve(counter.size());
	Counter val;
	while(queue.pop(val))
	{
		std::cout << " OUT " << std::endl;
		for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
			words.push_back(it);
		}
		// queue.stop();
	}
}

void print(Words& words, std::ostream& stream, const size_t k ){
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