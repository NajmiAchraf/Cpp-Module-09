#ifndef RPN_HPP
#define RPN_HPP

#include <algorithm>
#include <cstring>
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
	char		 *_entry, *_ptr;
	string		  str;
	stack<double> _num_stack;
	char		 *_next_token;
	int			  o;
	double		  a, b, r;

  public:
	RPN(char *entry);
	RPN(const RPN &rpn);
	RPN &operator=(const RPN &rpn);
	~RPN();

	int	 stringToInt(string str);
	void getResult();

	class Error : public std::exception {
	  public:
		virtual const char *what() const throw() {
			return "Error";
		}
	};
};

#endif
