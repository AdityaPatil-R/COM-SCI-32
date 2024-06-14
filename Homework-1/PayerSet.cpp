#include "PayerSet.h"
#include <iostream>

using namespace std;

PayerSet::PayerSet() {
    m_set = Set();
}

bool PayerSet::add(ItemType accountNum) {
    return m_set.insert(accountNum);
}

int PayerSet::size() const {
    return m_set.size();
}

void PayerSet::print() const {
    for (int i = 0; i < m_set.size(); i++) {
        // Can't print items of a set directly
        // Have to use get() to set a temporary variable to them and then print that out
        ItemType tempValue;
        m_set.get(i, tempValue);
        cout << tempValue << endl;
    }
}