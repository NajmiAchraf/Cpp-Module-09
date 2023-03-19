#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
	cout << C_GREEN << "Default constructor" << C_RES << endl;
}

PmergeMe::PmergeMe(char **nbrs) {
	cout << C_GREEN << "Parameterize constructor" << C_RES << endl;

	this->_nbrs = nbrs;

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
		this->_entry = pmergeMe._entry;
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

	if (str[i] == '-') {
		sign = -1;
		i++;
	} else if (str[i] == '+')
		i++;
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
}

void PmergeMe::getResult() {
}
