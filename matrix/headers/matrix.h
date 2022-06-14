#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<string>

namespace advm {

	class matrix {

	private:

		int rows;
		int cols;
		double** container;

		const int default_rows;
		const int default_cols;

		/*

		* NOT_EQUAL_ERROR (3) - the check_number of rows/columns of the first matrix is not obj to the check_number of rows/columns of the second matrix

		* MULTIPLY_ERROR (5) - the check_number of columns of the first matrix is not obj to the check_number of rows of the second matrix when performing matrix multiplication

		* OUT_OF_RANGE_DIMS_INDEXES (7) - the insert_row_index of the rows and columns goes beyond the acceptable dimension range

		* OUT_OF_RANGE_ROWS (11) - the insert_row_index of the two rows or one row goes beyond the acceptable dimension range

		* OUTOF_RANGE_COLS (13) - the insert_row_index of the two columns or one column goes beyond the acceptable dimension range

		* NUMBER_IS_NAN (17) - one of the parameters of the function is NAN

		* ROWS_ARE_EQUAL (19) - rows are obj

		* COLS_ARE_EQUAL (23) - cols are obj

		* ROWS_ARE_DEFAULT (29) - the check_number of rows is default (it is impossible to delete a row)

		* COLS_ARE_DEFAULT (31) - the check_number of cols is default (it is impossible to delete a column)

		* INSERT_ROW_ERROR (37) - the insert_row_index of the inserted row is out of the acceptable range, or the length of the inserted row does not match the
		  check_number of columns of the matrix

		* INSERT_COL_ERROR (39) - the insert_row_index of the inserted column is out of the acceptable range, or the length of the inserted column does not match the
		  check_number of rows of the matrix

		* ROWS_AND_COLS_NOT_EQUAL (43) - rows != cols (for function trace())

		* KRAMER_ERROR (47) - the length of the free column does not match the row length of the current matrix or determinant is null

		* VALUE_IS_NULL (53) - the value of determinant is null

		* FREE_COLUMN_ERROR (57) - the dimension of free column mismatch dimension of current matrix

		* DEFAULT_MATRIX_ERROR (59) - 1X1 system has no solutions

		* NOT_DEFAULT_MATRIX_ERROR (61) - MXN system has no solutions

		* LESS_TNAN_NULL (67) - the value of the number is less than zero

		*/

		enum error_list {
			UNKNOW_ERROR = -1,
			NOT_EQUAL_ERROR = 3,
			MULTIPLY_ERROR = 5,
			OUT_OF_RANGE_DIMS_INDEXES = 7,
			OUT_OF_RANGE_ROWS = 11,
			OUT_OF_RANGE_COLS = 13,
			NUMBER_IS_NAN = 17,
			ROWS_ARE_EQUAL = 19,
			COLS_ARE_EQUAL = 23,
			ROWS_ARE_DEFAULT = 29,
			COLS_ARE_DEFAULT = 31,
			INSERT_ROW_ERROR = 37,
			INSERT_COL_ERROR = 41,
			ROWS_AND_COLS_NOT_EQUAL = 43,
			KRAMER_ERROR = 47,
			VALUE_IS_NULL = 53,
			FREE_COL_DIM_ERROR = 57,
			DEFAULT_MATRIX_ERROR = 59,
			NOT_DEFAULT_MATRIX_ERROR = 61,
			LESS_THAN_NULL = 67
		};

		void check_equality_rows_and_cols(const std::string& ex, const int& dim_1, const int& dim_2);

		void check_equality_dims_for_multi(const std::string& ex, const int& dim);

		void check_range_rows_and_cols_indexes(const std::string& ex, const int& row_index, const int& col_index);

		void check_range_two_rows_indexes(const std::string& ex, const int& row_index_1, const int& row_index_2);

		void check_range_two_cols_indexes(const std::string& ex, const int& col_index_1, const int& col_index_2);

		void check_range_row_index(const std::string& ex, const int& row_index);

		void check_range_col_index(const std::string& ex, const int& col_index);

		void is_nan(const std::string& ex, const double& number);

		void rows_indexes_are_equal(const std::string& ex, const int& row_index_1, const int& row_index_2);

		void cols_indexes_are_equal(const std::string& ex, const int& col_index_1, const int& col_index_2);

		void rows_are_default(const std::string& ex);

		void cols_are_default(const std::string& ex);

