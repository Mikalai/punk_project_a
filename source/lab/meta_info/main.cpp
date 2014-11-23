//#include "test_class.h"
//
//int main() {
//	TestClass c;
//	c.GetType()->Invoke(&c, "Method");
//	c.GetType()->Invoke(&c, "Method2", 10);
//	int k = 0;	
//	c.GetType()->Invoke<int&>(&c, "Method3", k);
//	std::cout << "k = " << k << std::endl;
//
//	k = 0;
//	c.GetType()->Invoke(&c, "Method4", &k);
//	std::cout << "k = " << k << std::endl;
//}

#include <iostream>

void print(int* k) {
	std::cout << *k << std::endl;
}

template<class T, void(*F)(T*)>
struct S{
	int k = 10;
	void run() {
		F(&k);
	}
};

int main() {
	S<int, print> s;
	s.run();
}