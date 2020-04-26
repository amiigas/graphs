//
// Created by Aleksy on 2020-04-08.
//

#ifndef GRAPHS_LIST_H
#define GRAPHS_LIST_H

#include <iostream>

template<class T>
class List;

template<class T>
class ListNode;

template<class T>
class Iterator {
private:

    ListNode<T>* node;

    friend class List<T>;

public:

    Iterator()
            : node(nullptr)
    {}
    explicit Iterator(ListNode<T>* node)
            : node(node)
    {}
    Iterator(Iterator<T>& it)
            : node(it.node)
    {}

    ListNode<T>* getNode() const;
    ListNode<T>& operator * () const;
    ListNode<T>* operator -> () const;
    bool         operator == (Iterator x) const;
    bool         operator != (Iterator x) const;
    bool         operator == (ListNode<T>* x) const;
    bool         operator != (ListNode<T>* x) const;
    Iterator<T>& operator ++ (int i);
    Iterator<T>& operator -- (int i);
    Iterator<T>& operator ++ ();
    Iterator<T>& operator -- ();
    Iterator<T>& operator + (int i);
    Iterator<T>& operator - (int i);


};

template<class T>
class ListNode {
private:

    T            element;
    ListNode<T>* prev;
    ListNode<T>* next;

    friend class List<T>;
    friend class Iterator<T>;

public:

    explicit ListNode(T element)
            : element(element), prev(nullptr), next(nullptr)
    {}
    ~ListNode();

    T            getElement() const;
    void         setElement(T element);
    ListNode<T>* getPrev() const;
    ListNode<T>* getNext() const;

};

template<class T>
class List {
private:

    ListNode<T>* head;
    ListNode<T>* tail;
    int          size;

public:

    List()
            : head(nullptr), tail(nullptr), size(0)
    {}
    ~List();

    Iterator<T> begin() const;      //returns iterator to head element
    Iterator<T> end() const;        //returns iterator to tail element

    T&   operator [] (int position) const;
    T&   at(int position) const;      //returns reference to element at "position"
    T&   front() const;               //returns reference to first element
    T&   back() const;                //returns reference to last element

    T&   find(T search) const;        //returns reference to element if found
    bool consists(T search) const;  //returns true if list consists search
    bool isEmpty() const;           //returns true if empty, false otherwise
    int  getSize() const;            //returns list's size

    T*   insert(T element, int position);
    void erase(int position);       //deletes element at "position"

    T*   push_front(T element);     //adds element at front
    T*   push_back(T element);      //adds element in the back
    void pop_front();               //deletes front node
    void pop_back();                //deletes back node

};

template<class T>
std::ostream& operator << (std::ostream& stream, const List<T> &list) {
    if(!list.isEmpty()) {
        Iterator<T> it = list.end();
        while (it != nullptr) {
            stream << it->getElement() << " ";
            it++;
        }
    }
    return stream;
}

// ------------- LIST ------------- //

template<class T>
List<T>::~List() {
    while (head != nullptr) {
        auto p = head;
        head = head->prev;
        delete p;
    }
}

template<class T>
Iterator<T> List<T>::begin() const {
    return Iterator<T>(head);
}

template<class T>
Iterator<T> List<T>::end() const {
    return Iterator<T>(tail);
}

template<class T>
T& List<T>::operator [] (int position) const {

    if (position >= size) {
        std::cerr << "subscript: position outside range" << std::endl;
    } else {
        if (position == size - 1) {
            return front();
        }

        if (position == 0) {
            return back();
        }

        Iterator<T> it(tail);
        it + position;
        return it.node->element;
    }
}

template<class T>
T& List<T>::at(int position) const {

    if (position >= size || position < 0) {
        std::cerr << "at: position outside range" << std::endl;
    } else {
        if (position == size - 1) {
            return front();
        }

        if (position == 0) {
            return back();
        }

        Iterator<T> it(tail);
        it + position;
        return it.node->element;
    }
}

template<class T>
T& List<T>::front() const {
    if (head != nullptr) {
        return head->element;
    } else {
        std::cerr << "front: no elements" << std::endl;
    }
}

template<class T>
T& List<T>::back() const {
    if (tail != nullptr) {
        return tail->element;
    } else {
        std::cerr << "back: no elements" << std::endl;
    }
}

template<class T>
T& List<T>::find(T search) const {

    if(!isEmpty()) {
        Iterator<T> it = end();
        while (it != nullptr) {
            if (it->getElement() == search) {
                return it->element;
            }
            it++;
        }
    }
    std::cerr << "find: not found" << std::endl;
}

