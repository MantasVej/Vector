#pragma once

template <typename T> 
class vector {

public:
	vector() : v_data(nullptr), v_size(0), v_capacity(0) {
		ReAlloc(2);
	}
	~vector() {
		delete[] v_data;
	}
	void push_back(const T& value) {
		if (v_size >= v_capacity)
			ReAlloc(2 * v_capacity);

		v_data[v_size] = value;
		v_size++;
	}
	void push_back(const T&& value) {
		if (v_size >= v_capacity)
			ReAlloc(2 * v_capacity);

		v_data[v_size] = std::move(value);
		v_size++;
	}
	void pop_back() {
		if (v_size > 0) {
			v_size--;
			v_data[v_size].~T();
		}
	}
	void clear() {
		for (size_t i = 0; i < v_size; i++)
			v_data[i].~T();
		v_size = 0;
	}
	template<typename... Args>
	T& emplace_back(Args&&... args) {
		if (v_size >= v_capacity)
			ReAlloc(2 * v_capacity);
		new(&v_data[v_size]) T(std::forward<Args>(args)...);
		return v_data[v_size++];
	}
	vector(const vector& other){

		T* newBlock = new T[other.v_size];

		for (size_t i = 0; i < other.v_size; i++)
			newBlock[i] = other.v_data[i];

		v_data = newBlock;
		v_size = other.v_size;
		v_capacity = other.v_capacity;
	}
	vector& operator=(const vector& other) {
		if (this == &other)
			return *this;

		T* newBlock = new T[other.v_size];

		for (size_t i = 0; i < other.v_size; i++)
			newBlock[i] = other.v_data[i];

		delete[] v_data;
		v_data = newBlock;
		v_size = other.v_size;
		v_capacity = other.v_capacity;
		return *this;
	}
	T& operator[](size_t index) { 
		if (index >= size) {
			//klaida
		};
		return v_data[index]; 
	}
	const T& operator[](size_t index) const { 
		if (index >= v_size) {
			//klaida
		};
		return v_data[index]; 
	}
	size_t size() const{ return v_size; }
private:
	void ReAlloc(size_t newCapacity) {

		T* newBlock = new T[newCapacity];

		if (newCapacity < v_size) {
			v_size = newCapacity;
		}

		for (size_t i = 0; i < v_size; i++)
			newBlock[i] = std::move (v_data[i]);

		delete[] v_data;
		v_data = newBlock;
		v_capacity = newCapacity;
	}
private:
	T* v_data;
	size_t v_size;
	size_t v_capacity;
};