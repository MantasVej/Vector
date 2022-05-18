#pragma once

template <typename T> 
class vector {

public:
	vector() {
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

		std::cout << "alloc" << std::endl;

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
	T* v_data = nullptr;
	size_t v_size = 0;
	size_t v_capacity = 0;
};