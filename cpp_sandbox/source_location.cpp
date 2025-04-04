#include <iostream>
#include <source_location>
#include <format>
#include <string>

void my_function(std::string caller, std::string file, std::string line)
{
	std::cout << std::format("{}() | {} [{}, line {}]",
		__func__,
		caller,
		file,
		line) << std::endl;
}

// use std::source_location::current() to get caller function location
void my_function(std::source_location caller = std::source_location::current())
{
	std::cout << std::format("{}() | {} [{}, line {}]\n",
		__func__, //std::source_location::current().function_name(),
		caller.function_name(),
		caller.file_name(), // caller.file_name(),
		caller.line());
}

void other_function()
{
	my_function();
}

int main()
{
	my_function();
	my_function(__func__, __FILE__, std::to_string(__LINE__));

	other_function();
}