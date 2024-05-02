/*
* [[deprecated]] Attribute
*
* [[deprecated]] attribute will show as error C4996  =/
* The flag for its warning is under "SDL checks"; i.e. /sdl or /sdl-,
* Not "Treat Warnings as error (/WX-)"
*
* To keep "/sdl" and set C4996 as warning, add the flag /w34996
* "w3" means to set error 4996 as warning level 3
*
* P.S. This project has added "/w34996" to its command line option
*
* The attribute is not always places on left side, so take note when writing it. Check CPP reference if needed
*/

#include <iostream>

[[deprecated]]
void oldFunc() {}

[[deprecated("Deprecated function. Please use NewFunc()")]]
void oldFunc2() {}

// for some declaration, [[deprecated]] attribute is infix
struct [[deprecated]] MyStruct {};
namespace [[deprecated]] MyNamespace { int x; }

int main()
{
	using namespace std;

	oldFunc();
	oldFunc2();
	MyStruct s;

	[[deprecated]] int x;

	MyNamespace::x = 0;

	return 0;
}