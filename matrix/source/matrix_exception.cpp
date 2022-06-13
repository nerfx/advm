#include<ctime>
#include "matrix.h"

namespace advm {

	void matrix::check_equality_rows_and_cols(const std::string& ex, const int& dim_1, const int& dim_2) {

		if (this->rows != dim_1 || this->cols != dim_2) {
			throw "error(" + std::to_string(NOT_EQUAL_ERROR) + "): " + ex;
		}
	}

	void matrix::check_equality_dims_for_multi(const std::string& ex, const int& dim) {

		if (this->cols != dim) {
			throw "error(" + std::to_string(MULTIPLY_ERROR) + "): " + ex;
		}
	}

	void matrix::check_range_rows_and_cols_indexes(const std::string& ex, const int& row_index, const int& col_index) {

		if (row_index < 0 || row_index >= this->rows || col_index < 0 || col_index >= this->cols) {
			throw "error(" + std::to_string(OUT_OF_RANGE_DIMS_INDEXES) + "): " + ex;
		}
	}

	void matrix::check_range_two_rows_indexes(const std::string& ex, const int& row_index_1, const int& row_index_2) {

		if (row_index_1 < 0 || row_index_1 >= this->rows || row_index_2 < 0 || row_index_2 >= this->rows) {
			throw "error(" + std::to_string(OUT_OF_RANGE_ROWS) + "): " + ex;
		}
	}

	void matrix::check_range_two_cols_indexes(const std::string& ex, const int& col_index_1, const int& col_index_2) {

		if (col_index_1 < 0 || col_index_1 >= this->cols || col_index_2 < 0 || col_index_2 >= this->cols) {
			throw "error(" + std::to_string(OUT_OF_RANGE_COLS) + "): " + ex;
		}
	}

	void matrix::check_range_row_index(const std::string& ex, const int& row_index) {

		if (row_index < 0 || row_index >= this->rows) {
			throw "error(" + std::to_string(OUT_OF_RANGE_ROWS) + "): " + ex;
		}
	}

	void matrix::check_range_col_index(const std::string& ex, const int& col_index) {

		if (col_index < 0 || col_index >= this->cols) {
			throw "error(" + std::to_string(NOT_EQUAL_ERROR) + "): " + ex;
		}
	}

	void matrix::is_nan(const std::string& ex, const double& number) {

		if (number != number) {
			throw "error(" + std::to_string(NUMBER_IS_NAN) + "): " + ex;
		}
	}

	void matrix::rows_indexes_are_equal(const std::string& ex, const int& row_index_1, const int& row_index_2) {

		if (row_index_1 == row_index_2) {
			throw "error(" + std::to_string(ROWS_ARE_EQUAL) + "): " + ex;
		}
	}

	void matrix::cols_indexes_are_equal(const std::string& ex, const int& col_index_1, const int& col_index_2) {

		if (col_index_1 == col_index_2) {
			throw "error(" + std::to_string(COLS_ARE_EQUAL) + "): " + ex;
		}
	}

	void matrix::rows_are_default(const std::string& ex) {

		if (this->rows == this->default_rows) {
			throw "error(" + std::to_string(ROWS_ARE_DEFAULT) + "): " + ex;
		}
	}

	void matrix::cols_are_default(const std::string& ex) {

		if (this->cols == this->default_cols) {
			throw "error(" + std::to_string(COLS_ARE_DEFAULT) + "): " + ex;
		}
	}

	void matrix::insert_row_check(const std::string& ex, const int& insert_row_index, const int& rows_size) {

		if (insert_row_index < 0 || insert_row_index > this->rows || rows_size != this->cols) {
			throw "error(" + std::to_string(INSERT_ROW_ERROR) + "): " + ex;
		}
	}

	void matrix::insert_col_check(const std::string& ex, const int& insert_col_index, const int& cols_size) {

		if (insert_col_index < 0 || insert_col_index > this->cols || cols_size != this->rows) {
			throw "error(" + std::to_string(INSERT_COL_ERROR) + "): " + ex;
		}
	}

	void matrix::matrix_is_square(const std::string& ex) {

		if (this->cols != this->rows) {
			throw "error(" + std::to_string(ROWS_AND_COLS_NOT_EQUAL) + "): " + ex;
		}
	}

	void matrix::kramer_error(const std::string& ex, const int& length, const double& kramer_det) {

		if (this->rows != length || !kramer_det) {
			throw "error(" + std::to_string(KRAMER_ERROR) + "): " + ex;
		}
	}

	void matrix::value_is_null(const std::string& ex, const double& value) {

		if (!value) {
			throw "error(" + std::to_string(VALUE_IS_NULL) + "): " + ex;
		}
	}

	void matrix::check_free_column_dim(const std::string& ex, const int& dim) {

		if (dim != this->rows) {
			throw "error(" + std::to_string(FREE_COL_DIM_ERROR) + "): " + ex;
		}
	}

	void matrix::check_default_matrix(const std::string& ex, const double& free_column_element, const double& default_matrix_elem) {

		if (this->rows == this->default_rows && this->cols == this->default_cols) {

			if (!default_matrix_elem && !free_column_element) {

				throw rand() % 50;
			}
			else if (!default_matrix_elem && free_column_element) {

				throw "error(" + std::to_string(DEFAULT_MATRIX_ERROR) + "): " + ex;
			}
			else {

				throw free_column_element / default_matrix_elem;
			}
		}
	}

	void matrix::check_not_default_matrix(const std::string& ex, const int& null_rows, const int& null_cols, const bool& factor) {

		if (this->rows == this->cols && null_rows == this->rows && factor) {

			matrix exception_object(this->cols, 1);

			for (int i = 0; i < this->cols; ++i) {

				int rand_value = rand() % (50);
				exception_object.container[i][0] = static_cast<double>(rand_value);
			}

			throw exception_object;
		}
		else if (this->rows == this->cols && null_rows == this->rows && !factor) {

			throw "error(" + std::to_string(NOT_DEFAULT_MATRIX_ERROR) + "): " + ex;
		}
		else if (this->rows != this->cols && this->rows == null_rows && this->cols == null_cols && factor) {

			matrix exception_object(this->cols, 1);

			for (int i = 0; i < this->cols; ++i) {

				int random_value = rand() % 50;
				exception_object.container[i][0] = static_cast<double>(random_value);
			}

			throw exception_object;
		}
		else if (this->rows != this->cols && this->rows == null_rows && this->cols == null_cols && !factor) {

			throw "error(" + std::to_string(NOT_DEFAULT_MATRIX_ERROR) + "): " + ex;
		}
	}

	void matrix::power_check(const std::string& ex, const int& value) {

		if (value < 0) {

			throw "error(" + std::to_string(LESS_THAN_NULL) + "): " + ex;
		}
	}
}