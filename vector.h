//
// Created by shanPic on 2018/2/2.
//

#ifndef TINYSTL_VECTOR_H
#define TINYSTL_VECTOR_H

#include "alloc.h"
#include "uninitialized.h"
#include <stddef.h>
#include <stdexcept>

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
        using allocator = simple_alloc<value_type, Alloc> ;

    protected:
        iterator first;         //指向第一个可用元素
        iterator last;          //最后一个可用元素的下一个位置
        iterator end_of_storage;//存储空间的最后一个位置的下一个位置

        void copy_backward_overlay(iterator target,iterator first, iterator last) {
            if(target == nullptr || first == nullptr || last == nullptr) return;

            size_type sz = last - first;
            last--;
            for ( ; first != last; target--, last--) {
                destroy(target);
                construct(target, *last);
                //destroy(last);
            }
            destroy(target);
            construct(target, *first);

            for( ; first != target ; first++) {
                destroy(first);
            }
        }


    public:
        //构造与析构
        vector() : first(nullptr), last(nullptr), end_of_storage(nullptr){}
        vector(size_type sz, const value_type & value) { fill_initialized(sz, value); }
        ~vector() {
            destroy(first, last);
            if(first) allocator::deallocate(first, end_of_storage - first);
        }

        void fill_initialized(size_type sz, const value_type & value) {
            first = alloc_and_fill(sz, value);
            last = first + sz;
            end_of_storage = last;
        }

        iterator alloc_and_fill(size_type sz, const value_type & value) {
            iterator start = allocator::allocate(sz);
            uninitialized_fill_n(start, sz, value);
            return start;
        }

        //迭代器
        iterator begin() { return first; }
        iterator end() { return last; }

        //容量
        size_type size() { static_cast<size_type>(last - first); }
        size_type capacity() { return static_cast<size_type>(end_of_storage - first); }
        bool emopty() { return first == last; }

        //访问元素
        reference at(size_type loc);
        reference operator[] (size_type loc) { return at(loc); } //不同于sgi实现，此时进行了越界检查

        //修改
        void clear();
        iterator insert( iterator pos, const T& value ) { return insert_one_elem(pos,value); }
        iterator insert( iterator pos, size_type n, const T &value); //TODO
        iterator insert_one_elem( iterator pos, const T &value);
        iterator erase( iterator pos );
        iterator erase( iterator begin, iterator end);
        void push_back( const T& value );
        void swap( vector& other ); //TODO

    };

#define VEC_NAME typename vector<T,Alloc>
    template <typename T, typename Alloc>
    VEC_NAME::reference vector<T,Alloc>::at(VEC_NAME::size_type loc) {
        if(loc >= size()) {
            throw std::out_of_range("too big location");
        }
        else if (loc < 0) {
            throw std::out_of_range("too small location");
        }
        return *(first + loc);
    }

    template <typename T, typename Alloc>
    void vector<T,Alloc>::clear() {
        destroy(first, last);
        first = last = nullptr;
    }

    template <typename T, typename Alloc>
    void vector<T,Alloc>::push_back(const T &value) {
        if(last != end_of_storage) {
            construct(last, value);
            last++;
        }
        else {
            insert_one_elem(last, value);
        }
    };

    template <typename T, typename Alloc>
    VEC_NAME::iterator vector<T,Alloc>::insert_one_elem( VEC_NAME::iterator pos, const T &value) {
        if (last != end_of_storage) {
            construct(last, last + 1);
            copy_backward_overlay(last, pos, last);
            last++;
            construct(pos, value);
            return pos;
        }
        else {
            size_type old_sz = size();
            size_type new_cap = (old_sz == 0) ? 1 : 2 * capacity();

            iterator new_first = allocator::allocate(new_cap);

            iterator new_pos = uninitialized_copy(first, pos, new_first);
            iterator new_last = new_pos;
            construct(new_last, value);
            new_last++;
            new_last = uninitialized_copy(pos, last, new_last);

            destroy(first, last);
            if(first) allocator::deallocate(first, old_sz);

            first = new_first;
            last = new_last;
            end_of_storage = first + new_cap;

            return new_pos;

        }
    };

    template <typename T, typename Alloc>
    VEC_NAME::iterator vector<T,Alloc>::erase(VEC_NAME::iterator pos) {
        destroy(pos);
        iterator cur = pos + 1;
        if (cur != last){
            for( ; cur != last; cur++) {
                construct(cur - 1, *cur);
                destroy(cur);
            }
        }
        last--;
        destroy(last);
        return pos;
    }

    template <typename T, typename Alloc>
    VEC_NAME::iterator vector<T,Alloc>::erase(VEC_NAME:: iterator begin, VEC_NAME::iterator end) {
        iterator fill_cur = begin;
        iterator copy_cur = begin;

        for( ; copy_cur != end ; copy_cur++) {
            destroy(copy_cur);
        }

        for( ; copy_cur != last; copy_cur++, fill_cur++) {
            construct(fill_cur, *copy_cur);
            destroy(copy_cur);
        }

        last = fill_cur;
        return begin;
    };

    template <typename T, typename Alloc>
    VEC_NAME::iterator vector<T,Alloc>::insert( VEC_NAME::iterator pos, size_type n, const T &value) {
        size_type old_sz = size();
        size_type new_sz = old_sz + n;


        if(new_sz <= capacity()) {
            iterator copy_cur = last;
            iterator fill_cur = last + (n - 1);
            size_type n_cur = n;

            for ( ; n_cur > 0; n_cur--, copy_cur--, fill_cur--) {
                construct(fill_cur, *copy_cur);
            }
            copy_backward_overlay(last - 1, pos, copy_cur + 1);

            uninitialized_fill(pos, pos + n, value);

            last = last + n;
            return pos;
        }
        else {
            size_type new_cap = (old_sz == 0) ? 1 : 2 * capacity();
            while (new_sz < new_cap ) {
                new_cap = new_cap * 2;
            }

            iterator new_first = allocator::allocate(new_cap);
            iterator fill_cur_1 = uninitialized_copy(first, pos - 1, new_first);
            iterator fill_cur_2 = uninitialized_fill_n(fill_cur_1, n, value);
            last = uninitialized_copy(pos, last, fill_cur_2);

            first = new_first;
            end_of_storage = first + new_cap;
            return fill_cur_1;
        }

    }
}
#endif //TINYSTL_VECTOR_H
