#include "PmergeMe.hpp"
#include <iterator>

PmergeMe::PmergeMe(/* args */)
{
}

int PmergeMe::parsing(char **str, int size)
{
	std::string args[size];

	for (int i = 0; i < size; i++)
		args[i] = str[i + 1];
	for (int i = 0; i < size; i++)
	{
		for (unsigned int j = 0; j < args[i].length(); j++)
		{
			if(args[i][0] == '+')
				continue;
			if (args[i][0] == '-')
			{
				std::cout << "Error: argument " << args[i] << " is negative" << std::endl;
				return 0;
			}
			else if(!isdigit(args[i][j]))
			{
				std::cout << "Error: argument " << args[i] << " not digit" << std::endl;
				return (0);
 			}
		}
	}
	return 1;
}

void PmergeMe::first_container(char **av, int size)
{
	std::vector<int> vec;
	int struggler;
	struggler = -1;
	if(size % 2)
	{
		struggler = atoi(av[size]);
		--size;
	}
	for (int i = 0; i < size; i++)
		vec.push_back(atoi(av[i + 1]));
	// vector content :
	std::vector<std::pair<int, int> > pair_vec;
	std::vector<int>::iterator it3 = vec.begin();
	std::vector<int>::iterator it4 = vec.end();
	int j = 0;
	while (it3 != it4)
	{
		pair_vec.push_back(std::make_pair(*(it3++), *(it3++)));
		if(pair_vec[j].first < pair_vec[j].second)
		{
			int swap;
			swap = pair_vec[j].first;
			pair_vec[j].first = pair_vec[j].second;
			pair_vec[j].second = swap;
		}
		j++;
	}
	// the pairs :
	std::vector<std::pair<int, int> >::iterator it6 = pair_vec.end();
	std::vector<std::pair<int, int> >::iterator it7 = pair_vec.begin();
	std::vector<std::pair<int, int> >::iterator it8;
	j = 0;
	int i = 0;
	while (it7 != it6)
	{
		it8 = it7 + 1;
		j = i + 1;
		while (it8 != it6)
		{
			if(pair_vec[i].first > pair_vec[j].first)
			{
				int tmp1 = pair_vec[i].first;
				int tmp2 = pair_vec[i].second;
				pair_vec[i] = pair_vec[j];
				pair_vec[j].first = tmp1;
				pair_vec[j].second = tmp2;
			}
			it8++;
			j++;
		}
		i++;
		it7++;
	}
	// after sorting the vector of pairs:
	std::vector<int> main_chain;
	std::vector<int> pend;
	i = 0;
	while (i < size / 2)
	{
		if (i == 0)
		{
			main_chain.push_back(pair_vec[0].second);
			main_chain.push_back(pair_vec[0].first);
		}
		else
		{
			main_chain.push_back(pair_vec[i].first);
			pend.push_back(pair_vec[i].second);
		}
		i++;
	}
	// the main chain and the pend :
	std::vector<int> jacob = jacob_sequence(size);
	std::vector<int> my_indexing = indexing(size);
	std::vector<int> comb = combination(jacob, my_indexing);
	// the jacob sequence :
	std::vector<int> sec_pend;
	int index;
	unsigned int number;
	sec_pend = pend;
	std::vector<int>::iterator it;
	for (unsigned int i = 0; i < pend.size(); i++)
	{
		number = comb[i] - 1;
		while (number >= pend.size())
			number--;
		it = std::find(sec_pend.begin(), sec_pend.end(), pend[number]);
		while (it == sec_pend.end())
		{
			number--;
			it = std::find(sec_pend.begin(), sec_pend.end(), pend[number]);
		}
		index = get_index(main_chain, pend[number]);
		main_chain.insert(main_chain.begin() + index, pend[number]);
		if (it != sec_pend.end())
			sec_pend.erase(it);
	}
	if (struggler != -1)
	{
		index = get_index(main_chain, struggler);
		main_chain.insert(main_chain.begin() + index, struggler);
	}
	std::cout << "        First container :    " << std::endl << std::endl;
	for (unsigned int i = 0; i < main_chain.size(); i++)
	{
		std::cout << main_chain[i] << "  " ;
	}
	std::cout << std::endl;
}

