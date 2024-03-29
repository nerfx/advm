#include<iostream>
#include <iomanip>
#include"matrix.h"
#include"complex.h"
#include<ctime>

int main() {
	srand(static_cast<unsigned int>(time(0)));

	setlocale(LC_ALL, "rus");

	/*
	advm::matrix init(3, 3);
	init.int_random_input(30, 50);
	std::cout << init << '\n';
	
	advm::matrix test1(3, 3), test2(3, 3), pow_test(3, 3), power_ex(2, 3), t1(3, 3);
	
	std::cin >> test1;
	std::cout << test1.rank() << '\n';

	std::cin >> test2;
	std::cout << test2.gauss<3>({ 1, 2, 4 });

	std::cin >> pow_test;

	power_ex.power(2);
	pow_test.power(3);

	std::cout << pow_test << '\n';
	
	t1.int_random_input(10, 0);
	std::cout << t1 << '\n';

	t1.to_upper_triangular();
	std::cout << t1 << '\n';
	

	advm::matrix t2(3, 3), t3(3, 3);
	t2.int_random_input(10, 0);
	t3.int_random_input(10, 0);

	std::cout << t2 << '\n';
	std::cout << t3 << '\n';

	t2.to_upper_triangular();
	t3.to_lower_triangular();

	std::cout << t2 << '\n';
	std::cout << t3 << '\n';
	*/

	advm::matrix j_g(3, 3);
	std::cin >> j_g;

	j_g.jordan_gauss();

	std::cout << j_g << '\n';

	return 0;
}
