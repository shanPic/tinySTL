//
// Created by shanPic on 2018/3/27.
//

#ifndef TINYSTL_RB_TREE_DATACLASS_H
#define TINYSTL_RB_TREE_DATACLASS_H

#include "alloc.h"
#include <stddef.h>
#include "pair.h"
#include "construct.h"

namespace tinystl{

    //KeyOfValue是一个函数对象
    template <typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc = malloc_alloc>
    class rb_tree{
    protected:
        using void_pointer = void*;
        using base_ptr = _rb_tree_node_base*;
        using rb_tree_node = rb_tree_node<Value>;
        using rb_tree_node_allocator = simple_alloc<rb_tree_node, Alloc>;
        using color_type = __rb_tree_color_type;
        using size_type = size_t ;

    public:
        using key_type = Key;
        using value_type = Value;
        using pointer = value_type*;
        using const_pointer = const pointer;
        using reference = value_type&;
        using const_reference = const reference;
        using link_type = rb_tree_node*;
        using difference_type = ptrdiff_t;

    protected:
        link_type get_node() { return rb_tree_node_allocator::allocate(); }     //为1个节点申请内存
        void put_node(link_type p) { rb_tree_node_allocator::deallocate(p); }   //释放p处内存

        link_type create_node(value_type const& x) {
            link_type tmp = get_node();
            construct(&tmp->value, x);//TODO 此处需要异常处理
            return tmp;
        }

        link_type clone_node(link_type x) {     //注意，这个函数只复制值和颜色
            link_type tmp = create_node(x->value);
            tmp->color = x->color;
            tmp->parent = nullptr;
            tmp->left = nullptr;
            tmp->right = nullptr;
            return tmp;
        }

        void destroy_node(link_type p) {
            destroy(&p->value);
            put_node(p);
        }

    protected:
        size_type    node_count;           //维护树的大小 （节点数量）
        link_type header;               //end()
        Compare   key_compare;          //一个函数对象（key值的比较规则）


        //利用header轻松实现下面三个函数
        link_type& root() const { return (link_type&)(header->parent); }
        link_type& leftmost() const { return (link_type&)(header->left); }
        link_type& rightmost() const { return (link_type&)(header->right); }

        static link_type&  left(link_type x) { return (link_type&)(x->left);}
        static link_type&  right(link_type x) { return (link_type&)(x->right);}
        static link_type&  parent(link_type x) { return (link_type&)(x->parent);}
        static reference   value(link_type x) { return x->value;}
        static color_type& color(link_type x) { return x->color;}

        static link_type&  left(base_ptr x) { return (link_type&)(x->left);}
        static link_type&  right(base_ptr x) { return (link_type&)(x->right);}
        static link_type&  parent(base_ptr x) { return (link_type&)(x->parent);}
        static reference   value(base_ptr x) { return ((link_type&)x)->value;}
        static color_type& color(base_ptr x) { return x->color;}
        static Key key(base_ptr x) { return KeyOfValue()(value(x));}

        static link_type& minimum(link_type x) {
            return (link_type&)(_rb_tree_node_base::minimum(x));
        }
        static link_type& maximum(link_type x) {
            return (link_type&)(_rb_tree_node_base::maximum(x));
        }

    public:
        using iterator = _rb_tree_iterator<value_type ,reference ,pointer >;

    private:
        iterator __insert(base_ptr x,base_ptr y,const value_type& v);
        link_type __copy(link_type x, link_type p);//todo
        void __erase(link_type x);                  //todo
        void init(){
            header = get_node();
            color(header) = __rb_tree_red;//设为red，用来与root区分
            root() = nullptr;
            leftmost() = header;
            rightmost() = header; //初始化header左右都指向自己
        }
        void __aux_erase(link_type now){
            if(now != nullptr){
                __aux_erase(left(now));
                __aux_erase(right(now));
                put_node(now);
            }
        }

    public:
        rb_tree(const Compare& cmp = Compare()):node_count(0), key_compare(cmp){ init(); };
        ~rb_tree(){clear(); put_node(header);}

        rb_tree<Key,Value,KeyOfValue,Compare,Alloc>&
                operator=(const rb_tree<Key,Value,KeyOfValue,Compare,Alloc>&);//todo

    public:

        Compare key_comp() const {return key_compare;}
        iterator begin() {return leftmost();}
        iterator end() {return header;}
        bool empty() {return node_count == 0;}
        size_type size(){return node_count;}
        size_type max_size() { return size_type(-1);}

    public:
        pair<iterator ,bool> insert_unique(const value_type& x);
        iterator insert_equal(const value_type& x);
        void clear(){
            __aux_erase(root());
            left(header) = header;
            right(header) = header;
            parent(header) = 0;
        }
        iterator find(const key_type& k){
            link_type y = header;
            link_type x = root();
            while(x != nullptr){
                if(!key_compare(key(x),k)){
                    y = x;
                    x = left(x);
                }
                else x = right(x);
            }
            iterator j = iterator(y);
            return (j == end() || key_compare(k,key(j.node))) ? end() : j;
        }
    };

    template <typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
    typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::iterator
    rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::__insert(base_ptr x_, base_ptr y_, const value_type& v)
    {   //参数x_为新值插入点，参数y_为插入点之父节点，参数v 为新值
        link_type x = (link_type) x_;
        link_type y = (link_type) y_;
        link_type z;

        if (y == header || x != nullptr || key_compare(KeyOfValue()(v), key(y))) {
            z = create_node(v);    //创建值为v的节点z
            left(y) = z;

            if (y == header) {
                root() = z;
                rightmost() = z;
            }
            else if (y == leftmost())   //若y为最左节点
                leftmost() = z;
        }
        else {
            z = create_node(v);
            right(y) = z;
            if (y == rightmost())
                rightmost() = z;
        }
        parent(z) = y;
        left(z) = nullptr;
        right(z) = nullptr;
        _rb_tree_rebalance(z, header->parent); //调整RB-Tree使其满足性质
        ++node_count;
        return iterator(z);                   //返回新节点迭代器（新建的迭代器）
    }

    template <typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
    typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::iterator
    rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::insert_equal(const value_type &v) {
        link_type y = header;   //寻找插入点时的父节点
        link_type x = root();   //寻找插入点时的当前节点
        while(x != nullptr){
            y = x;
            x = key_compare(KeyOfValue()(v),key(x)) ? left(x) : right(x);
        }
        return __insert(x,y,v);
    }


    template <typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
    pair<typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::iterator ,bool>
    rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::insert_unique(const value_type &v) {

        link_type y = header;
        link_type x = root();   //y所指即为安插点的父节点，x必为叶子节点
        bool comp = true;
        while (x != nullptr) {
            y = x;
            comp = key_compare(KeyOfValue()(v), key(x));
            x = comp ? left(x) : right(x);
        }

        iterator j = iterator(y);
        if (comp)       //如果离开while时comp为1，则说明遇大，将插入至左节点
            if (j == begin())               //若插入点之父节点为最左节点
                return pair<iterator,bool>(__insert(x, y, v), true);
            else                            //否则(插入点之父节点不在最左节点)
                --j;
        // 小于新值（表示遇小，将安插于右侧）
        if (key_compare(key(j.node), KeyOfValue()(v)))
            return pair<iterator,bool>(__insert(x, y, v), true);
        //若运行到这里，表示键值有重复，不应该插入
        return pair<iterator,bool>(j, false);
    };
}
#endif //TINYSTL_RB_TREE_DATACLASS_H
