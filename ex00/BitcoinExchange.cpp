#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
	cout << C_GREEN << "Default constructor" << C_RES << endl;
}

BitcoinExchange::BitcoinExchange(string file_name) : file_name(file_name) {
	cout << C_GREEN << "Parameterize constructor" << C_RES << endl;
	try {
		this->init();
		this->print();
	} catch (const BitcoinExchange::BadInput &e) {
		throw BitcoinExchange::BadInput();
	} catch (const BitcoinExchange::NegativeNumber &e) {
		throw BitcoinExchange::NegativeNumber();
	} catch (const BitcoinExchange::LargeNumber &e) {
		throw BitcoinExchange::LargeNumber();
	} catch (const BitcoinExchange::OpenFile &e) {
		throw BitcoinExchange::OpenFile();
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &bitcoinExchange) : file_name(bitcoinExchange.file_name) {
	cout << C_CYAN << "Copy constructor" << C_RES << endl;
	*this = bitcoinExchange;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &bitcoinExchange) {
	cout << C_CYAN << "Copy assignment operator" << C_RES << endl;
	if (this != &bitcoinExchange) {
		this->content = bitcoinExchange.content;
		this->row	  = bitcoinExchange.row;
		this->line	  = bitcoinExchange.line;
		this->word	  = bitcoinExchange.word;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {
	cout << C_RED << "Destructor" << C_RES << endl;
}

void BitcoinExchange::init() {
	this->fill(this->base, "data.csv", ',');
	this->fill(this->content, this->file_name, '|');
}

void BitcoinExchange::fill(vector<vectring> &to_fill, string name_file, char spliter) {
	std::fstream file(name_file.c_str(), std::ios::in);
	if (file.is_open()) {
		while (std::getline(file, line, '\n')) {
			row.clear();
			std::stringstream str(line);
			for (size_t i = 1; std::getline(str, word, spliter); i++) {
				if (word[word.length() - 1] == ' ' && i == 1) {
					word.pop_back();
					this->row.push_back(word);
				} else if (word[0] == ' ' && i == 2) {
					word.erase(0, 1);
					this->row.push_back(word);
				} else if (spliter == ',') {
					this->row.push_back(word);
				} else if (spliter == '|')
					this->row.push_back("word");
			}
			to_fill.push_back(row);
		}
	} else {
		throw BitcoinExchange::OpenFile();
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
	int				  type;

	while (std::getline(ss_date, str_nbr, '-')) {
		type = checkType(str_nbr);
		if (type == 1)
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
	const int	leap_year_months[12]	 = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	const int	non_leap_year_months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	date = splitDate(this->content[i][0]);
	// 9 January 2009 => 31 December 2023
	// Check year & month range
	if ((date[0] < 2009 || 2023 < date[0]) || (date[1] < 1 || 12 < date[1]))
		throw BitcoinExchange::BadInput();

	// Check day range
	if (date[0] % 4 == 0) {
		if (date[2] < 1 || leap_year_months[date[1] - 1] < date[2])
			throw BitcoinExchange::BadInput();
	} else if (date[2] < 1 || non_leap_year_months[date[1] - 1] < date[2])
		throw BitcoinExchange::BadInput();
}

double BitcoinExchange::validate(int i) {
	double value = 0.0;
	int	   type;

	try {
		this->validateDate(i);
	} catch (...) {
		throw BitcoinExchange::BadInput();
	}

	try {
		type = checkType(this->content[i][1]);
		if (type == 1 || type == 3 || type == 2)
			value = stringToDouble(this->content[i][1]);
		else
			throw BitcoinExchange::BadInput();
	} catch (...) {
		throw BitcoinExchange::BadInput();
	}
	if (value < 0)
		throw BitcoinExchange::NegativeNumber();
	if (1000 < value)
		throw BitcoinExchange::LargeNumber();
	return value;
}

int BitcoinExchange::findPrevious(int i) {
	vector<int> base_date;
	vector<int> content_date;

	content_date = splitDate(this->content[i][0]);
	for (size_t a = this->base.size() - 1; a > 1; a--) {
		// check previous Dates
		base_date = splitDate(this->base[a][0]);
		if (base_date[0] <= content_date[0] && base_date[1] <= content_date[1] && base_date[2] <= content_date[2]) {
			return a;
		}
	}
	return -1;
}

int BitcoinExchange::find(int i) {
	for (size_t k = 1; k < this->base.size(); k++) {
		// check similar Dates
		if (this->base[k][0] == this->content[i][0]) {
			return k;
		}
	}
	return -1;
}

void BitcoinExchange::print(int i, int value, int index) {
	double exchange;

	exchange = stringToDouble(this->base[index][1]);
	for (size_t j = 0; j < this->content[i].size(); j++) {
		if (j == 0)
			cout << this->content[i][j] << " => ";
		else if (j == 1)
			cout << this->content[i][j] << " = " << exchange * value << endl;
	}
}

void BitcoinExchange::print() {
	double value;
	int	   current_index;
	int	   previous_index;

	for (size_t i = 1; i < this->content.size(); i++) {
		try {
			value		   = validate(i);
			current_index  = this->find(i);
			previous_index = this->findPrevious(i);
			// cout << i << " current_index = " << current_index << "  ||  "
			// << "previous_index = " << previous_index << endl;
			if (current_index > 0) {
				this->print(i, value, current_index);
			} else if (previous_index > 0) {
				this->print(i, value, previous_index);
			}
		} catch (const BitcoinExchange::BadInput &e) {
			if (this->find(i) > 0 || this->findPrevious(i) > 0)
				cerr << "Error: " << e.what() << " => " << this->content[i][0] << endl;
		} catch (const std::exception &e) {
			if (this->find(i) > 0 || this->findPrevious(i) > 0)
				cerr << "Error: " << e.what() << endl;
		}
	}
}
