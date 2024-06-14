#include "Set.h"

Set::Set() {
    // Head and tail don't point to anything yet
    numItems = 0;
    head = nullptr;
    tail = nullptr;
}

bool Set::empty() const {
    return (numItems == 0);
}

int Set::size() const {
    return numItems;
}

bool Set::insert(const ItemType& value) {
    if (contains(value)) {
        return false;
    }

    Node* newNode = new Node;
    newNode->m_item = value;

    if (numItems == 0) {
        // Only one node in the set
        newNode->prev = nullptr;
        newNode->next = nullptr;

        head = newNode;
        tail = newNode;
    } else if (value > head->m_item) {
        // Inserting the new node at the front
        newNode->prev = nullptr;
        newNode->next = head;

        head->prev = newNode;
        head = newNode;
    } else if (value < tail->m_item) {
        // Inserting the new node at the end
        newNode->prev = tail;
        newNode->next = nullptr;

        tail->next = newNode;
        tail = newNode;
    } else {
        // Inserting the new node somewhere in the middle
        Node* p = head;

        while (value < p->next->m_item) {
            p = p->next;
        }

        newNode->next = p->next;
        newNode->prev = p;

        p->next->prev = newNode;
        p->next = newNode;
    }

    numItems++;

    return true;
}

bool Set::erase(const ItemType& value) {
    if (!contains(value)) {
        return false;
    }

    Node* p = head;

    while (p != nullptr) {
        if (p->m_item == value) {
            if (p == head) {
                // Reassigns head
                Node* temp = head;
                head = head->next;

                head->prev = nullptr;
                temp->next = nullptr;

                delete temp;
            } else if (p == tail) {
                // Reassigns tail
                Node* temp = tail;
                tail = tail->prev;

                tail->next = nullptr;
                temp->prev = nullptr;

                delete temp;
            } else {
                // Connects surrounding nodes
                p->prev->next = p->next;
                p->next->prev = p->prev;

                // Disconnects node to be deleted and deletes it
                p->prev = nullptr;
                p->next = nullptr;

                delete p;
            }

            numItems--;

            return true;
        }

        p = p->next;
    }

    return false;
}

bool Set::contains(const ItemType& value) const {
    if (numItems == 0) {
        return false; 
    }

    Node* p = head;

    // Iterate until value is found
    while (p != nullptr) {
        if (p->m_item == value) {
            return true;
        }

        p = p->next;
    }

    return false;
}

bool Set::get(int pos, ItemType& value) const {
    if (pos >= 0 && pos < numItems) {
        Node* p = head;

        for (int i = 0; i < pos; i++) {
            p = p->next;
        }

        value = p->m_item;

        return true;
    }

    return false;
}

void Set::swap(Set& other) {
    // Swap sizes
    int tempItems = other.numItems;
    other.numItems = numItems;
    numItems = tempItems;

    // Swap head and tail pointers
    Node* tempHead = other.head;
    other.head = head;
    head = tempHead;

    Node* tempTail = other.tail;
    other.tail = tail;
    tail = tempTail;
}

Set::~Set() {
    Node* p = head;

    while (p != nullptr) {
        Node* temp = p;
        p = p->next;
        delete temp;
    }
}

Set::Set(const Set& other) {
    numItems = other.numItems;

    if (other.numItems == 0) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = new Node;
        head->prev = nullptr;
        
        Node* member = head;

        // Iterates through the other set and copies the values
        for (Node* current = other.head; current->next != nullptr; current = current->next) {
            Node* newNode = new Node;

            member->m_item = current->m_item;
            member->next = newNode;
            newNode->prev = member;
            member = newNode;
        }

        member->m_item = other.tail->m_item;
        member->next = nullptr;
        tail = member;
    }
}

Set& Set::operator=(const Set& other) {
    if (this != &other) {
        Set tempSet(other);
        swap(tempSet);
    }

    return *this;
}

void unite(const Set& s1, const Set& s2, Set& result) {
    Set tempSet = Set();

    // Insert automatically checks for duplicates
    for (int i = 0; i < s1.size(); ++i) {
        ItemType value;
        s1.get(i, value);
        tempSet.insert(value);
    }

    for (int i = 0; i < s2.size(); ++i) {
        ItemType value;
        s2.get(i, value);
        tempSet.insert(value);
    }

    result = tempSet;
}

void inOnlyOne(const Set& s1, const Set& s2, Set& result) {
    Set tempSet = Set();

    // Only adds values to tempSet if it is in s1 or s2, but not both
    for (int i = 0; i < s1.size(); ++i) {
        ItemType value;
        s1.get(i, value);

        if (!s2.contains(value)) {
            tempSet.insert(value);
        }
    }

    for (int i = 0; i < s2.size(); ++i) {
        ItemType value;
        s2.get(i, value);

        if (!s1.contains(value)) {
            tempSet.insert(value);
        }
    }

    result = tempSet;
}