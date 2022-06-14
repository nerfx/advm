#include "matrix.h"

namespace advm {

	void matrix::plus_cols(const int& first_col_index, const int& last_col_index, const double& factor) {
		try {
			check_range_two_cols_indexes("in function plus_cols(const size_t&, const size_t&, const& double&) some of the row/column index values are outside the allowed range of row/column indexes",
				first_col_index, last_col_index);

			cols_indexes_are_equal("in function plus_rows(const size_t&, const size_t&, const double&) column indexes are equal to each other",
				first_col_index, last_col_index);

			for (int i = 0; i < this->rows; ++i) {
				this->container[i][first_col_index] += factor * this->container[i][last_col_index];
			}
		}
		catch (std::string& ex) {
			std::cout << ex << '\n';
		}
	}

	void matrix::multiply_col_by_num(const int& current_col_index, const double& value) {
		try {
			check_range_col_index("in the function multiply_col_by_num(const size_t&, const double&) the value of the column index is outside the allowed range of indexes",
				current_col_index);

			for (int i = 0; i < this->rows; ++i) {
				this->container[i][current_col_index] *= value;
			}
		}
		catch (std::string& ex) {
			std::cout << ex << '\n';
		}
	}

	void matrix::swap_cols(const int& col_index_1, const int& col_index_2) {
		try {
			check_range_two_cols_indexes("in function swap_cols(const size_t&, const size_t&) one of the column indexes or both indexes are out of the allowed range",
				col_index_1, col_index_2);

			cols_indexes_are_equal("in function swap_cols(const size_t&, const size_t&) column indexes are equal to each other",
				col_index_1, col_index_2);

			for (int i = 0; i < this->rows; ++i) {
				double temp = this->container[i][col_index_1];
				this->container[i][col_index_1] = this->container[i][col_index_2];
				this->container[i][col_index_2] = temp;
			}
		}
		catch (std::string& ex) {
			std::cout << ex << '\n';
		}
	}

	void matrix::delete_col(const int& delete_col_index) {
		try {
			check_range_col_index("in function delete_col(const size_t&) the column index is out of the allowed range", delete_col_index);
			cols_are_default("in function delete_col(const size_t&) it is impossible to delete the column corresponding to the entered index because the matrix have only one column");

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

			--this->cols;

			this->container = new double* [this->rows];
			for (int i = 0; i < this->rows; ++i) {
				this->container[i] = new double[this->cols];
			}

			for (int i = 0; i < this->cols; ++i) {
				if (i < delete_col_index) {

					for (int j = 0; j < this->rows; ++j) {
						this->container[j][i] = buffer[j][i];
					}
				}
				else {

					for (int j = 0; j < this->rows; ++j) {
						this->container[j][i] = buffer[j][i + 1];
					}
				}
			}

			for (int i = 0; i < this->rows; ++i) {
				delete[] buffer[i];
			}
			delete[] buffer;
		}
		catch (std::string& ex) {
			std::cout << ex << '\n';
		}
	}
}