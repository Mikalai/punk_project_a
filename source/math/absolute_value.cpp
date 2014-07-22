
template<class T, int D>
class A
{

};


template<class T, int D>
class B : public A < T, D > {

};

template<class T>
class B<T, 2> : public A < T, 2 > {

};

int f()
{
	B<float, 2> b;

	A<float, 2>& a = b;

	return 1;
}