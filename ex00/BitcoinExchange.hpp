#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <iterator>

#ifndef BITCOIN_HPP
#define BITCOIN_HPP

class BitcoinExchange
{
	private:
		double value;
		std::map<std::string, double> data;

	public:
		BitcoinExchange();
		void fill_data(void);
		void file_parsing(char *str);
		int check_date(std::string date);
		int check_value(std::string value);
		double bring_rate(std::string date);
		bool is_digit(std::string str);
		~BitcoinExchange();
};

#endif