#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN


#include "Common.h"

#include "../../doctest.h"

typedef std::complex<double> cd;

TEST_CASE("Testing Fast Fourier Transform alogrithms") {

    srand(time(NULL));
    int numberofiter = 25;
    
        for (int i = 0; i < numberofiter; i++) {
            std::cout << std::endl;

            std::vector<cd> a = getRandomVec(pow(2, i));

            auto start = std::chrono::high_resolution_clock::now();
            std::vector<cd> b = FFT::fft(a);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> ms_result = end - start;
            std::cout << "----------- Time non-multithread : " << ms_result.count() << std::endl;

            for (int j = 1; j < 6; j++) {

                const int maxth = pow(2, j);
                std::cout << std::endl;
                std::cout << " MAX number of add threads: " << maxth << " ";

                auto start1 = std::chrono::high_resolution_clock::now();
                std::vector<cd> b1 = MT_FFT::fft(a, maxth);
                auto end1 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> ms_result1 = end1 - start1;
                std::cout << "Time multithread : " << ms_result1.count() << std::endl;

                std::this_thread::sleep_for(std::chrono::milliseconds(1));

                CHECK(b == b1);
            }
        }
    
}
