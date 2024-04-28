#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

#include <iostream>
using namespace std;
#include "Node.h"

template <typename T>
class LinkedQueue
{
protected:
	Node<T>* backPtr;
	Node<T>* frontPtr;
	int counter = 0;
public:
	LinkedQueue() {
		backPtr = nullptr;
		frontPtr = nullptr;

	};
	bool isEmpty() const {
		return (frontPtr == nullptr);
	};
	bool enqueue(const T& newEntry) {

		Node<T>* newNodePtr = new Node<T>(newEntry);
		// Insert the new node
		if (isEmpty())	//special case if this is the first node to insert
			frontPtr = backPtr = newNodePtr; // The queue is empty
		else
			backPtr->setNext(newNodePtr); // The queue was not empty

		backPtr = newNodePtr; // New node is the last node now
		counter++;
		return true;
	};
	T* dequeue() {
		if (isEmpty())
			return NULL;

		Node<T>* nodeToDeletePtr = frontPtr;
		frontPtr = frontPtr->getNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
			backPtr = nullptr;
		T* item = new T(nodeToDeletePtr->getItem());
		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;
		counter--;
		return item;
	};
	bool peek(T& frntEntry)  const {
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
		return true;

	};
	void PrintQueue() {
		if (this->isEmpty())
		{
			return;
		}
		T K;

		Node<T>* ptr;
		ptr = this->frontPtr;
		cout << "[";
		while (ptr)
		{
			K = ptr->getItem();
			cout << K << ", ";
			ptr = ptr->getNext();
		}
		cout << "]" << endl;
	};
	Node<T>* getFrnt() { return frontPtr; }
	int getCounter() { return counter; }
	~LinkedQueue() {
		while (dequeue());

	};
};
#endif