template<class T>
bool List<T>::consists(T search) const {

    if(!isEmpty()) {
        Iterator<T> it = end();
        while (it != nullptr) {
            if (it->getElement() == search) {
                return true;
            }
            it++;
        }
    }
    return false;
}

template<class T>
bool List<T>::isEmpty() const {
    return (head == nullptr);
}

template<class T>
int List<T>::getSize() const {
    return size;
}

template<class T>
T* List<T>::insert(T element, int position) {

    if (position > size || position < 0) {
        std::cerr << "insert: position outside range" << std::endl;
        return nullptr;
    }

    if (position == size) {
        this->push_front(element);
        return nullptr;
    }

    if (position == 0) {
        this->push_back(element);
        return nullptr;
    }

    auto *p = new ListNode<T>(element);
    Iterator<T> inplace(end());
    inplace+position;

    p->prev = inplace->prev;
    inplace->prev->next = p;
    inplace->prev = p;
    p->next = inplace.node;

    size++;

    return &at(position);
}

template<class T>
void List<T>::erase(int position) {

    if (position >= size || position < 0) {
        std::cerr << "erase: position outside range" << std::endl;
        return;
    }

    if (position == size-1) {
        this->pop_front();
        return;
    }

    if (position == 0) {
        this->pop_back();
        return;
    }

    Iterator<T> it(tail);
    it+position;
    it->prev->next = it->next;
    it->next->prev = it->prev;
    delete it.node;
    size--;
}

template<class T>
T* List<T>::push_front(T element) {

    auto *p = new ListNode<T>(element);

    if (this->isEmpty()) {
        tail = p;
        head = p;
    } else {
        p->prev = head;
        head->next = p;
        head = p;
    }
    size++;

    return &front();
}

template<class T>
T* List<T>::push_back(T element) {

    auto *p = new ListNode<T>(element);

    if (this->isEmpty()) {
        tail = p;
        head = p;
    } else {
        p->next = tail;
        tail->prev = p;
        tail = p;
    }
    size++;

    return &back();
}

template<class T>
void List<T>::pop_front() {
    head = head->prev;
    delete head->next;
    head->next = nullptr;
    size--;
}

template<class T>
void List<T>::pop_back() {
    tail = tail->next;
    delete tail->prev;
    tail->prev = nullptr;
    size--;
}

// ------------- LIST NODE ------------- //

template<class T>
ListNode<T>::~ListNode() {

}

template<class T>
T ListNode<T>::getElement() const {
    return element;
}

template<class T>
void ListNode<T>::setElement(T elem) {
    element = elem;
}

template<class T>
ListNode<T>* ListNode<T>::getPrev() const {
    return prev;
}

template<class T>
ListNode<T>* ListNode<T>::getNext() const {
    return next;
}

// ------------- ITERATOR ------------- //

template<class T>
ListNode<T>* Iterator<T>::getNode() const {
    return node;
}

template<class T>
ListNode<T>& Iterator<T>::operator * () const {
    return *node;
}

template<class T>
ListNode<T>* Iterator<T>::operator -> () const {
    return node;
}

template<class T>
bool Iterator<T>::operator == (Iterator x) const {
    return node == x.node;
}

template<class T>
bool Iterator<T>::operator != (Iterator x) const {
    return node != x.node;
}

template<class T>
bool Iterator<T>::operator == (ListNode<T>* x) const {
    return node == x;
}

template<class T>
bool Iterator<T>::operator != (ListNode<T>* x) const {
    return node != x;
}

template<class T>
Iterator<T>& Iterator<T>::operator ++ (int) {
    node = node->next;
    return *this;
}

template<class T>
Iterator<T>& Iterator<T>::operator -- (int) {
    node = node->prev;
    return *this;
}

template<class T>
Iterator<T>& Iterator<T>::operator ++ () {
    node = node->next;
    return *this;
}

template<class T>
Iterator<T>& Iterator<T>::operator -- () {
    node = node->prev;
    return *this;
}

template<class T>
Iterator<T>& Iterator<T>::operator + (int i) {
    for (int j = 0 ; j < i ; j++ ) {
        (*this)++;
    }
    return *this;
}

template<class T>
Iterator<T>& Iterator<T>::operator - (int i) {
    for (int j = 0 ; j < i ; j++ ) {
        (*this)--;
    }
    return *this;
}



#endif


