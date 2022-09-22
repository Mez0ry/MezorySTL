#include <iostream>
#include "vector.h"
 
int main() {
	mezstd::vector<int> vec;
	int lval = 1;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
 
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec.at(i) << '\n';
	}
 
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << '\n';
	}
	std::cin.get();
	return 0;
}

//#include <iostream>
//#include <vector>
//
//int main()
//{
//    using namespace std;
//
//    vector<int> normal;
//    cout << normal.capacity() << endl;
//
//    for (unsigned int loop = 0; loop != 10; ++loop)
//    {
//        normal.push_back(1);
//        cout << normal.capacity() << endl;
//    }
//
//    cin.get();
//    return 0;
//}