/*
* Saw an interesting implementation that uses exception to handle flow control
* 
* Can only be used *safely* if there's guarantee that memory is handled properly
*/

#include <iostream>
#include <functional>
#include <array>

// create a custom struct for exception
struct MyException {};

class MyClass
{
	std::array<int, 5> _list{0,1,2,3,4};
public:
	void iterate(std::function<void(int)> callback)
	{
		for (auto i : _list)
		{
			callback(i);
		}
	}
};

int main()
{
	MyClass my_class;

	my_class.iterate([](int i) {
		std::cout << i;
	});
	std::cout << std::endl;

	try
	{
		my_class.iterate([](int i) {
			std::cout << i;
			if (i == 2)
			{
				throw MyException{};
			}
		});
	}
	catch (MyException)
	{
	}
}