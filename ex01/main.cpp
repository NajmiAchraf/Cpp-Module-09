#include "RPN.hpp"

bool run(int ac) {
	if (ac != 2)
		return false;
	return true;
}

int main(int ac, char **av) {
	if (run(ac)) {
		try {
			RPN btc(av[1]);
			btc.getResult();
		} catch (const std::exception &e) {
			cerr << e.what() << endl;
		}
	} else {
		cout << "Error" << endl;
	}

	return 0;
}