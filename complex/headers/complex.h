#pragma once 

#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

namespace advm {

	class complex {

	private:

		double* number;
		const int size;
	public:

		complex(const double& re = 0.0, const double& im = 0.0);

		complex(const complex& object);

		complex& operator = (const complex& object);

		complex& operator = (const double& value);

		complex operator + (const complex& object);

		complex operator - (const complex& object);

		complex operator * (const complex& object);

		complex& operator * (const double& value);

		complex& operator ++ ();

		complex operator ++ (int value);

		complex& operator -- ();

		complex operator -- (int value);

		complex operator / (const complex& object);

		void int_random_number(const int& value_1, const int& value_2);

		void double_random_number(const int& value_1, const int& value_2);

		friend std::istream& operator >> (std::istream& in, const complex& in_number);

		friend std::ostream& operator << (std::ostream& out, const complex& out_number);

		double get_re();

		double get_im();

		~complex();

	};
}

#endif 