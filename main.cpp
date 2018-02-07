#include <iostream>
#include "vector.h"
#include "deque.h"
using namespace tinystl;
int main() {
    int cnt = 0, value = 1;
    deque<int> test;
    test.push_back(3);
    test.push_back(4);
    cnt+=2;
    for( int i = 0; i < cnt; i++) {
        std::cout << test[i] << std::endl;
    }
    return 0;
}