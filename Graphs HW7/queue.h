#ifndef QUEUE_INTERFACE 
#define QUEUE_INTERFACE 

template<class LabelType>
class QueueInterface {
public:
    virtual bool isEmpty() const = 0;
    virtual bool enqueue(const LabelType& newEntry) = 0;
    virtual bool dequeue() = 0;
    virtual LabelType peekFront() const = 0;

    virtual ~QueueInterface() { }
};
#endif