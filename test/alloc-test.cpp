//
// Created by shanPic on 2020/3/16.
//

#include "alloc.h"
#include "gtest/gtest.h"

TEST(AllocTest, AllocTestCase1) {
    auto ret = tinystl::simple_alloc<int, tinystl::alloc>::allocate(1024);
    ASSERT_NE(ret, nullptr);
}

TEST(AllocTest, AllocTestCase2) {

}