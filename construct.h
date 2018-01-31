//
// Created by shanPic on 2018/1/30.
//

#ifndef TINYSTL_CONSTRUCT_H
#define TINYSTL_CONSTRUCT_H

namespace tinystl
{
    template <typename T1, typename T2>
    inline void construct(T1 *ptr, const T2 &value){
        new(ptr) T1(value); //定位new，在ptr位置new一个T1对象，使用value初始化
    };

    //接受一个指针的destory()
    template <typename T>
    inline void destory(T *ptr){
        ptr -> ~T();
    }

    //接受两个迭代器的destory()
    //TODO

}



#endif //TINYSTL_CONSTRUCT_H
