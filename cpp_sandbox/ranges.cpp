#include <iostream>
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>
#include <functional>

int main()
{
	// simple example
	{
		std::vector<int> numbers{ 1,2,3,4,5 };
		auto is_even = [](int i)->bool {return i % 2 == 0; };
		auto square = [](int i)->int {return i * i; };
		// composing syntax		
		for (int i : std::views::transform(std::views::filter(numbers, is_even), square))
			std::cout << i << ' ';
		std::cout << '\n';

		// "pipe" composing syntax
		using namespace std::views;
		for(int i : numbers | std::views::filter(is_even) | std::views::transform(square))
			std::cout << i << ' ';
		std::cout << '\n';
		auto print = [](int i) {std::cout << i << ' '; };
		std::ranges::for_each(
			numbers
			| filter(is_even)
			| transform(square)
			, print);
		std::cout << '\n';
	}

	std::cout << "===========================\n";

	// a more relevant example: string sanitization for username/password
	// functions are simplied 
	{
		std::string us_string = " %#Hello&* "; // unsanitized text
		std::string s_string; // sanitized text

		auto non_white_space = [](unsigned char c) -> bool { return c != ' '; };
		auto alpha_numeric = [](unsigned char c) -> bool 
		{
			if ((c >= 48 && c <= 57) || // digits
				(c >= 65 && c <= 90) || // uppercase
				(c >= 97 && c <= 122)) // lowercase
				return true;
			else
				return false;
		};

		auto encrypt_rot13 = [](const char x, const char a)->char
		{
			return ((x - a + 13) % 26) + a;
		};

		auto encrypt = [&encrypt_rot13](const char x)->char
		{
			if (x >= 'A' && x <= 'Z')
				return encrypt_rot13(x, 'A');
			else if (x >= 'a' && x <= 'z')
				return encrypt_rot13(x, 'a');
			else
				return x;
		};

		using namespace std::views;
		std::ranges::copy(
			us_string
			| filter(non_white_space)
			| filter(alpha_numeric)
			| transform(encrypt)
			, std::back_inserter(s_string));
		std::cout << "before:\'" << us_string << "\'\n";
		std::cout << " after:\'" << s_string << "\'\n"; // prints "Uryyb"
	}
}