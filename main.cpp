#include<iostream>
#include <iomanip>
#include"matrix.h"
#include"complex.h"
#include<ctime>

int main() {
	srand(static_cast<unsigned int>(time(0)));

	setlocale(LC_ALL, "rus");

	advm::matrix init(3, 3);
	init.int_random_input(30, 50);
	std::cout << init << '\n';

	advm::matrix test1(3, 3), test2(3, 3);

	std::cin >> test1;
	std::cout << test1.rank() << '\n';

	std::cin >> test2;
	std::cout << test2.gauss<3>({ 1, 2, 4 });

	return 0;
}
