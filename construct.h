//
// Created by shanPic on 2018/1/30.
//

#ifndef TINYSTL_CONSTRUCT_H
#define TINYSTL_CONSTRUCT_H

#include "iterator.h"
#include "type_traits.h"


namespace tinystl {
    template <typename T1, typename T2>
    inline void construct(T1 *ptr, const T2 &value){
        //定位new，在ptr位置new一个T1对象，使用value初始化
        new(ptr) T1(value);
    };

    //接受一个指针的destory()
    template <typename T>
    inline void destroy(T *ptr) {
        ptr -> ~T();
    }

    //接受两个迭代器的destory()

    // {POD类型 或者 有着trivial析构函数} 的类型离开作用域自动销毁
    template <typename ForwardIterator>
    inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __true_type) {};

    //非 {POD类型 或者 有着trivial析构函数} 调用destroy()
    template <typename ForwardIterator>
    inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __false_type) {
        for (; first != last; first++) {
            destroy(&*first);
        }
    };

    //value_type返回的是一个指针类型,
    //此辅助函数利用模板技术得到这个指针的底层类型,从而为使用Traits技术创造条件
    template <typename ForwardIterator, typename T>
    inline void __destroy(ForwardIterator first, ForwardIterator last, T*) {
        using H_T_D =typename __type_traits<T>::has_trivial_destructor;
        __destroy_aux(first, last, H_T_D());
    };

    template <typename ForwardIterator>
    inline void destroy(ForwardIterator first, ForwardIterator last) {
        __destroy(first, last,value_type(first));
    }

}



#endif //TINYSTL_CONSTRUCT_H
