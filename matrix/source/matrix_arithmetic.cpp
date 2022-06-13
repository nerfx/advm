#include<iostream>
#include "matrix.h"

namespace advm {

	matrix& matrix::operator = (const matrix& copy) {

		try {
			check_equality_rows_and_cols("in the operator = (const matrix&) the number of columns/rows of the first matrix is not equal to the number of columns/rows of the second",
				copy.rows, copy.cols);

			for (int i = 0; i < this->rows; ++i) {
				for (int j = 0; j < this->cols; ++j) {
					this->container[i][j] = copy.container[i][j];
				}
			}

			return*this;
		}
		catch (std::string ex) {
			std::cout << ex << '\n';
			return*this;
		}
	}

	matrix& matrix::operator = (const double& value) {

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				this->container[i][j] = value;
			}
		}

		return*this;
	}

	matrix matrix::operator + (const matrix& plus_obj) {

		try {
			check_equality_rows_and_cols("in the operator + (const matrix&) the number of columns/rows of the first matrix is not equal to the number of columns/rows of the second",
				plus_obj.rows, plus_obj.cols);

			matrix current(this->rows, this->cols);

			for (int i = 0; i < this->rows; ++i) {
				for (int j = 0; j < this->cols; ++j) {
					current.container[i][j] = this->container[i][j] + plus_obj.container[i][j];
				}
			}

			return current;
		}
		catch (std::string ex) {
			std::cout << ex << '\n';
			return*this;
		}
	}

	matrix matrix::operator - (const matrix& minus_obj) {

		try {
			check_equality_rows_and_cols("in the operator - (const matrix&) the number of columns/rows of the first matrix is not equal to the number of columns/rows of the second",
				minus_obj.rows, minus_obj.cols);

			matrix current(this->rows, this->cols);

			for (int i = 0; i < this->rows; ++i) {
				for (int j = 0; j < this->cols; ++j) {
					current.container[i][j] = this->container[i][j] - minus_obj.container[i][j];
				}
			}

			return current;
		}
		catch (std::string ex) {
			std::cout << ex << '\n';
			return*this;
		}
	}

	matrix& matrix::operator += (const matrix& assign_plus_obj) {

		try {
			check_equality_rows_and_cols("in the operator += (const matrix&) the number of columns/rows of the first matrix is not equal to the number of columns/rows of the second",
				assign_plus_obj.rows, assign_plus_obj.cols);

			for (int i = 0; i < this->rows; ++i) {
				for (int j = 0; j < this->cols; ++j) {
					this->container[i][j] += assign_plus_obj.container[i][j];
				}
			}

			return*this;
		}
		catch (std::string ex) {
			std::cout << ex << '\n';
			return*this;
		}
	}

	matrix& matrix::operator -= (const matrix& assign_minus_obj) {

		try {
			check_equality_rows_and_cols("in the operator -= (const matrix&) the number of columns/rows of the first matrix is not equal to the number of columns/rows of the second",
				assign_minus_obj.rows, assign_minus_obj.cols);

			for (int i = 0; i < this->rows; ++i) {
				for (int j = 0; j < this->cols; ++j) {
					this->container[i][j] -= assign_minus_obj.container[i][j];
				}
			}

			return*this;
		}
		catch (std::string ex) {
			std::cout << ex << '\n';
			return*this;
		}
	}

	matrix& matrix::operator ++ () {

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				++this->container[i][j];
			}
		}

		return*this;
	}

	matrix matrix::operator ++ (int value) {

		matrix current(*this);

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				++this->container[i][j];
			}
		}

		return current;
	}

	matrix& matrix::operator -- () {

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				--this->container[i][j];
			}
		}

		return*this;
	}

	matrix matrix::operator -- (int value) {

		matrix current(*this);

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				--this->container[i][j];
			}
		}

		return current;
	}

	matrix& matrix::operator * (const double& num) {

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				this->container[i][j] *= num;
			}
		}

		return*this;
	}

	matrix matrix::operator * (const matrix& multiply_obj) {

		try {
			check_equality_dims_for_multi("in the operator * (const matrix&) the number of columns of the first matrix is not equal to the number of rows of the second matrix",
				multiply_obj.rows);

			matrix result(this->rows, multiply_obj.cols);

			for (int i = 0; i < multiply_obj.cols; ++i) {
				for (int j = 0; j < this->rows; ++j) {
					for (int k = 0; k < multiply_obj.rows; ++k) {
						result.container[j][i] += this->container[j][k] * multiply_obj.container[k][i];
					}
				}
			}

			return result;
		}
		catch (std::string ex) {
			std::cout << ex << '\n';
			return*this;
		}
	}

	double matrix::operator () (const int& row_index, const int& col_index) {

		try {
			check_range_rows_and_cols_indexes("operator () (const size_t&, const size_t&) row/column indexes out of the allowed range of number of rows/columns",
				row_index, col_index);

			return this->container[row_index][col_index];
		}
		catch (std::string ex) {
			std::cout << ex << '\n';

			float nanf = NAN;
			return static_cast<double>(nanf);
		}
	}

	bool matrix::operator == (const matrix& obj) {

		if (this->rows != obj.rows || this->cols != obj.cols) {
			return false;
		}

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {

				if (this->container[i][j] != obj.container[i][j]) {
					return false;
				}
			}
		}

		return true;
	}

	bool matrix::operator != (const matrix& obj) {

		if (this->rows != obj.rows || this->cols != obj.cols) {
			return true;
		}

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {

				if (this->container[i][j] != obj.container[i][j]) {
					return true;
				}
			}
		}

		return false;
	}

	std::istream& operator >> (std::istream& in, const matrix& in_matrix) {

		for (int i = 0; i < in_matrix.rows; ++i) {
			for (int j = 0; j < in_matrix.cols; ++j) {
				in >> in_matrix.container[i][j];
			}
		}

		return in;
	}

	std::ostream& operator << (std::ostream& out, const matrix& out_matrix) {

		for (int i = 0; i < out_matrix.rows; ++i) {
			for (int j = 0; j < out_matrix.cols; ++j) {
				out << out_matrix.container[i][j] << '\t';
			}

			std::cout << '\n';
		}

		return out;
	}

}
