#include "matrix.h"

namespace advm {

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

	void matrix::to_null() {
		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < this->cols; ++j) {
				this->container[i][j] = 0.0;
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

	void matrix::to_upper_triangular() {

		if (this->rows == this->default_rows && this->cols == this->default_cols) {
			return;
		}

		for (int i = 0; i < this->cols; ++i) {

			for (int j = i; j < this->rows; ++j) {

				if (!this->container[j][i]) {

					int result_index;
					bool factor = true;

					for (int k = j + 1; k < this->rows && factor; ++k) {

						if (this->container[k][i]) {
							result_index = k;

							for (int col_index = 0; col_index < this->cols; ++col_index) {

								double temp = this->container[result_index][col_index];
								this->container[result_index][col_index] = this->container[j][col_index];
								this->container[j][col_index] = temp;
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

					value_is_null("to_upper_triangular(): the system cannot be converted to a triangular form", 
						this->container[i][i]);

					double multiplier = this->container[j][i] / this->container[i][i];
					for (int k = 0; k < this->cols; ++k) {

						this->container[j][k] = this->container[j][k] - (multiplier * this->container[i][k]);
					}
				}
				catch (std::string& ex) {

					std::cout << ex << '\n';

					return;
				}
			}
		}

		for (int i = 0; i < this->rows; ++i) {

			double value = this->container[i][i];

			for (int j = 0; j < this->cols; ++j) {
				this->container[i][j] = (!this->container[i][j]) ? 0.0 : (this->container[i][j] / value);
			}
		}
	}

	void matrix::to_lower_triangular() {

		if (this->rows == this->default_rows && this->cols == this->default_cols) {
			return;
		}

		for (int i = 0; i < this->cols; ++i) {

			for (int j = i; j < this->rows; ++j) {

				if (!this->container[j][i]) {

					int result_index;
					bool factor = true;

					for (int k = j + 1; k < this->rows && factor; ++k) {

						if (this->container[k][i]) {
							result_index = k;

							for (int col_index = 0; col_index < this->cols; ++col_index) {

								double temp = this->container[result_index][col_index];
								this->container[result_index][col_index] = this->container[j][col_index];
								this->container[j][col_index] = temp;
							}

							factor = false;
						}
					}
				}
			}
		}

		for (int k = this->rows - 1; k >= 0; --k) {

			for (int i = k - 1; i >= 0; --i) {

				try {

					value_is_null("to_lower_triangular(): the system cannot be converted to a triangular form",
						this->container[k][k]);

					double multiplier = this->container[i][k] / this->container[k][k];

					for (int j = this->cols - 1; j >= 0; --j) {

						this->container[i][j] = this->container[i][j] - (multiplier * this->container[k][j]);
					}
				}
				catch (std::string& ex) {

					std::cout << ex << '\n';

					return;
				}
			}
		}
		
		for (int i = 0; i < this->rows; ++i) {

			double value = this->container[i][i];

			for (int j = 0; j < this->cols; ++j) {
				this->container[i][j] = (!this->container[i][j]) ? 0.0 : (this->container[i][j] / value);
			}
		}
	}
}