		void insert_row_check(const std::string& ex, const int& insert_row_index, const int& rows_size);

		void insert_col_check(const std::string& ex, const int& insert_col_index, const int& cols_size);

		void matrix_is_square(const std::string& ex);

		void kramer_error(const std::string& ex, const int& length, const double& kramer_det);

		void value_is_null(const std::string& ex, const double& value);

		void check_free_column_dim(const std::string& ex, const int& dimension);

		void check_default_matrix(const std::string& ex, const double& free_column_element, const double& default_matr_element);

		void check_not_default_matrix(const std::string& ex, const int& null_rows, const int& null_cols, const bool& factor);

		void power_check(const std::string& ex, const int& value);

		double value_det(double** buffer, const int& buffer_rows, const int& buffer_cols);

	public:

		matrix(int rows = 1, int cols = 1, double default_value = 0.0);

		matrix(const matrix& copy);

		double** get_matrix();

		int size_rows();

		int size_cols();

		void double_random_input(const int& double_value_1, const int& double_value_2);

		void int_random_input(const int& int_value_1, const int& int_value_2);

		matrix& operator = (const matrix& copy_obj);

		matrix& operator = (const double& value);

		matrix operator + (const matrix& plus_obj);

		matrix operator - (const matrix& minus_obj);

		matrix& operator ++ ();

		matrix operator ++ (int value);

		matrix& operator -- ();

		matrix operator -- (int value);

		matrix& operator * (const double& num);

		matrix operator * (const matrix& multiply_obj);

		matrix& operator += (const matrix& assign_plus_obj);

		matrix& operator -= (const matrix& assign_minus_obj);

		double operator () (const int& row_index, const int& col_index);

		bool operator == (const matrix& obj);

		bool operator != (const matrix& obj);

		bool is_null();

		void to_null();

		void transpose();

		void plus_rows(const int& first_row_index, const int& last_row_index, const double& factor = 1.0);

		void plus_cols(const int& first_col_index, const int& last_col_index, const double& factor = 1.0);

		void multiply_row_by_num(const int& current_row_index, const double& value);

		void multiply_col_by_num(const int& current_col_index, const double& value);

		void to_bool();

		void to_identity();

		void swap_rows(const int& first_row_index, const int& last_row_index);

		void swap_cols(const int& first_col_index, const int& last_col_index);

		template <int N>
		void insert_row(const int& insert_row_index, const double(&list)[N] = { 0.0 });

		template <int N>
		void insert_col(const int& insert_col_index, const double(&list)[N] = { 0.0 });

		void delete_row(const int& delete_row_index);

		void delete_col(const int& delete_col_index);

		double m_norm();

		double l_norm();

		double k_norm();

		double trace();

		double det();

		void invert_matrix();

		void delete_null_rows();

		void delete_null_cols();

		void power(const int& value);

		void to_upper_triangular();

		int rank();

		template <int N>
		matrix kramer(const double(&free_column_list)[N] = { 0.0 });

		template <int N>
		matrix gauss(const double(&free_column)[N] = { 0.0 });

		friend std::istream& operator >> (std::istream& in, const matrix& in_matrix);

		friend std::ostream& operator << (std::ostream& out, const matrix& out_matrix);

		~matrix();

	};

	template <int N>
	void matrix::insert_row(const int& insert_row_index, const double(&row_list)[N]) {

		try {
			insert_row_check("to insert a row impossible because or the row insert_row_index is out of range or the size of the inserted row doesn't match the size of the matrix columns",
				insert_row_index, N);

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

			++this->rows;

			this->container = new double* [this->rows];
			for (int i = 0; i < this->rows; ++i) {
				this->container[i] = new double[this->cols];
			}

			int step = 0;
			for (int i = 0; i < this->rows; ++i) {

				if (i == insert_row_index) {

					step = 1;
					for (int j = 0; j < this->cols; ++j) {
						this->container[i][j] = row_list[j];
					}
				}
				else {

					for (int j = 0; j < this->cols; ++j) {
						this->container[i][j] = buffer[i - step][j];
					}
				}
			}

			for (int i = 0; i < this->rows - 1; ++i) {
				delete[] buffer[i];
			}
			delete[] buffer;
		}
		catch (std::string& ex) {
			std::cout << ex << '\n';
		}
	}