std::vector<int> PmergeMe::jacob_sequence(int size)
{
	std::vector<int> jacob;
	jacob.push_back(0);
	jacob.push_back(1);
	for (int i = 2; i < size; i++)
	{
		jacob.push_back(jacob[i - 1] + (jacob[i - 2] * 2));
	}
	return (jacob);
}

std::vector<int> PmergeMe::indexing(int size)
{
	std::vector<int> index;
	for (int i = 0; i < size; i++)
	{
		index.push_back(i);
	}
	return (index);
}

std::vector<int> PmergeMe::combination(std::vector<int> jacob, std::vector<int> indexing)
{
	std::vector<int> comb;
	indexing.erase(indexing.begin(), indexing.begin() + 2);
	if (jacob.size() > 3)
		jacob.erase(jacob.begin(), jacob.begin() + 3);
	std::vector<int>::iterator it1 = jacob.begin();
	std::vector<int>::iterator it2 = jacob.end();
	std::vector<int>::iterator it3;
	int target = 0;
	while (it1 != it2)
	{
		target = *it1;
		it3 = std::find(indexing.begin(), indexing.end(), target);
		while(it3 != indexing.end())
		{
			// it's found
			comb.push_back(target);
			indexing.erase(it3);
			target--;
			it3 = std::find(indexing.begin(), indexing.end(), target);
			while (it3 == indexing.end() && target > 0)
			{
				target--;
				it3 = std::find(indexing.begin(), indexing.end(), target);
			}
		}
		it1++;
	}
	return (comb);
}

