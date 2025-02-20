/*
* consteval
* Also called immediate function
* specifies that a function is an immediate function;
* i.e. every call to the function must produce a compile-time constant
*/
#include <iostream>

consteval int square(int a)
{
	return a * a;
}

int main()
{
	square(10); // ok, as 10 is a literal
	
	const int MY_VALUE = 1;
	square(MY_VALUE); // ok, as MY_VALUE is a const, which can be evaluate during compile-time

	int my_other_value = 0;
	//square(my_other_value); // not ok. my_other_value cannot be evaluated during compile-time
}