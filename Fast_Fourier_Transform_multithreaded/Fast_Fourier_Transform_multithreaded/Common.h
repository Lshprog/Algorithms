#pragma once
#include <vector>
#include <complex>
#include <vector>
#include <chrono>

#include "fft.h"
#include "fftmultithread.h"
#include "ThreadPool.h"

typedef std::complex<double> cd;

std::vector<std::complex<double>> getRandomVec(int n, int mod = 10) {

	std::vector<std::complex<double>> result;

	for (int i = 0; i < n; i++) {
		result.push_back(rand()  %  mod);
	}

	return result;
}

bool compareComplexVec(const std::vector<cd>& a1,const std::vector<cd>& a2 ){
	for (int i = 0; i < a1.size(); i++) {
		if ((std::real(a1[i]) - std::real(a2[i]) > 0.01) || (std::imag(a1[i]) - std::imag(a2[i]) > 0.01))
			return false;
	}
	return true;
}