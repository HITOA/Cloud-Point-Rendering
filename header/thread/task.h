#pragma once

#include <thread>
#include <optional>

namespace elm::thread {

	template<class R, class... Args>
	class Task {};

	template<class R>
	class Task<R> {
	public:
		Task() { this->function = nullptr; }
		Task(R(*function)()) { this->function = function; }
		R Wait() { 
			thread.join(); 
			return result.value();
		}
		std::optional<R> GetResult() { return result; }
		Task operator=(R(*function)()) const { return Task(function); }
		void operator()() { this->thread = std::thread(&Task<R>::Run, this); }
	private:
		void Run() { result = function(); }
	private:
		R(*function)();
		std::thread thread;
		std::optional<R> result;
	};

	template<class R, class Arg1>
	class Task<R, Arg1> {
	public:
		Task() { this->function = nullptr; }
		Task(R(*function)(Arg1)) { this->function = function; }
		R Wait() {
			thread.join();
			return result.value();
		}
		std::optional<R> GetResult() { return result; }
		Task operator=(R(*function)(Arg1)) const { return Task(function); }
		void operator()(Arg1 arg1) { this->thread = std::thread(&Task<R, Arg1>::Run, this, arg1); }
	private:
		void Run(Arg1 arg1) { result = function(arg1); }
	private:
		R(*function)(Arg1);
		std::thread thread;
		std::optional<R> result;
	};

	template<class R, class Arg1, class Arg2>
	class Task<R, Arg1, Arg2> {
	public:
		Task() { this->function = nullptr; }
		Task(R(*function)(Arg1, Arg2)) { this->function = function; }
		R Wait() {
			thread.join();
			return result.value();
		}
		std::optional<R> GetResult() { return result; }
		Task operator=(R(*function)(Arg1, Arg2)) const { return Task(function); }
		void operator()(Arg1 arg1, Arg2 arg2) { this->thread = std::thread(&Task<R, Arg1, Arg2>::Run, this, arg1, arg2); }
	private:
		void Run(Arg1 arg1, Arg2 arg2) { result = function(arg1, arg2); }
	private:
		R(*function)(Arg1, Arg2);
		std::thread thread;
		std::optional<R> result;
	};

}
