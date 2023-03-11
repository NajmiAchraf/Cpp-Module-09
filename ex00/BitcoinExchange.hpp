#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
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
	vector<string>	 row;
	string			 line, word;

  public:
	BitcoinExchange(string file_name);
	// BitcoinExchange(const BitcoinExchange &bitcoinExchange);
	// BitcoinExchange &operator=(const BitcoinExchange &bitcoinExchange);
	// ~BitcoinExchange();

	void init(string file_name);
	void print();
};

#endif
