#ifndef RPN_HPP
#define RPN_HPP

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

#define C_RES "\033[0m"
#define C_RED "\033[1;31m"
#define C_GREEN "\033[1;32m"
#define C_CYAN "\033[1;36m"

using std::cerr;
using std::cout;
using std::endl;
using std::stack;
using std::string;

class RPN {
  private:
	RPN();
	string _entry;

  public:
	RPN(string entry);
	RPN(const RPN &rpn);
	RPN &operator=(const RPN &rpn);
	~RPN();

	void init();
	int	 checkType(string str);
	int	 stringToInt(string str);

	class Error : public std::exception {
	  public:
		virtual const char *what() const throw() {
			return "Error";
		}
	}
};

#endif
