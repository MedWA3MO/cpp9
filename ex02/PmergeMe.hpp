#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <utility>
# include <sys/time.h>

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

class PmergeMe
{
	private:
		/* data */
	public:
		PmergeMe(/* args */);
		int parsing(char **str, int size);
		void first_container(char **av, int size);
		std::vector<int> jacob_sequence(int size);
		std::vector<int> indexing(int size);
		std::vector<int> combination(std::vector<int> jacob, std::vector<int> indexing);
		int get_index(std::vector<int> tab, int target);
		void second_container(char **av, int size);
		std::deque<int> jacob_sequence2(int size);
		std::deque<int> indexing2(int size);
		std::deque<int> combination2(std::deque<int> jacob, std::deque<int> indexing);
		int get_index2(std::deque<int> tab, int target);
		unsigned long long	get_time(void);
		~PmergeMe();
};

#endif