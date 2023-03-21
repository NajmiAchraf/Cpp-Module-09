#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
	cout << C_GREEN << "Default constructor" << C_RES << endl;
}

PmergeMe::PmergeMe(int ac, char **av) {
	cout << C_GREEN << "Parameterize constructor" << C_RES << endl;

	this->_nbrs = av;
	this->_len	= ac - 1;

	try {
		this->init();
		this->getResult();
	} catch (const PmergeMe::Error &e) {
		throw PmergeMe::Error();
	}
}

PmergeMe::PmergeMe(const PmergeMe &pmergeMe) {
	cout << C_CYAN << "Copy constructor" << C_RES << endl;
	*this = pmergeMe;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &pmergeMe) {
	cout << C_CYAN << "Copy assignment operator" << C_RES << endl;
	if (this != &pmergeMe) {
		this->_nbrs = pmergeMe._nbrs;
	}
	return *this;
}

PmergeMe::~PmergeMe() {
	cout << C_RED << "Destructor" << C_RES << endl;
}

int PmergeMe::stringToInt(string str) {
	int	 i	  = 0;
	int	 len  = str.length();
	int	 sign = 1;
	long num  = 0;

	if (str[i] == '\0')
		throw PmergeMe::Error();
	while (i < len) {
		if (isdigit(str[i]))
			num = num * 10 + (str[i] - '0');
		else
			throw PmergeMe::Error();
		i++;
	}
	return (static_cast<int>(num * sign));
}

void PmergeMe::init() {
	string s;
	for (size_t i = 0; i < this->_len; i++) {
		s = this->_nbrs[i + 1];

		this->_num_map[i] = stringToInt(s);
		this->_num_lst.push_back(stringToInt(s));
	}

	// list<int>::iterator it = this->_num_lst.begin();
	// for (size_t i = 0; i < this->_len; i++) {
	// 	cout << this->_num_map[i] << "   |   " << *it << endl;
	// 	it++;
	// }
}

void PmergeMe::merge_insert_sort() {
	if (this->_num_map.size() < 2) {
		return;
	}
}
