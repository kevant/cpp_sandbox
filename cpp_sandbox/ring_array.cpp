/*
* An example implementation of ring array/ring buffer array
*/

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <format>

class ring_array
{
	std::array<int, 5> _inner_array{};
	size_t _limit = 5;
	size_t _size = 0;
	int _push_index = 0;
	int _pop_index = 0;

public:

	bool insert(int val)
	{
		if (_size == _limit)
		{
			std::cout << "Array full!\n";
			return false;
		}
		else
		{
			std::cout << std::format("Insert value {} to index {}\n", val, _push_index);
			++_size;
			_inner_array[_push_index++] = val;
			if (_push_index > 4)
			{
				_push_index = 0;
			}

			return true;
		}
	}

	int pop()
	{
		if (_size > 0)
		{
			int result = _inner_array[_pop_index++];
			if (_pop_index > 4)
			{
				_pop_index = 0;
			}
			--_size;

			return result;
		}

		return -1;
	}

	void print()
	{
		for (auto i : _inner_array)
		{
			std::cout << i;
		}
		std::cout << std::endl;
	}
};

int main()
{
	ring_array ra;

	ra.insert(1);
	ra.insert(2);
	ra.insert(3);
	ra.insert(4);
	ra.insert(5);
	ra.insert(6);
	std::cout << "Pop value " << ra.pop() << '\n';
	ra.insert(7);
	std::cout << "Pop value " << ra.pop() << '\n';
	std::cout << "Pop value " << ra.pop() << '\n';
	ra.insert(8);

	ra.print();
}