int PmergeMe::get_index(std::vector<int> tab, int target)
{
	unsigned int size = tab.size();
	if (target > tab[size - 1])
		return (size);
	int lower = 0;
	int upper = tab.size() - 1;
	int mid;
	while (lower <= upper)
	{
		mid = (lower + upper) / 2;
		if (target < tab[mid])
			upper = mid - 1;
		else
			lower = mid + 1;
	}
	return lower;
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::second_container(char **av, int size)
{
	std::deque<int> vec;
	int struggler;
	struggler = -1;
	if(size % 2)
	{
		struggler = atoi(av[size]);
		--size;
	}
	for (int i = 0; i < size; i++)
		vec.push_back(atoi(av[i + 1]));
	// vector content :
	std::deque<std::pair<int, int> > pair_vec;
	std::deque<int>::iterator it3 = vec.begin();
	std::deque<int>::iterator it4 = vec.end();
	int j = 0;
	while (it3 != it4)
	{
		pair_vec.push_back(std::make_pair(*(it3++), *(it3++)));
		if(pair_vec[j].first < pair_vec[j].second)
		{
			int swap;
			swap = pair_vec[j].first;
			pair_vec[j].first = pair_vec[j].second;
			pair_vec[j].second = swap;
		}
		j++;
	}
	// the pairs :
	std::deque<std::pair<int, int> >::iterator it6 = pair_vec.end();
	std::deque<std::pair<int, int> >::iterator it7 = pair_vec.begin();
	std::deque<std::pair<int, int> >::iterator it8;
	j = 0;
	int i = 0;
	while (it7 != it6)
	{
		it8 = it7 + 1;
		j = i + 1;
		while (it8 != it6)
		{
			if(pair_vec[i].first > pair_vec[j].first)
			{
				int tmp1 = pair_vec[i].first;
				int tmp2 = pair_vec[i].second;
				pair_vec[i] = pair_vec[j];
				pair_vec[j].first = tmp1;
				pair_vec[j].second = tmp2;
			}
			it8++;
			j++;
		}
		i++;
		it7++;
	}
	// after sorting the vector of pairs:
	std::deque<int> main_chain;
	std::deque<int> pend;
	i = 0;
	while (i < size / 2)
	{
		if (i == 0)
		{
			main_chain.push_back(pair_vec[0].second);
			main_chain.push_back(pair_vec[0].first);
		}
		else
		{
			main_chain.push_back(pair_vec[i].first);
			pend.push_back(pair_vec[i].second);
		}
		i++;
	}
	// the main chain and the pend :
	std::deque<int> jacob = jacob_sequence2(size);
	std::deque<int> my_indexing = indexing2(size);
	std::deque<int> comb = combination2(jacob, my_indexing);
	// the jacob sequence :
	std::deque<int> sec_pend;
	int index;
	sec_pend = pend;
	unsigned int number;
	std::deque<int>::iterator it;
	for (unsigned int i = 0; i < pend.size(); i++)
	{
		number = comb[i] - 1;
		while (number >= pend.size())
			number--;
		it = std::find(sec_pend.begin(), sec_pend.end(), pend[number]);
		while (it == sec_pend.end())
		{
			number--;
			it = std::find(sec_pend.begin(), sec_pend.end(), pend[number]);
		}
		index = get_index2(main_chain, pend[number]);
		main_chain.insert(main_chain.begin() + index, pend[number]);
		if (it != sec_pend.end())
			sec_pend.erase(it);
	}
	if (struggler != -1)
	{
		index = get_index2(main_chain, struggler);
		main_chain.insert(main_chain.begin() + index, struggler);
	}
	std::cout << "        Second container :" << std::endl << std::endl;
	for (unsigned int i = 0; i < main_chain.size(); i++)
	{
		std::cout << main_chain[i] << "  " ;
	}
	std::cout << std::endl;
}

std::deque<int> PmergeMe::jacob_sequence2(int size)
{
	std::deque<int> jacob;
	jacob.push_back(0);
	jacob.push_back(1);
	for (int i = 2; i < size; i++)
	{
		jacob.push_back(jacob[i - 1] + (jacob[i - 2] * 2));
	}
	return (jacob);
}

std::deque<int> PmergeMe::indexing2(int size)
{
	std::deque<int> index;
	for (int i = 0; i < size; i++)
	{
		index.push_back(i);
	}
	return (index);
}

std::deque<int> PmergeMe::combination2(std::deque<int> jacob, std::deque<int> indexing)
{
	std::deque<int> comb;
	indexing.erase(indexing.begin(), indexing.begin() + 2);
	if (jacob.size() > 3)
		jacob.erase(jacob.begin(), jacob.begin() + 3);
	std::deque<int>::iterator it1 = jacob.begin();
	std::deque<int>::iterator it2 = jacob.end();
	std::deque<int>::iterator it3;
	int target = 0;
	while (it1 != it2)
	{
		target = *it1;
		it3 = std::find(indexing.begin(), indexing.end(), target);
		while(it3 != indexing.end())
		{
			// it's found
			comb.push_back(target);
			indexing.erase(it3);
			target--;
			it3 = std::find(indexing.begin(), indexing.end(), target);
			while (it3 == indexing.end() && target > 0)
			{
				target--;
				it3 = std::find(indexing.begin(), indexing.end(), target);
			}
		}
		it1++;
	}
	return (comb);
}

int PmergeMe::get_index2(std::deque<int> tab, int target)
{
	unsigned int size = tab.size();
	if (target > tab[size - 1])
		return (size);
	int lower = 0;
	int upper = tab.size() - 1;
	int mid;
	while (lower <= upper)
	{
		mid = (lower + upper) / 2;
		if (target < tab[mid])
			upper = mid - 1;
		else
			lower = mid + 1;
	}
	return lower;
}


unsigned long long	PmergeMe::get_time(void)
{
	unsigned long long		sec;
	unsigned long long		u_sec;
	struct timeval			cur_time;

	if (gettimeofday(&cur_time, NULL))
		std::cout << "error in get time func" << std::endl;
	sec = (unsigned long long)cur_time.tv_sec * 1000000;
	u_sec = (unsigned long long)cur_time.tv_usec;
	sec += u_sec;
	return (sec);
}
