#include <iostream>

# include "mod2.h"
# include "mod4.h"

int main (void)
{
	std::cout << "\n I am mod-5\nI'am Calling fun2 of libmod2.so (Shared/Dynamic Library).\n\n";
	fun2();

	std::cout << "\n\n I am mod-5\nI'am Calling f4 of libmod4.a (Static Library).\n\n";
	f4();

	return (0);
}

