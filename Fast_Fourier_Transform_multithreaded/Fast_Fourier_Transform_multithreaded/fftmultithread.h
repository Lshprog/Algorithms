#pragma once
#include "fft.h"
#include <thread>
#include <future>
#include <mutex>
#include <iostream>

#include "fft.h"

//constexpr int THREAD_NUMBER = 16;


namespace MT_FFT {

	template<typename Complex>
	std::vector<Complex> fftmultithread(std::vector<Complex>& coefs, int& current_thread_amount, const int& max_threads) {

		static std::mutex mut;

		int n = coefs.size();

		if (n == 1)
			return std::vector<Complex>(1, coefs[0]);

		std::vector<Complex> A0(n / 2), A1(n / 2);

		for (int i = 0; i < n / 2; i++) {

			A0[i] = coefs[i * 2];
			A1[i] = coefs[i * 2 + 1];

		}

		std::vector<Complex> w(n);
		std::vector<Complex> y0;
		std::vector<Complex> y1;

		if (current_thread_amount < max_threads) {
			
			std::future<std::vector<Complex>> handle = std::async(std::launch::async, std::ref(fftmultithread<Complex>), std::ref(A0), std::ref(current_thread_amount), max_threads);
			//std::thread t1(&calcRootsOfUnity<Complex>,coefs ,std::ref(w), n);
			std::future<std::vector<Complex>> handle2 = std::async(std::launch::async, std::ref(fftmultithread<Complex>), std::ref(A1), std::ref(current_thread_amount), max_threads);
			{
				std::lock_guard<std::mutex> lock(mut);
				current_thread_amount += 2;
			}

			FFT::calcRootsOfUnity<Complex>(coefs, w, n);
			
			y0 = handle.get();
			y1 = handle2.get();
			
			//t1.join();
			
		}
		else {
			FFT::calcRootsOfUnity<Complex>(coefs, w, n);
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
	std::vector<Complex> fft(std::vector<Complex>& coefs,const int max_threads) {
		int current_thread_amount = 1;
		return fftmultithread<Complex>(coefs, current_thread_amount, max_threads);

	}
}