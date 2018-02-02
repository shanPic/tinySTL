//
// Created by shanPic on 2018/2/2.
//

#ifndef TINYSTL_VECTOR_H
#define TINYSTL_VECTOR_H

#include "alloc.h"
#include <stddef.h>

namespace tinystl {

    //类型alloc默认为第一级空间配置器

    template <typename T, typename Alloc = malloc_alloc>
    class vector {
    public:
        //一些型别定义
        using value_type        = T;
        using pointer           = T*;
        using iterator          = T*;     //原生指针即可
        using reference         = T&;
        using difference_type   = ptrdiff_t;
        using size_type         = size_t;
    protected:
        iterator first;         //指向第一个可用元素
        iterator last;          //最后一个可用元素的下一个位置
        iterator end_of_storage;//存储空间的最后一个位置的下一个位置
    public:

        //迭代器
        iterator begin() { return first; }
        iterator end() { return last; }

        //容量
        size_type size() { static_cast<size_type>(last - first); }
        size_type capacity() { return static_cast<size_type>(end_of_storage - first); }
        bool emopty() { return first == last ? true : false ;}

        //访问元素
        reference at(size_type loc);  //TODO 判断是否越界，若越界，抛出一个异常
        reference operator[] (size_type loc) { return at(loc); } //不同于sgi实现，此时进行了越界检查

        //修改
        void clear() noexcept; //TODO
        iterator insert( iterator pos, const T& value ); //TODO
        iterator erase( iterator pos ); //TODO
        void push_back( const T& value ); //TODO
        void swap( vector& other ); //TODO

    };
}
#endif //TINYSTL_VECTOR_H
