#include <iostream>
#include "MyVector.h"

template <typename T>
void Print(const Vector<T>& v) {
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << std::endl;
}
int main() {
	Vector<std::string> v;
	v.push_back("M");
	v.push_back("V");
	Print(v);
	return 0;
};