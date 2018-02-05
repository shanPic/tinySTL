//
// Created by shanPic on 2018/2/4.
//

#ifndef TINYSTL_DEQUE_H
#define TINYSTL_DEQUE_H

#include "alloc.h"
#include "iterator.h"

namespace tinystl {

    template <typename T, typename Ref, typename Ptr, size_t BufSiz>
    struct __deque_iterator {
        //类型声明
        using iterator = __deque_iterator<T, T&, T*, BufSiz>;
        using const_iterator = __deque_iterator<T, const T&, const T*, BufSiz>;

        using iterator_category = random_access_iterator_tag;
        using value_type = T;
        using pointer = Ptr;
        using reference = Ref;
        using size_type = size_t;
        using difference_typr = ptrdiff_t;
        using map_pointer = T**;

        using self = __deque_iterator;


        //数据成员
        T* cur;
        T* first;
        T* last;
        map_pointer node;

        //成员函数
        static size_t buffer_size() { return __deque_buf_size(BufSiz, sizeof(T)); }
    };

    size_t __deque_buf_size(size_t BufSiz, size_t size) {
        //TODO
    }

    template <typename T, typename Alloc = alloc, size_t BufSiz =0>
    class deque {

        //类型声明
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using size_type = size_t;
        using difference_typr = ptrdiff_t;

        using iterator = __deque_iterator<T, T&, T*, BufSiz>;
    protected:
        using map_pointer = T**;

        //数据成员
    protected:
        iterator begin;
        iterator end;
        map_pointer map;
        size_type map_size;

        //成员函数
    public:


    };
}

#endif //TINYSTL_DEQUE_H
