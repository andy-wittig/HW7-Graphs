#ifndef ARRAY_QUEUE
#define ARRAY_QUEUE

#include "queue.h"

template<class ItemType>
class ArrayQueue : public QueueInterface<ItemType>
{
private:
    //index values to track front and back of queue
    int front;
    int back;
    int count;
    static const int ARRAY_SIZE = 100;
    ItemType array_queue[ARRAY_SIZE];
public:
    ArrayQueue() : back(-1), front(0), count(0) { }

    bool isEmpty() const
    {
        bool empty(count <= 0);
        return empty;
    }

    bool enqueue(const ItemType& newEntry)
    {
        if (count >= ARRAY_SIZE) { return false; } //array at capacity

        count++;
        back = (back + 1) % ARRAY_SIZE;
        array_queue[back] = newEntry;
        return true;
    }

    bool dequeue()
    {
        bool canDequeue = !isEmpty();
        if (canDequeue)
        {
            count--;
            front = (front + 1) % ARRAY_SIZE;
            return true;
        }
        else { return false; }
    }

    ItemType peekFront() const
    {
        bool canPeek = !isEmpty();
        if (canPeek)
        {
            return array_queue[front];
        }
        else { throw "Item not found!"; }
    }

    void displayQueue()
    {
        cout << "Array Queue:" << endl;
        for (int i = 0; i < count; i++)
        {
            cout << array_queue[(front + i) % ARRAY_SIZE].getTime()
                << ", type:" << array_queue[(front + i) % ARRAY_SIZE].getType() << endl;
        }
    }

    ~ArrayQueue() { }
};

#endif
