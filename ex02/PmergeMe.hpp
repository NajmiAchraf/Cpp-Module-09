#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <array>
#include <exception>
#include <iostream>
#include <map>
#include <string>

#define C_RES "\033[0m"
#define C_RED "\033[1;31m"
#define C_GREEN "\033[1;32m"
#define C_CYAN "\033[1;36m"

using std::array;
using std::cerr;
using std::cout;
using std::endl;
using std::map;
using std::string;

class PmergeMe {
  private:
	PmergeMe();
	char		**_nbrs;
	map<int, int> _num_map;
	array		  _num_arr;

  public:
	PmergeMe(char **nbrs);
	PmergeMe(const PmergeMe &pmergeMe);
	PmergeMe &operator=(const PmergeMe &pmergeMe);
	~PmergeMe();

	int	 stringToInt(string str);
	void init();
	void getResult();

	class Error : public std::exception {
	  public:
		virtual const char *what() const throw() {
			return "Error";
		}
	};
};

#endif
