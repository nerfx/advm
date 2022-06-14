#include "matrix.h"

namespace advm {

	void matrix::int_random_input(const int& int_value_1, const int& int_value_2) {
		int copy_value_1;
		int copy_value_2;

		if (int_value_1 < int_value_2) {
			copy_value_1 = int_value_2;
			copy_value_2 = int_value_1;
		}
		else {
			copy_value_1 = int_value_1;
			copy_value_2 = int_value_2;
		}

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				int random_value = rand() % (copy_value_1 - copy_value_2 + 1) + copy_value_2;
				this->container[i][j] = static_cast<double>(random_value);
			}
		}
	}

	void matrix::double_random_input(const int& double_value_1, const int& double_value_2) {
		int copy_value_1;
		int copy_value_2;

		if (double_value_1 < double_value_2) {
			copy_value_1 = double_value_2;
			copy_value_2 = double_value_1;
		}
		else {
			copy_value_1 = double_value_1;
			copy_value_2 = double_value_2;
		}

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				this->container[i][j] = rand() % ((copy_value_1 - copy_value_2) * 1000) / 1000.0 + copy_value_2;
			}
		}
	}
}