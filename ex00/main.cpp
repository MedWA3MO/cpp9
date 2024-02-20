#include "BitcoinExchange.hpp"

int main(int ac, char **arv)
{
	if (ac == 2)
	{
		BitcoinExchange btc;
		btc.fill_data();
		btc.file_parsing(arv[1]);
	}
	else
		std::cout << "Error: could not open file." << std::endl;
	return (0);
}