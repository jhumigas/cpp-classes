#pragma once

#include <iostream>
#include <iomanip>
#include <type_traits>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <thread>

using namespace std::literals;

class Chrono {
	using my_clock = std::chrono::high_resolution_clock;
	my_clock::duration duree;

public:

	Chrono() : duree{} {}

	template<typename Callable, typename... Args> 
	typename std::enable_if<
		std::is_void<
			typename std::result_of<Callable(Args...)>::type
		>::value,
		void
	>::type
	operator() (const Callable& f, Args... args){
		auto depart = my_clock::now();
		f(args...);
		auto arrivee = my_clock::now();
		duree += (arrivee - depart);
	}

	template<typename Callable, typename... Args> 
	typename std::enable_if<
		! std::is_void<
			typename std::result_of<Callable(Args...)>::type
		>::value, 
		typename std::result_of<Callable(Args...)>::type
	>::type
	operator() (const Callable& f, Args... args) {
		auto depart = my_clock::now();
		auto res = f(args...);
		auto arrivee = my_clock::now();
		duree = (arrivee - depart);
		return res;
	}

	friend std::ostream& operator<<(std::ostream& os, const Chrono& chrono) {
		double ns = std::chrono::duration_cast<std::chrono::nanoseconds>(chrono.duree).count();
		os << std::setprecision(3);
		if(ns < 1.E3) os << ns << " ns";
		else if(ns < 1.E6) os << ns / 1.E3 << " us";
		else if(ns < 1.E9) os << ns / 1.E6 << " ms";
		else os << ns / 1.E9 << " s";
		return os;
	}
};