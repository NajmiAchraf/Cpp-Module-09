#include "BitcoinExchange.hpp"

int main(int ac, char **av) {
	if (ac == 2) {
		string str(av[1]);

		try {
			BitcoinExchange btc(str);
			btc.init();
			btc.print();
		} catch (const std::exception &e) {
			cerr << "Error: " << e.what() << endl;
		}
	} else {
		cout << "Error: could not open file." << endl;
	}

	return 0;
}