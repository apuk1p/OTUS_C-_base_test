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

std::condition_variable condition_variable;
std::mutex mutex;
bool notificated = false;

std::string tolower(const std::string &str);

void count_words(std::istream& stream, Counter&);

void print_topk(std::ostream& stream, const Counter&, const size_t k);

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: topk_words [FILES...]\n";
		return EXIT_FAILURE;
	}

	auto start = std::chrono::high_resolution_clock::now();

	Counter freq_dict;
	WorkQueue work_queue;

	std::ifstream input;
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
	// count_words(input, freq_dict);
	std::thread reader{
		count_words,
		std::ref(input),
		std::ref(freq_dict)
	};
	std::thread writer{
		print_topk,
		std::ref(std::cout),
		std::cref(freq_dict),
		TOPK
	};

	reader.join();
	writer.join();

	// print_topk(std::cout, freq_dict, TOPK);
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

void count_words(std::istream& stream, Counter& counter) {
	std::unique_lock<std::mutex> lock(mutex);
	std::for_each(std::istream_iterator<std::string>(stream),
				std::istream_iterator<std::string>(),
				 [&counter](const std::string &s) { ++counter[tolower(s)];
				 condition_variable.notify_all();
				 std::cout << "FIRST" << std::endl;
				 notificated = true;
				  });
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
	std::unique_lock<std::mutex> lock(mutex);
	while(!notificated) condition_variable.wait(lock);
	std::cout << "SECOND" << std::endl;
	std::vector<Counter::const_iterator> words;
	words.reserve(counter.size());
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