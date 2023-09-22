#include <iostream>

// Template class Test with two type parameters T1 and T2.
template<class T1, class T2>
class Test
{
public:
    // Constructor for the general case.
    Test() { std::cout << "Date<T1, T2>" << std::endl; }

private:
    T1 _num1;
    T2 _num2;
};

// Specialization for when both T1 and T2 are double.
template<>
class Test<double, double>
{
public:
    // Constructor for the specialization with double types.
    Test() : _num1(0.0), _num2(0.0) { std::cout << "Date<double, double>" << std::endl; }

private:
    double _num1;
    double _num2;
};

int main()
{   
    // Create an instance of Test<int, int>.
    Test<int, int> t;

    // Create an instance of Test<double, double>.
    Test<double, double> t1;

    // Wait for user input before exiting.
    std::cin.get();
}
