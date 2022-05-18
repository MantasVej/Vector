#include <iostream>
#include "MyVector.h"

template <typename T>
void Print(const vector<T>& v) {
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << std::endl;
}
int main() {
	vector<std::string> v;
	v.push_back("M");
	v.push_back("V");
	v.pop_back();
	v.emplace_back("E");
	v.emplace_back("B");
	Print(v);
	return 0;
};