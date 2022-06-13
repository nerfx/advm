#include "complex.h"

#include<ctime>

namespace advm {

	complex::complex(const double& re, const double& im) : size(2) {

		srand(unsigned int(time(NULL)));

		this->number = new double[this->size];

		this->number[0] = re;
		this->number[1] = im;
	}

	complex::complex(const complex& object) : size(2) {

		this->number = new double[this->size];

		for (int i = 0; i < this->size; ++i) {
			this->number[i] = object.number[i];
		}
	}


	double complex::get_re() {

		return this->number[0];
	}

	double complex::get_im() {

		return this->number[1];
	}

	void complex::int_random_number(const int& value_1, const int& value_2) {

		int add_value_1;
		int add_value_2;

		if (value_1 > value_2) {

			add_value_1 = value_2;
			add_value_2 = value_1;
		}
		else {

			add_value_1 = value_1;
			add_value_2 = value_2;
		}

		for (int i = 0; i < this->size; ++i) {

			int int_random_number = rand() % (add_value_2 - add_value_1 + 1) + add_value_1;
			this->number[i] = static_cast<double>(int_random_number);
		}
	}

	void complex::double_random_number(const int& value_1, const int& value_2) {

		int add_value_1;
		int add_value_2;

		if (value_1 > value_2) {

			add_value_1 = value_2;
			add_value_2 = value_1;
		}
		else {

			add_value_1 = value_1;
			add_value_2 = value_2;
		}

		for (int i = 0; i < this->size; ++i) {

			double double_random_number = rand() % ((add_value_2 - add_value_1) * 1000) / 1000.0 + add_value_1;
			this->number[i] = double_random_number;
		}
	}

	complex::~complex() {
		delete[] this->number;
	}

}