#pragma once
#include "fft.h"
#include <thread>
#include <future>
#include <mutex>
#include <iostream>

#include "fft.h"

#define THREAD_NUMBER   16
static std::mutex mut;

namespace MT_FFT {

	template<typename Complex>
	std::vector<Complex> fftmultithread(std::vector<Complex>& coefs, int& current_thread_amount) {

		int n = coefs.size();

		if (n == 1)
			return std::vector<Complex>(1, coefs[0]);

		std::vector<Complex> w(n);

		for (int i = 0; i < n; i++) {
			double alpha = -2 * PI * i / n;
			w[i] = Complex(cos(alpha), sin(alpha));
		}

		std::vector<Complex> A0(n / 2), A1(n / 2);

		for (int i = 0; i < n / 2; i++) {

			A0[i] = coefs[i * 2];
			A1[i] = coefs[i * 2 + 1];

		}

		std::vector<Complex> y0;
		std::vector<Complex> y1;

		/*if (current_thread_amount < THREAD_NUMBER) {
			std::promise<std::vector<Complex>> p;
			std::future<std::vector<Complex>> f = p.get_future();
			std::thread t([&]() { p.set_value(fftmultithread<Complex>(A0, current_thread_amount)); });
			t.detach();
			current_thread_amount++;
			y1 = FFT::fft(A1);
			y0 = f.get();
		}
		else {
			y0 = FFT::fft(A0);
			y1 = FFT::fft(A1);
		}*/

		if (current_thread_amount < THREAD_NUMBER) {
			std::future<std::vector<Complex>> handle = std::async(std::launch::async, std::ref(fftmultithread<Complex>), std::ref(A0), std::ref(current_thread_amount));
			y1 = FFT::fft(A1);
			y0 = handle.get();
			std::lock_guard<std::mutex> lock(mut);
			current_thread_amount++;
		}
		else {
			y0 = FFT::fft(A0);
			y1 = FFT::fft(A1);
		}



		std::vector<Complex> y(n);

		for (int k = 0; k < n / 2; k++) {
			y[k] = y0[k] + w[k] * y1[k];
			y[k + n / 2] = y0[k] - w[k] * y1[k];
		}

		return y;

	}

	template<typename Complex>
	std::vector<Complex> fft(std::vector<Complex>& coefs) {
		int current_thread_amount = 0;
		return fftmultithread<Complex>(coefs, current_thread_amount);

	}
}