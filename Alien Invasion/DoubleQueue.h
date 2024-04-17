#pragma once

#include <iostream>
using namespace std;
#include "DoubleNode.h"

template <typename T>
class DoubleQueue
{
private:
	DoubleNode<T>* backPtr;
	DoubleNode<T>* frontPtr;
	int counter=0;
public:
	DoubleQueue();
	DoubleNode<T>* getFrnt() { return frontPtr; }
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	T* dequeueFront();
	T* dequeueBack();
	bool peek(T& frntEntry)  const;
	void PrintQueue();
	int getCounter() { return counter; }
	~DoubleQueue();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
DoubleQueue<T>::DoubleQueue()
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
bool DoubleQueue<T>::isEmpty() const
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
bool DoubleQueue<T>::enqueue(const T& newEntry)
{
	DoubleNode<T>* newNodePtr = new DoubleNode<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
	{
		newNodePtr->setprev(backPtr);
		backPtr->setNext(newNodePtr); // The queue was not empty
	}

	backPtr = newNodePtr; // New node is the last node now
	this->counter++;
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
T* DoubleQueue<T>::dequeueFront()
{
	if (isEmpty())
		return NULL;

	DoubleNode<T>* nodeToDeletePtr = frontPtr;
	T* item = new T(backPtr->getItem());
	frontPtr = frontPtr->getNext();
	if (frontPtr)
	{
		frontPtr->setprev(NULL);
	}

	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	this->counter--;
	return item;
}

template <typename T>
T* DoubleQueue<T>::dequeueBack()
{
	if (isEmpty())
		return NULL;

	DoubleNode<T>* nodeToDeletePtr = backPtr;
	T* item = new T(backPtr->getItem());
	backPtr = backPtr->getprev();
	backPtr->setNext(NULL);
	// Queue is not empty; remove Back
	if (nodeToDeletePtr == frontPtr)	 // Special case: first node in the queue
		frontPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	this->counter--;
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
bool DoubleQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
template<typename T>
void DoubleQueue<T>::PrintQueue()
{
	T* K;
	cout << "\nQueue contents: ";
	while (K=this->dequeueFront())
		cout << K << " ";
	cout << endl;
}
///////////////////////////////////////////////////////////////////////////////////


template <typename T>
DoubleQueue<T>::~DoubleQueue()
{

	while (dequeueFront());

}
