#include "RPN.hpp"

RPN::RPN() {
	cout << C_GREEN << "Default constructor" << C_RES << endl;
}

RPN::RPN(char *entry) {
	cout << C_GREEN << "Parameterize constructor" << C_RES << endl;

	this->_entry	  = entry;
	this->_next_token = NULL;

	try {
		this->getResult();
		cout << "the answer : " << this->_num_stack.top() << endl;
	} catch (const RPN::Error &e) {
		throw RPN::Error();
	}
}

RPN::RPN(const RPN &rpn) {
	cout << C_CYAN << "Copy constructor" << C_RES << endl;
	this->_entry = rpn._entry;
	*this		 = rpn;
}

RPN &RPN::operator=(const RPN &rpn) {
	cout << C_CYAN << "Copy assignment operator" << C_RES << endl;
	if (this != &rpn) {
		this->_entry = rpn._entry;
	}
	return *this;
}

RPN::~RPN() {
	cout << C_RED << "Destructor" << C_RES << endl;
}

int RPN::stringToInt(string str) {
	int	 i	  = 0;
	int	 len  = str.length();
	int	 sign = 1;
	long num  = 0;

	if (len != 1)
		throw RPN::Error();
	if (str[i] == '\0')
		throw RPN::Error();
	while (i < len) {
		if (isdigit(str[i]))
			num = num * 10 + (str[i] - '0');
		else
			throw RPN::Error();
		i++;
	}
	return (static_cast<int>(num * sign));
}

void RPN::getResult() {
	this->_ptr = strtok_r(this->_entry, " ", &this->_next_token);
	while (this->_ptr) {
		this->o = this->_ptr[0];
		if (this->o == '+' || this->o == '-' || this->o == '*' || this->o == '/') {
			if (this->_num_stack.size() < 2)
				throw RPN::Error();
			this->b = this->_num_stack.top();
			this->_num_stack.pop();
			this->a = this->_num_stack.top();
			this->_num_stack.pop();
			switch (this->o) {
			case '+':
				this->r = this->a + this->b;
				break;
			case '-':
				this->r = this->a - this->b;
				break;
			case '*':
				this->r = this->a * this->b;
				break;
			case '/':
				if (this->b == 0)
					throw RPN::Error();
				this->r = this->a / this->b;
				break;
			default:
				throw RPN::Error();
				break;
			}
			this->_num_stack.push(this->r);
		} else {
			str = this->_ptr;
			this->_num_stack.push(this->stringToInt(str));
		}
		this->_ptr = strtok_r(nullptr, " ", &this->_next_token);
		if (!this->_ptr && this->_num_stack.size() != 1)
			throw RPN::Error();
	}
}
