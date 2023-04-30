#pragma once
#include <vector>
#include <complex>
#include <vector>
#include <chrono>

#include "fft.h"
#include "fftmultithread.h"
#include "ThreadPool.h"

std::vector<std::complex<double>> getRandomVec(int n, int mod = 10) {

	std::vector<std::complex<double>> result;

	for (int i = 0; i < n; i++) {
		result.push_back(rand()  %  mod);
	}

	return result;
}