#include <iostream>
#include "construct.h"
int main() {

    int *ptr = new int(1);
    tinystl::construct(ptr, sizeof(int));
    tinystl::destroy(ptr);
    return 0;
}