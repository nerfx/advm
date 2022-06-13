#include<iostream>
#include<ctime>

#include "matrix.h"

namespace advm {

	matrix::matrix(int rows, int cols, double default_value) : default_rows(1), default_cols(1) {
		srand(static_cast<unsigned int>(time(NULL)));

		if (rows < default_rows || cols < default_cols) {
			this->rows = default_rows;
			this->cols = default_cols;
		}
		else {
			this->rows = rows;
			this->cols = cols;
		}

		this->container = new double* [this->rows];
		for (int i = 0; i < this->rows; ++i) {
			this->container[i] = new double[this->cols];
		}

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				this->container[i][j] = default_value;
			}
		}
	}

	matrix::matrix(const matrix& copy) : default_rows(1), default_cols(1), rows(copy.rows), cols(copy.cols) {
		this->container = new double* [this->rows];
		for (int i = 0; i < this->rows; ++i) {
			this->container[i] = new double[cols];
		}

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				this->container[i][j] = copy.container[i][j];
			}
		}
	}

	double** matrix::get_matrix() {
		return this->container;
	}

	int matrix::size_rows() {
		return this->rows;
	}

	int matrix::size_cols() {
		return this->cols;
	}

	bool matrix::is_null() {
		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				if (this->container[i][j]) {
					return false;
				}
			}
		}

		return true;
	}

	void matrix::to_null() {
		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				this->container[i][j] = 0.0;
			}
		}
	}

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

	void matrix::transpose() {
		if (this->rows == this->default_rows && this->cols == this->default_cols) {
			return;
		}
		else if (this->rows == this->cols) {
			matrix buffer(*this);

			for (int i = 0; i < this->rows; ++i) {
				for (int j = 0; j < this->cols; ++j) {
					this->container[i][j] = buffer.container[j][i];
				}
			}
		}
		else {
			matrix current(*this);

			int temp = this->rows;
			this->rows = this->cols;
			this->cols = temp;

			for (int i = 0; i < this->rows; ++i) {
				delete[] this->container[i];
			}
			delete[] this->container;

			this->container = new double* [this->rows];
			for (int i = 0; i < this->rows; ++i) {
				this->container[i] = new double[this->cols];
			}

			for (int i = 0; i < this->rows; ++i) {
				for (int j = 0; j < this->cols; ++j) {
					this->container[i][j] = current.container[j][i];
				}
			}
		}
	}

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

	void matrix::to_bool() {
		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				int random_bool = rand() % 2;
				this->container[i][j] = static_cast<double>(random_bool);
			}
		}
	}

	void matrix::to_identity() {
		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				if (i == j) {
					this->container[i][j] = 1.0;
				}
				else {
					this->container[i][j] = 0.0;
				}
			}
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

	double* matrix::to_vector() {

		double* new_vector = new double[this->rows * this->cols];

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				new_vector[j + i * this->cols] = this->container[i][j];
			}
		}

		return new_vector;
	}

	double matrix::m_norm() {
		if (this->rows == this->default_rows && this->cols == this->default_cols) {

			//if the matrix consists of one element, then the m-norm in this case is guaranteed to be equal to the modulus of this element
			return fabs(this->container[0][0]);
		}
		else if (this->cols == this->default_cols) {

			double m_norm_max = fabs(this->container[0][0]);

			for (int i = 1; i < this->rows; ++i) {

				double m_norm_current = fabs(this->container[i][0]);

				if (m_norm_max < m_norm_current) {
					m_norm_max = m_norm_current;
				}
			}

			return m_norm_max;
		}
		else if (this->rows == this->default_rows) {

			double m_norm_value = fabs(this->container[0][0]);

			for (int i = 1; i < this->cols; ++i) {
				m_norm_value += fabs(this->container[0][i]);
			}

			return m_norm_value;
		}
		else {
			//the sum of the absolute values of the elements is written to the array for further search of the maximum in this array, which will be the m-norm 

			double* m_norm_amounts = new double[this->rows];
			double m_norm_current_amount;

			for (int i = 0; i < this->rows; ++i) {

				m_norm_current_amount = 0.0;

				for (int j = 0; j < this->cols; ++j) {
					m_norm_current_amount += fabs(this->container[i][j]);
				}

				m_norm_amounts[i] = m_norm_current_amount;
			}

			double m_norm_result = m_norm_amounts[0];
			for (int i = 1; i < this->rows; ++i) {

				double current_result = m_norm_amounts[i];

				if (m_norm_result < current_result) {
					m_norm_result = current_result;
				}
			}

			delete[] m_norm_amounts;
			m_norm_amounts = nullptr;

			return m_norm_result;
		}
	}

	double matrix::l_norm() {
		if (this->rows == this->default_rows && this->cols == this->default_cols) {
			//if the matrix consists of one element, then the l-norm in this case is guaranteed to be equal to the modulus of this element
			return fabs(this->container[0][0]);
		}
		else if (this->cols == this->default_cols) {

			double l_norm_value = fabs(this->container[0][0]);

			for (int i = 1; i < this->rows; ++i) {
				l_norm_value += fabs(this->container[i][0]);
			}

			return l_norm_value;
		}
		else if (this->rows == this->default_rows) {

			double l_norm_max = fabs(this->container[0][0]);

			for (int i = 1; i < this->cols; ++i) {

				double l_norm_current = fabs(this->container[0][i]);

				if (l_norm_max < l_norm_current) {
					l_norm_max = l_norm_current;
				}
			}

			return l_norm_max;
		}
		else {

			//the sum of the absolute values of the elements is written to the array for further search of the maximum in this array, which will be the l-norm

			double* l_norm_amounts = new double[this->cols];
			double l_norm_current_amount;

			for (int i = 0; i < this->cols; ++i) {

				l_norm_current_amount = 0.0;

				for (int j = 0; j < this->rows; ++j) {
					l_norm_current_amount += fabs(this->container[j][i]);
				}

				l_norm_amounts[i] = l_norm_current_amount;
			}

			double l_norm_result = l_norm_amounts[0];
			for (int i = 1; i < this->cols; ++i) {

				double current_result = l_norm_amounts[i];

				if (l_norm_result < current_result) {
					l_norm_result = current_result;
				}
			}

			delete[] l_norm_amounts;
			l_norm_amounts = nullptr;

			return l_norm_result;
		}
	}

	double matrix::k_norm() {
		if (this->rows == this->default_rows && this->cols == this->default_cols) {
			return fabs(this->container[0][0]);
		}
		else {

			double k_norm_current = 0.0;

			for (int i = 0; i < this->rows; ++i) {
				for (int j = 0; j < this->cols; ++j) {
					k_norm_current += this->container[i][j] * this->container[i][j];
				}
			}

			return sqrt(k_norm_current);
		}
	}

	double matrix::trace() {
		try {
			matrix_is_square("trace(): it is impossible to find the trace of the matrix because the matrix is not square");

			double trace_result = 0.0;
			for (int i = 0; i < this->rows; ++i) {
				trace_result += this->container[i][i];
			}

			return trace_result;
		}
		catch (const std::string& e) {
			std::cout << e << '\n';

			float nanf = NAN;
			return static_cast<double>(nanf);
		}
	}

	double matrix::value_det(double** buffer, const int& buffer_rows, const int& buffer_cols) {
		if (buffer_rows < 2 && buffer_cols < 2) {

			return buffer[0][0];
		}
		else if (buffer_rows == 2 && buffer_cols == 2) {

			return buffer[0][0] * buffer[1][1] - buffer[0][1] * buffer[1][0];
		}
		else if (buffer_rows == 3 && buffer_cols == 3) {

			return buffer[0][0] * buffer[1][1] * buffer[2][2] + buffer[0][1] * buffer[1][2] * buffer[2][0] + buffer[0][2] * buffer[1][0] * buffer[2][1] -
				buffer[0][2] * buffer[1][1] * buffer[2][0] - buffer[0][1] * buffer[1][0] * buffer[2][2] - buffer[1][2] * buffer[2][1] * buffer[0][0];
		}
		else {
			const int new_rows = buffer_rows - 1;
			const int new_cols = buffer_cols - 1;

			double** current_buffer = new double* [new_rows];
			for (int i = 0; i < new_rows; ++i) {
				current_buffer[i] = new double[new_cols];
			}

			double current_det = 0.0;
			double factor = 1.0;
			for (int col = 0; col < buffer_cols; ++col) {

				int index = 0;
				for (int i = 0; i < new_cols; ++i) {

					if (i == col) {

						index = 1;
						for (int j = 0; j < new_rows; ++j) {
							current_buffer[j][i] = buffer[j + 1][i + 1];
						}
					}
					else {

						for (int j = 0; j < new_rows; ++j) {
							current_buffer[j][i] = buffer[j + 1][i + index];
						}
					}
				}

				current_det += factor * buffer[0][col] * value_det(current_buffer, new_rows, new_cols);
				factor *= -1.0;
			}

			for (int i = 0; i < new_rows; ++i) {
				delete[] current_buffer[i];
			}
			delete[] current_buffer;

			return current_det;
		}
	}

	double matrix::det() {
		try {
			matrix_is_square("det(): rows and columns of current matrix are not equality");

			return value_det(this->container, this->rows, this->cols);
		}
		catch (std::string& e) {
			std::cout << e << '\n';

			float nanf = NAN;
			return static_cast<double>(nanf);
		}
	}

	void matrix::invert_matrix() {

		try {
			matrix_is_square("invert_matrix(): to invert matrix impossible because matrix isn't square");
			const double invert_matrix_det = value_det(this->container, this->rows, this->cols);

			value_is_null("invert_matrix(): to invert matrix impossible because matrix determinant is null", invert_matrix_det);

			if (this->rows == 1 && this->cols == 1) {

				container[0][0] = 1 / invert_matrix_det;
				return;
			}
			else if (this->rows == 2 && this->cols == 2) {

				double** current_buffer = new double* [this->rows];
				for (int i = 0; i < this->rows; ++i) {
					current_buffer[i] = new double[this->cols];
				}

				current_buffer[0][0] = (!this->container[1][1]) ? 0.0 : this->container[1][1] / invert_matrix_det;
				current_buffer[0][1] = (!this->container[0][1]) ? 0.0 : -1 * this->container[0][1] / invert_matrix_det;
				current_buffer[1][0] = (!this->container[1][0]) ? 0.0 : -1 * this->container[1][0] / invert_matrix_det;
				current_buffer[1][1] = (!this->container[0][0]) ? 0.0 : this->container[0][0] / invert_matrix_det;

				for (int i = 0; i < this->rows; ++i) {
					for (int j = 0; j < this->cols; ++j) {
						this->container[i][j] = current_buffer[i][j];
					}
				}

				for (int i = 0; i < this->rows; ++i) {
					delete[] current_buffer[i];
				}
				delete[] current_buffer;
			}
			else {

				const int buffer_rows = this->rows - 1;
				const int buffer_cols = this->cols - 1;

				double** buffer = new double* [buffer_rows];
				for (int i = 0; i < buffer_rows; ++i) {
					buffer[i] = new double[buffer_cols];
				}

				double** inverted_matrix = new double* [this->rows];
				for (int i = 0; i < this->rows; ++i) {
					inverted_matrix[i] = new double[this->cols];
				}

				for (int i = 0; i < this->rows; ++i) {

					for (int j = 0; j < this->cols; ++j) {

						//generating an add minor without current row and current column
						int current_row_index = i;
						int current_col_index = j;

						for (int k = 0; k < buffer_rows; ++k) {

							if (k < current_row_index) {

								for (int l = 0; l < buffer_cols; ++l) {

									if (l < current_col_index) {
										buffer[k][l] = this->container[k][l];
									}
									else {
										buffer[k][l] = this->container[k][l + 1];
									}
								}
							}
							else {
								for (int l = 0; l < buffer_cols; ++l) {

									if (l < current_col_index) {
										buffer[k][l] = this->container[k + 1][l];
									}
									else {
										buffer[k][l] = this->container[k + 1][l + 1];
									}
								}
							}
						}

						int factor = -1;
						if (!((i + j + 2) % 2)) {

							factor = 1;
						}

						double current_det = factor * value_det(buffer, buffer_rows, buffer_cols) / invert_matrix_det;
						if (!current_det) {
							inverted_matrix[j][i] = 0.0;
						}
						else {
							inverted_matrix[j][i] = current_det;
						}
					}
				}

				for (int i = 0; i < this->rows; ++i) {
					for (int j = 0; j < this->cols; ++j) {
						this->container[i][j] = inverted_matrix[i][j];
					}
				}

				for (int i = 0; i < buffer_rows; ++i) {
					delete[] buffer[i];
				}
				delete[] buffer;

				for (int i = 0; i < this->rows; ++i) {
					delete[] inverted_matrix[i];
				}
				delete[] inverted_matrix;
			}
		}
		catch (std::string& ex) {
			std::cout << ex << '\n';
		}
	}

	void matrix::delete_null_rows() {

		if (this->rows == this->default_rows && this->cols == this->default_cols) {
			return;
		}

		int null_row_count = 0;
		for (int i = 0; i < this->rows; ++i) {

			bool factor = true;

			for (int j = 0; j < this->cols && factor; ++j) {

				if (this->container[i][j]) {
					factor = false;
				}
			}

			if (factor) {
				++null_row_count;
			}
		}

		if (!null_row_count || null_row_count == this->rows) {
			return;
		}

		int not_null_row_count = this->rows - null_row_count;
		int* not_null_row_indexes = new int[not_null_row_count];
		int current_index = 0;

		for (int i = 0; i < this->rows; ++i) {

			int factor = true;
			for (int j = 0; j < this->cols && factor; ++j) {

				if (this->container[i][j]) {

					not_null_row_indexes[current_index] = i;

					factor = false;
					++current_index;
				}
			}
		}

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

		this->rows -= null_row_count;

		this->container = new double* [this->rows];
		for (int i = 0; i < this->rows; ++i) {
			this->container[i] = new double[this->cols];
		}

		for (int k = 0; k < not_null_row_count; ++k) {

			for (int i = 0; i < not_null_row_count + null_row_count; ++i) {

				if (i == not_null_row_indexes[k]) {

					for (int j = 0; j < this->cols; ++j) {
						this->container[k][j] = buffer[i][j];
					}
				}
			}
		}

		for (int i = 0; i < not_null_row_count + null_row_count; ++i) {
			delete[] buffer[i];
		}
		delete[] buffer;

		delete[] not_null_row_indexes;
	}

	void matrix::delete_null_cols() {

		if (this->rows == this->default_rows && this->cols == this->default_cols) {
			return;
		}

		int null_col_count = 0;
		for (int i = 0; i < this->cols; ++i) {

			bool factor = true;
			for (int j = 0; j < this->rows && factor; ++j) {

				if (this->container[j][i]) {
					factor = false;
				}
			}

			if (factor) {
				++null_col_count;
			}
		}

		if (!null_col_count || null_col_count == this->cols) {
			return;
		}

		int not_null_col_count = this->cols - null_col_count;
		int* not_null_col_indexes = new int[not_null_col_count];
		int current_index = 0;

		for (int i = 0; i < this->cols; ++i) {

			bool factor = true;
			for (int j = 0; j < this->rows && factor; ++j) {

				if (this->container[j][i]) {

					not_null_col_indexes[current_index] = i;

					factor = false;
					++current_index;
				}
			}
		}

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

		this->cols -= null_col_count;

		this->container = new double* [this->rows];
		for (int i = 0; i < this->rows; ++i) {
			this->container[i] = new double[this->cols];
		}

		for (int k = 0; k < not_null_col_count; ++k) {

			for (int i = 0; i < not_null_col_count + null_col_count; ++i) {

				if (i == not_null_col_indexes[k]) {

					for (int j = 0; j < this->rows; ++j) {
						this->container[j][k] = buffer[j][i];
					}
				}
			}
		}

		for (int i = 0; i < this->rows; ++i) {
			delete[] buffer[i];
		}
		delete[] buffer;

		delete[] not_null_col_indexes;
	}

	void matrix::power(const int& value) {

		try {

			matrix_is_square("power(const int&): matrix is not square");

			power_check("power(const int&): value of the pow less than null", value);

			if (!value || value == 1) {
				return;
			}

			if (this->rows == this->default_rows && this->cols == this->default_cols) {

				double multiplier = this->container[0][0];

				for (int i = 2; i <= value; ++i) {
					this->container[0][0] *= multiplier;
				}

				return;
			}

			int dim = this->rows;

			double** matrix_power = new double* [dim];
			for (int i = 0; i < dim; ++i) {
				matrix_power[i] = new double[dim];
			}

			for (int i = 0; i < dim; ++i) {
				for (int j = 0; j < dim; ++j) {
					matrix_power[i][j] = 0.0;
				}
			}

			double** matrix_buffer = new double* [dim];
			for (int i = 0; i < dim; ++i) {
				matrix_buffer[i] = new double[dim];
			}

			for (int i = 0; i < dim; ++i) {
				for (int j = 0; j < dim; ++j) {
					matrix_buffer[i][j] = this->container[i][j];
				}
			}

			for (int k = 2; k <= value; ++k) {

				for (int i = 0; i < dim; ++i) {

					for (int j = 0; j < dim; ++j) {

						for (int l = 0; l < dim; ++l) {
							matrix_power[j][i] += matrix_buffer[j][l] * this->container[l][i];
						}
					}
				}

				for (int i = 0; i < dim; ++i) {
					for (int j = 0; j < dim; ++j) {
						matrix_buffer[i][j] = matrix_power[i][j];
					}
				}

				for (int i = 0; i < dim; ++i) {
					for (int j = 0; j < dim; ++j) {
						matrix_power[i][j] = 0.0;
					}
				}
			}

			for (int i = 0; i < dim; ++i) {
				for (int j = 0; j < dim; ++j) {
					this->container[i][j] = matrix_buffer[i][j];
				}
			}

			for (int i = 0; i < dim; ++i) {
				delete[] matrix_power[i];
			}
			delete[] matrix_power;

			for (int i = 0; i < dim; ++i) {
				delete[] matrix_buffer[i];
			}
			delete[] matrix_buffer;
		}
		catch (std::string& ex) {
			std::cout << ex << '\n';
		}
	}

	matrix::~matrix() {
		for (int i = 0; i < this->rows; ++i) {
			delete[] this->container[i];
		}
		delete[] this->container;
	}

}