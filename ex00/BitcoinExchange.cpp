#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(string file_name) {
	this->init(file_name);
	this->print();
}

void BitcoinExchange::init(string file_name) {
	std::fstream file(file_name, std::ios::in);
	if (file.is_open()) {
		while (std::getline(file, line) && line[0] != '\0') {
			row.clear();
			std::stringstream str(line);
			while (std::getline(str, word, ',')) {
				this->row.push_back(word);
				cout << word << " | ";
			}
			this->content.push_back(row);
			cout << "\n";
		}
	} else {
		cerr << "error can't open file : " << file_name << endl;
	}
}

void BitcoinExchange::print() {
	for (size_t i = 0; i < this->content.size(); i++) {
		for (size_t j = 0; j < this->content[i].size(); j++) {
			// cout << this->content[i][j] << " | ";
		}
		// cout << "\n";
	}
}