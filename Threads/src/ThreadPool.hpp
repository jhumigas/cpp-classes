#pragma once

#include <iostream>

class ThreadPool {

	// ... A compléter ...

public:
    ThreadPool(size_t nThreads);
    ~ThreadPool();

	template<typename Func, typename... Args>
	ThreadPool& operator() (const Func& func, Args... args) {

		// ... A compléter ...

		return *this;
	}

	void join();
};