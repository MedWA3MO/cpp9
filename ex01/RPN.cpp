#include "RPN.hpp"

RPN::RPN(/* args */)
{
}

int RPN::get_result() const
{
	return this->result;
}

bool RPN::get_found() const
{
	return this->is_found;
}

void RPN::polish_not(std::string args)
{
	if (!check_args(args))
	{
		this->is_found = false;
		std::cout << "Error" << std::endl;
		return ;
	}
	for (unsigned int i = 0; i < args.length(); i++)
	{
		if (args[i] != '*' && args[i] != '+' && args[i] != '-' && args[i] != '/' && args[i] != 32)
		{
			this->_stack.push(args[i] - 48);
			continue;
		}
		else if (args[i] != 32)
		{
			int num1 = this->_stack.top();
			this->_stack.pop();
			int num2;
			if (this->_stack.size() > 0)
			{
				num2 = this->_stack.top();
				this->_stack.pop();
			}
			if (args[i] == '+')
				this->_stack.push(num2 + num1);
			if (args[i] == '*')
				this->_stack.push(num2 * num1);
			if (args[i] == '-')
				this->_stack.push(num2 - num1);
			if (args[i] == '/')
			{
				if (num1 == 0)
				{
					std::cout << "Error: Division by zero!!!" << std::endl;
					this->is_found = false;
					return ;
				}
				this->_stack.push(num2 / num1);
			}
		}
	}
	if (this->_stack.size() != 1)
	{
		std::cout << "Error" << std::endl;
		this->is_found = false;
		return ;
	}
	this->is_found = true;
	this->result = this->_stack.top();
	return ;
}

bool RPN::check_args(std::string args)
{
	unsigned int len;

	len = args.length();
	if (len < 4 || !isdigit(args[0]) || !isdigit(args[2]))
		return false;
	for (unsigned int i = 0; i < len; i++)
	{
		if (args[i] == '-' || args[i] == '+' || args[i] == '*' || args[i] == '/' || args[i] == 32)
		{
			if (i == len - 1 && args[i - 1] != 32)
				return false;
			else if (args[i] != 32 && args[i - 1] != 32 && args[i + 1] != 32)
				return false;
			continue;
		}
		if (!isdigit(args[i]))
			return false;
		if (i == 0 && args[i + 1] != 32)
			return false;
		if (i > 0 && (args[i - 1] != 32 || args[i + 1] != 32))
			return false;
	}
	while(args[len - 1] == ' ')
		len--;
	if (!(args[len - 1] == '-' || args[len - 1] == '+' || args[len - 1] == '*' || args[len - 1] == '/'))
		return false;
	return true;
}

RPN::~RPN()
{
}


//