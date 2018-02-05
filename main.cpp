#include <iostream>
#include "vector.h"
using namespace tinystl;
int main() {

    vector<int> vec(1,4);
    //vec.push_back(4);
    vector<int>::iterator ite = vec.begin();
    //std::cout << vec.size() << std::endl;
    //vec.erase(vec.begin(),vec.begin()+2);
    vec.insert(ite,5);
     ite = vec.begin();
    vec.insert(ite,2,3);
    for(vector<int>::iterator ite = vec.begin(); ite != vec.end(); ite++) {
        std::cout << *ite << std::endl;
    }
    return 0;
}