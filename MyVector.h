#pragma once

template <typename T> 
class Vector {

public:
	Vector() {
		ReAlloc(2);
	}
	void push_back(const T& value) {

		if (v_size >= v_capacity) {
			ReAlloc(2 * v_capacity);
		}

		v_data[v_size] = value;
		v_size++;
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
			newBlock[i] = v_data[i];

		delete[] v_data;
		v_data = newBlock;
		v_capacity = newCapacity;
	}
private:
	T* v_data = nullptr;
	size_t v_size = 0;
	size_t v_capacity = 0;
};