#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(string file_name) : file_name(file_name) {
	this->init();
	this->print();
}

void BitcoinExchange::init() {
	std::fstream file(this->file_name.c_str(), std::ios::in);
	if (file.is_open()) {
		while (std::getline(file, line, '\n')) {
			row.clear();
			std::stringstream str(line);
			// cout << line << endl;
			while (std::getline(str, word, ',')) {
				this->row.push_back(word);
				// cout << word << "  ";
			}
			// cout << endl;
			this->content.push_back(row);
		}
	} else {
		cerr << "Error: can't open file " << file_name << endl;
	}
}

int BitcoinExchange::checkType(string str) {
	int	 i		= 0;
	int	 len	= str.length();
	bool point	= false;
	int	 num	= 0;
	int	 decLen = 0;
	int	 type	= -1; // 0: char, 1: int, 2: float, 3: double

	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return type;
	while (i < len) {
		if (isdigit(str[i]))
			num++;
		else if (str[i] == '.') {
			if (point || i == len - 1)
				break;
			point = true;
			i++;
			while (i < len) {
				if (isdigit(str[i])) {
					decLen++;
				} else if (str[i] == 'f' && i == len - 1)
					break;
				else
					break;
				i++;
			}
			break;
		} else
			break;
		i++;
	}
	if (decLen > 0) {
		if (str[len - 1] == 'f' && i == len - 1)
			type = 2;
		else if (i == len)
			type = 3;
	} else if (num > 0 && i == len) {
		if (len == 1)
			type = 0;
		else
			type = 1;
	}
	return type;
}

int BitcoinExchange::stringToInt(string str) {
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
		throw BitcoinExchange::BadInput();
	while (i < len) {
		if (isdigit(str[i]))
			num = num * 10 + (str[i] - '0');
		else
			throw BitcoinExchange::BadInput();
		i++;
	}
	return (static_cast<int>(num * sign));
}

double BitcoinExchange::stringToDouble(string str) {
	int i	   = 0;
	int len	   = str.length();
	int sign   = 1;
	int num	   = 0;
	int dec	   = 0;
	int decLen = 0;

	if (str[i] == '-') {
		sign = -1;
		i++;
	} else if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		throw BitcoinExchange::BadInput();
	while (i < len) {
		if (isdigit(str[i]))
			num = num * 10 + (str[i] - '0');
		else if (str[i] == '.') {
			i++;
			while (i < len) {
				if (isdigit(str[i])) {
					dec = dec * 10 + (str[i] - '0');
					decLen++;
				} else if (str[i] == 'f' && i == len - 1)
					break;
				else
					throw BitcoinExchange::BadInput();
				i++;
			}
			break;
		} else
			throw BitcoinExchange::BadInput();
		i++;
	}
	return ((num + (dec / pow(10, decLen))) * sign);
}

vector<int> BitcoinExchange::splitDate(const string &str) {
	vector<int>		  vect_nbr;
	std::stringstream ss_date(str);
	string			  str_nbr;
	while (std::getline(ss_date, str_nbr, '-')) {
		if (checkType(str_nbr) == 1 || checkType(str_nbr) == 3)
			try {
				vect_nbr.push_back(stringToInt(str_nbr));
			} catch (...) {
				throw BitcoinExchange::BadInput();
			}
		else
			throw BitcoinExchange::BadInput();
	}
	if (vect_nbr.size() != 3)
		throw BitcoinExchange::BadInput();
	return vect_nbr;
}

void BitcoinExchange::validateDate(int i) {
	vector<int> date;
	const int	leap_months[12]		= {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	const int	non_leap_months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	date = splitDate(this->content[i][0]);
	// 9 January 2009 => 31 December 2023
	// Check year & month range
	if ((date[0] < 2009 || 2023 < date[0]) || (date[1] < 1 || 12 < date[1]))
		throw BitcoinExchange::BadInput();

	// Check day range
	if (date[0] % 4 == 0) {
		if (date[2] < 1 || leap_months[date[1] - 1] < date[2])
			throw BitcoinExchange::BadInput();
	} else if (date[2] < 1 || non_leap_months[date[1] - 1] < date[2])
		throw BitcoinExchange::BadInput();
}

double BitcoinExchange::validate(int i) {
	double nbd;

	try {
		this->validateDate(i);
	} catch (...) {
		throw BitcoinExchange::BadInput();
	}

	try {
		nbd = stringToDouble(this->content[i][1]);
	} catch (...) {
		throw BitcoinExchange::BadInput();
	}
	if (nbd < 0)
		throw BitcoinExchange::NegativeNumber();
	if (1000 < nbd)
		throw BitcoinExchange::LargeNumber();
	return nbd;
}

void BitcoinExchange::print() {
	double nbd;

	for (size_t i = 1; i < this->content.size(); i++) {
		try {
			nbd = validate(i);
			for (size_t j = 0; j < this->content[i].size(); j++) {
				if (j == 0)
					cout << this->content[i][j] << " => ";
				else if (j == 1)
					cout << this->content[i][j] << " = " << nbd * 1.1;
			}
		} catch (const BitcoinExchange::BadInput &e) {
			cerr << "Error: " << e.what() << " => " << this->content[i][0];
		} catch (const std::exception &e) {
			cerr << "Error: " << e.what();
		}
		cout << endl;
	}
}
