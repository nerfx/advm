#include <iostream>
#include "complex.h"

namespace advm {

	complex& complex::operator = (const complex& object) {

		this->number[0] = object.number[0];
		this->number[1] = object.number[1];

		return*this;
	}

	complex& complex::operator = (const double& value) {

		for (int i = 0; i < this->size; ++i) {
			this->number[i] = value;
		}

		return*this;
	}

	complex complex::operator + (const complex& object) {

		complex buffer(*this);

		for (int i = 0; i < this->size; ++i) {
			buffer.number[i] = this->number[i] + object.number[i];
		}

		return buffer;
	}

	complex complex::operator - (const complex& object) {

		complex buffer(*this);

		for (int i = 0; i < this->size; ++i) {
			buffer.number[i] = this->number[i] - object.number[i];
		}

		return buffer;
	}

	complex complex::operator * (const complex& object) {

		complex buffer(*this);

		buffer.number[0] = this->number[0] * object.number[0] - this->number[1] * object.number[1];
		buffer.number[1] = this->number[1] * object.number[0] + this->number[0] * object.number[1];

		return buffer;
	}

	complex& complex::operator * (const double& value) {

		for (int i = 0; i < this->size; ++i) {
			this->number[i] *= value;
		}

		return*this;
	}

	complex& complex::operator ++ () {

		for (int i = 0; i < this->size; ++i) {
			++this->number[i];
		}

		return*this;
	}

	complex complex::operator ++ (int value) {

		complex buffer(*this);

		for (int i = 0; i < this->size; ++i) {
			++this->number[i];
		}

		return buffer;
	}

	complex& complex::operator -- () {

		for (int i = 0; i < this->size; ++i) {
			--this->number[i];
		}

		return*this;
	}

	complex complex::operator -- (int value) {

		complex buffer(*this);

		for (int i = 0; i < this->size; ++i) {
			--this->number[i];
		}

		return buffer;
	}

	complex complex::operator / (const complex& object) {

		if (!object.number[0] && !object.number[1]) {

			std::cout << "division by zero!\n";

			complex buffer;
			float nan_float = NAN;

			for (int i = 0; i < this->size; ++i) {
				buffer.number[i] = static_cast<double>(nan_float);
			}

			return buffer;
		}

		complex result_number;
		double divider = object.number[0] * object.number[0] + object.number[1] * object.number[1];

		result_number.number[0] = this->number[0] * object.number[0] + this->number[1] * object.number[1];
		result_number.number[1] = this->number[1] * object.number[0] - this->number[0] * object.number[1];

		result_number.number[0] /= divider;
		result_number.number[1] /= divider;

		return result_number;
	}

	std::istream& operator >> (std::istream& in, const complex& in_number) {

		for (int i = 0; i < in_number.size; ++i) {
			in >> in_number.number[i];
		}

		return in;
	}

	std::ostream& operator << (std::ostream& out, const complex& out_number) {

		for (int i = 0; i < out_number.size; ++i) {
			out << out_number.number[i] << '\n';
		}

		std::cout << '\n';

		return out;
	}

}