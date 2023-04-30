//#pragma once
//#include <vector>
//#include <thread>
//#include <queue>
//#include <mutex>
//#include <condition_variable>
//#include <future>
//
//
//// Define a structure to hold the task data
//template<typename Complex>
//struct TaskData {
//    std::vector<Complex>& coefs;
//    std::vector<Complex>& output;
//    int n;
//
//    TaskData(std::vector<Complex>& _coefs, std::vector<Complex>& _output, int _n)
//        : coefs(_coefs), output(_output), n(_n)
//    {}
//};
//
//
//
//
//// Define a thread pool class
//class ThreadPool {
//public:
//    ThreadPool(int n_threads)
//        : stop(false)
//    {
//        // Create the specified number of worker threads
//        for (int i = 0; i < n_threads; i++) {
//            workers.emplace_back([this]() {
//                while (true) {
//                    std::function<void()> task;
//                    {
//                        std::unique_lock<std::mutex> lock(queue_mutex);
//                        condition.wait(lock, [this]() { return stop || !tasks.empty(); });
//                        if (stop && tasks.empty()) return;
//                        task = std::move(tasks.front());
//                        tasks.pop();
//                    }
//                    task();
//                }
//                });
//        }
//    }
//
//    // Add a new task to the queue
//    template<class F, class... Args>
//    auto enqueue(F&& f, Args&&... args)
//        -> std::future<typename std::result_of<F(Args...)>::type>
//    {
//        using return_type = typename std::result_of<F(Args...)>::type;
//
//        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
//
//        std::future<return_type> res = task->get_future();
//        {
//            std::unique_lock<std::mutex> lock(queue_mutex);
//
//            // don't allow enqueueing after stopping the pool
//            if (stop)
//                throw std::runtime_error("enqueue on stopped ThreadPool");
//
//            tasks.emplace([task]() { (*task)(); });
//        }
//        condition.notify_one();
//        return res;
//    }
//
//    // Stop the thread pool and wait for all tasks to complete
//    ~ThreadPool() {
//        {
//            std::unique_lock<std::mutex> lock(queue_mutex);
//            stop = true;
//        }
//        condition.notify_all();
//        for (std::thread& worker : workers) {
//            worker.join();
//        }
//    }
//
//private:
//    std::vector<std::thread> workers;
//    std::queue<std::function<void()>> tasks;
//    std::mutex queue_mutex;
//    std::condition_variable condition;
//    bool stop;
//};
//
//// Define a thread pool with a maximum number of threads
//static ThreadPool thread_pool(std::thread::hardware_concurrency() /* maximum number of threads */);
//
//// Define a function to compute the FFT of a sub-vector
//template<typename Complex>
//void fft_worker(TaskData<Complex>& data) {
//
//    int n = data.n;
//
//    if (n == 1) {
//        data.output.resize(1);
//        data.output[0] = data.coefs[0];
//        return;
//    }
//
//    std::vector<Complex> w(n);
//
//    for (int i = 0; i < n; i++) {
//        double alpha = -2 * PI * i / n;
//        w[i] = Complex(cos(alpha), sin(alpha));
//    }
//
//    std::vector<Complex> A0(n / 2), A1(n / 2);
//
//    for (int i = 0; i < n / 2; i++) {
//        A0[i] = data.coefs[i * 2];
//        A1[i] = data.coefs[i * 2 + 1];
//    }
//
//    // Create tasks for even and odd indexed coefficients
//    std::vector<Complex> y0, y1;
//    TaskData task0(A0, y0, n / 2);
//    TaskData task1(A1, y1, n / 2);
//
//    // Enqueue the tasks on the thread pool
//    auto future0 = thread_pool.enqueue(&fft_worker<Complex>, std::ref(task0));
//    auto future1 = thread_pool.enqueue(&fft_worker<Complex>, std::ref(task1));
//
//    // Wait for the tasks to complete and retrieve the results
//    future0.wait();
//    future1.wait();
//    y0 = future0.get();
//    y1 = future1.get();
//
//    // Combine the results
//    data.output.resize(n);
//    for (int k = 0; k < n / 2; k++) {
//        data.output[k] = y0[k] + w[k] * y1[k];
//        data.output[k + n / 2] = y0[k] - w[k] * y1[k];
//    }
//}
//
//
//
//// Define the main FFT function
//template<typename Complex>
//std::vector<Complex> fft(std::vector<Complex>& coefs) {
//
//    int n = coefs.size();
//
//    std::vector<Complex> output(n);
//
//    TaskData<Complex> task(coefs, output, n);
//
//    fft_worker<Complex>(task);
//
//    return output;
//}
//
//
