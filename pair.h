//
// Created by shanPic on 2018/3/27.
//

#ifndef TINYSTL_PAIR_H
#define TINYSTL_PAIR_H
namespace tinystl{
    template <class T1, class T2>
    struct pair {
        using firstType = T1;
        using secondType = T2;

        T1 first;
        T2 second;
        //以下是构造函数
        pair() : first(T1()), second(T2()) {}
        pair(const T1& a, const T2& b) : first(a), second(b) {}

    };

    //operator==操作符重载
    template <class T1, class T2>
    inline bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return x.first == y.first && x.second == y.second;
    }

    //operator<操作符重载
    //比较两个pair时,以第一个成员变量first为主,若第一个成员变量first不能判断表达式的大小
    //则对其第二个成员变量second进行比较
    template <class T1, class T2>
    inline bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
    }

    template <class T1, class T2>
    inline bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y) {
      return !(x == y);
    }

    template <class T1, class T2>
    inline bool operator>(const pair<T1, T2>& x, const pair<T1, T2>& y) {
      return y < x;
    }

    template <class T1, class T2>
    inline bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y) {
      return !(y < x);
    }

    template <class T1, class T2>
    inline bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y) {
      return !(x < y);
    }

    //根据两个数值，构造一个pair
    template <class T1, class T2>
    inline pair<T1, T2> make_pair(const T1& x, const T2& y)
    {
        return pair<T1, T2>(x, y);
    }
}
#endif //TINYSTL_PAIR_H
