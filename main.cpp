//#include <iostream>
//#include "vector.h"
//#include "deque.h"
//#include "RB_tree.h"
//using namespace tinystl;
//int main() {
//    int cnt = 0, value = 1;
//    deque<int> test;
//    test.push_back(3);
//    test.push_back(4);
//    cnt+=2;
//    for( int i = 0; i < cnt; i++) {
//        std::cout << test[i] << std::endl;
//    }
//    return 0;
//}
#include "D:\CodeAndProject\Cpp\tinySTL\RB_tree.h"
#include "D:\CodeAndProject\Cpp\tinySTL\function.h"
#include <iostream>
using namespace tinystl;

void fun_rb_tree_test(){
    rb_tree<int,int,identity<int>,std::less<int> > itree;
    itree.insert_unique(1);
    itree.insert_unique(2);
    itree.insert_unique(2);
    itree.insert_unique(3);

    rb_tree<int,int,identity<int>,std::less<int> >::iterator ite = itree.begin();

    for(;ite != itree.end(); ++ite){
        std::cout << *ite << std::endl;
    }
    std::cout << *itree.find(2) << std::endl;
}
int main(){
    fun_rb_tree_test();
}