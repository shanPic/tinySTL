//
// Created by shanPic on 2020/3/15.
//

#include "RB_tree.h"
#include "function.h"
#include <iostream>
#include "gtest/gtest.h"
#include <map>
using namespace tinystl;

bool less_fun(int a, int b) {
    return a < b;
}

TEST(MapTestCase1, MapTest) {
    EXPECT_EQ(1, 1);
    rb_tree<int,int,identity<int>, std::less<int>> itree;
    itree.insert_unique(1);
    itree.insert_unique(2);
    itree.insert_unique(2);
    itree.insert_unique(3);

    rb_tree<int,int,identity<int>,std::less<int> >::iterator ite = itree.begin();

    for(;ite != itree.end(); ++ite){
        std::cout << *ite << std::endl;

    }
    EXPECT_EQ(*ite, 1);
    std::cout << *itree.find(2) << std::endl;
}
