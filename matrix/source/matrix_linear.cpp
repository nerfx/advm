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
					matrix_power[i][j] = this->container[i][j];
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
						this->container[i][j] = 0.0;
					}
				}

				for (int i = 0; i < dim; ++i) {

					for (int j = 0; j < dim; ++j) {

						for (int l = 0; l < dim; ++l) {

							this->container[j][i] += matrix_buffer[j][l] * matrix_power[l][i];
						}
					}
				}

				if (k != value) {

					for (int i = 0; i < dim; ++i) {
						for (int j = 0; j < dim; ++j) {
							matrix_power[i][j] = this->container[i][j];
						}
					}
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

	int matrix::rank() {

		if (this->rows == this->default_rows && this->cols == this->default_cols) {

			if (!this->container[0][0]) {
				return 0;
			}

			return 1;
		}

		if (this->rows == this->default_rows) {

			bool factor = true;
			for (int i = 0; i < this->cols && factor; ++i) {

				if (this->container[0][i]) {
					factor = false;
				}
			}

			if (factor) {
				return 0;
			}
			else {
				return 1;
			}
		}

		double** rank_transform = new double* [this->rows];
		for (int i = 0; i < this->rows; ++i) {
			rank_transform[i] = new double[this->cols];
		}

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				rank_transform[i][j] = this->container[i][j];
			}
		}

		for (int i = 0; i < this->cols; ++i) {

			for (int j = i; j < this->rows; ++j) {

				if (!rank_transform[j][i]) {

					int result_index;
					bool factor = true;

					for (int k = j + 1; k < this->rows && factor; ++k) {

						if (rank_transform[k][i]) {
							result_index = k;

							for (int col_index = 0; col_index < this->cols; ++col_index) {

								double temp = rank_transform[result_index][col_index];
								rank_transform[result_index][col_index] = rank_transform[j][col_index];
								rank_transform[j][col_index] = temp;
							}

							factor = false;
						}
					}
				}
			}
		}

		for (int i = 0; i < this->rows; ++i) {

			for (int j = i + 1; j < this->rows; ++j) {

				try {

					value_is_null("rank(): the system cannot be converted to a triangular form", rank_transform[i][i]);

					double multiplier = rank_transform[j][i] / rank_transform[i][i];
					for (int k = 0; k < this->cols; ++k) {

						rank_transform[j][k] = rank_transform[j][k] - (multiplier * rank_transform[i][k]);
					}
				}
				catch (std::string& ex) {

					std::cout << ex << '\n';
				}
			}
		}

		for (int i = 0; i < this->rows; ++i) {

			double value = rank_transform[i][i];

			for (int j = 0; j < this->cols; ++j) {
				rank_transform[i][j] = (!rank_transform[i][j]) ? 0.0 : (rank_transform[i][j] / value);
			}
		}
		
		int null_row_count = 0;
		
		for (int i = 0; i < this->rows; ++i) {

			bool factor = true;
			for (int j = 0; j < this->cols && factor; ++j) {

				if (rank_transform[i][j]) {
					factor = false;
				}
			}

			if (factor) {
				++null_row_count;
			}
		}

		for (int i = 0; i < this->rows; ++i) {
			delete[] rank_transform[i];
		}
		delete[] rank_transform;

		return this->rows - null_row_count;
	}

	matrix::~matrix() {
		for (int i = 0; i < this->rows; ++i) {
			delete[] this->container[i];
		}
		delete[] this->container;
	}

}