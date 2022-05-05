#include <frac.hpp>
using namespace std;
int main()
{
     // Step 1: TEST the Constructor
     // ctor testing
     cout << "TEST the constructor: " << endl;
     fraction f0; // TEST the default constructor
     cout << "f0 =  : " << f0.to_string() << endl
          << "   expect: 0/1" << endl;
     fraction f1(-17, -34); // TEST the constructor with numerator and denominator
     cout << "f1 is : " << f1 << endl
          << "   expect: 1/2" << endl;
     fraction f2 = 8 / 19.0; // TEST the constructor with double
     cout << "f2 is : " << f2 << endl
          << "   expect: 8/19" << endl;
     fraction f3;

     // Step 2: TEST the Arithmetical Operators
     // arithmetical operators and copy ctor
     cout << endl
          << "TEST the Arithmetical Operators" << endl;
     f1 = f1 + f2; // TEST the += operator
     cout << "f1 is : " << f1 << endl
          << "   expect: 35/38" << endl;
     f2 += f2; // TEST the += operator
     cout << "f2 is : " << f2 << endl
          << "   expect: 16/19" << endl;
     f2 *= f2; // TEST the *= operator
     cout << "f2 is : " << f2 << endl
          << "   expect: 256/361" << endl;
     f2 /= fraction(8 / 19.0); // TEST the /= operator
     cout << "f2 is : " << f2 << endl
          << "   expect: 32/19" << endl;
     f3 = f1 + f2; // TEST the copy ctor
     cout << "f3 is : " << f3 << endl
          << "   expect: 99/38" << endl;

     // Step 3: TEST the Relational Operators
     // relational operators testing
     cout << endl
          << "TEST the Relational Operators" << endl;
     if (f2 == f2) // test the == operator
          cout
              << f2 << " equal to " << f2 << endl;
     if (f1 > f2) // test the > operator
          cout << f1 << " larger than " << f2 << endl;
     if (double(f1) <= 1.245) // test the <= operator and double cast
          cout << f1 << " no larger than 1.245" << endl;

     // Step 4: TEST the Cast Operators and Stream Operators
     // type cast to double/stream and stream test
     cout << endl
          << "TEST the Cast Operators and Stream Operators by yourself" << endl;
     cout << "please input f3 (as the format of: $numerator $denominator)" << endl;
     cin >> f3; // TEST the cin operator
     cout << f3 << endl;
     double d; // test the double->fraction casting
     cout << "please input a double number: " << endl;
     cin >> d;
     fraction f4 = d;
     cout << "This number is casting to: " << f4 << endl;

     // Step 5: TEST the conversion from a string
     // string conversion testing
     cout << endl
          << "TEST the conversion from a string" << endl;
     string s = "1.414";
     fraction f5 = s;
     cout << "This string is casting to: " << f5 << endl
          << "   expect: 707/500" << endl;
}