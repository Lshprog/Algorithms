#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN


#include "Common.h"

#include "../../doctest.h"



TEST_CASE("Testing Fast Fourier Transform alogrithms") {

    std::vector<cd> aa = { 1, 2, 3, 4 };
    std::vector<cd> bb = { cd(10.0, 0.0), cd(-2.0, 2.0), cd(-2.0, 0.0), cd(-2.0, -2.0) };

    CHECK(compareComplexVec(FFT::fft(aa), bb));
    CHECK(compareComplexVec(MT_FFT::fft(aa,16),bb));

    std::vector<cd> aa1 = { 1, 0, -2, 1 };
    std::vector<cd> bb1 = { cd(0.0, 0.0), cd(3.0, 1.0), cd(-2.0, 0.0), cd(3.0, -1.0) };
    std::vector<cd> tt = FFT::fft(aa1);
    /*for (int i = 0; i < 4; i++) {
        std::cout << tt[i];
    }*/

    CHECK(compareComplexVec(tt, bb1));
    CHECK(compareComplexVec(MT_FFT::fft(aa1, 16), bb1));

    srand(time(NULL));
    int numberofiter = 25;
    
        for (int i = 0; i < numberofiter; i++) {
            std::cout << std::endl;

            std::vector<cd> a = getRandomVec(pow(2, i));

            auto start = std::chrono::high_resolution_clock::now();
            std::vector<cd> b = FFT::fft(a);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> ms_result = end - start;
            std::cout << "----------- Time non-multithread : " << ms_result.count()<< " ms" << std::endl;

            for (int j = 1; j < 6; j++) {

                const int maxth = pow(2, j);
                std::cout << std::endl;
                std::cout << " MAX number of add threads: " << maxth << " ";

                auto start1 = std::chrono::high_resolution_clock::now();
                std::vector<cd> b1 = MT_FFT::fft(a, maxth);
                auto end1 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> ms_result1 = end1 - start1;
                std::cout << "Time multithread : " << ms_result1.count()<<" ms    ||||  Increase in speed: x" <<ms_result/ms_result1 <<std::endl;

                std::this_thread::sleep_for(std::chrono::milliseconds(1));

                CHECK(b == b1);
            }
        }
    
}