	template <int N>
	void matrix::insert_col(const int& insert_col_index, const double(&column_list)[N]) {

		try {
			insert_col_check("to insert a col impossible because or the col insert_row_index is out of range or the size of the inserted col doesn't match the size of the matrix rows",
				insert_col_index, N);

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

			++this->cols;

			this->container = new double* [this->rows];
			for (int i = 0; i < this->rows; ++i) {
				this->container[i] = new double[this->cols];
			}

			int step = 0;
			for (int i = 0; i < this->cols; ++i) {

				if (i == insert_col_index) {

					step = 1;
					for (int j = 0; j < this->rows; ++j) {
						this->container[j][i] = column_list[j];
					}
				}
				else {

					for (int j = 0; j < this->rows; ++j) {
						this->container[j][i] = buffer[j][i - step];
					}
				}
			}

			for (int i = 0; this->rows; ++i) {
				delete[] buffer[i];
			}
			delete[] buffer;
		}
		catch (std::string& ex) {
			std::cout << ex << '\n';
		}
	}

	template <int N>
	matrix matrix::kramer(const double(&free_column_list)[N]) {

		matrix roots(this->rows, 1);

		try {
			const double main_det = value_det(this->container, this->rows, this->cols);

			kramer_error("kramer(const double (&)[]): matrix is not square or determinant is null", N, main_det);

			double* temp_column = new double[this->rows];
			for (int i = 0; i < this->cols; ++i) {

				for (int j = 0; j < this->rows; ++j) {
					temp_column[j] = this->container[j][i];
					this->container[j][i] = free_column_list[j];
				}

				double current_det = value_det(this->container, this->rows, this->cols);
				if (current_det) {
					roots.container[i][0] = current_det / main_det;
				}
				else {
					roots.container[i][0] = 0.0;
				}

				for (int k = 0; k < this->rows; ++k) {
					this->container[k][i] = temp_column[k];
				}
			}

			delete[] temp_column;
			return roots;
		}
		catch (std::string& e) {

			std::cout << e << '\n';

			float nanf = NAN;
			for (int i = 0; i < this->rows; ++i) {
				roots.container[i][0] = static_cast<double>(nanf);
			}

			return roots;
		}
	}

