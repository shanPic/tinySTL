//
// Created by shanPic on 2020/3/15.
//

#include "RB_tree.h"
#include "function.h"
#include <iostream>
#include "gtest/gtest.h"
using namespace tinystl;

TEST(map-test-case-1, map-test) {
    EXPECT_EQ(1, 1);
}

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