//
// Created by shanPic on 2018/3/28.
//

#ifndef TINYSTL_MAP_H
#define TINYSTL_MAP_H

#include "function.h"
#include "alloc.h"
#include "pair.h"
#include "RB_Tree.h"

namespace tinystl{


//map内部元素根据键值key默认使用递增排序less
//map定义
    template <typename Key, typename T, typename Compare = less<Key>, typename Alloc = malloc_alloc >
    class map {
    public:

        typedef Key key_type;
        typedef T data_type;
        typedef pair<const Key, T> value_type;  //包含(键值/实值),const保证键值key不被修改
        typedef Compare keyCompare;

        class valueCompare : public binary_function<value_type, value_type, bool> {
            friend class map<Key, T, Compare, Alloc>;

        protected :
            Compare comp;

            valueCompare(Compare __c) : comp(__c) {}

        public:
            bool operator()(const value_type &x, const value_type &__y) const {
                return comp(x.first, __y.first);
            }
        };

    private:
        //底层机制是RB-Tree
        //以pair的第一个类型作为TB-tree的键值类型.
        //所以键值key不能修改
        typedef rb_tree<key_type, value_type, select1st<value_type>, keyCompare, Alloc> rep_type;
        rep_type t;
    public:
        typedef typename rep_type::pointer pointer;
        typedef typename rep_type::const_pointer const_pointer;
        typedef typename rep_type::reference reference;
        typedef typename rep_type::const_reference const_reference;
        typedef typename rep_type::iterator iterator;
        typedef typename rep_type::size_type size_type;
        typedef typename rep_type::difference_type differenceType;

        map() : t(Compare()) {};

//        //拷贝构造函数
//        map(const map<Key, T, Compare, Alloc> &x) : t(x.t) {}


//        map<Key, T, Compare, Alloc> &
//        operator=(const map<Key, T, Compare, Alloc> &x) {
//            t = x.t;
//            return *this;
//        }



        //调用RB-Tree的操作
        keyCompare key_comp() const { return t.key_comp(); }

        valueCompare value_comp() const { return valueCompare(t.key_comp()); }

        iterator begin() { return t.begin(); }

        iterator end() { return t.end(); }

        bool empty() { return t.empty(); }

        size_type size() { return t.size(); }

        size_type max_size() { return t.max_size(); }

        T &operator[](const key_type &k) {
            return (*((insert(value_type(k, T()))).first)).second;
        }


        pair<iterator, bool> insert(const value_type &x) { return t.insert_unique(x); }




//        sizeType erase(const keyType& x) { return t.erase(x); }//todo


        void clear() { t.clear(); }


        iterator find(const key_type &x) { return t.find(x); }

        size_type count(const key_type &x) { return t.find(x) == t.end() ? 0 : 1; }
    };
}
#endif //TINYSTL_MAP_H
