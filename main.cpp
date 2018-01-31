#include <iostream>
#include "construct.h"
int main() {

    int *ptr = new int(1);
    tinystl::construct(ptr, sizeof(int));
    tinystl::destory(ptr);
    return 0;
}