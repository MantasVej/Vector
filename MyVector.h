#pragma once

template <typename T> 
class vector {

public:

	std::allocator<T> alloc;
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef size_t size_type;
	typedef T value_type;

	//Member functions

	vector() { create(); }

	explicit vector(size_t n, const T& t = T{}) { create(n, t); }

	vector(const vector& v) { create(v.begin(), v.end()); }

	vector(const std::initializer_list<T> il) {	create(il.begin(), il.end()); }

	~vector() { uncreate(); }

	vector& operator=(const vector& other) {
		if (&other != this) {
			uncreate();
			create(other.begin(), other.end());
		}
		return *this;
	}

	vector& operator=(std::initializer_list<T> il) {
		create(il.begin(), il.end());
		return *this;
	}

	void assign(size_t n, const T& t = T{}) {
		uncreate();
		create(n, t);
	}

	template< class InputIt >
	void assign(InputIt first, InputIt last) {
		uncreate();
		create(first, last);
	}
	void assign(std::initializer_list<T> il) {
		uncreate();
		create(il.begin(), il.end());
	}

	//Element access

	T& at(int index)
	{
		if (index < 0 || size() <= index) throw std::out_of_range("index out of range");
		return values[index];
	}
	const T& at(int index) const
	{
		if (index < 0 || size() <= index) throw std::out_of_range("index out of range");
		return values[index];
	}

	T& operator[](size_t index) { return values[index]; }
	const T& operator[](size_t index) const { return values[index]; }

	T& front() { return values[0]; }
	const T& front() const { return values[0]; }

	T& back() { return values[size() - 1]; }
	const T& back() const { return values[size() - 1]; }

	T* data() { return values; }
	const T* data() const { return values; }

	//Capacity

	bool empty() const { return size() == 0; }

	size_t size() const { return avail - values; }
	size_t max_size() const { return std::numeric_limits<size_t>::max() / sizeof(T); }

	void reserve(size_t new_limit)
	{
		if (new_limit > capacity()) {
			iterator new_values = alloc.allocate(new_limit);
			iterator new_avail = std::uninitialized_copy(values, avail, new_values);
			uncreate();
			values = new_values;
			avail = new_avail;
			limit = values + new_limit;
		}
	}

	void shrink_to_fit()
	{
		iterator new_values = alloc.allocate(avail - values);
		iterator new_avail = uninitialized_copy(values, avail, new_values);
		uncreate();
		values = new_values;
		avail = new_avail;
		limit = avail;
	}

	size_t capacity() const { return limit - values; }

	//Iterators

	iterator begin() { return values; }
	const_iterator begin() const { return values; }
	const_iterator cbegin() const { return values; }

	iterator end() { return avail; }
	const_iterator end() const { return avail; }
	const_iterator cend() const { return avail; }

	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator crbegin() const { return reverse_iterator(end()); }

	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator crend() const { return reverse_iterator(begin()); }

	//Modifiers

	void clear() {
		uncreate();
	}

	void insert(const iterator pos, const T& value){
		int index = pos - values;
		if (index < 0 || size() < index) throw std::out_of_range("index out of range");

		if (avail == limit)
			grow();

		for (int i = size() - 1; i >= index; --i)
			values[i + 1] = std::move(values[i]);

		values[index] = value;
		avail++;
	}

	iterator insert(const_iterator pos, size_type count, const T& value) {
		int index = pos - values;
		if (index < 0 || size() < index) throw std::out_of_range("index out of range");

		resize(size() + count);

		for (int i = size() - 1; i >= index + count; i--)
			values[i] = std::move(values[i-count]);

		for (int i = index + count - 1; i >= index; i--)
			values[i] = value;
		return &values[index];
	}

	template< class InputIt >
	iterator insert(const_iterator pos, InputIt first, InputIt last) {
		int index = pos - values;
		if (index < 0 || size() < index) throw std::out_of_range("index out of range");

		int sz = last - first;
		resize(size() + sz);

		for (int i = size() - 1; i >= index + sz ; --i)
			values[i] = std::move(values[i - sz]);

		int count = 0;
		for (int i = index + sz - 1; i >= index; --i) {
			values[i] = first[count++];
		}
		return &values[index];
	}

