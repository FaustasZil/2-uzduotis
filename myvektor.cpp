#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>

template <class T>
class myVector {
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;

	myVector() { create(); }
	explicit myVector(size_type n, const T& val = T{}) { create(n, val); }
private:
	iterator data;
	iterator limit;
};