#include "BitcoinExchange.hpp"

bool run(int ac) { //, char **av) {
	if (ac != 2)
		return false;

	// string str(av[1]);
	// if (str.substr(str.find_last_of(".") + 1) != "csv")
	// 	return false;
	return true;
}

int main(int ac, char **av) {
	if (run(ac)) {
		string str(av[1]);

		try {
			BitcoinExchange btc(str);
		} catch (const std::exception &e) {
			cerr << "Error: " << e.what() << endl;
		}

	} else {
		cout << "Error: could not open file." << endl;
	}

	return 0;
}