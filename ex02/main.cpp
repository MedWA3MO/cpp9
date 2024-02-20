#include "PmergeMe.hpp"


int main(int ac , char **av)
{
	unsigned long long t1;
	unsigned long long t2;
	unsigned long long t3;

	if (ac > 2)
	{
		PmergeMe pmergeme;
		if (!pmergeme.parsing(av, ac - 1))
			return (1);
		t1 = pmergeme.get_time();
		pmergeme.first_container(av, ac - 1);
		t2 = pmergeme.get_time();
		std::cout << std::endl << "Time : " << t2 - t1 << std::endl << std::endl;
		pmergeme.second_container(av, ac - 1);
		t3 = pmergeme.get_time();
		std::cout  << std::endl << "Time : " << t3 - t2 << std::endl;
	}
	else
	{
		std::cout << "Error usage" << std::endl;
	}
	return (0);
}



//
