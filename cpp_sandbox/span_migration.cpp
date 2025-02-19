/*
* The following example is a method to gradually migrate functions that uses pointer(C array) to std::span
*/
#include <iostream>
#include <span>
#include <vector>
#include <array>

// Old Function
void print_numbers(int* numbers, size_t bufferSize)
{
	
	for (size_t i = 0; i < bufferSize; ++i)
		std::cout << numbers[i];
	std::cout << "(C style)\n";
}

// Migrated Function
// Migrated function has bufferSize parameter with default value, but it will not be used
// This allows support for older code, while newer code does not need to pass in buffer size argument
// Once all code is migrated or updated, bufferSize parameter can be safely removed
void print_numbers(std::span<int> numbers, size_t bufferSize = 0)
{
	for (auto const& i : numbers)
		std::cout << i;
	std::cout << "(span)\n";
}

int main()
{
	constexpr size_t BUFFER_SIZE = 5;
	{
		int numbers[BUFFER_SIZE] = { 1, 2, 3, 4, 5 };
		print_numbers(numbers, BUFFER_SIZE); // will invoke print_numbers(int*, size_t)
		print_numbers(numbers); // will invoke print_numbers(std::span<int>, size_t)
	}

	{
		std::vector<int> numbers{ 1, 2, 3, 4, 5 };
		print_numbers(numbers); // will invoke print_numbers(std::span<int>, size_t)
	}

	{
		std::array<int, BUFFER_SIZE> numbers{ 1, 2, 3, 4, 5 };
		print_numbers(numbers); // will invoke print_numbers(std::span<int>, size_t)
	}
}