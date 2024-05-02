#ifndef LINKED_LIST
#define LINKED_LIST

#include "list.h"
#include "node.h"

template<class LabelType>
class LinkedList : public ListInterface<LabelType> {
	Node<LabelType>* headPtr;
	int itemCount; // Current count of list items

	Node<LabelType>* getNodeAt(int position) const {
		// enforce precondition
		if ((position >= 1) && (position <= itemCount)) {
			// Count from the beginning of the chain
			Node<LabelType>* curPtr = headPtr;
			for (int skip = 1; skip < position; skip++) {
				curPtr = curPtr->getNext();
			}
			return curPtr;
		}
		return nullptr;
	}
public:
	LinkedList() : headPtr(nullptr), itemCount(0) {}

	LinkedList(const LinkedList<LabelType>& aList) : headPtr(nullptr), itemCount(0) {
		Node<LabelType>* orgPtr = aList.headPtr;
		Node<LabelType>* curPtr = nullptr;
		if (orgPtr == nullptr)
		{
			headPtr = nullptr;
			itemCount = 0;
		}
		else
		{
			headPtr = new Node<LabelType>(orgPtr->getItem());
			curPtr = headPtr;
			orgPtr = orgPtr->getNext();
		}

		while (orgPtr != nullptr)
		{
			LabelType orgEntry = orgPtr->getItem();
			Node<LabelType>* newPtr = new Node<LabelType>(orgEntry);
			curPtr->setNext(newPtr);
			curPtr = curPtr->getNext();
			orgPtr = orgPtr->getNext();
		}
		itemCount = aList.itemCount;
	}

	bool isEmpty() const {
		return itemCount == 0;
	}

	int getLength() const {
		return itemCount;
	}

	bool insert(int newPosition, const LabelType& newEntry) {
		bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
		if (ableToInsert)
		{
			if (newPosition == 1)
			{
				if (headPtr == nullptr)
				{
					headPtr = new Node<LabelType>(newEntry);
				}
				else
				{
					Node<LabelType>* oldHead = headPtr;
					headPtr = new Node<LabelType>(newEntry);
					headPtr->setNext(oldHead);
				}
			}
			else
			{
				Node<LabelType>* newPtr = new Node<LabelType>(newEntry);
				Node<LabelType>* prevPtr = getNodeAt(newPosition - 1);
				Node<LabelType>* curPtr = getNodeAt(newPosition);

				prevPtr->setNext(newPtr);
				newPtr->setNext(curPtr);

			}
			itemCount++;
			return ableToInsert;
		}
	}

	bool remove(int position) {
		bool ableToRemove = (position >= 1) && (position <= itemCount);
		if (ableToRemove) {
			Node<LabelType>* ptrToDelete = nullptr;
			if (position == 1) {
				// Remove the first node in the chain
				ptrToDelete = headPtr; // Save pointer to node 
				headPtr = headPtr->getNext();// save pointer to next node
			}
			else {
				// Find node that is before the one to remove
				Node<LabelType>* prevPtr = getNodeAt(position - 1);
				// Point to node to remove
				ptrToDelete = prevPtr->getNext();
				// Disconnect indicated node from chain by connecting the prior node with the one after
				prevPtr->setNext(ptrToDelete->getNext());
			}

			ptrToDelete->setNext(nullptr);
			delete ptrToDelete;
			ptrToDelete = nullptr;
			itemCount--; // Decrease count of entries
		}
		return ableToRemove;
	}

	void clear() {
		Node<LabelType>* curPtr = headPtr;
		Node<LabelType>* nextPtr = nullptr;
		while (curPtr != nullptr)
		{
			nextPtr = curPtr->getNext();
			delete curPtr;
			curPtr = nextPtr;
		}
		headPtr = nullptr;
		itemCount = 0;
	}

	LabelType getEntry(int position) const {
		bool ableToGet = (position >= 1) && (position <= itemCount);
		if (ableToGet)
		{
			Node<LabelType>* nodePtr = getNodeAt(position);
			LabelType temp_item = nodePtr->getItem();
			return temp_item;
		}
		throw "Index out of range";
	}

	LabelType replace(int position, const LabelType& newEntry) {
		// enforce precondition
		bool ableToReplace = (position >= 1) && (position <= itemCount);
		if (ableToReplace) {
			Node<LabelType>* nodePtr = getNodeAt(position);
			LabelType oldEntry = nodePtr->getItem();
			nodePtr->setItem(newEntry);
			return oldEntry;
		}
		throw "Item not found";
	}

	~LinkedList() {
		clear();
	}
};
#endif
