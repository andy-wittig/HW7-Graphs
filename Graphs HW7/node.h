#ifndef NODE
#define NODE

template<class LabelType>
class Node {
	LabelType item;
	Node<LabelType>* next;
public:
	Node() : next(nullptr) {}
	Node(const LabelType& anItem) : item(anItem), next(nullptr) { }
	Node(const LabelType& anItem, Node<LabelType>* nextNodePtr) :
		item(anItem), next(nextNodePtr) { }

	void setItem(const LabelType& anItem) 
	{
		item = anItem;
	}

	void setNext(Node<LabelType>* nextNodePtr) 
	{
		next = nextNodePtr;
	}

	LabelType getItem() const 
	{
		return item;
	}

	Node<LabelType>* getNext() const 
	{
		return next;
	}
};
#endif