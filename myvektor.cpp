#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <memory>

template <class T>
class myVector {
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;

	myVector() { create(); }
	explicit myVector(size_type n, const T& val = T{}) { create(n, val); }

	size_type size() const { return avail - data; }
	T& operator[](size_type i) { return data[i]; }
	const T& operator[](size_type i) const { return data[i]; }

	iterator begin() { return data; }
	const_iterator begin() const { return data; } 
	iterator end() { return avail; } 
	const_iterator end() const { return avail; } 

	myVector(const myVector& v) { create(v.begin(), v.end()); }
	myVector& operator=(const myVector&);
	~myVector() { uncreate(); } 

	void push_back(const T& val) {
		if (avail == limit)
			grow();
		unchecked_append(val);
	}


private:
	iterator data;
	iterator avail;
	iterator limit;

	allocator<T> alloc;

	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);

	void uncreate();

	void grow();
	void unchecked_append(const T&);
};

template <class T>
myVector<T>& myVector<T>::operator=(const myVector& rhs) {
	if (&rhs != this) {
		uncreate();
		create(rhs.begin(), rhs.end());
	}
	return *this;
}

template <class T> 
void myVector<T>::create() {
	data = avail = limit = nullptr;
}
template <class T> 
void myVector<T>::create(size_type n, const T& val) {
	data = alloc.allocate(n); 
	limit = avail = data + n; 
	uninitialized_fill(data, limit, val); 
}
template <class T>
void myVector<T>::create(const_iterator i, const_iterator j) {
	data = alloc.allocate(j - i); 
	limit = avail = uninitialized_copy(i, j, data); 
}

template <class T> 
void myVector<T>::uncreate() {
	if (data) {
		iterator it = avail;
		while (it != data)
			alloc.destroy(--it);
		alloc.deallocate(data, limit - data);
	}
	data = limit = avail = nullptr;
}

template <class T> 
void myVector<T>::grow() {
	size_type new_size = max(2 * (limit - data), ptrdiff_t(1));
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = uninitialized_copy(data, avail, new_data);
	uncreate();
	data = new_data;
	avail = new_avail;
	limit = data + new_size;
}
template <class T> 
void myVector<T>::unchecked_append(const T& val) {
	alloc.construct(avail++, val);
}
