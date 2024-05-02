#ifndef LIST_INTERFACE 
#define LIST_INTERFACE 

template<class LabelType>
class ListInterface {
public:
	virtual bool isEmpty() const = 0;
	virtual int getLength() const = 0;
	virtual bool insert(int newPosition, const LabelType& newEntry) = 0;
	virtual bool remove(int position) = 0;
	virtual void clear() = 0;
	virtual LabelType getEntry(int position) const = 0;
	virtual LabelType replace(int position, const LabelType& newEntry) = 0;
	virtual ~ListInterface() { }
};
#endif