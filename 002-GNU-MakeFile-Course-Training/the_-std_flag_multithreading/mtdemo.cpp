#include <future>
#include <iostream>

void f()
{
	std::cout << "Multi Threading - Demo - Async\n";
}

int main()
{
	auto fut = std::async(std::launch::deferred, f);
	fut.wait();

	return 0;
}
