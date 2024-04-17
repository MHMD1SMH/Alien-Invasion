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
	LinkedQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	T* dequeue();
	bool peek(T& frntEntry)  const;
	void PrintQueue();
	Node<T>* getFrnt() { return frontPtr; }
	int getCounter() { return counter; }
	~LinkedQueue();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
	
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr=backPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	counter++;
	return true;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
T* LinkedQueue<T>::dequeue()
{
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

	return item;
}




/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/

template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
template<typename T>
 void LinkedQueue<T>::PrintQueue()
{
	 T K;
	 cout << "\nQueue contents: ";
	 while (this->dequeue())
		 cout << K << " ";
	 cout << endl;
}
///////////////////////////////////////////////////////////////////////////////////


template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	
	//T temp;
	while (dequeue());

}

#endif