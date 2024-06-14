#include <iostream>
#include <cassert>
#include "Set.h" // Assuming you have a Set class defined

int main() {
    Set ss;
    ss.insert(123456);
    ss.insert(789012);
    ss.insert(345678);
    ss.insert(901234);
    ss.insert(789012);
    ss.insert(567890);
    ss.insert(901234);
    assert(ss.size() == 5);  // Duplicate numbers were not added

    unsigned long x;
    ss.get(0, x);
    assert(x == 901234);  // 901234 is less than exactly 0 items in ss

    ss.get(4, x);
    assert(x == 123456);  // 123456 is less than exactly 4 items in ss

    ss.get(2, x);
    assert(x == 567890);  // 567890 is less than exactly 2 items in ss

    Set ss1;
    ss1.insert(111111);
    Set ss2;
    ss2.insert(567890);
    ss2.insert(222222);
    ss1.swap(ss2);
    assert(ss1.size() == 2  &&  ss1.contains(567890)  &&  ss1.contains(222222)  &&
           ss2.size() == 1  &&  ss2.contains(111111));

    std::cout << "Passed all tests" << std::endl;

    return 0;
}