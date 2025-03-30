#include <iostream>
# include "mod2.h"

int main()
{
	std::cout << "\nModule 3.\n\n";
	std::cout << "Calling & Linking into Dynamic Library (libmod2.so) and using its fun2(); ::\n";
	fun2();
	return (0);
}
