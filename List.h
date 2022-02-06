#ifndef LIST_H
#define LIST_H

#include <algorithm>
using namespace std;

template <typename Object>
class List
{
private:
    // The basic doubly linked list node.
    // Nested inside of List, can be public
    // because the Node is itself private
    struct Node
    {
        Object  data;
        Node* prev;
        Node* next;

        Node(const Object& d = Object{ }, Node* p = nullptr, Node* n = nullptr)
            : data{ d }, prev{ p }, next{ n } { }

        Node(Object&& d, Node* p = nullptr, Node* n = nullptr)
            : data{ std::move(d) }, prev{ p }, next{ n } { }
    };

public:
    class const_iterator
    {
    public:

        // Public constructor for const_iterator.
        const_iterator() : current{ nullptr }
        { }

        // Return the object stored at the current position.
        // For const_iterator, this is an accessor with a
        // const reference return type.
        const Object& operator* () const
        {
            return retrieve();
        }

        const_iterator& operator++ ()
        {
            current = current->next;
            return *this;
        }

        const_iterator operator++ (int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        const_iterator& operator-- ()
        {
            current = current->prev;
            return *this;
        }

        const_iterator operator-- (int)
        {
            const_iterator old = *this;
            --(*this);
            return old;
        }

        bool operator== (const const_iterator& rhs) const
        {
            return current == rhs.current;
        }

        bool operator!= (const const_iterator& rhs) const
        {
            return !(*this == rhs);
        }

    protected:
        Node* current;

        // Protected helper in const_iterator that returns the object
        // stored at the current position. Can be called by all
        // three versions of operator* without any type conversions.
        Object& retrieve() const
        {
            return current->data;
        }

        // Protected constructor for const_iterator.
        // Expects a pointer that represents the current position.
        const_iterator(Node* p) : current{ p }
        { }

        friend class List<Object>;
    };

    class iterator : public const_iterator
    {
    public:

        // Public constructor for iterator.
        // Calls the base-class constructor.
        // Must be provided because the private constructor
        // is written; otherwise zero-parameter constructor
        // would be disabled.
        iterator()
        { }

        Object& operator* ()
        {
            return const_iterator::retrieve();
        }

        // Return the object stored at the current position.
        // For iterator, there is an accessor with a
        // const reference return type and a mutator with
        // a reference return type. The accessor is shown first.
        const Object& operator* () const
        {
            return const_iterator::operator*();
        }

        iterator& operator++ ()
        {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++ (int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator& operator-- ()
        {
            this->current = this->current->prev;
            return *this;
        }

        iterator operator-- (int)
        {
            iterator old = *this;
            --(*this);
            return old;
        }

    protected:
        // Protected constructor for iterator.
        // Expects the current position.
        iterator(Node* p) : const_iterator{ p }
        { }

        friend class List<Object>;
    };

public:
    List()
    {
        init();
    }

    ~List()
    {
        clear();
        delete head;
        delete tail;
    }


    /*      ONLY TOUCH CODE AFTER THIS LINE      */

    // Return mutable iterator representing beginning of list.
    iterator begin()
    {
        Node* starter = head;
        starter++;
        return iterator(starter);
    }

    // Return constant iterator representing beginning of list.
    const_iterator begin() const
    {
        Node* starter = head;
        starter++;
        return const_iterator(starter++);
    }

    // Return iterator representing endmarker of list.
    // Mutator version is first, then accessor version.
    iterator end()
    {
        Node* ender = tail;
        ender--;
        return iterator(ender);
    }

    const_iterator end() const
    {
        Node* ender = tail;
        ender--;
        return const_iterator(ender);
    }

    // Return number of elements currently in the list.
    int size() const
    {
        Node* checker = head;
        int x = 0;
        checker = checker->next;
        while (checker != tail) {
            checker = checker -> next;
            x++;
        }
        
        return x;
    }

    // Return true if the list is empty, false otherwise.
    bool empty() const
    {
        Node* checker = head;
        checker = checker -> next;
        if (checker == tail) {
            return true;
        }
        return false;
    }

    // Removes all elements from the list
    void clear()
    {
        head->next = tail;
        tail->prev = head;
    }

    /* front, back, push_front, push_back, pop_front, and pop_back
       are the basic double-ended queue operations. */
    

    //Returns the value stored in the first element of the list
    const Object& front() const
    {
       
        Node* starter = head -> next;


        
        //note: these values need to be replaced, just here for compilation purposes
        return starter->data;
    }

    //Returns the value stored in the last element of the list
    const Object& back() const
    {
        Node* ender = tail->prev;

        return ender -> data;
    }

    //Inserts an object at the front of the list
    void push_front(const Object& x)
    {
        Node* second = head->next;
        Node* newnode = new Node(x, head, second);
        head->next = newnode;
        second->prev = newnode;

       
    }

    //Inserts an object at the back of the list
    void push_back(const Object& x)
    {
        Node* second = tail->prev;
        Node* newnode = new Node(x, second, tail);
        tail->prev = newnode;
        second->next = newnode;
    }

    //Removes the first element in the list
    void pop_front()
    {
        Node* waste = head-> next;
        Node* second = waste->next;
        head->next = second;
        second->prev = head;
        delete waste;
        

        
    }

    //Removes the last element in the list
    void pop_back()
    {
        Node* waste = tail->prev;
        Node* second = waste->prev;
        tail->prev = second;
        second->next = tail;
        delete waste;
    }

    // Insert x before itr.
    iterator insert(iterator itr, const Object& x)
    {

        iterator previous = itr--;
        Node* newnode = new Node(x, previous.current, itr.current);
        previous.current->next = newnode;
        itr.curent->prev = newnode;

        

        //need to update the return value, just itr so it will compile
        return newnode;
    }

    // Erase item at itr.
    iterator remove(iterator itr)
    {
        iterator checker = itr;
        iterator nextup = checker++;
        iterator previ = checker--;
        
        nextup.current->previ = previ.current;
        previ.current->next = nextup.current;

        delete checker.current;
        //need to update the return value, just itr so it will compile
        return nextup;
    }

    // Return the index of the node containing the matching value
    // Return -1 if no matching value
    int find(const Object& x)
    {
        Node* checker = head->next;
        int y = 0;
        while (checker != tail) {
            if (checker->data == x) {
                return y;
            }
            y++;
            checker = checker->next;
        }
        return -1;
    }

private:
     Node* head;
     Node* tail;

    

    void init()
    {
        head = new Node;
        tail = new Node;

        head->next = tail;
        tail->prev = head;
        

    }
};

#endif
