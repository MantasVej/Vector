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
	return 0;
};