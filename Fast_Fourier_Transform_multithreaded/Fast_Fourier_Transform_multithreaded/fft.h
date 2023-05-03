#pragma once
#include <vector>
#include <cmath>


//#include "../../AA_tree_complexnumbers/ComplexNumber.h"

//typedef std::complex<double> cd;

#define PI     3.14159265358979323846

namespace FFT{

	template<typename Complex>
	void calcRootsOfUnity(const std::vector<Complex> coefs, std::vector<Complex>& w, const int n) {

		for (int i = 0; i < n; i++) {
			double alpha = -2 * PI * i / n;
			w[i] = Complex(cos(alpha), sin(alpha));
		}

	}


	template<typename Complex>
	std::vector<Complex> fft(std::vector<Complex>& coefs) {
		
		int n = coefs.size();

		if (n == 1)
			return std::vector<Complex>(1, coefs[0]);

		std::vector<Complex> w(n);

		calcRootsOfUnity(coefs,w,n);

		std::vector<Complex> A0(n / 2), A1(n / 2);

		for (int i = 0; i < n / 2; i++) {

			A0[i] = coefs[i * 2];
			A1[i] = coefs[i * 2 + 1];

		}

		// Recursive call for even indexed coefficients
		std::vector<Complex> y0 = fft(A0);

		// Recursive call for odd indexed coefficients
		std::vector<Complex> y1 = fft(A1);

		std::vector<Complex> y(n);

		for (int k = 0; k < n / 2; k++) {
			y[k] = y0[k] + w[k] * y1[k];
			y[k + n / 2] = y0[k] - w[k] * y1[k];
		}

		return y;
		
	}
		
}