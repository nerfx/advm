#include "matrix.h"

namespace advm {

	void matrix::plus_rows(const int& first_row_index, const int& last_row_index, const double& factor) {
		try {
			check_range_two_rows_indexes("in function plus_rows(const size_t&, const size_t&, const double&) some of the row/column index values are outside the allowed range of row/column indexes",
				first_row_index, last_row_index);

			rows_indexes_are_equal("in function plus_rows(const size_t&, const size_t&, const double&) the row indexes are equal to each other",
				first_row_index, last_row_index);

			for (int i = 0; i < this->cols; ++i) {
				this->container[first_row_index][i] += factor * this->container[last_row_index][i];
			}
		}
		catch (std::string& ex) {
			std::cout << ex << '\n';
		}
	}

	void matrix::multiply_row_by_num(const int& current_row_index, const double& value) {
		try {
			check_range_row_index("in the function multiply_row_by_num(const size_t&, const double&) the value of the row index is outside the allowed range of indexes",
				current_row_index);

			for (int i = 0; i < this->cols; ++i) {
				this->container[current_row_index][i] *= value;
			}
		}
		catch (std::string& ex) {
			std::cout << ex << '\n';
		}
	}

	void matrix::swap_rows(const int& row_index_1, const int& row_index_2) {
		try {
			check_range_two_rows_indexes("in function swap_rows(const size_t&, const size_t&) one of the row indexes or both indexes are out of the allowed range",
				row_index_1, row_index_2);

			rows_indexes_are_equal("in function swap_rows(const size_t&, const size_t&) row indexes are equal to each other",
				row_index_1, row_index_2);

			for (int i = 0; i < this->cols; ++i) {
				double temp = this->container[row_index_1][i];
				this->container[row_index_1][i] = this->container[row_index_2][i];
				this->container[row_index_2][i] = temp;
			}
		}
		catch (std::string& ex) {
			std::cout << ex << '\n';
		}
	}

	void matrix::delete_row(const int& delete_row_index) {
		try {
			check_range_row_index("in function delete_row(const size_t&) the row index is out of the allowed range", delete_row_index);
			rows_are_default("in function delete_row(const size_t&) it is impossible to delete the row corresponding to the entered index because the matrix have only one row");

			double** buffer = new double* [this->rows];
			for (int i = 0; i < this->rows; ++i) {
				buffer[i] = new double[this->cols];
			}

			for (int i = 0; i < this->rows; ++i) {
				for (int j = 0; j < this->cols; ++j) {
					buffer[i][j] = this->container[i][j];
				}
			}

			for (int i = 0; i < this->rows; ++i) {
				delete[] this->container[i];
			}
			delete[] this->container;

			--this->rows;

			this->container = new double* [this->rows];
			for (int i = 0; i < this->rows; ++i) {
				this->container[i] = new double[this->cols];
			}

			for (int i = 0; i < this->rows; ++i) {
				if (i < delete_row_index) {

					for (int j = 0; j < this->cols; ++j) {
						this->container[i][j] = buffer[i][j];
					}
				}
				else {

					for (int j = 0; j < this->cols; ++j) {
						this->container[i][j] = buffer[i + 1][j];
					}
				}
			}

			for (int i = 0; i < this->rows + 1; ++i) {
				delete[] buffer[i];
			}
			delete[] buffer;
		}
		catch (std::string& ex) {
			std::cout << ex << '\n';
		}
	}
}