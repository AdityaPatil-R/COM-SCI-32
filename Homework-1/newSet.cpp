#include "newSet.h"

Set::Set(int capacity) {
    // Exits the program for an invalid capacity
    if (capacity < 0) {
        std::exit(1);
    }

    m_size = 0;
    m_capacity = capacity;
    m_items = new ItemType[m_capacity];
}

Set::Set(const Set &other) {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_items = new ItemType[m_capacity];

    for (int i = 0; i < m_size; i++) {
        m_items[i] = other.m_items[i];
    }
}

Set::~Set() {
    delete[] m_items;
}

Set& Set::operator=(const Set &other) {
    // If they aren't already equal, set this set to the other set
    // Creates a temporary set to hold the other set, and then swaps them
    if (this != &other) {
        Set tempSet(other);
        this->swap(tempSet);
    }

    return *this;
}

bool Set::empty() const {
    return (m_size == 0);
}

int Set::size() const {
    return m_size;
}

bool Set::insert(const ItemType &value) {
    // Check if the value is already in the set
    for (int i = 0; i < m_size; i++) {
        if (m_items[i] == value) {
            return false;
        }
    }

    // Check if the set is at the default maximum items or at capacity
    if (m_size == DEFAULT_MAX_ITEMS || m_size >= m_capacity) {
        return false;
    }

    m_items[m_size] = value;
    m_size++;

    return true;
}

bool Set::erase(const ItemType &value) {
    for (int i = 0; i < m_size; i++) {
        if (m_items[i] == value) {
            // Uses assignment operator to shift all elements after the erased element to the left
            for (int j = i; j < m_size - 1; j++) {
                m_items[j] = m_items[j + 1];
            }

            m_size--;
            return true;
        }
    }

    return false;
}

bool Set::contains(const ItemType &value) const {
    for (int i = 0; i < m_size; i++) {
        if (m_items[i] == value) {
            return true;
        }
    }

    return false;
}

bool Set::get(int i, ItemType &value) const {
    //Initial conditions
    if (i >= 0 && i < m_size) {
        for (int j = 0; j < m_size; j++) {
            int count = 0;

            // Counts the number of items in the set less than the current item
            for (int k = 0; k < m_size; k++) {
                if (m_items[j] < m_items[k]) {
                    count++;
                }
            }

            // If there are exactly i values less than the current item, set value to the current item
            // End program by returning true so that it doesn't set value to another item less than exactly i values
            if (count == i) {
                value = m_items[j];
                return true;
            }
        }
    }

    return false;
}

void Set::swap(Set &other) {
    // Swap the sizes of the sets
    int tempSize = this->m_size;
    this->m_size = other.m_size;
    other.m_size = tempSize;

    // Swap the capacities of the sets
    int tempCapacity = this->m_capacity;
    this->m_capacity = other.m_capacity;
    other.m_capacity = tempCapacity;

    // Swap the pointers to the sets
    ItemType* tempItems = this->m_items;
    this->m_items = other.m_items;
    other.m_items = tempItems;
}