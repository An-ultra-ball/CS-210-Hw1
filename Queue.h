#pragma once
template <typename Object>
class Queue
{
public:
    bool isEmpty() const
    {
        return theList.empty();
    }
    const Object& getFront() const
    {
        return theList.front();

    }
    void enqueue(const Object& x)
    {
        theList.push_back(x);
    }
    Object& dequeue()
    {
        Object y = theList.front();

        theList.pop_front();
;

        return y;
    }
private:
    List<Object> theList;
};
