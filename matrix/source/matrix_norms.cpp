#include "matrix.h"

namespace advm {

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
}