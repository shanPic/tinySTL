//
// Created by shanPic on 2018/2/1.
//

#ifndef TINYSTL_UNINITIALIZED_H
#define TINYSTL_UNINITIALIZED_H

#include "construct.h"
#include <cstring>

namespace tinystl {

    //以下是uninitialized_fill_n的实现（下面两组函数的实现与之类似）
    //是POD类型
    template <typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator
    __uninitialized_fill_n_aux(ForwardIterator target, Size n, const T& value, __true_type) {
        for (; n > 0; n--, target++) {
            *target = value;
        }
        return target;
    };

    //不是POD类型
    template <typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator
    __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, __false_type) {
        ForwardIterator cur = first;
        try {
            for(; n > 0; n-- , cur++){
                construct(cur, value);
            }
            return cur;
        }
        catch (...){ destroy(first, cur); }
    };

    template <typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator
    __uninitialized_fill_n(ForwardIterator target, Size n,
                           const T& value, T*) {
        using isPOD = typename __type_traits<T>::is_POD_type ;
        return __uninitialized_fill_n_aux(target, n, value, isPOD());
    };

    template <typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator
    uninitialized_fill_n(ForwardIterator target, Size n, const T &value) {
        return __uninitialized_fill_n(target, n, value, value_type(target));
    };




    //以下是uninitialized_copy的实现
    template <typename InputIterator, typename ForwardIterator>
    inline ForwardIterator
    __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator target, __true_type) {

        for(; first != last; first++, target++) {
            *target = *first;
        }
        return target;
    };

    template <typename InputIterator, typename ForwardIterator>
    inline ForwardIterator
    __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator target, __false_type) {
        ForwardIterator cur = target;
        try{
            for(; first != last; first++, cur++) {
                construct(&*cur, *first);
            }
            return cur;
        }
        catch (...) {destroy(target, cur); }
    };

    template <typename InputIterator, typename ForwardIterator, typename T>
    inline ForwardIterator
    __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator target, T*) {
        using isPOD = __type_traits<T>::is_POD_type;
        return __uninitialized_copy_aux(first, last, target, isPOD());
    };

    template <typename InputIterator, typename ForwardIterator>
    inline ForwardIterator
    uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator target) {
        return __uninitialized_copy(first, last, target, value_type(first));
    };

    //特化char*与wchar_t*两个版本，直接使用memmove()这一速度很快的底层函数
    template <>
    inline char*
    uninitialized_copy(const char *first, const char *last, char *target) {
        memmove(target, first, last - first);
        return target + (last - first);
    };

    template <>
    inline wchar_t*
    uninitialized_copy(const wchar_t *first, const wchar_t *last, wchar_t *target) {
        memmove(target, first, (last - first) * sizeof(wchar_t));
        return target + (last - first);
    }



    //下面是uninitialized_fill的实现
    template <typename InputIterator, typename T>
    inline void
    __uninitialized_fill_aux(InputIterator first, InputIterator last, const T &value, __true_type) {
        //fill(first, last, value);
        for (; first != last; first++ ) {
            *first = value;
        }
    };

    template <typename InputIterator, typename T>
    inline void
    __uninitialized_fill_aux(InputIterator first, InputIterator last, const T &value, __false_type) {
        InputIterator cur = first;
        try {
            for( ; cur != last; cur++){
                construct(cur, value);
            }
        }
        catch (...){ destroy(first, cur); };

    };


    template <typename InputIterator, typename T>
    inline void
    __uninitialized_fill(InputIterator first, InputIterator last, const T &value, T*) {
        using isPOD = __type_traits<T>::is_POD_type ;
        __uninitialized_fill_aux(first, last, value, isPOD());
    };

    template <typename ForwardIterator, typename T>
    inline void
    uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &value) {
        __uninitialized_fill(first, last, value, value_type(first));
    };

}
#endif //TINYSTL_UNINITIALIZED_H
