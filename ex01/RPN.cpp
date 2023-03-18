#include "RPN.hpp"

RPN::RPN() {
	cout << C_GREEN << "Default constructor" << C_RES << endl;
}

RPN::RPN(string entry) : _entry(entry) {
	cout << C_GREEN << "Parameterize constructor" << C_RES << endl;
	try {
		this->init();
	} catch (const RPN::Error &e) {
		throw RPN::Error();
	}
}

RPN::RPN(const RPN &rpn) : _entry(rpn._entry) {
	cout << C_CYAN << "Copy constructor" << C_RES << endl;
	*this = rpn;
}

RPN &RPN::operator=(const RPN &rpn) {
	cout << C_CYAN << "Copy assignment operator" << C_RES << endl;
	if (this != &rpn) {
		this->Entry = rpn.Entry
	}
	return *this;
}

RPN::~RPN() {
	cout << C_RED << "Destructor" << C_RES << endl;
}

int RPN::checkType(string str) {
	int	 i		= 0;
	int	 len	= str.length();
	bool point	= false;
	int	 num	= 0;
	int	 decLen = 0;
	int	 type	= -1; // {0: char} {1: int} {2: float} {3: double}

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

int RPN::stringToInt(string str) {
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
		throw RPN::BadInput();
	while (i < len) {
		if (isdigit(str[i]))
			num = num * 10 + (str[i] - '0');
		else
			throw RPN::BadInput();
		i++;
	}
	return (static_cast<int>(num * sign));
}
