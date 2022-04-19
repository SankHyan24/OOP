#include <frac.hpp>
using namespace std;
int main()
{
    // ctor
    fraction f1(-17, -34);
    cout << f1 << endl;
    fraction f2 = 0.125; // 对2的负次方和小数位数较低的数效果尤佳，因为构造使用了两种规约方法中的最优的一种
    cout << f2 << endl;
    fraction f3;

    // arithmetical operators and copy ctor
    f1 = f1 + f2;
    cout << f1 << endl;
    f2 += f2;
    cout << f2 << endl;
    f2 *= f2;
    cout << f2 << endl;
    f2 /= fraction(0.7);
    cout << f2 << endl;
    f3 = f1 + f2;
    cout << f3 << endl;

    // relational operators
    if (f2 == f2)
        cout << f2 << " equal to " << f2 << endl;
    if (f1 > f2)
        cout << f1 << " larger than " << f2 << endl;

    // type cast to double/stream and stream test
    if (double(f1) <= 1.245)
        cout << f1 << " no larger than 1.245" << endl;
    cout << "please input f3: ";
    cin >> f3;
    cout << string(f3) + " is the fraction you input" << endl;
}