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
	string str;
	for (size_t i = 0; i < this->_len; i++) {
		str = this->_nbrs[i + 1];

		this->_num_map[i] = stringToInt(str);
		this->_num_dqu.push_back(stringToInt(str));
	}

	// Before: 3 5 9 7 4
	cout << "Before: ";
	for (size_t i = 0; i < this->_len; i++) {
		cout << this->_num_map[i] << " ";
	}
	// for (size_t i = 0; i < this->_len; i++) {
	// 	cout << << this->_num_dqu[i] << " ";
	// }
	cout << endl;

	clock_t s, e;
	s			   = clock();
	this->_num_map = this->merge_insert_sort(this->_num_map);
	e			   = clock();
	// get the differential time in microseconds
	double time1 = static_cast<double>((e - s) / (CLOCKS_PER_SEC / 1e6));

	s			   = clock();
	this->_num_dqu = this->merge_insert_sort(this->_num_dqu);
	e			   = clock();
	// get the differential time in microseconds
	double time2 = static_cast<double>((e - s) / (CLOCKS_PER_SEC / 1e6));

	// After: 3 4 5 7 9
	cout << "After: ";
	for (size_t i = 0; i < this->_len; i++) {
		cout << this->_num_map[i] << " ";
	}
	// for (size_t i = 0; i < this->_len; i++) {
	// 	cout << this->_num_dqu[i] << " ";
	// }
	cout << endl;
	// Time to process a range of 5 elements with std::[..] : 0.00031 us
	// Time to process a range of 5 elements with std::[..] : 0.00014 us
	cout << "Time to process a range of " << this->_len << " elements with std::map : " << time1 << " us" << endl;
	cout << "Time to process a range of " << this->_len << " elements with std::deque : " << time2 << " us" << endl;
}

map<int, int> PmergeMe::merge_sort(map<int, int> _left_arr, map<int, int> _right_arr) {
	map<int, int> result;
	size_t		  i = 0, j = 0, k = 0;

	while (i < _left_arr.size() && j < _right_arr.size()) {
		if (_left_arr[i] < _right_arr[j]) {
			result[k] = _left_arr[i];
			i++;
		} else {
			result[k] = _right_arr[j];
			j++;
		}
		k++;
	}
	for (size_t a = i; a < _left_arr.size(); a++) {
		result[k] = _left_arr[a];
		k++;
	}
	for (size_t b = j; b < _right_arr.size(); b++) {
		result[k] = _right_arr[b];
		k++;
	}

	return result;
}

map<int, int> PmergeMe::insert_sort(map<int, int> _arr) {
	int key;
	int j;

	for (size_t i = 1; i < _arr.size(); i++) {
		key = _arr[i];
		j	= i - 1;
		while (j >= 0 && _arr[j] > key) {
			_arr[j + 1] = _arr[j];
			j--;
		}
		_arr[j + 1] = key;
	}
	return _arr;
}

map<int, int> PmergeMe::merge_insert_sort(map<int, int> _arr) {
	// base case
	if (_arr.size() < 5)
		return this->insert_sort(_arr);

	// split the map into two halves
	map<int, int> left_arr;
	map<int, int> right_arr;
	size_t		  mid = _arr.size() / 2;
	size_t		  i	  = 0;
	for (map<int, int>::iterator it = _arr.begin(); it != _arr.end(); it++) {
		if (i < mid)
			left_arr[i] = it->second;
		else
			right_arr[i - mid] = it->second;
		i++;
	}

	// sort each half
	left_arr  = this->merge_insert_sort(left_arr);
	right_arr = this->merge_insert_sort(right_arr);

	// merge the sorted halves
	return this->merge_sort(left_arr, right_arr);
}

deque<int> PmergeMe::merge_sort(deque<int> _left_arr, deque<int> _right_arr) {
	deque<int> result;
	size_t	   i = 0, j = 0;

	while (i < _left_arr.size() && j < _right_arr.size()) {
		if (_left_arr[i] < _right_arr[j]) {
			result.push_back(_left_arr[i]);
			i++;
		} else {
			result.push_back(_right_arr[j]);
			j++;
		}
	}
	for (size_t a = i; a < _left_arr.size(); a++)
		result.push_back(_left_arr[a]);

	for (size_t b = j; b < _right_arr.size(); b++)
		result.push_back(_right_arr[b]);

	return result;
}

deque<int> PmergeMe::insert_sort(deque<int> _arr) {
	int key;
	int j;

	for (size_t i = 1; i < _arr.size(); i++) {
		key = _arr[i];
		j	= i - 1;
		while (j >= 0 && _arr[j] > key) {
			_arr[j + 1] = _arr[j];
			j--;
		}
		_arr[j + 1] = key;
	}
	return _arr;
}

deque<int> PmergeMe::merge_insert_sort(deque<int> _arr) {
	// base case
	if (_arr.size() < 5)
		return this->insert_sort(_arr);

	// split the map into two halves
	deque<int> left_arr;
	deque<int> right_arr;
	size_t	   mid = _arr.size() / 2;
	size_t	   i   = 0;
	for (deque<int>::iterator it = _arr.begin(); it != _arr.end(); it++) {
		if (i < mid)
			left_arr.push_back(*it);
		else
			right_arr.push_back(*it);
		i++;
	}

	// sort each half
	left_arr  = this->merge_insert_sort(left_arr);
	right_arr = this->merge_insert_sort(right_arr);

	// merge the sorted halves
	return this->merge_sort(left_arr, right_arr);
}
