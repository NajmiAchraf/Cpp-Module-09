#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <array>
#include <ctime>
#include <deque>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <string>

#define C_RES "\033[0m"
#define C_RED "\033[1;31m"
#define C_GREEN "\033[1;32m"
#define C_CYAN "\033[1;36m"

using std::array;
using std::cerr;
using std::cout;
using std::deque;
using std::endl;
using std::map;
using std::string;

class PmergeMe {
  private:
	PmergeMe();
	char		**_nbrs;
	size_t		  _len;
	map<int, int> _num_map;
	deque<int>	  _num_dqu;

  public:
	PmergeMe(int ac, char **av);
	PmergeMe(const PmergeMe &pmergeMe);
	PmergeMe &operator=(const PmergeMe &pmergeMe);
	~PmergeMe();

	int	 stringToInt(string str);
	void init();

	map<int, int> merge_sort(map<int, int> _left_arr, map<int, int> _right_arr);
	map<int, int> insert_sort(map<int, int> _arr);
	map<int, int> merge_insert_sort(map<int, int> _arr);

	deque<int> merge_sort(deque<int> _left_arr, deque<int> _right_arr);
	deque<int> insert_sort(deque<int> _arr);
	deque<int> merge_insert_sort(deque<int> _arr);

	class Error : public std::exception {
	  public:
		virtual const char *what() const throw() {
			return "Error";
		}
	};
};

#endif
