// 运行期以索引获取tuple元素
// 需支持C++11及以上标准的编译器，VS2017 15.5.x、CodeBlocks 16.01 gcc 7.2
// 参考《深入应用C++11:代码优化与工程级应用》p148，祁宇，机械工业出版社，2015年05
#include <tuple>
#include <iostream>
#include <vector>
#include <map>

template <typename Visit>
void VisitTuple(size_t index, std::tuple<> &t, Visit v) {}

template <typename T, typename... Ts, typename Visit>
void VisitTuple(size_t index, std::tuple<T, Ts...> &t, Visit v)
{
    if (index >= (1 + sizeof...(Ts)))
        throw std::invalid_argument("bad index");
    if (index > 0)
        VisitTuple(index - 1, reinterpret_cast<std::tuple<Ts...> &>(t), v);
    else
        v(std::get<0>(t));
}

// 测试代码
class Vistor
{
public:
    template <typename Arg>
    void operator()(Arg &&arg)
    {
        std::clog << arg << std::endl;
    }
};

int main(int argc, char *argv[])
{
    auto t = std::make_tuple(1, 2, 3, 4, "123");

    for (size_t i = 0; i < std::tuple_size<decltype(t)>::value; ++i)
    {
        VisitTuple(i, t, Vistor{});
    }
}