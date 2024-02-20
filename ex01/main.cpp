#include "RPN.hpp"

int main(int ac, char **arv)
{
	std::string args;
	if (ac == 2)
	{
		RPN rpn;
		args = arv[1];
		rpn.polish_not(args);
		if (rpn.get_found())
			std::cout << rpn.get_result() <<std::endl;
	}
	else
		std::cout << "Error: num of args is incorrect." << std::endl;
	return (0);
}