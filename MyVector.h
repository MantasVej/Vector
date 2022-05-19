#pragma once

template <typename T> 
class vector {

public:

	//Member functions

	vector() : v_data(nullptr), v_size(0), v_capacity(0) {
		ReAlloc(2);
	}

	vector(size_t size, const T& value) {
		ReAlloc(size);
		v_size = size;
		std::fill_n(v_data, v_size, value); 
	}

	vector(const std::initializer_list<T> il) {
		ReAlloc(il.size());
		v_size = il.size();
		std::copy(il.begin(), il.end(), v_data);
	}

	vector(const vector& other) {

		T* newBlock = new T[other.v_size];

		for (size_t i = 0; i < other.v_size; i++)
			newBlock[i] = other.v_data[i];

		v_data = newBlock;
		v_size = other.v_size;
		v_capacity = other.v_capacity;
	}

	~vector() {
		delete[] v_data;
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
	vector& operator=(std::initializer_list<T> il) {
		ReAlloc(il.size());
		v_size = il.size();
		std::copy(il.begin(), il.end(), v_data);
		return *this;
	}

	void assign(size_t newCapacity, const T& value) {

		ReAlloc(newCapacity);

		for (int i = 0; i < newCapacity; i++)
			v_data[i] = value;

		v_size = newCapacity;
	}

	//Element access

	T& at(int index)
	{
		if (index < 0 || v_size <= index) throw std::out_of_range("index out of range");
		return v_data[index];
	}
	const T& at(int index) const
	{
		if (index < 0 || v_size <= index) throw std::out_of_range("index out of range");
		return v_data[index];
	}

	T& operator[](size_t index) { return v_data[index]; }
	const T& operator[](size_t index) const { return v_data[index]; }

	T& front() { return v_data[0]; }
	const T& front() const { return v_data[0]; }

	T& back() { return v_data[v_size - 1]; }
	const T& back() const { return v_data[v_size - 1]; }

	T* data() { return v_data; }
	const T* data() const { return v_data; }

	//Capacity

	bool empty() const { return v_size == 0; }

	size_t size() const { return v_size; }
	size_t max_size() const { return std::numeric_limits<size_t>::max() / sizeof(T); }

	void reserve(size_t newCapacity)
	{
		if (newCapacity > v_capacity)
			ReAlloc(newCapacity);
	}

	void shrink_to_fit()
	{
		ReAlloc(v_size);
	}

	size_t capacity() const { return v_capacity; }

	//Modifiers

	void clear() {
		for (size_t i = 0; i < v_size; i++)
			v_data[i].~T();
		v_size = 0;
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

	template<typename... Args>
	T& emplace_back(Args&&... args) {
		if (v_size >= v_capacity)
			ReAlloc(2 * v_capacity);
		new(&v_data[v_size]) T(std::forward<Args>(args)...);
		return v_data[v_size++];
	}

	void pop_back() {
		if (v_size > 0) {
			v_size--;
			v_data[v_size].~T();
		}
	}
	void resize(size_t newCapacity)
	{
		ReAlloc(v_capacity);
		v_size = newCapacity;
	}

	void resize(size_t newCapacity, const T& value)
	{

		ReAlloc(newCapacity);

		if (newCapacity > v_size)
		{
			for (int i = v_size; i < newCapacity; i++)
				v_data[i] = value;
		}

		v_size = newCapacity;
	}

	void swap(vector& other)
	{
		using std::swap;

		swap(v_size, other.v_size);
		swap(v_capacity, other.v_capacity);
		swap(v_data, other.v_data);
	}

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