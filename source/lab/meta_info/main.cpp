#include "test_class.h"

int main() {
	TestClass c;
	c.GetType()->Invoke(&c, "Method");
	c.GetType()->Invoke(&c, "Method2", 10);
	int k = 0;	
	c.GetType()->Invoke<int&>(&c, "Method3", k);
	std::cout << "k = " << k << std::endl;

	k = 0;
	c.GetType()->Invoke(&c, "Method4", &k);
	std::cout << "k = " << k << std::endl;
}