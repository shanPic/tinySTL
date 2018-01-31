//
// Created by shanPic on 2018/1/31.
//

#ifndef TINYSTL_TYPE_TRAITS_H
#define TINYSTL_TYPE_TRAITS_H

#define __STL_TEMPLATE_NULL template<>

namespace tinystl{
    struct __true_type {};

    struct __false_type {};

    template <typename type>
    struct __type_traits {
        using this_dummy_member_must_be_first = __true_type;
        using has_trivial_default_constructor = __false_type;
        using has_trivial_copy_constructor    = __false_type;
        using has_trivial_assignment_operator = __false_type;
        using has_trivial_destructor          = __false_type;
        using is_POD_type                     = __false_type;
    };


    //以下为一些特化版本

    __STL_TEMPLATE_NULL struct __type_traits<char> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<signed char> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<unsigned char> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<short> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<unsigned short> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<int> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<unsigned int> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<long> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<unsigned long> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<float> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<double> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<long double> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };


    //针对原生指针进行设置
    template <typename T>
    struct __type_traits<T*> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };
    //一些原生指针的特化
    __STL_TEMPLATE_NULL struct __type_traits<char*> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<signed char*> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<unsigned char*> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<short*> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<unsigned short*> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<int*> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<unsigned int*> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<long*> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<unsigned long*> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<float*> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<double*> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

    __STL_TEMPLATE_NULL struct __type_traits<long double*> {
        using has_trivial_default_constructor = __true_type;
        using has_trivial_copy_constructor    = __true_type;
        using has_trivial_assignment_operator = __true_type;
        using has_trivial_destructor          = __true_type;
        using is_POD_type                     = __true_type;
    };

}

#endif //TINYSTL_TYPE_TRAITS_H

