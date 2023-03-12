#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(string file_name) : file_name(file_name) {
	this->init();
	this->print();
}

void BitcoinExchange::init() {
	std::fstream file(this->file_name, std::ios::in);
	if (file.is_open()) {
		while (std::getline(file, line, '\n')) {
			row.clear();
			std::stringstream str(line);
			while (std::getline(str, word, ',')) {
				this->row.push_back(word);
			}
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
	vector<int>	 vect;
	std::sstream ss(str);
	string		 nbr;
	while (std::getline(ss, nbr, '-')) {
		if (checkType(nbr) == 1 || checkType(nbr) == 3)
			try {
				vect.push_back(stringToInt(nbr));
			} catch (...) {
				throw BitcoinExchange::BadInput();
			}
		else
			throw BitcoinExchange::BadInput();
	}
	if (nbr.size() != 3)
		throw BitcoinExchange::BadInput();
	return nbr;
}

int BitcoinExchange::validate(int i) {
	vector<int> nbr;
	double		nbd;
	try {
		nbr = splitDate(this->content[i][0]);
		// 9 January 2009
		if (nbr[0] < 2009 && 2023 < nbr[0] || nbr[1] < 1 && 12 < nbr[1] || nbr[3] < 1 && 31 < nbr[3])
			throw BitcoinExchange::BadInput();

	} catch (...) {
		throw BitcoinExchange::BadInput();
	}
	try {
		nbd = stringToDouble(this->content[i][1]);
		if (nbd[0] < 0)
			throw BitcoinExchange::NegativeNumber();
		if (1000 < nbd[0])
			throw BitcoinExchange::LargeNumber();
	} catch (...) {
		throw BitcoinExchange::BadInput();
	}
}

void BitcoinExchange::print() {

	for (size_t i = 0; i < this->content.size(); i++) {
		try {
			validate(i);
			for (size_t j = 0; j < this->content[i].size(); j++) {
				cout << this->content[i][j] << " => ";
			}
		} catch (const BitcoinExchange::BadInput &e) {
			cerr << "Error: " << e.what() << " => " << this->content[0];
		} catch (const std::exception &e) {
			cerr << "Error: " << e.what();
		}
		cout << endl;
	}
}
