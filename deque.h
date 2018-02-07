//
// Created by shanPic on 2018/2/4.
//

#ifndef TINYSTL_DEQUE_H
#define TINYSTL_DEQUE_H

#include "alloc.h"
#include "iterator.h"
#include "uninitialized.h"

namespace tinystl {

    size_t __deque_buf_size(size_t n, size_t size) {//n为缓冲区大小，size为T大小
        if(n != 0)
            return n;
        else if(size < 512)
            return static_cast<size_t>(512 / size);
        else
            return static_cast<size_t>(1);
    }


    template <typename T, typename Ref, typename Ptr, size_t BufSiz>
    struct __deque_iterator {
        //类型声明
        using iterator = __deque_iterator<T, T&, T*, BufSiz>;
        using const_iterator = __deque_iterator<T, const T&, const T*, BufSiz>;

        using iterator_category = random_access_iterator_tag;
        using value_type = T;
        using pointer = Ptr;
        using reference = Ref;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using map_pointer = T**;

        using self = __deque_iterator;


        //数据成员
        T* cur;
        T* first;
        T* last;
        map_pointer node;

        //构造函数
        __deque_iterator() : cur(nullptr), first(nullptr),last(nullptr), node(nullptr){};
        //其他成员函数
        static size_t buffer_size() { return __deque_buf_size(BufSiz, sizeof(T)); }

        void set_node(map_pointer new_node) { //跳一个缓冲区
            node = new_node;
            first = *new_node;
            last = first + static_cast<difference_type>(buffer_size());
        }

        //重载运算符
        reference operator*() const {return *cur;}
        pointer operator->() const {return &*cur;}

        difference_type operator-(const self& x) const {
            return static_cast<difference_type>( buffer_size() * (node - x.node) + (cur - first) + (x.last - x.cur));
        }
        self& operator++() {
            cur++;
            if(cur == last) {
                set_node(node + 1);
                cur = first;
            }
            return *this;
        }
        self& operator++(int) { //重载后置式
            self tmp = *this;
            ++*this;
            return tmp;
        }
        self& operator--() {
            if(cur != first){
                cur--;
            }
            else{
                set_node(node - 1);
                cur = last;
            }
        }
        self& operator--(int) {
            self tmp = *this;
            this->operator--();
            return tmp;
        }


        self& operator+=(difference_type n) {
            difference_type offset = n + (cur - first);
            if(offset>=0 && offset <= (last - first)) {
                cur += n;
            }
            else{
                difference_type sz = static_cast<difference_type >(buffer_size());
                difference_type node_offset = (offset >= 0) ? static_cast<difference_type >(offset) / sz : -(static_cast<difference_type >(-offset - 1) / sz + 1) ;
                set_node(node + node_offset);
                cur += (offset - node_offset * sz);
            }
            return *this;
        }
        self& operator-=(difference_type n) {
            this->operator+=(-n);
        }
        self& operator+(difference_type n) const {
            self tmp = *this;
            return tmp += n;
        }
        self& operator-(difference_type n) const {
            self tmp = *this;
            return tmp -= n;
        }

        reference operator[](difference_type n) const {
            return *(*this + n);
        }

        bool operator==(const self& x) const {return cur == x.cur; }
        bool operator!=(const self& x) const {return !(*this == x);}
        bool operator<(const self& x) const {
            return (node == x.node) ? (cur < x.cur) : (node < x.node);
        }
    };



    template <typename T, typename Alloc = alloc, size_t BufSize =0>
    class deque {

        //类型声明
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

        using iterator = __deque_iterator<T, T&, T*, BufSize>;
    protected:
        using map_pointer = T**;

        using data_allocator = simple_alloc<value_type , Alloc>;
        using map_allocator = simple_alloc<pointer ,Alloc>;


        //数据成员
    protected:
        iterator start;
        iterator finish;
        map_pointer map;
        size_type map_size; //map可容纳的缓冲区指针数量
        size_type num_of_elements; //容器中此时的元素数目

        //成员函数
    public:

        //构造与析构
        deque() : start(), finish(), map(nullptr),map_size(0),
                  num_of_elements(static_cast<size_type>(0)){
            create_map_and_nodes(0);
        };
        deque(const int n, const value_type& value):start(),finish(),map(), map_size(0),
                                                    num_of_elements(static_cast<size_type>(n)) {
            create_map_and_nodes(n);    //创建deque的结构
            fill_initialized(n, value);
        }

        void fill_initialized(size_type n, value_type value);
        void create_map_and_nodes(size_t n);


        //迭代器相关
        iterator begin() {return start;}
        iterator end() {return finish;};

        //元素相关
        reference operator[](size_type n) {
            //进行越界检查
            if( n <0 || n >= num_of_elements){
                throw std::out_of_range("out of range");
            }
            else return (start[static_cast<difference_type>(n)]);
        };
        size_type size() const {
            return static_cast<size_type >(finish - start);
        }
        bool empty() const {
            return start == finish;
        }

        reference front() {return *start;};
        reference back() { //最后一个可用的元素
            iterator tmp = finish;
            --tmp;
            return *tmp;

        }

        void push_back(const value_type &value) {
            if(finish.cur != finish.last - 1 && map_size != 0) {
                construct(finish.cur, value);
                finish.cur++;
            }
            else push_back_aux(value);
            num_of_elements++;
        }
        void push_front(const value_type &value);//TODO

    protected:
        //一些内部函数
        size_t buf_size() { return __deque_buf_size(BufSize, sizeof(T));}
        void push_back_aux(const value_type &value); //push_back的辅助函数,处理需要新建空间的情况
        void reallocate_map(size_type,bool);
    };

