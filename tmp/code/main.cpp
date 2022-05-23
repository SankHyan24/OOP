#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <list>
#include <vector>

template <class ForwardIt, class Compare>
ForwardIt min_elem(ForwardIt first, ForwardIt last, Compare comp)
{
    if (first == last)
        return first;

    ForwardIt smallest = first++;
    for (; first != last; ++first)
    {
        if (comp(*first, *smallest))
        {
            smallest = first;
        }
    }
    return smallest;
}

template <class ForwardIt>
ForwardIt min_elem(ForwardIt first, ForwardIt last)
{
    return min_elem(first, last, std::less<std::iterator_traits<ForwardIt>::pointer, std::iterator_traits<ForwardIt>::value_type>()); // TODO???????
}

struct Student
{
    int id;
    std::string name;
    bool operator<(const Student &s2) const
    {
        return id < s2.id;
    }
};

std::ostream &operator<<(std::ostream &out, const Student &s)
{
    out << s.name << s.id;
    return out;
}

int main()
{
    std::vector<int> v = {3, 1, 4, 2, 5, 9};
    std::cout << "min element is: " << *min_elem(std::begin(v), std::end(v)) << std::endl;

    std::list<double> l = {3.1, 1.2, 4.3, 2.4, 5.5, 9.7};
    std::cout << "min element is: " << *min_elem(std::begin(l), std::end(l), std::greater<double>()) << std::endl;
    Student s[] = {{30, "Curry"}, {23, "Lebron"}, {35, "Durant"}};
    std::cout << "min element is: " << *min_elem(std::begin(s), std::end(s)) << std::endl;
}