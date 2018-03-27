//
// Created by shanPic on 2018/2/23.
//

#ifndef TINYSTL_RB_TREE_H
#define TINYSTL_RB_TREE_H

//#include <winreg.h>
#include <stddef.h>

namespace tinystl{
    using __rb_tree_color_type = bool;
    const __rb_tree_color_type __rb_tree_red = false;
    const __rb_tree_color_type __rb_tree_black = true;

    struct _rb_tree_node_base{
        using  base_ptr = _rb_tree_node_base*;

        __rb_tree_color_type color;
        base_ptr parent;
        base_ptr left;
        base_ptr right;

        _rb_tree_node_base():color(__rb_tree_red),parent(nullptr),left(nullptr),right(nullptr){};

        static _rb_tree_node_base* minimum(_rb_tree_node_base* x){
            while(x -> left != nullptr) x = x->left;
            return x;
        }
        static _rb_tree_node_base* maximum(_rb_tree_node_base* x){
            while(x -> right != nullptr) x = x->right;
            return x;
        }
    };





    struct _rb_tree_iterator_base
    {
        using base_ptr = _rb_tree_node_base::base_ptr;
        using difference_type = ptrdiff_t;
        base_ptr node;


        //下一个节点（最小的比当前节点大的节点）
        void increment()
        {
            //【情况1】:存在右子树，则找出右子树的最小节点
            if (node->right != nullptr) {             //如果有右子树
                node = node->right;             //向右边走
                while (node->left != nullptr)         //往右子树中的左边一直走到底
                    node = node->left;          //最左节点就是后继结点
            }
            else {
                base_ptr y = node->parent;    //沿其父节点上溯
                while (node == y->right) {    //【情况2】:若节点是其父节点的右孩子,则上溯
                    node = y;			      //一直上溯,直到“某节点不是其父节点的右孩子”为止
                    y = y->parent;
                }
                //根节点和header节点是互为父节点
                if (node->right != y)   //【情况3】:若此时的右子节点不等于此时的父节点（初始node为最大元素 或者 只有root一个元素
                    node = y;           //此时的父节点即为解答
                //【情况4】：否则此时的node为解答
            }
        }

        //上一个节点（最大的比当前节点小的节点）
        void decrement()
        {
            if (node->color == __rb_tree_red && node->parent->parent == node)// 如果是红节点而且父节点的父节点等于自己
                node = node->right;			    //【情况1】：此时node为根节点

            else if (node->left != nullptr) {   //若有左孩子节点。【情况2】:左子树的最大值即为前驱节点
                base_ptr y = node->left;        //向左边走,即令y指向左孩子
                while (y->right != nullptr)     //y存在右孩子,
                    y = y->right;               //一直往右走到底
                node = y; //最后即为解答
            }
            else {                              //即非根节点,且没有左孩子节点,【情况3】
                base_ptr y = node->parent;      //找出父节点
                while (node == y->left) {       //node节点是其父节点的左孩子
                    node = y;                   //一直交替上溯
                    y = y->parent;              //直到不为左孩子结点
                }
                node = y;//此时父节点即为解答
            }
        }
    };

    template <typename Value>
    struct rb_tree_node : public _rb_tree_node_base{

        using link_type = rb_tree_node<Value>*;
        Value value;
    };

    //两个迭代器相等，意味着指向RB-Tree的同一个节点
    inline bool operator==(const _rb_tree_iterator_base& __x, const _rb_tree_iterator_base& __y) {
        return __x.node == __y.node;
    }

    inline bool operator!=(const _rb_tree_iterator_base& __x, const _rb_tree_iterator_base& __y) {
        return __x.node != __y.node;
        //两个迭代器不相等，意味着所指向的节点不同
    }

    //RB-Tree的迭代器iterator结构
    //继承基类迭代器Rb_tree_base_iterator
    template <typename _Value, typename _Ref, typename _Ptr>
    struct _rb_tree_iterator : public _rb_tree_iterator_base
    {


        using value_type = _Value;
        using reference  = _Ref;
        using pointer  = _Ptr;
        using iterator = _rb_tree_iterator<_Value,_Value&,_Value*>;
        using const_iterator = _rb_tree_iterator<_Value,const _Value&,const _Value*>;
        using _Self = _rb_tree_iterator<_Value,_Ref,_Ptr>;
        using link_type = rb_tree_node<_Value>*;    //节点指针

        //构造函数
        _rb_tree_iterator() = default;
        _rb_tree_iterator(link_type __x) { node = __x; }
        _rb_tree_iterator(const iterator& __it) { node = __it.node; }

        /*
        以下是操作符重载
        */
        reference operator*() const { return static_cast<link_type>(node)->value; }  //TODO!!!

        pointer operator->() const { return &(operator*()); }



        _Self& operator++() { increment(); return *this; }

        _Self operator++(int) {
            _Self __tmp = *this;
            increment();
            return __tmp;
        }


        _Self& operator--() { decrement(); return *this; }

        _Self operator--(int) {
            _Self __tmp = *this;
            decrement();
            return __tmp;
            }
    };

}
#include "RB_tree_handle.h"
#include "RB_tree_dataClass.h"
#endif //TINYSTL_RB_TREE_H