    /*
     * fill_initialized
     * 将已经创建好的deque的结构，填充为value
     */
    template <typename T, typename Alloc, size_t BufSize>
    void deque<T,Alloc,BufSize>::fill_initialized(size_type n, value_type value) {

        map_pointer cur = start.node;
        for( ; cur != finish.node; cur++) {
            uninitialized_fill_n(*cur, buf_size(), value);
        }
        uninitialized_fill(finish.first, finish.cur,value);
    };

    /*
     * create_map_and_nodes
     * 如此写法的结果是：
     * 当元素个数n被buf_size整除时：
     * finish.cur指向{ { {存储有效元素的最后一个buffer} 的下一个buffer} 的第一个元素}
     * 当元素个数n不被buf_size整除时：
     * finish.cur指向{ { {存储有效元素的最后一个buffer} 的最后一个有效元素} 的下一个元素}
     *
     * 总而言之，总是指向下一个可用元素
     */
    template <typename T, typename Alloc, size_t BufSize>
    void deque<T,Alloc,BufSize>::create_map_and_nodes(size_t n) {
        size_t _buf_size = buf_size();
        //计算map中需要多少节点, 由于是向下整除，需要加一个1，以保证空间足够
        //还需要再前后加1(+2)，以便扩充时使用

        map_size = n / _buf_size + 3;
        map = map_allocator::allocate(map_size);

        map_pointer new_start = map + 1;
        map_pointer new_end = new_start + n / _buf_size;

        //TODO
        // 以下申请空间的操作最好写一下异常处理，确保申请空间出问题时，可以销毁以申请的空间，防止产生内存泄漏
        map_pointer cur = new_start;
        for( ; cur <= new_end; cur++) {
            *cur = data_allocator::allocate(_buf_size);
        }

        start.set_node(new_start);
        finish.set_node(new_end);
        start.cur = start.first;
        finish.cur = finish.first + n % _buf_size;
    }

    template <typename T, typename Alloc, size_t BufSize>
    void deque<T,Alloc,BufSize>::push_back_aux(const value_type &value) {
        //进入此函数说明需要push元素至下一个缓冲区
        //检查下一个缓冲区是否存在，若不存在则分配空间
        if(finish.node + 1 == map + map_size)
            reallocate_map(static_cast<size_type>(1), false);   //分配新的map（中控表）
        *(finish.node + 1) = data_allocator::allocate(buf_size());  //分配新的缓冲区

        //更新指针
        finish.set_node(finish.node + 1);
        construct(finish.first, value);
        finish.cur = finish.first + 1;

    }

    /*
     * reallocate_map
     * 当map的空间不足时(finish.node map中最后一个元素),利用此函数申请空间
     * 同时会更新start，finish（不更改这两者中的cur，以保证数据正确）
     */
    template <typename T, typename Alloc, size_t BufSize>
    void deque<T,Alloc,BufSize>::reallocate_map(size_type __nodes_to_add, //需要添加的 {map的节点(node)} 数目
                                              bool __add_at_front) //__add_at_front指明是(1)否(0)向头添加
    {
        //map原始节点数
        size_type old_num_nodes = finish.node - start.node + 1;
        //map新的节点数
        size_type new_num_nodes = old_num_nodes + __nodes_to_add;

        map_pointer new_nstart = nullptr;
        map_pointer cur_copy = nullptr, cur_tar = nullptr;
        if (map_size > 2 * new_num_nodes) {//若map的大小比新节点数的两倍还大，则只需调整迭代器start和finish

            //新的start指针，尽量指向map中间，并给需要添加的node提供足够大的空间
            new_nstart = map + (map_size - new_num_nodes) / 2
                           + (__add_at_front ? __nodes_to_add : 0);

            //将旧的map拷贝过去
            if (new_nstart < start.node){
                cur_copy = start.node;
                cur_tar = new_nstart;
                for( ; cur_copy <= finish.node; cur_copy++, cur_tar++){
                    construct(cur_tar, *cur_copy);
                    destroy(cur_copy);
                }
            }
            else{
                cur_copy = finish.node;
                cur_tar = new_nstart + old_num_nodes - 1;

                for( ; cur_copy >= start.node; cur_copy--, cur_tar--) {
                    construct(cur_tar, *cur_copy);
                    destroy(cur_copy);
                }
            }

        }
        else {//否则需重新分配一个新的map空间
            //新map的大小，足够大以容下新添加的节点
            size_type new_map_size =
                    map_size + std::max(map_size, __nodes_to_add) + 2;

            map_pointer new_map = map_allocator::allocate(new_map_size);

            new_nstart = new_map + (new_map_size - new_num_nodes) / 2
                           + (__add_at_front ? __nodes_to_add : 0);

            //若map不为空，拷贝原始map的内容，并释放空间
            if( map_size != 0){
                //拷贝原始map的内容
                cur_copy = start.node;
                cur_tar = new_nstart;
                for( ; cur_copy <= finish.node; cur_copy++, cur_tar++) {
                    construct(cur_tar, *cur_copy);
                    destroy(cur_copy);
                }

                //释放原始map空间
                map_allocator::deallocate(map, map_size);
            }

            //更新map的起始地址和大小
            map = new_map;
            map_size = new_map_size;
        }

        //更新迭代器start和finish
        //注意，setnode并不会更改iterator的cur！！
        start.set_node(new_nstart);
        finish.set_node(new_nstart + old_num_nodes - 1);
    }

}

#endif //TINYSTL_DEQUE_H