	iterator insert(const_iterator pos, std::initializer_list<T> il) {
		int index = pos - values;
		if (index < 0 || size() < index) throw std::out_of_range("index out of range");

		int sz = il.size();
		resize(size() + sz);

		for (int i = size() - 1; i >= index + sz; --i)
			values[i] = std::move(values[i - sz]);

		int count = sz-1;
		for (int i = index + sz - 1; i >= index; --i) {
			values[i] = il.begin()[count--];
		}
		return &values[index];
	}

	iterator erase(const iterator pos) {
		std::move(pos + 1, end(), pos);
		resize(size() - 1);
		return pos;
	}

	iterator erase(iterator first, iterator last) {
		const size_t n = last - first;
		iterator iter = &values[first - values];
		std::move(last, end(), first);
		resize(size() - n);
		return iter;
	}

	void push_back(const T& value) {
		if (avail == limit)
			grow();
		alloc.construct(avail++, value);
	}

	void push_back(const T&& value) {

		if (avail == limit)
			grow();
		alloc.construct(avail++, value);
	}

	template<typename... Args>

	iterator emplace(const_iterator pos, Args&&... args) {
		int index = pos - values;
		if (index < 0 || size() < index) throw std::out_of_range("index out of range");

		if (avail == limit)
			grow();

		alloc.construct(avail++, std::forward<Args>(args)...);

		for (int i = size() - 1; i >= index+1; --i) 
			std::swap(values[i], values[i-1]);
			
		return &values[index];
	}

	template<typename... Args>

	T& emplace_back(Args&&... args) {
		if (avail == limit)
			grow();
		alloc.construct(avail++, std::forward<Args>(args)...);
		return values[size()];
	}

	void pop_back() {
		if (size() > 0)
			alloc.destroy(--avail);
	}

	void resize(size_t new_Size)
	{
		size_t vector_size = size();
		if (new_Size > size()) {
			iterator new_values = alloc.allocate(new_Size);
			iterator new_avail = std::uninitialized_copy(values, avail, new_values);
			uncreate();
			values = new_values;
			avail = limit = values + new_Size;
			std::uninitialized_fill(new_avail, limit, T{});
		}
		else for (size_t i = new_Size; i < vector_size; i++)
			alloc.destroy(--avail);
	}
	void resize(size_t new_Size, const T& value)
	{
		size_t vector_size = size();
		if (new_Size > size()) {
			iterator new_values = alloc.allocate(new_Size);
			iterator new_avail = std::uninitialized_copy(values, avail, new_values);
			uncreate();
			values = new_values;
			avail = limit = values + new_Size;
			std::uninitialized_fill(new_avail, limit, value);
			avail = limit;
		}
		else for (size_t i = new_Size; i < vector_size; i++)
			alloc.destroy(--avail);
	}

	void swap(vector& other)
	{
		using std::swap;

		swap(values, other.values);
		swap(avail, other.avail);
		swap(limit, other.limit);
	}

	friend bool operator==(const vector& lhs, const vector& rhs) {
		if (lhs.size() != rhs.size())
			return false;

		for (int i = 0; i < lhs.size(); ++i)
			if (lhs.values[i] != rhs.values[i])
				return false;

		return true;
	}

	friend bool operator!=(const vector& lhs, const vector& rhs) {
		return !(lhs == rhs);
	}


private:

	void create() {
		values = avail = limit = nullptr;
	}
	void create(size_t n, const T& val) {
		values = alloc.allocate(n);
		limit = avail = values + n;
		std::uninitialized_fill(values, limit, val);
	}
	
	void create(const_iterator i, const_iterator j) {
		values = alloc.allocate(j - i);
		limit = avail = std::uninitialized_copy(i, j, values);
	}
	void uncreate() {
		if (values) {
			iterator it = avail;
			while (it != values)
				alloc.destroy(--it);
			alloc.deallocate(values, limit - values);
		}
		values = limit = avail = nullptr;
	}
	void grow() {
		size_t new_size = std::max(2 * (limit - values), ptrdiff_t(1));
		iterator new_values = alloc.allocate(new_size);
		iterator new_avail = std::uninitialized_copy(values, avail, new_values);
		uncreate();
		values = new_values;
		avail = new_avail;
		limit = values + new_size;
	}

private:
	
	iterator values;
	iterator avail;
	iterator limit;
};
