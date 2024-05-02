#ifndef NODE
#define NODE

template<class LabelType>
class Node {
	LabelType item; // A data item
	Node<LabelType>* next; // Points to next node
public:
	Node() : next(nullptr) {} // end default constructor
	Node(const LabelType& anItem) : item(anItem), next(nullptr) {} // end constructor
	Node(const LabelType& anItem, Node<LabelType>* nextNodePtr) :
		item(anItem), next(nextNodePtr) {} // end constructor

	void setItem(const LabelType& anItem) {
		item = anItem;
	} // end setItem

	void setNext(Node<LabelType>* nextNodePtr) {
		next = nextNodePtr;
	} // end setNext

	LabelType getItem() const {
		return item;
	} // end getItem

	Node<LabelType>* getNext() const {
		return next;
	} // end getNext
};
#endif