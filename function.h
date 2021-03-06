//
// Created by shanPic on 2018/3/28.
//

#ifndef TINYSTL_FUNCTION_H
#define TINYSTL_FUNCTION_H
namespace tinystl{

    //一元
    template<typename Arg,typename Result>
    struct unary_function
    {
        typedef Arg argument_type;
        typedef Result result_type;
    };

    //二元
    template<typename Arg1,typename Arg2,typename Result>
    struct binary_function
    {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };

    //返回自己（目前只用于rbtree的测试，使键值与value为同一个值）
    template<typename T>
    struct identity:public unary_function<T,T>
    {
        const T& operator()(const T& x) const {return x;}
    };

    template<typename T>
    struct less:public binary_function<T,T,bool>
    {
        bool operator()(const T& x,const T& y)const
        {
            return x<y;
        }
    };

    template<typename T>
    struct greater:public binary_function<T,T,bool>
    {
        bool operator()(const T& x,const T& y)const
        {
            return x>y;
        }
    };

    template<class pair>
    struct select1st:public unary_function<pair,typename pair::first_type>
    {
        const typename pair::first_type& operator()(const pair& x) const
        {
            return x.first;
        }
    };


}
#endif //TINYSTL_FUNCTION_H
