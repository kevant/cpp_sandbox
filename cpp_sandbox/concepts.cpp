/*
* Concepts are compile time predicate that helps to constraint types
* This allows certain errors to be brought forward and raised during compilation,
* thus reducing the errors that may occur during runtime.
*
* It can make templates more readable, which may allow more complex templates to be used.
*/
#include <iostream>
#include <chrono>

/*
* A simple power function using postive integers
* Error of passing in wrong types can be raised during compile-time,
* Without using assert or additional checks during runtime
*/
template <typename T>
concept unsigned_integral = std::is_integral_v<T> && !std::signed_integral<T>;

template <typename T> requires unsigned_integral<T>
T simple_power(T a, T b)
{
	T result = 1;
	for (unsigned int i = 0; i < b; ++i)
	{
		result *= a;
	}
	return result;
}

/*
* Constraint to invocable; i.e. functions
*/ 
template <typename Fn> requires std::invocable<Fn>
void log_function(Fn fn)
{
	namespace ch = std::chrono;
	std::cout << "["
		<< std::format("{:%T}", ch::floor<ch::seconds>(ch::system_clock::now()))
		<< "] "
		<< typeid(Fn).name()
		<< " invoked\n";

	fn();
}

void print_statement()
{
	std::cout << "free function\n";
}

class my_class
{
public:
	void operator()()
	{
		std::cout << "function call overload\n";
	}
};

int main()
{
	{
		unsigned int a = 2, b = 4;

		std::cout << simple_power(a, b) << std::endl; // ok
		//std::cout << simple_power(a, -2) << std::endl; // error, as second argument is signed
		//std::cout << simple_power(1.0, 2.0) << std::endl; // error, as arguments are double
	}

	{
		log_function([] {std::cout << "lambda function\n"; });
		log_function(print_statement);
		log_function(my_class());
		//log_function(1); // error
	}
}