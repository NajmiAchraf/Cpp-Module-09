#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <algorithm>
#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define C_RES "\033[0m"
#define C_RED "\033[1;31m"
#define C_GREEN "\033[1;32m"
#define C_CYAN "\033[1;36m"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

typedef vector<string> vectring;

class BitcoinExchange {
  private:
	BitcoinExchange();
	vector<vectring> base;
	vector<vectring> content;
	vectring		 row;
	string			 line;
	string			 word;
	const string	 file_name;

  public:
	BitcoinExchange(string file_name);
	BitcoinExchange(const BitcoinExchange &bitcoinExchange);
	BitcoinExchange &operator=(const BitcoinExchange &bitcoinExchange);
	~BitcoinExchange();

	void		init();
	void		strim(int i, char spliter);
	void		fill(vector<vectring> &to_fill, string name_file, char spliter);
	int			checkType(string str);
	int			stringToInt(string str);
	double		stringToDouble(string str);
	vector<int> splitDate(const string &str);
	void		validateDate(int i);
	double		validate(int i);
	int			findPrevious(int i);
	int			find(int i);
	void		print(int i, int value, int index);
	void		print();

	class OpenFile : public std::exception {
	  public:
		virtual const char *what() const throw() {
			return "could not open file.";
		}
	};
	class BadInput : public std::exception {
	  public:
		virtual const char *what() const throw() {
			return "bad input";
		}
	};
	class NegativeNumber : public std::exception {
	  public:
		virtual const char *what() const throw() {
			return "not a positive number.";
		}
	};
	class LargeNumber : public std::exception {
	  public:
		virtual const char *what() const throw() {
			return "too large a number.";
		}
	};
};

#endif
