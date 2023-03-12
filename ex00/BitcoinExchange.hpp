#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

typedef vector<string> vectring;

class BitcoinExchange {
  private:
	BitcoinExchange();
	vector<vectring> content;
	vectring		 row;
	string			 line;
	string			 word;
	string			 file_name;

  public:
	explicit BitcoinExchange(string file_name);
	// BitcoinExchange(const BitcoinExchange &bitcoinExchange);
	// BitcoinExchange &operator=(const BitcoinExchange &bitcoinExchange);
	// ~BitcoinExchange();

	void		init();
	int			checkType(string str);
	int			stringToInt(string str);
	double		stringToDouble(string str);
	vector<int> splitDate(const string &str);
	int			validate(int i);
	void		print();

	class BadInput : public std::exception {
		virtual const char *what() const throw() {
			return "bad input";
		}
	};
	class NegativeNumber : public std::exception {
		virtual const char *what() const throw() {
			return "not a positive number.";
		}
	};
	class LargeNumber : public std::exception {
		virtual const char *what() const throw() {
			return "too large a number.";
		}
	};
};

#endif
