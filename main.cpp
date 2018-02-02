#include <iostream>
#include "vector.h"
using namespace tinystl;
int main() {

    vector<int> vec(3,3);
    for(vector<int>::iterator ite = vec.begin(); ite != vec.end(); ite++) {
        std::cout << *ite << std::endl;
    }
    return 0;
}