	template <int N>
	matrix matrix::gauss(const double(&free_column)[N]) {

		try {

			check_free_column_dim("gauss(const double (&)[]: the dimension of free column mismatch with the dimension of the rows of current matrix", N);

			check_default_matrix("gauss(const double (&)[]: the matrix is default and the system has no solves",
				free_column[0], this->container[0][0]);

			int dimension_diff = this->rows - this->cols;
			if (dimension_diff > 0) {

				double** copy_matrix = new double* [this->rows];
				for (int i = 0; i < this->rows; ++i) {
					copy_matrix[i] = new double[this->cols];
				}

				for (int i = 0; i < this->rows; ++i) {
					for (int j = 0; j < this->cols; ++j) {
						copy_matrix[i][j] = this->container[i][j];
					}
				}

				for (int i = 0; i < this->rows; ++i) {
					delete[] this->container[i];
				}
				delete[] this->container;

				int index = this->cols - 1;
				this->cols += dimension_diff;
				
				this->container = new double* [this->rows];
				for (int i = 0; i < this->rows; ++i) {
					this->container[i] = new double[this->cols];
				}

				for (int i = 0; i < this->cols; ++i) {

					if (i > index) {

						for (int j = 0; j < this->rows; ++j) {
							this->container[j][i] = 0.0;
						}
					}
					else {

						for (int j = 0; j < this->rows; ++j) {
							this->container[j][i] = copy_matrix[j][i];
						}
					}
				}

				for (int i = 0; i < this->rows; ++i) {
					delete[] copy_matrix[i];
				}
				delete[] copy_matrix;
			}
			
			int null_row_count = 0;
			for (int i = 0; i < this->rows; ++i) {

				int factor = true;
				for (int j = 0; j < this->cols && factor; ++j) {

					if (this->container[i][j]) {
						factor = false;
					}
				}

				if (factor) {
					++null_row_count;
				}
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

			bool factor = true;
			for (int i = 0; i < N && factor; ++i) {

				if (free_column[i]) {

					factor = false;
				}
			}

			check_not_default_matrix("gauss(const double(&)[]: system has no solutions", null_row_count, null_col_count, factor);
			
			int new_rows = this->rows;
			int new_cols = this->cols + 1;

			double** extended_matrix = new double* [new_rows];
			for (int i = 0; i < new_rows; ++i) {
				extended_matrix[i] = new double[new_cols];
			}

			for (int i = 0; i < new_cols; ++i) {

				if (i == this->cols) {

					for (int j = 0; j < new_rows; ++j) {
						extended_matrix[j][i] = free_column[j];
					}
				}
				else {

					for (int j = 0; j < new_rows; ++j) {
						extended_matrix[j][i] = this->container[j][i];
					}
				}
			}

			for (int i = 0; i < new_cols; ++i) {

				for (int j = i; j < new_rows; ++j) {

					if (!extended_matrix[j][i]) {

						int result_index;
						bool factor = true;

						for (int k = j + 1; k < new_rows && factor; ++k) {

							if (extended_matrix[k][i]) {
								result_index = k;

								for (int col_index = 0; col_index < new_cols; ++col_index) {

									double temp = extended_matrix[result_index][col_index];
									extended_matrix[result_index][col_index] = extended_matrix[j][col_index];
									extended_matrix[j][col_index] = temp;
								}

								factor = false;
							}
						}
					}
				}
			}

			double** copy_matrix = new double* [new_rows];
			for (int i = 0; i < new_rows; ++i) {
				copy_matrix[i] = new double[new_cols];
			}

			for (int i = 0; i < new_rows; ++i) {
				for (int j = 0; j < new_cols; ++j) {
					copy_matrix[i][j] = extended_matrix[i][j];
				}
			}

			for (int i = 0; i < new_rows; ++i) {

				for (int j = i + 1; j < new_rows; ++j) {

					try {

						value_is_null("gauss(const double(&)[]): system has no solutions", copy_matrix[i][i]);

						double multiplier = copy_matrix[j][i] / copy_matrix[i][i];
						for (int k = 0; k < new_cols; ++k) {

							copy_matrix[j][k] = copy_matrix[j][k] - (multiplier * copy_matrix[i][k]);
						}
					}
					catch (std::string& ex) {

						std::cout << ex << '\n';

						matrix roots;
						float nanf = NAN;

						roots.container[0][0] = static_cast<double>(nanf);

						return roots;
					}
				}

				/*
				for (int i = 0; i < new_rows; ++i) {
					for (int j = 0; j < new_cols; ++j) {
						extended_matrix[i][j] = copy_matrix[i][j];
					}
				}
				*/
			}

			for (int i = new_rows - 1; i >= 0; --i) {

				for (int j = i - 1; j >= 0; --j) {

					try {

						value_is_null("gauss(const double(&)[]): system has no solutions", copy_matrix[i][i]);

						double multiplier = copy_matrix[j][i] / copy_matrix[i][i];
						for (int k = new_cols - 1; k >= 0; --k) {

							copy_matrix[j][k] = copy_matrix[j][k] - (multiplier * copy_matrix[i][k]);
						}
					}
					catch (std::string& ex) {

						std::cout << ex << '\n';

						matrix roots;
						float nanf = NAN;

						roots.container[0][0] = static_cast<double>(nanf);

						return roots;
					}
				}
			}

			for (int i = 0; i < new_rows; ++i) {

				double div = copy_matrix[i][i];
				for (int j = 0; j < new_cols; ++j) {

					if (copy_matrix[i][j]) {
						copy_matrix[i][j] /= div;
					}
				}
			}

			matrix roots(new_rows, 1);
			for (int i = 0; i < new_rows; ++i) {
				roots.container[i][0] = copy_matrix[i][new_cols - 1];
			}

			for (int i = 0; i < new_rows; ++i) {
				delete[] extended_matrix[i];
			}
			delete[] extended_matrix;

			for (int i = 0; i < new_rows; ++i) {
				delete[] copy_matrix[i];
			}
			delete[] copy_matrix;

			return roots;
		}
		catch (std::string& ex) {

			std::cout << ex << '\n';

			matrix roots;
			float nanf = NAN;

			roots.container[0][0] = static_cast<double>(nanf);

			return roots;
		}
		catch (int& number) {

			matrix roots;

			roots.container[0][0] = static_cast<double>(number);

			return roots;
		}
		catch (double& number) {

			matrix roots;

			roots.container[0][0] = number;

			return roots;
		}
		catch (const matrix& ex_obj) {

			return ex_obj;
		}
	}

}

#endif