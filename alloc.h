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

namespace tinystl {

    //以下为一级配置器__malloc_alloc_template

    class __malloc_alloc_template {

        using PTR_VOID_FUN = void (*)();
    private:
        //oom:out of memory;
        //以下函数用来处理oom
        static void* oom_malloc(size_t);

        static void* oom_remalloc(void*, size_t);

        //模仿C++中的out-of-memory handler,初始为0,可以修改
        //__malloc_alloc_oom_handler
        //static void (* __malloc_alloc_oom_handler)();
        static PTR_VOID_FUN __malloc_alloc_oom_handler;
    public:

        static void* allocate(size_t sz) {
            void* res = std::malloc(sz);
            if (res == nullptr) {
                res = oom_malloc(sz);
            }
            return res;
        }

        static void* reallocate(void* p, size_t old_sz, size_t new_sz) {
            void* res = std::realloc(p, new_sz);
            if (res == nullptr) {
                res = oom_remalloc(p, new_sz);
            }
            return res;
        }

        static void* deallocate(void* p, size_t sz) {
            free(p);
        }

        //typedef void (* PTR_VOID_FUN)();

        PTR_VOID_FUN set_malloc_handler(PTR_VOID_FUN new_fuc) {
            PTR_VOID_FUN old = __malloc_alloc_oom_handler;
            __malloc_alloc_oom_handler = new_fuc;
            return old;
        }

    };

    void (* __malloc_alloc_template::__malloc_alloc_oom_handler)() = nullptr;

    void* __malloc_alloc_template::oom_malloc(size_t sz) {
        void* res;
        PTR_VOID_FUN my_alloc_handler;

        for (;;) {
            my_alloc_handler = __malloc_alloc_oom_handler;
            if (my_alloc_handler == nullptr) {
                __THROW_BAD_ALLOC
            }
            (*__malloc_alloc_oom_handler)();
            res = malloc(sz);
            if (res) return res;
        }
    }

    void* __malloc_alloc_template::oom_remalloc(void* p, size_t sz) {
        void* res;

        for (;;) {
            if (__malloc_alloc_oom_handler == nullptr) {
                __THROW_BAD_ALLOC
            }
            (*__malloc_alloc_oom_handler)();
            res = realloc(p, sz);
            if (res) return res;
        }
    }

    //直接将非类型参数inst指定为0
    using malloc_alloc = __malloc_alloc_template;
    using alloc = __malloc_alloc_template;

    //简单包装
    template<typename T, typename Alloc>
    class simple_alloc {
    public:
        static T* allocate(size_t n) {   //分配n个T
            return n == 0 ? 0 : static_cast<T*>(Alloc::allocate(n * sizeof(T)));
        }

        static T* allocate() {   //分配1个T
            return static_cast<T*>(Alloc::allocate(sizeof(T)));
        }

        static void deallocate(T* p, size_t n) { //在p销毁n个T
            if (n != 0) {
                Alloc::deallocate(p, n * sizeof(T));
            }
        }

        static void deallocate(T* p) {   //在p销毁1个T
            deallocate(p, sizeof(T));
        }
    };

}
#endif //TINYSTL_ALLOC_H
