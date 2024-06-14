#include "Set.h"

Set::Set() {
    m_size = 0;
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
        if (m_set[i] == value) {
            return false;
        }
    }

    // Check if the set is full
    if (m_size == DEFAULT_MAX_ITEMS) {
        return false;
    }

    m_set[m_size] = value;
    m_size++;

    return true;
}

bool Set::erase(const ItemType &value) {
    for (int i = 0; i < m_size; i++) {
        if (m_set[i] == value) {
            // Shift all elements after the erased element to the left
            for (int j = i; j < m_size - 1; j++) {
                m_set[j] = m_set[j + 1];
            }

            // Reduce the set's size by 1 and terminate the function
            m_size--;
            return true;
        }
    }

    return false;
}

bool Set::contains(const ItemType &value) const {
    for (int i = 0; i < m_size; i++) {
        if (m_set[i] == value) {
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
                if (m_set[j] < m_set[k]) {
                    count++;
                }
            }

            // If there are exactly i values less than the current item, set value to the current item
            // End program by returning true so that it doesn't set value to another item that's less than exactly i values
            if (count == i) {
                value = m_set[j];
                return true;
            }
        }
    }

    return false;
}

void Set::swap(Set &other) {
    // Swaps the sizes of the two sets
    int tempSetSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSetSize;

    // Swaps the contents of the two sets, but can't do so directly
    // Manually copies over all elements of each set into each other to swap them
    int largerSetSize = (m_size > other.m_size) ? m_size : other.m_size;

    for (int i = 0; i < largerSetSize; i++) {
        ItemType tempItem = m_set[i];
        m_set[i] = other.m_set[i];
        other.m_set[i] = tempItem;
    }
}