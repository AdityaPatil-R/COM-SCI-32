#ifndef SET_H
#define SET_H

#include <string>

using ItemType = std::string;

class Set {
    public:
        Set();
        bool empty() const;
        int size() const;
        bool insert(const ItemType& value);
        bool erase(const ItemType& value);
        bool contains(const ItemType& value) const;
        bool get(int pos, ItemType& value) const;
        void swap(Set& other);

        ~Set(); // Destructor
        Set(const Set& other); // Copy constructor
        Set& operator=(const Set& other); // Assignment operator

    private:
        // Doubly linked list nodes
        struct Node {
            Node* prev;
            ItemType m_item;
            Node* next;
        };

        int numItems;
        
        Node* head;
        Node* tail;
};

// Non-member functions
void unite(const Set& s1, const Set& s2, Set& result); 
void inOnlyOne(const Set& s1, const Set& s2, Set& result); 

#endif