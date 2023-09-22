#include <iostream>

// Date class representing a date with year, month, and day.
class Date
{
public:
    // Constructor with default values for year, month, and day.
    Date(int year = 1900, int month = 1, int day = 1)
        : _year(year)
        , _month(month)
        , _day(day)
    {}

    // Less than operator for comparing two Date objects.
    bool operator<(const Date& d) const
    {
        // Compare year first, then month, and finally day.
        return (_year < d._year) ||
            (_year == d._year && _month < d._month) ||
            (_year == d._year && _month == d._month && _day < d._day);
    }

    // Greater than operator for comparing two Date objects.
    bool operator>(const Date& d) const
    {
        // Compare year first, then month, and finally day.
        return (_year > d._year) ||
            (_year == d._year && _month > d._month) ||
            (_year == d._year && _month == d._month && _day > d._day);
    }

    // Friend function for printing Date objects in the format "year-month-day".
    friend std::ostream& operator<<(std::ostream& _cout, const Date& d)
    {
        _cout << d._year << "-" << d._month << "-" << d._day;
        return _cout;
    }

private:
    int _year;
    int _month;
    int _day;
};

// Template function to compare two objects of any type using the less than operator.
template<typename T>
bool less(T left, T right) {
    return left < right;
}

// Specialization for comparing Date pointers (Date*)
template<>
bool less<Date*>(Date* left, Date* right)
{
    // Dereference the pointers and compare the underlying Date objects.
    return *left < *right;
}

// Also true
//bool less(Date* left, Date* right)
//{
//    return *left < *right;
//}


//int main()
//{
//    // Compare two integers.
//    std::cout << less(1, 2) << std::endl;   // Can compare, result is correct
//
//    // Create two Date objects and compare them.
//    Date d1(2022, 7, 7);
//    Date d2(2022, 7, 8);
//    std::cout << less(d1, d2) << std::endl;  // Can compare, result is correct
//
//    // Create Date pointers and attempt to compare them (requires template specialization).
//    Date* p1 = &d1;
//    Date* p2 = &d2;
//    std::cout << less(p1, p2) << std::endl;  // Can compare, result is incorrect (requires template specialization)
//
//    return 0;
//}
