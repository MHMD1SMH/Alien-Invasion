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
	DoubleQueue() {
		backPtr = nullptr;
		frontPtr = nullptr;

	};
	DoubleNode<T>* getFrnt() { return frontPtr; }
	bool isEmpty() const {
		return (frontPtr == nullptr);
	};
	bool enqueue(const T& newEntry) {

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
	};
	T* dequeueFront() {
		if (isEmpty())
			return NULL;

		DoubleNode<T>* nodeToDeletePtr = frontPtr;
		T* item = new T(frontPtr->getItem());
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
	};
	T* dequeueBack() {
		if (isEmpty())
			return NULL;

		DoubleNode<T>* nodeToDeletePtr = backPtr;
		T* item = new T(backPtr->getItem());
		backPtr = backPtr->getprev();
		if (backPtr)
		{
			backPtr->setNext(NULL);
		}
		// Queue is not empty; remove Back
		if (nodeToDeletePtr == frontPtr)	 // Special case: first node in the queue
			frontPtr = nullptr;

		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;
		this->counter--;
		return item;
	};
	bool peek(T& frntEntry)  const {
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
		return true;

	};
	void PrintQueue() {
		if (isEmpty())
		{
			return;
		}
		T K;
		DoubleNode<T>* ptr;
		ptr = this->getFrnt();
		cout << "[";
		while (ptr)
		{
			K = ptr->getItem();
			cout << K << ", ";
			ptr = ptr->getNext();
		}
		cout << "]" << endl;
	};
	int getCounter() { return counter; }
	~DoubleQueue() {

		while (dequeueFront());

	};
};
