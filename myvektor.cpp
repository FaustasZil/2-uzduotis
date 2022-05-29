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
	myVector(const myVector& v) { create(v.begin(), v.end()); }

	iterator begin() { return data; }
	const_iterator begin() const { return data; } 
	iterator end() { return avail; } 
	const_iterator end() const { return avail; } 

	myVector& operator=(const myVector&);
	~myVector() { uncreate(); } 


	//element access

	T& at(int index) {
		if (index < 0 || size() <= index) throw std::out_of_range("Indeksas yra out of range");
		return data[index];
	}
	const T& at(int index) const {
		if (index < 0 || size() <= index) throw std::out_of_range("Indeksas yra out of range");
		return data[index];
	}

	T& operator[](size_type i) {
		if (i < 0 || size() <= i) throw std::out_of_range("Indeksas yra out of range");
		return data[i]; }
	const T& operator[](size_type i) const {
		if (i < 0 || size() <= i) throw std::out_of_range("Indeksas yra out of range");
		return data[i]; }

	T& front() { return data[0]; }
	const T& front() const { return data[0]; }

	T& back() { return data[size()-1]; }
	const T& back() const { return data[size()-1]; }

	T& value() { return data; }
	const T& value() const { return data; }

	//capacity

	bool is_empty() const { return size() == 0; }

	size_type size() const { return avail - data; }
	size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(T); }

	size_type capacity() const { return size() + limit-avail; }

	void reserve(size_t new_limit) {
		limit += new_limit;
	}
	void shrink_to_fit() {
		limit = avail;
	}

	//modifiers

	void push_back(const T& val) {
		if (avail == limit)
			grow();
		unchecked_append(val);
	}

	void clear() {
		avail = data;
	}

	void insert(int b, const T& val) {
		int i;
		for (i = size(); i > b; i--)
			data[i] = data[i - 1];
		data[i] = val;
		avail++;
	}

	void insert(int b, int n, const T& val) {
		for (int i = 0; i < n; i++)
			insert(b + i, val);
	}

	void insert(int b, const T val[]) {
		for (int i = 0; i < (sizeof(val) / sizeof(T))+1; i++)
			insert(b + i, val[i]);
	}

	void erase(int b) {
		for (int i = b; i < size(); ++i)
			data[i] = data[i + 1];
		avail--;
	}

	void erase(int from, int to) {
		for (int i = from; i < to; i++)
			erase(from);
	}

	void pop_back() {
		erase(size() - 1);
	}

	void resize(int b, const T& val) {
		int temp = size();
		if (size() < b) {
			for (int i = 0; i < b - temp; i++) {
				push_back(val);
			}
		}
		else if (size() > b) {
			for (int i = 0; i < temp - b; i++) {
				pop_back();
			}
		}
	}
private:
	iterator data;
	iterator avail;
	iterator limit;

	std::allocator<T> alloc;

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
	std::uninitialized_fill(data, limit, val); 
}
template <class T>
void myVector<T>::create(const_iterator i, const_iterator j) {
	data = alloc.allocate(j - i); 
	limit = avail = std::uninitialized_copy(i, j, data); 
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
	size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = std::uninitialized_copy(data, avail, new_data);
	uncreate();
	data = new_data;
	avail = new_avail;
	limit = data + new_size;
}
template <class T> 
void myVector<T>::unchecked_append(const T& val) {
	alloc.construct(avail++, val);
}
