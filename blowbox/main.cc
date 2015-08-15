#include <stdlib.h>
#include <iostream>

#include "../blowbox/memory/memory.h"
#include "../blowbox/memory/proxy_allocator.h"

#include <d3d12.h>

using namespace blowbox;

class Foo
{
public:
	Foo() {
		saved_ = 0;
	};
	~Foo() {};

	int add(int a, int b)
	{
		return a + b;
	}

	void save(int s)
	{
		saved_ = s;
	}
private:
	int saved_;
};

class Bar
{
public:
	Bar() {};
	~Bar() {};

	int add(int a, int b)
	{
		return a * b;
	}

	void save(int s)
	{
		saved_ = s;
	}
private:
	int saved_;
	long a;
	long b;
	long c;
	long d;
	long e;
};

int main(int argc, char** argv)
{
	Memory* memory = Memory::Instance();

	memory->StartUp(524288000);

	memory->Shutdown();

	delete memory;

	return 0;
}