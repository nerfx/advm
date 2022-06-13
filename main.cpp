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

	return 0;
}
