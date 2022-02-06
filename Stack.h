#pragma once
template <typename Object>
class Stack
{
public:
    bool isEmpty() const
    {
        return theList.empty();
    }
    const Object& top() const
    {
        return theList.back();
    }
    void push(const Object& x)
    {
        theList.push_back(x);
    }
    Object& pop()
    {
        Object x = theList.back();

        theList.pop_back();
        return x;
    }
private:
    List<Object> theList;
};