#include <cstddef>
#include <typeinfo>
#include <iostream>
#include <vector>
#include <cxxabi.h> // 所需头文件

char *abi::__cxa_demangle(const char *mangled_name, char *output_buffer, size_t *length, int *status);

using namespace std;
struct S
{
    float a;
    int b;
    const char *c;
    string d;
};

struct Member
{
    // const char *name;
    string name;
    const type_info &type;
    size_t offset;
};

template <class T, class M>
M member_type(M T::*) {}

#define MEMBER(T, M)                                   \
    {                                                  \
#M, typeid(member_type(&T::M)), offsetof(T, M) \
    }

template <class T>
const vector<Member> &get_members();

template <>
const vector<Member> &get_members<S>()
{
    static const vector<Member> members{
        MEMBER(S, a),
        MEMBER(S, b),
        MEMBER(S, c),
        MEMBER(S, d)};
    return members;
}

template <class M, class T>
M &get_member_by_index(T &a, size_t index)
{
    return *reinterpret_cast<M *>(reinterpret_cast<char *>(&a) + get_members<T>()[index].offset);
}

int main()
{
    for (auto &m : get_members<S>())
        cout << m.name << " " << abi::__cxa_demangle(m.type.name(), nullptr, nullptr, nullptr) << " " << m.offset << endl;

    S s{1.0f, 2, "hello"};
    cout << get_member_by_index<float>(s, 0) << endl;
    cout << get_member_by_index<int>(s, 1) << endl;
    cout << get_member_by_index<const char *>(s, 2) << endl;

    get_member_by_index<float>(s, 0) = 3.0f;
    cout << s.a << endl;
}