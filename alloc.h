//
// Created by shanPic on 2018/1/30.
//

#ifndef TINYSTL_ALLOC_H
#define TINYSTL_ALLOC_H

#if 0
#   include <new>
    #   define  __THROW_BAD_ALLOC throw bad_alloc
#elif !defined(__THROW_BAD_ALLOC)
#   include <iostream>
#   define __THROW_BAD_ALLOC std::cerr << "out of memory" << std::endl; exit(1);
#endif

#include <cstdlib>

namespace tinystl
{

    //以下为一级配置器__malloc_alloc_template

    template <int inst> //!??
    class __malloc_alloc_template {

    private:
        //oom:out of memory;
        //以下函数用来处理oom
        static void *oom_malloc(size_t);
        static void *oom_remalloc(void *,size_t);
        //模仿C++中的out-of-memory handler,初始为0,可以修改
        static void (* __malloc_alloc_oom_handler)() = 0;
    public:

        static void *allocate(size_t sz) {
            void *res = std::malloc(sz);
            if (res == 0) res = oom_malloc(sz);
            return res;
        }

        static void *reallocate(void *p, size_t old_sz, size_t new_sz) {
            void *res = std::realloc(p, new_sz);
            if (res == 0) res = oom_remalloc(p, new_sz);
            return res;
        }

        static void *deallocte(void *p, size_t sz) {
            free(p);
        }

        typedef void (* PTR_VOID_FUN)();
        PTR_VOID_FUN set_malloc_handler(PTR_VOID_FUN new_fuc) {
            PTR_VOID_FUN old = __malloc_alloc_oom_handler;
            __malloc_alloc_oom_handler = new_fuc;
            return old;
        }

    };

    void * __malloc_alloc_template::oom_malloc(size_t sz) {
        void * res;

        for (;;){
            if (__malloc_alloc_oom_handler == 0) { __THROW_BAD_ALLOC}
            (*__malloc_alloc_oom_handler)();
            res = malloc(sz);
            if (res) return res;
        }
    }

    void * __malloc_alloc_template::oom_remalloc(void *p, size_t sz) {
        void * res;

        for (;;) {
            if(__malloc_alloc_oom_handler == 0) {__THROW_BAD_ALLOC}
            (*__malloc_alloc_oom_handler)();
            res = realloc(p,sz);
            if (res) return res;
        }
    }

    //直接将非类型参数inst指定为0
    typedef __malloc_alloc_template<0> malloc_alloc;
}
#endif //TINYSTL_ALLOC_H
