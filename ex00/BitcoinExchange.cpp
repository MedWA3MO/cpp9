
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(/* args */)
{
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::fill_data(void)
{
	std::ifstream inf;
	std::string str1;

	inf.open("./data.csv");
	if (!inf.is_open())
		std::cout << "file not open!!!" << std::endl;
	while (getline(inf, str1))
	{
		this->data[str1.substr(0, 10)] = atof(str1.substr(11, str1.length()).c_str());
	}
}

void BitcoinExchange::file_parsing(char *file)
{
	std::string str;
	std::string date;
	std::ifstream inf;
	int position;
	str = file;

	position = 0;
	inf.open(str);
	if (!inf.is_open())
		std::cout << "file not open!!!" << std::endl;
	while (getline(inf, str))
	{
		if (!position && str == "date | value")
		{
			position = 1;
			continue;
		}
		else if (str.find(" | ", 0) != 10)
		{
			std::cout << "Error: bad input => " << str.substr(0, 10) << std::endl;
			continue;
		}
		date = str.substr(0, 10);
		if (check_date(date))
			std::cout << "Error: bad input => " << date << std::endl;
		else if (!check_value(str.substr(13, str.length() - 13)))
			std::cout << date << " => " << this->value << " = " << bring_rate(date) << std::endl;
	}
}

double BitcoinExchange::bring_rate(std::string date)
{
	std::map<std::string, double>::iterator iter = this->data.begin();
	std::map<std::string, double>::iterator key = this->data.lower_bound(date);
	if(key->first != iter->first &&  key->first != date)
		key--;
	return (key->second * this->value);
}

int BitcoinExchange::check_value(std::string value)
{
	if (!is_digit(value))
	{
		std::cerr << "Error: number is not digit." << std::endl;
		return (1);
	}
	this->value = atof(value.c_str());
	if (this->value < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return (1);
	}
	else if (this->value > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return (1);
	}
	return (0);
}

int BitcoinExchange::check_date(std::string date)
{
	std::string year;
	std::string month;
	std::string day;

	year = date.substr(0, 4);
	month = date.substr(5, 2);
	day = date.substr(8, 2);
	if (!is_digit(year) || !is_digit(month) || !is_digit(day))
	{
		return (1);
	}
	if (date[4] != '-' || date[7] != '-'
	|| atol(year.c_str()) < 2009 || atol(year.c_str()) > 2023
	|| atol(month.c_str()) < 1 || atol(month.c_str()) > 12
	|| atol(day.c_str()) < 1 || atol(day.c_str()) > 31)
		return (1);
	return (0);
}

bool BitcoinExchange::is_digit(std::string str)
{
	int dot;
	dot = 0;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[0] == '-' || str[0] == '+')
			i++;
		if (!isdigit(str[i]))
		{
			if (str[i] == '.')
				dot++;
			else
				return false;
		}
	}
	if (dot <= 1)
		return true;
	return false;
}
