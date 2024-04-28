#ifndef LINKED_STACK_
#define LINKED_STACK_
#include <iostream>
using namespace std;
#include "Node.h"

template <typename T>
class LinkedStack
{
private:
	Node<T>* frontPtr;
	int counter = 0;
public:
	LinkedStack() {
		frontPtr = nullptr;
	};
	bool isEmpty() const {
		return (frontPtr == nullptr);
	};
	bool Push(const T& newEntry) {
		Node<T>* newNodePtr = new Node<T>(newEntry);
		// Insert the new node
		if (isEmpty())	//special case if this is the first node to insert
			frontPtr = newNodePtr; // The Stack is empty
		else {
			newNodePtr->setNext(frontPtr); // The Stack was not empty
			frontPtr = newNodePtr;
		}
		this->counter++;
		return true;
	};
	T* Pop() {
		if (isEmpty())
			return NULL;

		Node<T>* nodeToDeletePtr = frontPtr;
		T* item = new T(frontPtr->getItem());
		frontPtr = frontPtr->getNext();
		// Stack is not empty; remove front


		// Free memory reserved for the deleted node
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
	void PrintStack() {
		if (isEmpty())
		{
			return;
		}
		T K;

		Node<T>* ptr;
		ptr = this->frontPtr;;
		cout << "[";
		while (ptr)
		{
			K = ptr->getItem();
			cout << K << ", ";
			ptr = ptr->getNext();
		}
		cout << "]" << endl;

	};
	int getCounter() { return counter; };
	bool Print(T& frntEntry) {
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();

		return true;
	};
	Node<T>* getFrnt() { return frontPtr; }
	~LinkedStack() {

		while (Pop());

	};
};
#endif