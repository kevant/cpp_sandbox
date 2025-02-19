/*
* span: non-owning view of contiguous memory
*
* Has support for STL containers and C arrays
* Can manage buffers size through the compiler, instead of code
* Recommended for usage in CppCoreGuidelines https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md
*/
#include <iostream>
#include <span>
#include <vector>
#include <array>

void print_numbers_span(std::span<int> numbers)
{
	for (auto const& i : numbers)
		std::cout << i;
	std::cout << std::endl;
}

void print_numbers_C(int* numbers, size_t bufferSize)
{
	for (size_t i = 0; i < bufferSize; ++i)
		std::cout << numbers[i];
	std::cout << std::endl;
}

int main()
{
	const size_t BUFFER_SIZE = 5;
	int numbers[BUFFER_SIZE] = { 1, 2, 3, 4, 5 };
	print_numbers_C(numbers, BUFFER_SIZE);

	// buffer size not needed
	// less error prone to out-of-range errors
	print_numbers_span(numbers);

	// Can pass in count for span
	print_numbers_span({ numbers, 2 }); // print 12
	print_numbers_span({ numbers, 6 }); // print 12345, with an uninitialized value for index 5

	// Support for STL containers
	std::vector<int> vec{ 1, 2, 3, 4, 5 };
	print_numbers_span(vec);
	std::array<int, 5> arr{ 1, 2, 3, 4, 5 };
	print_numbers_span(arr);
}