#include <iostream>
#include <stack>

#ifndef RPN_HPP
#define RPN_HPP

class RPN
{
	private:
		std::stack<int> _stack;
		bool			is_found;
		int 			result;
	public:
		RPN(/* args */);
		void polish_not(std::string args);
		bool check_args(std::string args);
		int get_result() const;
		bool get_found() const;
		~RPN();
};

#endif