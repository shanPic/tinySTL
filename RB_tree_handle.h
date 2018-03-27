//
// Created by shanPic on 2018/3/27.
//

#ifndef TINYSTL_RB_TREE_HANDLE_H
#define TINYSTL_RB_TREE_HANDLE_H
namespace tinystl{
    // 以下都是全域函式：__rb_tree_rotate_left(), __rb_tree_rotate_right(),
    // __rb_tree_rebalance(), __rb_tree_rebalance_for_erase()

    //新节点必须为红色节点。如果安插处的父节点为红色，就违反了红黑色规则
    //此时要旋转和改变颜色

    //左旋转
    //节点x为左旋转点
    inline void _rb_tree_rotate_left(_rb_tree_node_base* x, _rb_tree_node_base*& __root)
    {
        _rb_tree_node_base* y = x->right;    //获取左旋转节点x的右孩子y
        x->right = y->left;               //把y节点的左孩子作为旋转节点x的右孩子
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;

        //修改上层结构（修改原来x的上层节点的儿子指针的值）
        if (x == __root)                          //若原始位置节点x是根节点，则y为新的根节
            __root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    //右旋转
    //节点x为右旋转点
    inline void _rb_tree_rotate_right(_rb_tree_node_base* x, _rb_tree_node_base*& __root)
    {
        _rb_tree_node_base* y = x->left;     //获取右旋转节点x的左孩子y
        x->left = y->right;               //把y节点的右孩子作为旋转节点x的左孩子
        if (y->right != 0)
            y->right->parent = x;
        y->parent = x->parent;

        //修改上层结构（修改原来x的上层节点的儿子指针的值）
        if (x == __root)
            __root = y;                           //若原始位置节点x是根节点，则y为新的根节点
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }


    //重新令RB-tree平衡（改变颜色和旋转）
    //参数一为新增节点x，参数二为root节点
    inline void _rb_tree_rebalance(_rb_tree_node_base* x, _rb_tree_node_base*& __root)
    {
        //伪代码及详细说明见《算法导论3th》P178
        x->color = __rb_tree_red;

        while (x != __root && x->parent->color == __rb_tree_red) {

            if(x->parent == x->parent->parent->left) {

                _rb_tree_node_base* y = x->parent->parent->right;   //x的叔节点
                if (y && y->color == __rb_tree_red) {               //case1
                    x->parent->color = __rb_tree_black;
                    y->color = __rb_tree_black;
                    x->parent->parent->color = __rb_tree_red;
                    x = x->parent->parent;
                }
                else {
                    if (x == x->parent->right) {                    //case2
                        x = x->parent;
                        _rb_tree_rotate_left(x, __root);
                    }
                    x->parent->color = __rb_tree_black;             //case3
                    x->parent->parent->color = __rb_tree_red;       //case3
                    _rb_tree_rotate_right(x->parent->parent, __root);//case3
                }
            }
            else{
                //父节点为祖父节点的右节点时为类似情况
                _rb_tree_node_base* y = x->parent->parent->left;
                if (y && y->color == __rb_tree_red) {
                    x->parent->color = __rb_tree_black;
                    y->color = __rb_tree_black;
                    x->parent->parent->color = __rb_tree_red;
                    x = x->parent->parent;
                }
                else {
                    if (x == x->parent->left) {
                        x = x->parent;
                        _rb_tree_rotate_right(x, __root);
                    }
                    x->parent->color = __rb_tree_black;
                    x->parent->parent->color = __rb_tree_red;
                    _rb_tree_rotate_left(x->parent->parent, __root);
                }
            }
        }

        __root->color = __rb_tree_black;
    }
//
////删除节点
//    inline _rb_tree_node_base* _rb_tree_rebalance_for_erase(_rb_tree_node_base* z, _rb_tree_node_base*& __root, _rb_tree_node_base*& __leftmost, _rb_tree_node_base*& __rightmost)
//    {
//        //伪代码及详细说明见《算法导论3th》P183
//        _rb_tree_node_base* y = z;
//        _rb_tree_node_base* x = 0;
//        _rb_tree_node_base* x_parent = nullptr;
//        if (y->left == 0)     // z has at most one non-null child. y == z.
//            x = y->right;     // x might be null.
//        else if (y->right == nullptr)  // z has exactly one non-null child. y == z.
//            x = y->left;    // x is not null.
//        else {                   // z has two non-null children.  Set y to
//            y = y->right;   //   z's successor.  x might be null.
//            while (y->left != nullptr)
//                y = y->left;
//            x = y->right;
//        }
//        if (y != z) {          // relink y in place of z.  y is z's successor
//            z->left->parent = y;
//            y->left = z->left;
//            if (y != z->right) {
//                x_parent = y->parent;
//                if (x) x->parent = y->parent;
//                y->parent->left = x;      // y must be a child of left
//                y->right = z->right;
//                z->right->parent = y;
//            }
//            else
//                x_parent = y;
//            if (__root == z)
//                __root = y;
//            else if (z->parent->left == z)
//                z->parent->left = y;
//            else
//                z->parent->right = y;
//            y->parent = z->parent;
//            //__STD::swap(y->color, z->color);
//            __rb_tree_color_type tmp = y->color;
//            y->color = z->color;
//            z->color = tmp;
//            y = z;
//            // y now points to node to be actually deleted
//        }
//        else {                        // y == z
//            x_parent = y->parent;
//            if (x) x->parent = y->parent;
//            if (__root == z)
//                __root = x;
//            else
//            if (z->parent->left == z)
//                z->parent->left = x;
//            else
//                z->parent->right = x;
//            if (__leftmost == z)
//                if (z->right == 0)        // z->left must be null also
//                    __leftmost = z->parent;
//                    // makes __leftmost == _M_header if z == __root
//                else
//                    __leftmost = _rb_tree_node_base::minimum(x);
//            if (__rightmost == z)
//                if (z->left == 0)         // z->right must be null also
//                    __rightmost = z->parent;
//                    // makes __rightmost == _M_header if z == __root
//                else                      // x == z->left
//                    __rightmost = _rb_tree_node_base::maximum(x);
//        }
//        if (y->color != __rb_tree_red) {
//            while (x != __root && (x == 0 || x->color == __rb_tree_black))
//                if (x == x_parent->left) {
//                    _rb_tree_node_base* w = x_parent->right;
//                    if (w->color == __rb_tree_red) {
//                        w->color = __rb_tree_black;
//                        x_parent->color = __rb_tree_red;
//                        _rb_tree_rotate_left(x_parent, __root);
//                        w = x_parent->right;
//                    }
//                    if ((w->left == 0 ||
//                         w->left->color == __rb_tree_black) &&
//                        (w->right == 0 ||
//                         w->right->color == __rb_tree_black)) {
//                        w->color = __rb_tree_red;
//                        x = x_parent;
//                        x_parent = x_parent->parent;
//                    } else {
//                        if (w->right == 0 ||
//                            w->right->color == __rb_tree_black) {
//                            if (w->left) w->left->color = __rb_tree_black;
//                            w->color = __rb_tree_red;
//                            _rb_tree_rotate_right(w, __root);
//                            w = x_parent->right;
//                        }
//                        w->color = x_parent->color;
//                        x_parent->color = __rb_tree_black;
//                        if (w->right) w->right->color = __rb_tree_black;
//                        _rb_tree_rotate_left(x_parent, __root);
//                        break;
//                    }
//                } else {                  // same as above, with right <-> left.
//                    _rb_tree_node_base* w = x_parent->left;
//                    if (w->color == __rb_tree_red) {
//                        w->color = __rb_tree_black;
//                        x_parent->color = __rb_tree_red;
//                        _rb_tree_rotate_right(x_parent, __root);
//                        w = x_parent->left;
//                    }
//                    if ((w->right == 0 ||
//                         w->right->color == __rb_tree_black) &&
//                        (w->left == 0 ||
//                         w->left->color == __rb_tree_black)) {
//                        w->color = __rb_tree_red;
//                        x = x_parent;
//                        x_parent = x_parent->parent;
//                    } else {
//                        if (w->left == 0 ||
//                            w->left->color == __rb_tree_black) {
//                            if (w->right) w->right->color = __rb_tree_black;
//                            w->color = __rb_tree_red;
//                            _rb_tree_rotate_left(w, __root);
//                            w = x_parent->left;
//                        }
//                        w->color = x_parent->color;
//                        x_parent->color = __rb_tree_black;
//                        if (w->left) w->left->color = __rb_tree_black;
//                        _rb_tree_rotate_right(x_parent, __root);
//                        break;
//                    }
//                }
//            if (x) x->color = __rb_tree_black;
//        }
//        return y;
//    }


}
#endif //TINYSTL_RB_TREE_HANDLE_H
