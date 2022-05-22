#include <iostream>
#include "MyVector.h"

template <typename T>
void Print(const vector<T>& v) {
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << std::endl;
	std::cout << "--------------------" << std::endl;
}
int main() {
	vector<std::string> v;
	v.push_back("M");
	v.push_back("V");
	v.pop_back();
	v.emplace_back("E");
	v.emplace_back("B");
	Print(v);
	vector<std::string> y(v);
	Print(y);
	vector<std::string> w;
	w = v;
	Print(w);
	v.at(0) = "C";
	Print(v);
	std::cout << v.front() << std::endl;
	std::cout << v.back() << std::endl;
	std::cout << v.capacity() << std::endl;
	v.shrink_to_fit();
	std::cout << v.capacity() << std::endl;
	v.reserve(10);
	std::cout << v.capacity() << std::endl;
	std::cout << v.max_size() << std::endl;
	v.resize(5);
	Print(v);
	v.resize(3);
	v.resize(5, "A");
	Print(v);
	v.swap(w);
	Print(v);
	Print(w);
	v.assign(3, "B");
	Print(v);
	vector<std::string> x{ "A", "B", "C" };
	Print(x);
	vector<std::string> z{ 2, "A" };
	Print(z);
	vector<std::string> p;
	p = { "D", "F" };
	Print(p);
	std::cout << p.begin() << std::endl;
	std::cout << p.end() << std::endl;
	for (auto elem : p)
		std::cout << elem << std::endl;

	for (vector<std::string>::iterator it = p.begin(); it != p.end(); it++)
		std::cout << *it << std::endl;
	x.push_back("D");
	x.push_back("E");
	x.push_back("F");
	x.push_back("G");
	std::cout << "--------------------" << std::endl;
	Print(x);
	x.erase(x.begin()+2);
	Print(x);
	x.erase(x.begin(), x.begin()+3);
	Print(x);
	return 0;
};